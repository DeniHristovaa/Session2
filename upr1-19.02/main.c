#include <stdio.h>

int main(void) {
    int seconds;
    printf("Enter number of seconds: ");
    scanf("%d", &seconds);
    int hour = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    int secondss = (seconds % 3600) % 60;

    if (seconds <= 0) {
        printf("Invalid input\n");
    }
    else {
        printf("hour: %d minutes:%d second:%d\n", hour, minutes, secondss);
    }
    return 0;
}