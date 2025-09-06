#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nameOfArtist[31];
    char namePicture[31];
    float price;
}Picture;

//2
float averagePicture(Picture *pictures, int n, float price);
//
//3
int save_in_file(Picture *pictures, int n, char letter);
//
//4
void printInfo(char nameOfArtist[31]);
//

int main(void) {
    int n;
    printf("Enter number of pictures: ");
    scanf("%d", &n);
    while (1) {
        if (n < 3 || n > 30) {
            printf("Invalid Input\n");
            printf("Enter number of pictures: ");
            scanf("%d", &n);
        }
        else {
            break;
        }
    }

    Picture *pictures = (Picture *)calloc(n, sizeof(Picture));
    if (pictures == NULL) {
        printf("Memory allocation error\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        Picture picture;
        printf("Insert the picture number: ");
        scanf("%d", &picture.id);
        printf("Insert artist name: ");
        scanf("%s", picture.nameOfArtist);
        printf("Insert picture name: ");
        scanf("%s", picture.namePicture);
        printf("Insert price: ");
        scanf("%f", &picture.price);

        pictures[i] = picture;
    }

    free(pictures);
    return 0;
}

//2
float averagePicture(Picture *pictures, int n, float price) {
    float prices = 0.0;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (pictures[i].price > price) {
            count++;
            prices += pictures[i].price;
        }
    }
    if (count > 0) {
        float average = prices / count;
        return average;
    }
    else {
        return 0;
    }
}

//3
int save_in_file(Picture *pictures, int n, char letter) {
    int count = 0;
    FILE *file = fopen("info.txt", "w");
    if (file == NULL) {
        printf("File could not be opened\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        if (pictures[i].nameOfArtist[0] == letter) {
            fprintf(file, "%d; %s; %f", pictures[i].id, pictures[i].namePicture, pictures[i].price);
            count++;
        }
    }

    fclose(file);

    if (count > 0){
        return count;
    }
    else {
        return 0;
    }
}

//4
void printInfoint(char nameOfArtist[31]) {
    FILE *file = fopen("picture.bin", "rb");
    if (file == NULL) {
        printf("File could not be opened\n");
        exit(1);
    }

    int count = 0;
    int artist_len;
    int picture_len;

    Picture picture;
    while (!feof(file)) {
        if (fread(&picture.id, sizeof(int), 1, file) != 1) break;
        if (fread(&artist_len, sizeof(int), 1, file) != 1) break;
        if (fread(&picture.nameOfArtist, sizeof(char), artist_len, file) != artist_len) break;
        picture.nameOfArtist[artist_len] = '\0';
        if (fread(&picture_len, sizeof(int), 1, file) != 1) break;
        if (fread(&picture.namePicture, sizeof(char), picture_len, file) != picture_len) break;
        picture.namePicture[picture_len] = '\n';
        if (fread(&picture.price, sizeof(float), 1, file) != 1) break;

        if (strcmp(picture.nameOfArtist, nameOfArtist) == 0) {
            printf("Picture name: %s \n Price: %f BGN\n", picture.namePicture, picture.price);
            printf("\n");
            count++;
        }
    }
    if (count == 0) {
        printf("There are not matches.");
    }
    fclose(file);
}