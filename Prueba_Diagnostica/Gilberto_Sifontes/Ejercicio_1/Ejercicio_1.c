#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

/* Coordenadas internas del tablero:
fila 0..7 (1..8) y columna 0..7 (a..h)*/

typedef struct {
    int fila;
    int columna;
} Posicion;

//Prototipo de Funciones

// Convierte una casilla tipo "c2" a índices internos.
int convertir_posicion(const char *str, Posicion *p);

// Valida un movimiento "Kxy" desde la posición actual.
int validar_movimiento(Posicion actual, const char *mov_str, Posicion *sig);

// Recorre hasta n_esperado movimientos y valida cada salto.
// Retorna 1 si toda la secuencia es válida; -cont si falla en el movimiento cont.
int verificar_secuencias(const char *pos_inicial, const char *movimientos, int n_esperado, int verbose);

int main(){
    
    // Secuencia de 500 movimientos dividida en literales adyacentes
    const char *moves =
        "Kb4 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 "
        "Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 "
        "Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 "
        "Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 "
        "Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 "
        "Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 "
        "Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 "
        "Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 "
        "Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 "
        "Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 "
        "Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 "
        "Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 "
        "Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 "
        "Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 "
        "Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 "
        "Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 "
        "Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 "
        "Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 "
        "Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 "
        "Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 "
        "Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 "
        "Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 "
        "Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 "
        "Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 "
        "Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 "
        "Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 "
        "Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 "
        "Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 "
        "Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 "
        "Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 "
        "Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 "
        "Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 "
        "Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 "
        "Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 "
        "Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 "
        "Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 "
        "Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 "
        "Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 "
        "Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 "
        "Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 "
        "Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 "
        "Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4";

    const char *cadena1 = "Kb4 Ka6 Kc5 Kb3 Kd4 Kf5 Kh4 Kg2 Ke3 Kc4";
    const char *cadena2 = "Kb4 Ka6 Kc5 Kb3 Kd4 Kf5 Kh4 Kg2 Ke3 Kc5";
    const char *cadena3 = "Kb4 Ka6 Kc5 Kb3 Kd4 Kf5 Kh4 Kg2 Ke3 Kal";
    
    printf("============================================================\n");
    printf("        MOVIMIENTOS DEL CABALLO EN AJEDREZ\n");
    printf("        Realizado por Gilberto Sifontes - V-32.416.786\n");
    printf("============================================================\n\n");
    printf("=== CASOS DE PRUEBA ===\n");

    printf("\n[CASO 1] c2 -> %s\n", cadena1);
    verificar_secuencias("c2",cadena1,10,1);

    printf("\n[CASO 2] c2 -> %s\n", cadena2);
    verificar_secuencias("c2",cadena2,10,1);

    printf("\n[CASO 3] c2 -> %s\n", cadena3);
    verificar_secuencias("c2",cadena3,10,1);

    printf("\n=== MEDICION DE TIEMPO ===\n");
    printf("[INFO] Verificando 10 iteraciones de 500 movimientos...\n\n");

    struct timespec inicio, fin;
    timespec_get(&inicio, TIME_UTC);

    int completadas = 0;
    for(int i=0; i<10; i++){
        if(verificar_secuencias("c2",moves,500,0) == 1){
            completadas++;
        }
    }

    timespec_get(&fin, TIME_UTC);

    double tiempo_segundos = (fin.tv_sec - inicio.tv_sec) + (fin.tv_nsec - inicio.tv_nsec) / 1e9;
    
    printf("  Iteraciones completadas : %d/10\n", completadas);
    printf("  Tiempo total            : %.6f s (%.3f ms)\n",
           tiempo_segundos, tiempo_segundos * 1000.0);
    printf("  Tiempo promedio         : %.8f s por iteracion\n", tiempo_segundos / 10.0);
    printf("============================================================\n\n");

    return 0;
}

// Convierte una casilla tipo "c2" a índices internos.
int convertir_posicion(const char *str, Posicion *p){
   
    if (strlen(str)<2) return 0;

    char c = tolower(str[0]);
    char f = str[1];

    if(c<'a' || c>'h' || f<'1' || f>'8'){
       return 0;
    } 

    p->columna = c - 'a';
    p->fila = f -'1';
    return 1;
}

// Retorna: 1 = correcto, -1 = movimiento ilegal, 0 = error de formato.
int validar_movimiento(Posicion actual, const char *mov_str, Posicion *sig){

   if(strlen(mov_str)<3 || (mov_str[0] !='K' && mov_str[0] != 'k')){
      return 0;
   }

   char destino_casilla[3];

   destino_casilla[0] = mov_str[1];
   destino_casilla[1] = mov_str[2];
   destino_casilla[2] = '\0';

   Posicion destino;

   if (!convertir_posicion(destino_casilla, &destino)){
     return 0;
   }

    //Verificar el movimiento del caballo
    int d_fila = abs(destino.fila - actual.fila);
    int d_columna=abs(destino.columna -actual.columna);

    if(!((d_fila == 1 && d_columna ==2) || (d_fila == 2 && d_columna ==1) ) ){
        return -1; //Movimiento Ilegal
    }

    *sig = destino;
    return 1; //Movimiento correcto;
}

// Retorna 1 si toda la secuencia es válida; -cont si falla en el movimiento cont.
int verificar_secuencias(const char *pos_inicial, const char *movimientos, int n_esperado, int verbose){
    
    Posicion actual;
    
    if(!convertir_posicion(pos_inicial, &actual)){
        if(verbose){
            printf("  [ERROR] Posicion inicial invalida: '%s' (formato a1-h8).\n", pos_inicial);
        }
        return 0;
    }

    // Se copia la cadena porque strtok modifica el texto original.
    char *copia = strdup(movimientos);
    char *token = strtok(copia, " ");
    int cont = 0;
    int result_final =1; // 1=Correcto por Defecto

    while (token != NULL){
        cont++;

        if(cont > n_esperado){
            break; //No procesar más movimientos de lo indicado
        }

        Posicion sig;
        int estado = validar_movimiento(actual, token, &sig);

        if (estado == 0){
            if(verbose){
                printf("  [FORMATO] Movimiento invalido en el paso %d/%d ('%s').\n", cont, n_esperado, token);
            }
            result_final = -cont;
            break;
        }

        if (estado == -1){
            if(verbose){
                printf("  [ERROR] Movimiento ilegal en el paso %d/%d ('%s').\n", cont, n_esperado, token);
            }
            result_final = -cont;
            break;
        }

        actual = sig;
        token = strtok(NULL," ");
    }

    free(copia);
    if(result_final == 1 && verbose){
        printf("  [OK] Secuencia valida: %d/%d movimientos correctos.\n", cont, n_esperado);
    }

    return result_final;

}