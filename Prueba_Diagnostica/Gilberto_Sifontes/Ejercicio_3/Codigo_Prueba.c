#include <stdio.h>

// Definición de una estructura para probar struct y typedef
typedef struct {
    int id;
    float saldo;
} Cliente;

// Función que utiliza un ciclo while y condiciones if-else
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

    // Ciclo for para probar palabras reservadas
    for (int i = 0; i < 10; i++) {
        contador += i;
    }

    // Uso de switch para control de flujo
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