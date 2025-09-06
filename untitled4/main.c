#include <stdio.h>

int main(void) {
    int x = 5;
    int y = 7;
    printf("%d\n", sum(x, y));
    printf("%d\n", fib());
    return 0;
}

int sum(int x, int y) {
    return x + y;
}

int fib() {
    int x = 1;
    x++;
    if (x < 10) {
        fib();
    }
    else {
        return x;
    }
}
