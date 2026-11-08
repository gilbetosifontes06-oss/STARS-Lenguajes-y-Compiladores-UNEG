#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//Prototipo de Funciones

// Reserva y calcula los n+1 coeficientes de (x + 1)^n
long long* crear_coeficientes(int n);

// Muestra el polinomio desarrollado
void mostrar_polinomio(int n, const long long *coeficiente);

// Evalúa el polinomio en x mostrando cada término del cálculo.
void evaluar_pasos(int n, const long long *coeficiente, double x);

int main(){
    struct timespec inicio, fin;
    int n;
    double x;

    printf("============================================================\n");
    printf("        EVALUACION DEL POLINOMIO (x + 1)^n\n");
    printf("        Realizado por Gilberto Sifontes - V-32.416.786\n");
    printf("============================================================\n\n");

    printf("Ingrese el valor entero para n: ");

    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Valor de n invalido.\n");
        return 1;
    }

    printf("Ingrese el valor de x: ");
    if (scanf("%lf", &x) != 1) {
        printf("Valor de x invalido.\n");
        return 1;
    }

    long long *coeficientes = crear_coeficientes(n);

    mostrar_polinomio(n,coeficientes);

    evaluar_pasos(n,coeficientes,x);

    free(coeficientes);

    int n_rendimiento = 100;
    printf("\n------------------------------------------------------------\n");
    printf("RENDIMIENTO\n");
    printf("------------------------------------------------------------\n");
    printf("  Midiendo 1000 iteraciones para n = %d...\n", n_rendimiento);

    timespec_get(&inicio, TIME_UTC);

    for(int i=0; i<1000; i++){
        long long *coef = crear_coeficientes(n_rendimiento);
        free(coef);
    }

    timespec_get(&fin, TIME_UTC);

    double tiempo_seg = (fin.tv_sec - inicio.tv_sec) + (fin.tv_nsec - inicio.tv_nsec) / 1e9;

    printf("  n = %d | iteraciones = 1000 | tiempo = %.6f s (%.3f ms)\n",
           n_rendimiento, tiempo_seg, tiempo_seg * 1000.0);
    printf("============================================================\n");

    return 0;
}

long long* crear_coeficientes(int n){

    //Se reserva memoria dinamica para n+1 coeficientes
    long long *coeficiente = (long long*) malloc((n+1)*sizeof(long long));

    if(coeficiente == NULL){
        printf("Error en la asignacion de memoria\n");
        exit(1);
    }

    coeficiente[0] = 1; //El primer coeficiente siempre es 1
    
    // Relación de Pascal: C(n,i) = C(n,i-1) * (n-i+1) / i
    for(int i=1; i<=n; i++){
        // La división es exacta porque el producto es múltiplo de i.
        coeficiente[i] = coeficiente[i-1]*(n-i+1)/i;
    }

    return coeficiente;
}

void mostrar_polinomio(int n, const long long *coeficiente){
     
    printf("\n------------------------------------------------------------\n");
    printf("POLINOMIO\n");
    printf("------------------------------------------------------------\n");
    printf("(x + 1)^%d = ",n);

    for(int i=0; i<=n; i++){
        int potencia = n-i;

        if(coeficiente[i]==0) continue;

        //Imprimir el separador "+" entre términos
        if(i>0 && coeficiente[i]>0){
            printf(" + ");
        }

        //Imprimir coeficiente si es diferente de 1 o si es la potencia de 0
        if(coeficiente[i]!=1 || potencia == 0){
            printf("%lld",coeficiente[i]);
        }

        //Imprimir la variable x y su potencia
        if(potencia>0){
            printf("x");
            if(potencia>1){
                printf("^%d",potencia);
            }
        }
    }
    printf("\n");
}

// Función para mostrar el cálculo paso a paso para un valor de x dado
void evaluar_pasos(int n, const long long *coeficiente, double x) {
    printf("\n------------------------------------------------------------\n");
    printf("EVALUACION PASO A PASO (x = %.2f)\n", x);
    printf("------------------------------------------------------------\n");
    printf("  %-8s %12s %13s %10s\n", "Termino", "Coeficiente", "x^potencia", "Valor");
    printf("  %-8s %12s %13s %10s\n", "-------", "-----------", "-----------", "---------");

    double resultado_total = 0;

    for (int i = 0; i <= n; i++) {
        int potencia = n - i;
        
        // Calcular x elevado a la potencia
        double termino_x = 1.0;
        for (int p = 0; p < potencia; p++) {
            termino_x *= x;
        }
        
        // Cada término es coeficiente[i] * x^(n-i) y se acumula en resultado_total
        double valor_termino = coeficiente[i] * termino_x;
        resultado_total += valor_termino;

        printf("  %7d %12lld %13.4f %10.4f\n",
               i + 1, coeficiente[i], termino_x, valor_termino);
    }
    printf("  --------------------------------------------------------\n");
    printf("  Resultado final: f(%.2f) = %.4f\n", x, resultado_total);
}