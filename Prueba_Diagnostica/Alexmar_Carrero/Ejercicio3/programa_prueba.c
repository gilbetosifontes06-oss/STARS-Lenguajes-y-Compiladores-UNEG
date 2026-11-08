#include <stdio.h>

int main() {
    int edad = 20;
    float estatura = 1.75;

    if (edad > 18) {
        printf("Eres mayor de edad\n");
    } else {
        printf("Eres menor de edad\n");
    }

    while (edad < 25) {
        edad = edad + 1;
    }

    return 0;
}
