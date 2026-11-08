#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct {
    const char *ingles;
    const char *espanol;
}PalabraReservada;

typedef struct {
    char palabra[30];
    const char *traduccion;
    int conteo;
} PalabraEncontrada;


PalabraReservada diccionario[] = {
    {"auto", "automatico"},
    {"break", "romper"},
    {"case", "caso"},
    {"char", "caracter"},
    {"const", "constante"},
    {"continue", "continuar"},
    {"default", "por_defecto"},
    {"do", "hacer"},
    {"double", "doble"},
    {"else", "sino"},
    {"enum", "enumeracion"},
    {"extern", "externo"},
    {"float", "flotante"},
    {"for", "para"},
    {"goto", "ir_a"},
    {"if", "si"},
    {"int", "entero"},
    {"long", "largo"},
    {"register", "registro"},
    {"return", "retornar"},
    {"short", "corto"},
    {"signed", "con_signo"},
    {"sizeof", "tamano_de"},
    {"static", "estatico"},
    {"struct", "estructura"},
    {"switch", "interruptor"},
    {"typedef", "definir_tipo"},
    {"union", "union"},
    {"unsigned", "sin_signo"},
    {"void", "vacio"},
    {"volatile", "volatile"},
    {"while", "mientras"}
};

int total_palabras = sizeof(diccionario) / sizeof(PalabraReservada); 

const char *buscar_palabra(const char *palabra);

char *cargar_archivo(const char *nombre, long *tamanio_out);

void analizar_palabras(const char *contenido);


int main(){
    char nombre_archivo[100] = "Codigo_Prueba.c";
    long tamanio_archivo = 0;

    printf("============================================================\n");
    printf("        ANALISIS DE PALABRAS RESERVADAS EN C\n");
    printf("        Realizado por Gilberto Sifontes - V-32.416.786\n");
    printf("============================================================\n\n");

    char *contenido_memoria = cargar_archivo(nombre_archivo, &tamanio_archivo);

    if(contenido_memoria!=NULL){
        printf("[OK] Archivo cargado: %s (%ld bytes)\n", nombre_archivo, tamanio_archivo);

        // Analizar y traducir palabras reservadas
        analizar_palabras(contenido_memoria);

        // Liberar la memoria dinámica reservada al inicio
        free(contenido_memoria);
    }


    return 0;
}

// Función para buscar una palabra en el diccionario
const char *buscar_palabra(const char *palabra){

    for(int i=0; i<total_palabras; i++){

        if(strcmp(diccionario[i].ingles, palabra) == 0){
            return diccionario[i].espanol;
        }
    }

    return NULL;
}

char *cargar_archivo(const char *nombre, long *tamanio_out){
    
    FILE *archivo = fopen(nombre,"r");

    if(archivo==NULL){
        fflush(stdout);
        fprintf(stderr, "[ERROR] No se pudo abrir el archivo: %s\n", nombre);
        return NULL;
    }
     
    // Ir al final del archivo para medir su tamaño
    fseek(archivo,0,SEEK_END);
    long tamanio = ftell(archivo);
    rewind(archivo);

    //Creación de memoria dinamica para el contenido del archivo
    char *buffer = (char*) malloc(tamanio+1);
    if(buffer == NULL){
        fflush(stdout);
        fprintf(stderr, "[ERROR] No se pudo asignar memoria.\n");
        fclose(archivo);
        return NULL;
    }

    // Leer el contenido completo hacia el buffer en memoria
    long byte_leidos = fread(buffer, 1, tamanio, archivo);
    buffer[byte_leidos] = '\0'; // Carácter nulo de cierre de cadena

    fclose(archivo);
    *tamanio_out = byte_leidos;
    return buffer;
}

// Busca palabras reservadas en el texto cargado
void analizar_palabras(const char *contenido){
    PalabraEncontrada unicas[100];
    int total_unicas = 0;

    char *copia = strdup(contenido);
    char *delimitadores = " \t\n\r,;(){}[]+-*=/%<>!&|#.\"" ;
    char *token = strtok(copia, delimitadores);

    while(token!=NULL){
        // Convertir el token a minúsculas para asegurar la coincidencia
        for(int i=0; token[i]; i++){
            token[i] = tolower(token[i]);
        }

        const char *traduccion = buscar_palabra(token);
        if (traduccion != NULL) {
            // Buscar si ya la habíamos registrado
            int index = -1;
            for (int i = 0; i < total_unicas; i++) {
                if (strcmp(unicas[i].palabra, token) == 0) {
                    index = i;
                    break;
                }
            }

            if (index != -1) {
                // Si ya existe, sumamos al contador
                unicas[index].conteo++;
            } else if (total_unicas < 100) {
                // Si es nueva, la agregamos
                strcpy(unicas[total_unicas].palabra, token);
                unicas[total_unicas].traduccion = traduccion;
                unicas[total_unicas].conteo = 1;
                total_unicas++;
            }
        }
        token = strtok(NULL, delimitadores);
    }

    free(copia);

    // Imprimir el reporte en formato de tabla alineada
    printf("\n------------------------------------------------------------\n");
    printf("PALABRAS RESERVADAS ENCONTRADAS Y TRADUCIDAS\n");
    printf("------------------------------------------------------------\n");

    if (total_unicas == 0) {
        printf("  No se encontraron palabras reservadas.\n");
    } else {
        int ancho_palabra = (int)strlen("Palabra");
        int ancho_trad = (int)strlen("Traduccion");

        for (int i = 0; i < total_unicas; i++) {
            int lp = (int)strlen(unicas[i].palabra);
            int lt = (int)strlen(unicas[i].traduccion);
            if (lp > ancho_palabra) ancho_palabra = lp;
            if (lt > ancho_trad) ancho_trad = lt;
        }

        printf("  %-*s  %-*s  %12s\n",
               ancho_palabra, "Palabra", ancho_trad, "Traduccion", "Apariciones");

        printf("  ");
        for (int i = 0; i < ancho_palabra; i++) putchar('-');
        printf("  ");
        for (int i = 0; i < ancho_trad; i++) putchar('-');
        printf("  %12s\n", "-----------");

        for (int i = 0; i < total_unicas; i++) {
            printf("  %-*s  %-*s  %12d\n",
                   ancho_palabra, unicas[i].palabra,
                   ancho_trad, unicas[i].traduccion,
                   unicas[i].conteo);
        }
    }

    printf("------------------------------------------------------------\n");
    printf("  Total de palabras reservadas distintas: %d\n", total_unicas);
    printf("============================================================\n");

}
