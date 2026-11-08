#include <stdio.h>

typedef struct {
    int id;
    float saldo;
} Cliente;

int evaluar_limite(int valor) {
    const int limite = 100;
    if (valor > limite) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int contador = 0;
    float total = 0.0f;
    char letra = 'A';

    for (int i = 0; i < 10; i++) {
        contador += i;
    }

    int opcion = 2;
    switch (opcion) {
        case 1:
            printf("Caso uno\n");
            break;
        case 2:
            printf("Caso dos\n");
            break;
        default:
            printf("Por defecto\n");
            break;
    }

    return 0;
}