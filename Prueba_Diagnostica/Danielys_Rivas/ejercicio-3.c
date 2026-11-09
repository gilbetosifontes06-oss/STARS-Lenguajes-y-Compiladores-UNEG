#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *ingles;
    char *espanol;
} PalabraReservada;

PalabraReservada tabla[] = {
    {"int", "entero"}, {"float", "flotante"}, {"char", "caracter"},
    {"return", "retornar"}, {"if", "si"}, {"else", "sino"},
    {"while", "mientras"}, {"for", "para"}, {"void", "llamada"},
    {"struct", "estructura"}
};
int total_palabras = 10;

char* traducir_codigo(const char *codigo_fuente) {
    size_t len = strlen(codigo_fuente);
    char *codigo_traducido = (char*) malloc(len * 3 + 1); 
    if (!codigo_traducido) return NULL;
    strcpy(codigo_traducido, "");

    char buffer[100];
    int b_idx = 0;

    for (size_t i = 0; i <= len; i++) {
        if (isalnum(codigo_fuente[i]) || codigo_fuente[i] == '_') {
            buffer[b_idx++] = codigo_fuente[i];
        } else {
            buffer[b_idx] = '\0';
            if (b_idx > 0) {
                int traducido = 0;
                for (int j = 0; j < total_palabras; j++) {
                    if (strcmp(buffer, tabla[j].ingles) == 0) {
                        strcat(codigo_traducido, tabla[j].espanol);
                        traducido = 1;
                        break;
                    }
                }
                if (!traducido) {
                    strcat(codigo_traducido, buffer);
                }
                b_idx = 0;
            }
            if (codigo_fuente[i] != '\0') {
                char separador[2] = {codigo_fuente[i], '\0'};
                strcat(codigo_traducido, separador);
            }
        }
    }
    return codigo_traducido;
}

int main() {
    // codigo de prueba para traducir
    char *codigo = strdup("int main() {\n    if (1) {\n        return 0;\n    } else {\n        while(0) {}\n    }\n}");

    char *resultado = traducir_codigo(codigo);

    printf("=== Codigo original C ===\n%s\n\n", codigo);
    printf("=== Codigo traducido ===\n%s\n", resultado);

    free(codigo);
    free(resultado);
    return 0;
}
