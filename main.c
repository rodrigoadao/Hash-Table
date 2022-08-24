#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashTable.h"

struct student create_student();
void menu();

int main() {
    menu();
    return 1;
}

 struct student create_student() {
    struct student student;
    char name[50];

    printf("ID: ");
    scanf("%d",&student.id);

    printf("NAME: ");
    scanf("%s",name);
    strcpy(student.name,name);

    return student;
 }

void menu() {
    int option, id;
    Hash* hash = create_hash(20);
    struct student student;

    do {
        printf("- - - HASH - - -\n");
        printf("1 - INSERT: \n");
        printf("2 - HASH DUMP: \n");
        printf("3 - DELETE BY ID: \n");
        printf("4 - SEARCH BY ID: \n");
        printf("5 - HASH SIZE: \n");
        printf("6 - HASH MAX_SIZE: \n");
        printf("0 - QUIT: \n\n");

        scanf("%d", &option);
        switch (option)
        {
            case 1:
                student = create_student();
                insert_closed_hash(hash, student);
            break;
            case 2:
                hash_dump(hash);
            break;
            case 3:
                printf("--- DELETE ---\n");
                printf("ID: ");
                scanf("%d", &id);
                hash_delete(hash, id);
            break;
            case 4:
                printf("--- SEARCH ---\n");
                printf("ID: ");
                scanf("%d", &id);
                hash_search(hash, id);
            break;
            case 5:
                printf("HASH SIZE: %d\n", hash->count);
            break;
            case 6:
                printf("HASH MAX_SIZE: %d\n", hash->TABLE_SIZE);
            break;
        }
    } while (option != 0);

}
