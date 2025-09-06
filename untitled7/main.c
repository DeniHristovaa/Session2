#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char brand[20];
    char model[5];
    float obem;
    float price;
    char registration;
} Automobil;

void save_in_file(Automobil a, const char *filename, const char *bin_file) {
    FILE *file = fopen(filename, "wb");

    if (file == NULL) {
        printf("Error opening file %s\n");
        return;
    }

    FILE *bin = fopen(bin_file, "rb");
    if (bin == NULL) {
        printf("Error opening file %s\n");
        return;
    }

    fwrite(&a, sizeof(Automobil), 1, bin);
    fprintf(file, "%s %s %.2f %.2f %c\n", a.brand, a.model, a.obem, a.price, a.registration);

    fclose(file);
    fclose(bin);

    printf("Automobil saved\n");
}

Automobil load_in_file(const char *filename, const char *bin_file) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file %s\n");
    }
    Automobil a;
    printf("Enter Brand and model: ");
    scanf("%s", &a.brand);
    printf("Enter Model: ");
    scanf("%s", &a.model);
    printf("Enter Obem: ");
    scanf("%f", &a.obem);
    printf("Enter Price: ");
    scanf("%f", &a.price);
    printf("Enter registration: ");
    scanf("%c", &a.registration);
    return a;
}

void readAndCompareFiles(Automobil a, const char *filename, const char *bin_file) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file %s\n");
    }

    FILE *bin = fopen(bin_file, "rb");
    if (bin == NULL) {
        printf("Error opening file %s\n");
    }

    Automobil a;
    char line[100];

    // if (bin == NULL || file == NULL) {
    //     printf("Error opening files %s\n");
    // }

    printf("\n--- Data of binary file ---\n");
    while (fread(&a, sizeof(Automobil), 1, file) == 1) {
        printf("%s %s %.2f %.2f %c \n", a.brand, a.model, a.obem, a.price, a.registration);
    }

    printf("\n--- Data of txt file ---\n");
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s\n", line);
    }

    fclose(file);
    fclose(bin);
}

int main() {
    int choice;

    do {
        printf("\n1. Enter New Automobil \n2. Display data of files \n3. Exit\n Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                Automobil new_automobil = load_in_file("new_automobil.txt", NULL);
                save_in_file(new_automobil, "new_automobil.txt", NULL);
                break;
            }
            case 2: {
                readAndCompareFiles(new_automobile, "new_automobile.txt", NULL);
                break;
            }
            case 3: {
                printf("Exiting...\n");
                break;
            }
            default:
                printf("Invalid Choice\n");
        }
    } while (choice != 3);

    return 0;
}