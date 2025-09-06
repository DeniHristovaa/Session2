#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char date[11];
    char name[31];
    char diagnose[51];
}Treatment;

//2
int count_treatment(Treatment *arr, int size, char name[31], char diagnose[51]);
//
//3
Treatment* odd_new_treatment(Treatment *arr, int size);
//
//4
int write_text_file(Treatment *arr, int size, char diagnose[51]);
//

int main(void) {
    FILE* file = fopen("history.bin", "rb");
    if (file == NULL) {
        printf("File could not be opened\n");
        exit(1);
    }

    int n;
    fread(&n, sizeof(int), 1, file);

    Treatment *history = (Treatment *)malloc(n * sizeof(Treatment));
    if (history == NULL) {
        printf("Error allocating memory\n");
        exit(1);
    }

    Treatment treat;
    for (int i = 0; i < n; i++) {
        fread(&treat, sizeof(Treatment), 1, file);
        history[i] = treat;
    }

    free(history);
    fclose(file);
    return 0;
}

//2
int count_treatment(Treatment *arr, int size, char name[31], char diagnose[51]) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i].name, name) == 0 && strcmp(arr[i].diagnose, diagnose) == 0) {
            count++;
        }
    }
    return count;
}

//3
Treatment* odd_new_treatment(Treatment *arr, int* size) {
    Treatment treat;
    printf("Insert treatment id: ");
    scanf("%d", &treat.id);
    printf("Insert treatment date: ");
    scanf("%s", treat.date);
    printf("Insert treatment name: ");
    scanf("%s", treat.name);
    printf("Insert treatment diagnose: ");
    scanf("%s", treat.diagnose);

    Treatment *temp = realloc(arr, (*size + 1) * sizeof(Treatment));
    if (temp == NULL) {
        printf("Error allocating memory\n");
        exit(1);
    }
    temp[*size] = treat;
    (*size)++;
    arr = temp;
    return arr;
}

//4
int write_text_file(Treatment *arr, int size, char diagnose[51]) {
    FILE* file = fopen("illness.txt", "w");
    if (file == NULL) {
        printf("File could not be opened\n");
        exit(1);
    }
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i].diagnose, diagnose) == 0) {
            count++;
            fprintf(file, "Bolnichen prestoi na %s\n za lechenie na %s: \n %s", arr[i].name, arr[i].diagnose, arr[i].date);
        }
    }
    fclose(file);
    return count;
}