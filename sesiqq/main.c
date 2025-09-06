#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[31];
    char expiryDate[8]; // формат ММ.ГГГГ (7 символа + '\0')
    unsigned long productCode; // 13-цифрен код
    double price;
    int quantity;
} Medicine;

//2
Medicine *getExpiredMedicine(Medicine *arr, int N, const char *givenDate);
//
//3
int write_text_file(Medicine *arr, int N, double maxPrice, double minPrice);
//
//4
void remove_medicine(Medicine *arr, int N, char name[31], char expiryDate[8]);
//

int main() {
    FILE *file = fopen("Medicine.bin", "rb");
    if (file == NULL) {
        printf("File could not be opened\n");
        exit(1);
    }

    // Определяме броя на записите
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file); // текуща позиция
    rewind(file); // позициониране в началото на файл

    size_t numMedicine = fileSize / sizeof(Medicine);

    // Създаване на динамичен  масив
    Medicine *medicines = (Medicine *)malloc(numMedicine);
    if (medicines == NULL) {
        printf("Memory allocation error\n");
        fclose(file);
        exit(1);
    }

    // Четене на данните от файла
    size_t readCount = fread(medicines, sizeof(Medicine), 1, file);
    if (readCount != numMedicine) {
        printf("File could not be read\n");
        free(medicines);
        fclose(file);
        exit(1);
    }

    fclose(file);
    free(medicines);
    return 0;
}

//2

Medicine *getExpiredMedicine(Medicine *arr, int N, char date[8]) {
    Medicine *expiredMedicine = (Medicine *)malloc(sizeof(Medicine));
    if (expiredMedicine == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }

    int curentM, curentY, givenM, givenY;
    sscanf(date, "%d.%d", &curentM, &curentY);

    int count = 0;

    for (int i = 0; i < N; i++) {
        sscanf(arr[i].expiryDate, "%d.%d", &givenM, &givenY);
        if (givenY < curentY || (givenY == curentY && givenM < curentM)) {
            expiredMedicine[count] = arr[i];
            count++;
        }
    }

    if (count == 0) {
        return NULL;
    }

    expiredMedicine = realloc(expiredMedicine, count * sizeof(Medicine));
    if (expiredMedicine == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }

    return expiredMedicine;
}

//3
int write_text_file(Medicine *arr, int N, double maxPrice, double minPrice) {
    FILE *file = fopen("offer.txt", "w");
    if (file == NULL) {
        printf("File could not be opened\n");
        exit(1);
    }

    int count = 0;
    for (int i = 0; i < N; i++) {
        if (arr[i].price > minPrice && arr[i].price < maxPrice) {
            fprintf(file,"%s\n", arr[i].name);
            fprintf(file,"%s\n", arr[i].expiryDate);
            fprintf(file, "%d\n", arr[i].productCode);
            fprintf(file, "%.2f\n", arr[i].price);
            count++;
        }
    }
    if (count == 0) {
        printf("There no maches.");
    }
    fclose(file);
    return count;
}

//4
Medicine* remove_medicine(Medicine *arr, int* N, char name[30], char expiryDate[8]) {
    int found = 0;
    for (int i = 0; i < *N; i++) {
        if (strcmp(arr[i].name, name) == 0 && strcmp(arr[i].expiryDate, expiryDate) == 0) {
            found++;
            (*N)--;
            for (int j = i; j < (*N - 1); j++) {
                arr[j] = arr[j + 1];
            }
            arr = realloc(arr, sizeof(Medicine) * *N);
            if (arr == NULL) {
                printf("Memory allocation error\n");
                exit(1);
            }
            return arr;
        }
    }
    if (found == 0) {
        return NULL;
    }
}