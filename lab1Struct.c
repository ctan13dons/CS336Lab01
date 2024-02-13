#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct user {
    char username[50];
    char password[50];
    int admin;
};

struct user* createUsers(int max_number_of_users) {
    return (struct user*)malloc(max_number_of_users * sizeof(struct user));
}

void initUsers(void* users, int max_number_of_users) {
    struct user* userList = (struct user*)users;
    for (int i = 0; i < max_number_of_users; ++i) {
        strncpy((userList + i)->username, "default", sizeof((userList + i)->username) - 1);
        strncpy((userList + i)->password, "default", sizeof((userList + i)->password) - 1);
        (userList + i)->admin = 0;
    }
}

void addUser1(struct user* users, char* username, char* password, int admin, int* count) {
    strncpy((users + *count)->username, username, sizeof((users + *count)->username) - 1);
    strncpy((users + *count)->password, password, sizeof((users + *count)->password) - 1);
    (users + *count)->admin = admin;
    (*count)++;
}

void addUser2(struct user* users, struct user newUser, int* count) {
    strncpy((users + *count)->username, newUser.username, sizeof((users + *count)->username) - 1);
    strncpy((users + *count)->password, newUser.password, sizeof((users + *count)->password) - 1);
    (users + *count)->admin = newUser.admin;
    (*count)++;
}

void printUser(struct user* users, int number_of_users) {
    for (int i = 0; i < number_of_users; ++i) {
        printf("username%d : %s\n", i, (users + i)->username);
        printf("password%d : %s\n", i, (users + i)->password);
    }
}

int main(void) {
    struct user* users = createUsers(10);
    if (users == NULL) {
        return 0;
    }
    int userCount = 0;
    initUsers(users, 10);
    addUser1(users, "admin", "s#1Pa5", 1, &userCount);
    addUser1(users, "vahab", "fgH!12", 0, &userCount);
    struct user u1;
    u1.admin = 2;
    strncpy(u1.username, "usf", sizeof(u1.username) - 1);
    strncpy(u1.password, "gA24?m", sizeof(u1.password) - 1);
    addUser2(users, u1, &userCount);
    printUser(users, userCount);
    free(users);
    return 0;
}

