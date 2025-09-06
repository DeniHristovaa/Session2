#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[3];
    char name[31];
    int weight;
    float price;
}IceCream;

//2
float pricesOfIceCreams(IceCream *iceCreams, int n, char letter);
//
//3
int write_in_file(IceCream *iceCreams, int n, float price, int weight);
//
//4
void findIceCreamByCode(char id[3]);
//

int main() {
    int n;
    printf("Please enter n: ");
    scanf("%d", &n);
    while (1) {
        if (n < 5 || n > 15) {
            printf("Please enter a number between 1 and 15\n");
            scanf("%d", &n);
        }
        else {
            break;
        }
    }

    IceCream* iceCreams = (IceCream *)malloc(n * sizeof(IceCream));
    if (iceCreams == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }

    IceCream iceCream;

    for (int i = 0; i < n; i++) {
        printf("Please enter id: ");
        scanf("%s", iceCream.id);
        printf("Please enter name: ");
        scanf("%s", iceCream.name);
        printf("Please enter weight: ");
        scanf("%d", &iceCream.weight);
        printf("Please enter price: ");
        scanf("%f", &iceCream.price);

        iceCreams[i] = iceCream;
    }

    free(iceCreams);
    return 0;
}

//2
float pricesOfIceCreams(IceCream *iceCreams, int n, char letter) {
    float price = 0;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (iceCreams[i].name[0] == letter || iceCreams[i].name[0] - 32 == letter || iceCreams[i].name[0] + 32 == letter) {
            price += iceCreams[i].price * iceCreams[i].weight;
            count++;
        }
    }
    if (count == 0) {
        return 0;
    }
    else {
        return price;
    }
}

//3
int write_in_file(IceCream *iceCreams, int n, float price, int weight) {
    FILE* file = fopen("info.txt", "w");
    if (file == NULL) {
        printf("File could not be opened\n");
        exit(1);
    }

    int count = 0;

    for (int i = 0; i < n; i++) {
        if (iceCreams[i].price < price && iceCreams[i].weight > weight) {
            fprintf(file, "%s; %s; %d; %fleva", iceCreams[i].id, iceCreams[i].name, iceCreams[i].weight, iceCreams[i].price);
            count++;
        }
    }

    fclose(file);

    if (count == 0) {
        return 0;
    }
    else {
        return count;
    }
}

//4
void findIceCreamByIceCreamByCode(char id[3]) {
    FILE* bin = fopen("icecream.bin", "rb");
    if (bin == NULL) {
        printf("File could not be opened\n");
        exit(1);
    }

    int count = 0;
    int name_size;

    IceCream iceCream;
    while (!feof(bin)) {
        if (fread(&iceCream.id, sizeof(char), 3, bin) != 3) break;
        iceCream.id[2] = "\0";
        if (fread(&name_size, sizeof(int), 1, bin) != 1) break;
        if (fread(iceCream.name, sizeof(char), name_size, bin) != name_size) break;
        iceCream.name[name_size] = '\0';
        if (fread(&iceCream.price, sizeof(float), 1, bin) != 1) break;
        if (fread(&iceCream.weight, sizeof(int), 1, bin) != 1) break;

        if (strcmp(iceCream.id, id) == 0) {
            printf("\n ");
            printf("Ice Cream - %s \n Price = %.2f BGN", iceCream.name, iceCream.price);
            printf("\n");
            count++;
        }
    }

    fclose(bin);

    if (count == 0) {
        printf("There are no maches.");
    }
}