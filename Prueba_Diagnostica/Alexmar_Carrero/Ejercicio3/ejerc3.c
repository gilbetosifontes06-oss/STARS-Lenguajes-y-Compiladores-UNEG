#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 1. Diccionario de traducción (Palabra en C -> Palabra en Español)
typedef struct {
    const char *en_ingles;
    const char *en_espanol;
} Traduccion;

Traduccion diccionario[] = {
    // Tipos de datos
    {"int", "entero"},
    {"char", "caracter"},
    {"float", "flotante"},
    {"double", "doble"},
    {"void", "vacio"},
    {"short", "corto"},
    {"long", "largo"},
    {"signed", "con_signo"},
    {"unsigned", "sin_signo"},
    {"struct", "estructura"},
    {"union", "union"},
    {"enum", "enumeracion"},
    {"typedef", "tipo_definido"},

    // Control de flujo
    {"if", "si"},
    {"else", "sino"},
    {"switch", "segun"},
    {"case", "caso"},
    {"default", "defecto"},
    {"while", "mientras"},
    {"do", "hacer"},
    {"for", "para"},
    {"break", "romper"},
    {"continue", "continuar"},
    {"return", "retornar"},
    {"goto", "ir_a"},

    // Modificadores y otros
    {"const", "constante"},
    {"volatile", "volatil"},
    {"static", "estatico"},
    {"extern", "externo"},
    {"register", "registro"},
    {"sizeof", "tamano_de"},

    // Directivas de preprocesador (no son palabras reservadas puras, pero sirven)
    {"include", "incluir"},
    {"define", "definir"},
    {"ifdef", "si_definido"},
    {"ifndef", "si_no_definido"},
    {"endif", "fin_si"},
    {"printf", "imprimir"},
    {"scanf", "leer"}
};

int total_palabras = sizeof(diccionario) / sizeof(diccionario[0]);

// 2. Función para cargar el archivo en memoria dinámica
char* cargar_archivo(const char *ruta, long *tamano) {
    FILE *archivo = fopen(ruta, "rb");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo %s\n", ruta);
        return NULL;
    }

    // Calcular tamaño
    fseek(archivo, 0, SEEK_END);
    *tamano = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    // Reservar memoria dinámica
    char *buffer = (char*) malloc(*tamano + 1);
    if (buffer == NULL) {
        printf("Error: No hay memoria suficiente.\n");
        fclose(archivo);
        return NULL;
    }

    // Leer archivo y agregar el caracter nulo al final
    fread(buffer, 1, *tamano, archivo);
    buffer[*tamano] = '\0';

    fclose(archivo);
    return buffer;
}

// 3. Función principal: Analizador Léxico (Scanner)
void traducir_codigo(const char *codigo) {
    int i = 0;
    int len = strlen(codigo);

    while (i < len) {
        // Si encontramos una letra o un guion bajo, empieza una palabra
        if (isalpha(codigo[i]) || codigo[i] == '_') {
            char palabra[100];
            int j = 0;

            // Extraer la palabra completa
            while (i < len && (isalnum(codigo[i]) || codigo[i] == '_')) {
                palabra[j++] = codigo[i++];
            }
            palabra[j] = '\0'; // Terminar la cadena

            // Verificar si está en el diccionario
            int encontrada = 0;
            for (int k = 0; k < total_palabras; k++) {
                if (strcmp(palabra, diccionario[k].en_ingles) == 0) {
                    printf("%s", diccionario[k].en_espanol); // Imprimir traducción
                    encontrada = 1;
                    break;
                }
            }

            if (!encontrada) {
                printf("%s", palabra); // Imprimir original si no es reservada
            }
        }
        else {
            // Si es un espacio, salto de línea o símbolo (ej: +, -, ;), se imprime igual
            printf("%c", codigo[i]);
            i++;
        }
    }
}

int main() {
    long tamano_archivo;
    const char *nombre_archivo = "programa_prueba.c";

    printf("--- Cargando archivo en memoria dinamica... ---\n\n");

    // Cargar a memoria dinámica
    char *codigo_en_memoria = cargar_archivo(nombre_archivo, &tamano_archivo);
    if (codigo_en_memoria == NULL) return 1;

    printf("--- Archivo cargado (%ld bytes). Traduciendo... ---\n\n", tamano_archivo);

    // Traducir
    traducir_codigo(codigo_en_memoria);

    printf("\n\n--- Fin de la traduccion ---\n");

    // ¡Crucial! Liberar la memoria dinámica
    free(codigo_en_memoria);

    return 0;
}
