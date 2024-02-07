#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct user{
    char username[50];
    char password[50];
    int admin;
};

struct user* createUsers(int max_number_of_users) {
    //Your code goes here
}

void initUsers(void* users, int max_number_of_users) {
    //Your code goes here
}

void addUser1(struct user* users, char* username, char* password, int admin, int* count) {
    //Your code goes here
}

void addUser2(struct user* users, struct user* newUser, int* count) {
    //Your code goes here
}

void printUser(struct user* users, int number_of_users) {
    //Your code goes here
}

int main(void) {
    struct user* users = createUsers(10);
    if(users == NULL) {
        return 0;
    }
    int userCount = 0;
    initUsers(users, 10);
    addUser1(users, "admin", "s#1Pa5", 1, &userCount);
    addUser1(users, "vahab", "fgH!12", 0, &userCount);

    struct user u1;
    u1.admin = 2;
    strcpy(u1.username, "usf");
    strcpy(u1.password, "gA24?m");
    addUser2(users, u1, &userCount);
    printUser(users, userCount);
    free(users);
    return 0;
}
