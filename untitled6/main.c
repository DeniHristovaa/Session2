#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    double price;
    int id;
}Product;

typedef struct {
    char* address;
    int ptoductId;
} Order;

int main() {
    Product* products = NULL;
    int productCount = 0;

    Order *new_orders = NULL;
    int new_orderCount = 0;

    char command[50];

    while (1) {
        scanf("%s", command);

        if (strcmp(command, "END") == 0) {
            break;
        }
        else if (strcmp(command, "Product") == 0) {
            char name[50];
            double price;
            int id;
            printf("Please enter the product's name: ");
            scanf("%s", name);
            printf("Please enter the product's price: ");
            scanf("%lf", &price);
            printf("Please enter the product's id: ");
            scanf("%d", &id);

            products = realloc(products, (productCount + 1) * sizeof(Product));
            products[productCount].name = malloc(strlen(name) + 1);
            strcpy(products[productCount].name, name);
            products[productCount].price = price;
            products[productCount].id = id;
            productCount++;

            for (int i = 0; i < new_orderCount; i++) {
                if (new_orders[i].ptoductId == id) {
                    printf("Client %s ordered %s \n", new_orders[i].address, name);

                    free(new_orders[i].address);

                    for (int j = i; j < new_orderCount - 1; j++) {
                        new_orders[j] = new_orders[j + 1];
                    }

                    new_orderCount--;
                    new_orders = realloc(new_orders, new_orderCount * sizeof(Order));
                    i--;
                }
            }
        }
        else if (strcmp(command, "Order") == 0) {
            char address[50];
            int ptoductId;

            printf("Please enter the product's address: ");
            scanf("%s", address);
            printf("Please enter the product's ptoductId: ");
            scanf("%d", &ptoductId);

            int found = 0;
            for (int i = 0; i < productCount; i++) {
                if (products[i].id == ptoductId) {
                    printf("Client %s ordered %s \n", address, products[i].name);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                new_orders = realloc(new_orders, (new_orderCount + 1) * sizeof(Order));
                new_orders[new_orderCount].address = malloc(strlen(address) + 1);
                strcpy(new_orders[new_orderCount].address, address);
                new_orders[new_orderCount].ptoductId = ptoductId;
                new_orderCount++;
            }
        }
    }

    for (int i = 0; i < productCount; i++) {
        free(products[i].name);
    }
    free(products);

    for (int i = 0; i < new_orderCount; i++) {
        free(new_orders[i].address);
    }
    free(new_orders);

    return 0;
}




