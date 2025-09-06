#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[31];
    char address[51];
    char number[11];
    int age;
} Contact;

//2
void editContact(Contact* contact, int n, int index, Contact newContact);
//
//3
Contact* removeContact(Contact* contact, int n, char name[31], char number[11]);
//
//4
void write_in_file(Contact* contact, int n, int min_age, int max_age);
//

int main() {
    FILE *bin = fopen("contacts.bin", "rb");
    if (bin == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    int n = fread(&n, sizeof(int), 1, bin);
    Contact *contacts = (Contact *) malloc(n * sizeof(Contact));

    if (contacts == NULL) {
        printf("Error allocating memory for contacts\n");
        exit(1);
    }

    Contact contact;
    for (int i = 0; i < n; i++) {
        fread(&contact, sizeof(Contact), 1, bin);
        contacts[i] = contact;
    }

    free(contacts);
    fclose(bin);
    return 0;
}

//2
void editContact(Contact* contact, int n, int index, Contact newContact) {
    if (index > n || index < 0) {
        printf("Invalid index.\n");
        exit(1);
    }

    strcpy(contact[index].name, newContact.name);
    strcpy(contact[index].address, newContact.address);
    strcpy(contact[index].number, newContact.number);
    contact[index].age = newContact.age;
}

//3
Contact* removeContact(Contact *contact, int* n, char name[31], char number[11]) {
    int found = 0;
    for (int i = 0; i < *n; i++) {
        if (strcmp(contact[i].name, name) == 0 && strcmp(contact[i].number, number) == 0) {
            found++;
            (*n)--;
            for (int j = 0; j < (*n - 1); j++) {
                contact[j] = contact[j + 1];
            }
            contact = realloc(contact, (*n) * sizeof(Contact));
            if (contact == NULL) {
                printf("Error allocating memory for contacts\n");
                exit(1);
            }
            return contact;
        }
    }
    if (found == 0) {
        return NULL;
    }
}

//4
void write_in_file(Contact* contact, int n, int min_age, int max_age) {
    FILE *file = fopen("envelops.txt", "w");
    if (file == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        if (contact[i].age > min_age && contact[i].age < max_age) {
            fprintf(file, "Name:\n%s\nAdress:\n%s", contact[i].name, contact[i].address);
        }
    }
    fclose(file);
}