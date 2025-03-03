#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct Person {
    char name[MAX_NAME];
    int age;
    struct Person *next;
} Person;

Person* hash_table[TABLE_SIZE];

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
        } else {
            printf("\t%i\t", i);

            Person* tmp = hash_table[i];

            while (tmp != NULL) {
                printf("%s - ", tmp->name);
                tmp = tmp->next;
            }

            printf("\n");
        }
    }

    printf("\tEnd of Table\n");
}

bool hash_table_insert(Person *p) {
    if (p == NULL) {
        return false;
    }

    int index = hash(p->name);

    p->next = hash_table[index];
    hash_table[index] = p;

    return true;
}

Person* hash_table_lookup(char *name) {
    int index = hash(name);

    Person *tmp = hash_table[index];

    while (tmp != NULL && strcmp(tmp->name, name) != 0) {
        tmp = tmp->next;
    }

    return tmp;
}

Person* hash_table_delete(char *name) {
    int index = hash(name);

    Person *tmp = hash_table[index];
    Person *prev = NULL;

    while (tmp != NULL && strcmp(tmp->name, name) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }

    if (tmp == NULL) {
        return NULL;
    }

    if (prev == NULL) {
        hash_table[index] = tmp->next; 
    } else {
        prev->next = tmp->next;
    }

    return tmp;
}


int main() {
    init_hash_table();
    // print_table();

    // Dynamically allocate memory for each person
    Person* shogun = malloc(sizeof(Person));
    strcpy(shogun->name, "Shogun");
    shogun->age = 19;
    
    Person* sarthak = malloc(sizeof(Person));
    strcpy(sarthak->name, "Sarthak");
    sarthak->age = 19;

    Person* riddhi = malloc(sizeof(Person));
    strcpy(riddhi->name, "Riddhi");
    riddhi->age = 21;

    Person* saaransh = malloc(sizeof(Person));
    strcpy(saaransh->name, "Saaransh");
    saaransh->age = 21;

    Person* laksh = malloc(sizeof(Person));
    strcpy(laksh->name, "Laksh");
    laksh->age = 21;

    hash_table_insert(shogun);
    hash_table_insert(sarthak);
    hash_table_insert(riddhi);
    hash_table_insert(saaransh);
    hash_table_insert(laksh);

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