#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Локальная переменная с ключевым словом static */

int f(void) {
    static int x = 5;
    printf("%d\n", x);
    x++;
    return 0;
}


int main(void) {
    f();
    f();
    f();
    return 0;
}
