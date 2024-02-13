# define _GNU_SOURCE
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>

struct user {
    char username[50];
    char password[256];
    char firstname[50];
    char lastname[50];
    int admin; // An integer in [0 ,9]
};

char * cs336Hash(const char * password) {
    return crypt(password, "00");
}

struct user * createUsers(int * count) {
    FILE *file = fopen("credential_file", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    int lines = 0;
    char ch;
    while (!feof(file)) {
        ch = fgetc(file);
        if (ch == '\n') {
            lines++;
        }
    }
    *count = lines;

    rewind(file);

    struct user * users = (struct user *)malloc(lines * sizeof(struct user));
    if (users == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < lines; ++i) {
        fscanf(file, "%s %s %s %s %d",
               users[i].firstname, users[i].lastname,
               users[i].username, users[i].password, &users[i].admin);
    }

    fclose(file);
    return users;
}

int checkAdminPassword(char * password, struct user * users, int count) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(users[i].username, "admin") == 0) {
            if (strcmp(cs336Hash(password), users[i].password) == 0) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    return 0;
}

struct user * addUser(struct user * users, int * count, char * username, char * password,
                      char * firstname, char * lastname, int admin) {
    *count += 1;
    users = (struct user *)realloc(users, (*count) * sizeof(struct user));
    if (users == NULL) {
        fprintf(stderr, "Memory reallocation failed.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(users[*count - 1].username, username);
    strcpy(users[*count - 1].password, cs336Hash(password));
    strcpy(users[*count - 1].firstname, firstname);
    strcpy(users[*count - 1].lastname, lastname);
    users[*count - 1].admin = admin;

    return users;
}

void saveUsers(struct user * users, int count) {
    FILE *file = fopen("credential_file", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < count; ++i) {
        fprintf(file, "%s\t%s\t%s\t%s\t%d\n",
                users[i].firstname, users[i].lastname,
                users[i].username, users[i].password, users[i].admin);
    }

    fclose(file);
}

int main(void) {
    int user_count = 0;
    struct user * users = createUsers(&user_count);
    if (users == NULL) {
        return EXIT_FAILURE;
    }

    printf("Enter admin password to add new users:");
    char entered_admin_password[50];
    scanf("%s", entered_admin_password);

    if (checkAdminPassword(entered_admin_password, users, user_count)) {
        struct user new_user;
        printf("Enter username:");
        scanf("%s", new_user.username);
        printf("Enter first name:");
        scanf("%s", new_user.firstname);
        printf("Enter last name:");
        scanf("%s", new_user.lastname);
        printf("Enter password:");
        scanf("%s", new_user.password);
        printf("Enter admin level:");
        scanf("%d", &(new_user.admin));

        users = addUser(users, &user_count, new_user.username, new_user.password,
                        new_user.firstname, new_user.lastname, new_user.admin);

        if (users == NULL) {
            return EXIT_FAILURE;
        }
    }

    saveUsers(users, user_count);
    free(users);
    return EXIT_SUCCESS;
}

