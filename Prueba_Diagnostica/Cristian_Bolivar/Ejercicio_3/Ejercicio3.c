#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estructura para asociar la palabra reservada en ingles con su traduccion
typedef struct {
    const char *ingles;
    const char *espanol;
} PalabraReservada;

// Diccionario de palabras reservadas del lenguaje C
PalabraReservada tabla_palabras[] = {
    {"auto", "automatico"},
    {"break", "romper / salir"},
    {"case", "caso"},
    {"char", "caracter"},
    {"const", "constante"},
    {"continue", "continuar"},
    {"default", "por defecto"},
    {"do", "hacer"},
    {"double", "doble"},
    {"else", "sino"},
    {"enum", "enumeracion"},
    {"extern", "externo"},
    {"float", "flotante"},
    {"for", "para"},
    {"goto", "ir a"},
    {"if", "si"},
    {"int", "entero"},
    {"long", "largo"},
    {"register", "registro"},
    {"return", "retornar"},
    {"short", "corto"},
    {"signed", "con signo"},
    {"sizeof", "tamano de"},
    {"static", "estatico"},
    {"struct", "estructura"},
    {"switch", "selector"},
    {"typedef", "definir tipo"},
    {"union", "union"},
    {"unsigned", "sin signo"},
    {"void", "vacio"},
    {"volatile", "volatil"},
    {"while", "mientras"}
};

int total_palabras = sizeof(tabla_palabras) / sizeof(PalabraReservada);

// Busca si una cadena es una palabra reservada valida
const char* buscar_traduccion(const char *palabra) {
    for (int i = 0; i < total_palabras; i++) {
        if (strcmp(tabla_palabras[i].ingles, palabra) == 0) {
            return tabla_palabras[i].espanol;
        }
    }
    return NULL;
}

int main() {
    char nombre_archivo[100];
    
    printf("Ingrese el nombre del archivo C a analizar (ej. codigo_prueba.c): ");
    if (scanf("%99s", nombre_archivo) != 1) {
        printf("Error al leer la entrada.\n");
        return 1;
    }

    // Abrir el archivo en modo lectura
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo '%s'.\n", nombre_archivo);
        return 1;
    }

    // Obtener el tamaño exacto del archivo
    fseek(archivo, 0, SEEK_END);
    long tamano = ftell(archivo);
    rewind(archivo);

    // Cargar el archivo en la memoria de forma dinamica usando malloc
    char *buffer = (char *)malloc((tamano + 1) * sizeof(char));
    if (buffer == NULL) {
        printf("Error: No se pudo asignar memoria dinamica.\n");
        fclose(archivo);
        return 1;
    }

    long bytes_leidos = fread(buffer, sizeof(char), tamano, archivo);
    buffer[bytes_leidos] = '\0';
    fclose(archivo);

    printf("\nAnalizando contenido cargado dinamicamente:\n");
    printf("--------------------------------------------------\n");

    // Recorrer el buffer en memoria para extraer palabras (tokens)
    int i = 0;
    int contador = 0;
    while (i < bytes_leidos) {
        if (isalpha(buffer[i]) || buffer[i] == '_') {
            int inicio = i;
            while (i < bytes_leidos && (isalnum(buffer[i]) || buffer[i] == '_')) {
                i++;
            }
            int longitud = i - inicio;
            char palabra[50];
            if (longitud < 50) {
                strncpy(palabra, &buffer[inicio], longitud);
                palabra[longitud] = '\0';

                // Verificar si la palabra extraida es reservada
                const char *traduccion = buscar_traduccion(palabra);
                if (traduccion != NULL) {
                    printf("Encontrada: %-10s -> Espanol: %s\n", palabra, traduccion);
                    contador++;
                }
            }
        } else {
            i++;
        }
    }

    printf("--------------------------------------------------\n");
    printf("Analisis completado. Total de palabras reservadas halladas: %d\n", contador);

    // Liberar la memoria dinamica reservada
    free(buffer);

    return 0;
}