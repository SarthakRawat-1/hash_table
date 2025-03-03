#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct {
    char name[MAX_NAME];
    int age;
    // More details can be added
} Person;

Person* hash_table[TABLE_SIZE];

static Person* DELETED_NODE = (Person*) -1;  

unsigned int hash(char *name) {
    int length = strnlen(name, MAX_NAME);

    unsigned int hash_value = 0;

    for (int i = 0; i < length; i++) {
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }

    return hash_value;
}

void init_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

void print_table() {
    printf("\tStart of Table\n");

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] == NULL) {
            printf("\t%i\t---\n", i);
        } else if (hash_table[i] == DELETED_NODE){
            printf("\t%i\tDeleted Node\n", i);
        } else {
            printf("\t%i\t%s\n", i, hash_table[i]->name);
        }
    }

    printf("\tEnd of Table\n");
}

bool hash_table_insert(Person *p) {
    if (p == NULL) {
        return false;
    }

    int index = hash(p->name);

    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (i + index) % TABLE_SIZE;

        if (hash_table[try] == NULL || hash_table[try] == DELETED_NODE) {
            hash_table[try] = p;
            return true;
        }
    }

    return false;
}

Person* hash_table_lookup(char *name) {
    int index = hash(name);

    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (index + i) % TABLE_SIZE;

        if (hash_table[try] == NULL) {
            return NULL;
        } 

        if (hash_table[try] == DELETED_NODE) {
            continue;
        }

        if (strcmp(hash_table[try]->name, name) == 0) {
            return hash_table[try];
        }
    }

    return NULL;
}

Person* hash_table_delete(char *name) {
    int index = hash(name);

    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (index + i) % TABLE_SIZE;

        if (hash_table[try] == NULL) {
            return NULL;
        } 

        if (hash_table[try] == DELETED_NODE) {
            continue;
        }

        if (strcmp(hash_table[try]->name, name) == 0) {
            Person *tmp = hash_table[try];
            hash_table[try] = DELETED_NODE;

            return tmp;
        }
    }

    return NULL;
}


int main() {
    init_hash_table();
    // print_table();

    Person shogun = {.name = "Shogun", .age = 19};
    Person sarthak = {.name = "Sarthak", .age = 19};
    Person riddhi = {.name = "Riddhi", .age = 21};
    Person saaransh = {.name = "Saaransh", .age = 21};
    Person laksh = {.name = "Laksh", .age = 21};
    
    hash_table_insert(&shogun);
    hash_table_insert(&sarthak);
    hash_table_insert(&riddhi);
    hash_table_insert(&saaransh);
    hash_table_insert(&laksh);

    print_table();

    Person* tmp = hash_table_lookup("Shogun");

    if (tmp == NULL) {
        printf("\tNot Found\n");
    } else {
        printf("\tFound %s\n", tmp->name);
    }

    hash_table_delete("Shogun");

    print_table();

    // printf("Shogun => %u\n", hash("Shogun"));
    // printf("Sarthak => %u\n", hash("Sarthak"));
    // printf("Riddhi => %u\n", hash("Riddhi"));
    // printf("Saaransh => %u\n", hash("Saaransh"));
    return 0;
}