#include <stdio.h>

main() {
    int a;
    scanf("%i",&a);
    printf("The number is %i ", a);
    printf("\n");


    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= i; j++) {
            printf("*");
        }
        printf("\n");
    }
}
