#include <stdlib.h>
#include <stdio.h>
#include "hashTable.h"

Hash* create_hash(int TABLE_SIZE) {
    Hash* hash = (Hash*) malloc(sizeof(Hash));

    if(hash != NULL) {
        int count;
        hash->TABLE_SIZE = TABLE_SIZE;
        hash->itens = (struct student**) malloc(TABLE_SIZE * sizeof(struct student*));

        if(hash->itens == NULL) {
            free(hash);
            return NULL;
        }

        hash->count = 0;
        for(count=0; count < hash->TABLE_SIZE; count++) {
            hash->itens[count] = NULL;
        }
    }

    return hash;
}

void free_table(Hash* hash) {
    if (hash != NULL) {
        int count;
        for(count=0; count < hash->TABLE_SIZE; count++) {
            if(hash->itens[count] != NULL) {
                free(hash->itens[count]);
            }
        }

        free(hash->itens);
        free(hash);
    }
}

int division_key(int key, int TABLE_SIZE) {
    int result = (key & 0x7FFFFFFF) % TABLE_SIZE;
    printf("key: %d\n", result);
    return result;
}

int insert_closed_hash(Hash* hash, Student student) {
    int slot;
    int key = student.id;

    if (hash == NULL || hash->count == hash->TABLE_SIZE){
        return 0;
    }

    struct student* newStudent;
    newStudent = (struct student*) malloc(sizeof(struct student));
    *newStudent = student;

    slot = division_key(key, hash->TABLE_SIZE);
    if(hash->itens[slot] == NULL) {
        if(newStudent == NULL) {
            return 0;
        }

        newStudent->next = NULL;
        hash->itens[slot] = newStudent;
        hash->count++;

        return 1;
    } else {
        printf("--- COLLISION ---\n");
        Student *aux = hash->itens[slot];

        while (aux->next != NULL) {
            aux = aux->next;
        }

        newStudent->next = NULL;
        aux->next = newStudent;
        hash->count++;
    }

    return 0;
}


void hash_search( Hash* hash, int id) {
   int slot;

   slot = division_key(id, hash->TABLE_SIZE);
   Student *student = hash->itens[slot];

   if (student == NULL) {
       printf("Student not found!\n");
   }

   while (student != NULL) {
       if(student->id == id) {
           printf("Student found!\n");
           printf("ID: %d, Name: %s\n\n", student->id, student->name);
       }

       student = student->next;
   }
}

int hash_delete(Hash* hash, int id) {
    int slot;
    slot = division_key(id, hash->TABLE_SIZE);
    Student *aux = hash->itens[slot];
    Student *prev;
    int index = 0;

    if (hash == NULL) {
        return 0;
    }

    if(aux == NULL) {
        return 0;
    }

    while (aux != NULL) {
        if (hash->itens[slot]->id == id) {
            // first item no next student
            if (aux->next == NULL && index == 0) {
                hash->itens[slot] = NULL;
            }

            // fisrt item with next student
            if (aux->next != NULL && index == 0) {
                hash->itens[slot] = aux->next;
            }

            // last item
            if (aux->next == NULL && index != 0) {
                prev->next = NULL;
            }

            // middle item
            if (aux->next != NULL && index != 0) {
                prev->next = aux->next;
            }

            free(aux);
            hash->count--;
            return 1;
        }

        // next compare
        prev = aux;
        aux = prev->next;
        index++;
    }

    return 1;
}

void hash_dump( Hash* hash) {
    for (int i = 0; i < hash->TABLE_SIZE; ++i) {
        Student *student = hash->itens[i];

        if (student == NULL) {
            continue;
        }

            printf("SLOT[%4d] => ", i);

        for(;;) {
            printf("[ID: %d, Name: %s] ", student->id, student->name);

            if (student->next == NULL) {
                break;
            }

            student = student->next;
        }

        printf("\n");
    }
}


