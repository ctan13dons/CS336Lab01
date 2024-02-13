#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned char bitmap8;

struct new_user {
    char username[50];
    char password[50];
    bool write;
    bool read;
    bool execute;
};

struct user {
    char username[50];
    char password[50];
    bitmap8 permissions;
};

void compare() {
    printf("The size of new_user is %lu.\n", sizeof(struct new_user));
    printf("The size of user is %lu.\n", sizeof(struct user));
}

void grantPermission(int bitIndex, struct user *user) {
    // Set the corresponding bit at bitIndex to 1
    user->permissions |= (1 << bitIndex);
}

void revokePermission(int bitIndex, struct user *user) {
    // Set the corresponding bit at bitIndex to 0
    user->permissions &= ~(1 << bitIndex);
}

int checkPermission(int bitIndex, struct user *user) {
    // Check if the corresponding bit at bitIndex is 1
    return (user->permissions & (1 << bitIndex)) != 0;
}

void printPermissions(struct user *user) {
    if (checkPermission(0, user)) {
        printf("%s has write permission.\n", user->username);
    } else {
        printf("%s doesn't have write permission.\n", user->username);
    }

    if (checkPermission(1, user)) {
        printf("%s has read permission.\n", user->username);
    } else {
        printf("%s doesn't have read permission.\n", user->username);
    }

    if (checkPermission(2, user)) {
        printf("%s has execute permission.\n", user->username);
    } else {
        printf("%s doesn't have execute permission.\n", user->username);
    }
}

void setPermissions(int new_permissions, struct user *user) {
    // Iterate through each bit position
    for (int i = 0; i < 3; ++i) {
        // Check if the corresponding bit at position i is set in new_permissions
        if (new_permissions & (1 << i)) {
            // If set, grant permission at position i
            grantPermission(i, user);
        } else {
            // If not set, revoke permission at position i
            revokePermission(i, user);
        }
    }
}

int main(void) {
    compare();

    struct user user;
    strcpy(user.username, "admin");
    strcpy(user.password, "s#1Pa5");
    user.permissions = 0; // Sets the permissions to 0

    grantPermission(0, &user);
    grantPermission(1, &user);
    printPermissions(&user);

    revokePermission(1, &user);
    grantPermission(2, &user);
    printPermissions(&user);

    // Example usage of setPermissions, similar to chmod in Unix
    setPermissions(7, &user); // Sets all read, write, and execute permissions
    printPermissions(&user);

    return EXIT_SUCCESS;
}

