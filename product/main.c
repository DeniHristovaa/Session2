#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[21];
    int id;
    char expiration_date[11];
    float price;
} Product;

//2
float avg_by_price(Product *product, int n, float price);
//
//3
int write_text_file(Product *products, int size, char expiration_date[11], float price);
//
//4
void print_info(char name[21], int id);
//

int main() {
    int n;
    printf("Enter number of products: ");
    scanf("%d", &n);
    while (1) {
        if (n < 10 || n > 30){
            printf("Enter n:");
            scanf("%d", &n);
        }
        else {
            break;
        }
    }

    Product* products = (Product*)malloc(sizeof(Product) * n);
    if (products == NULL) {
        printf("Memory allocation error");
        exit(1);
    }

    Product product;
    for (int i = 0; i < n; i++) {
        printf("Enter name: ");
        scanf("%s", product.name);
        printf("Enter id: ");
        scanf("%d", &product.id);
        printf("Enter expiration date: ");
        scanf("%s", product.expiration_date);
        printf("Enter price: ");
        scanf("%f", &product.price);

        products[i] = product;
    }

    free(products);
    return 0;
}

//2
float avg_by_price(Product *products, int n, float price) {
    int sum = 0;
    int count = 0;

    Product product;
    for (int i = 0; i < n; i++) {
        if (products[i].price < price) {
            sum += products[i].price;
            count++;
        }
    }
    if (count == 0) {
        return 0;
    }
    else {
        float average = sum / count;
        return average;
    }
}

//3
int write_text_file(Product *products, int size, char expiration_date[11], float price) {
    FILE *file = fopen("products.txt", "w");
    if (file == NULL) {
        printf("File could not be opened");
        exit(1);
    }

    int prod_year, prod_month, prod_day;
    int param_year, param_month, param_day;

    sscanf(expiration_date, "%d.%d.%d", &param_year, &param_month, &param_day);

    int isValid;
    int count = 0;

    for (int i = 0; i < size; i++) {
        sscanf(products[i].expiration_date, "%d.%d.%d", &prod_year, &prod_month, &prod_day);
        isValid = 0;
        if (products[i].price > price) {
            if (prod_year > param_year) {
                isValid = 1;
            }
            else if (prod_year == param_year && prod_month < param_month) {
                isValid = 1;
            }
            else if (prod_year == param_year && prod_month == param_month
                && prod_day < param_day) {
                isValid = 1;
            }
        }


        if (isValid == 0) {
            fprintf(file, "%s-%d-%s-%.2f", products[i].name, products[i].id, products[i].expiration_date, products[i].price);
            count++;
        }
    }
    fclose(file);
    return count;
}

//4
void print_info(char name[21], int id) {
    FILE *bin = fopen("product.bin", "rb");
    if (bin == NULL) {
        printf("File could not be opened");
        exit(1);
    }

    int count = 0;
    int size_name;

    Product product;
    while (!feof(bin)) {
        if (fread(&size_name, sizeof(int), 1, bin) != 1) break;
        if (fread(&product.name, sizeof(char), size_name, bin) != size_name) break;
        product.name[size_name] = '\0';
        if (fread(&product.id, sizeof(int), 1, bin) != 1) break;
        if (fread(&product.expiration_date, sizeof(char), 10, bin) != 10) break;
        product.expiration_date[10] = '\0';
        if (fread(&product.price, sizeof(float), 1, bin) != 1) break;

        if (product.name == name && product.id == id) {
            printf("Данни за продукт: %s - използвай преди %s  - цена %.2fлева", product.name, product.expiration_date, product.price);
            count++;
        }
    }

    fclose(bin);

    if (count == 0) {
        printf("There are no matches.");
    }
}