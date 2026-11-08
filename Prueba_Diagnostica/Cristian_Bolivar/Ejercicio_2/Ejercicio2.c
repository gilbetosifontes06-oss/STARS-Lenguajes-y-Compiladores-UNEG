#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Genera los coeficientes usando memoria dinámica y el triángulo de Pascal
long long* generar_pascal(int n) {
    // Asignación dinámica de memoria para n+1 elementos
    long long* fila = (long long*)malloc((n + 1) * sizeof(long long));
    if (fila == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        exit(1);
    }
    
    fila[0] = 1;
    for (int i = 1; i <= n; i++) {
        fila[i] = 0;
    }

    // Construcción iterativa del triángulo de Pascal
    for (int i = 1; i <= n; i++) {
        for (int j = i; j > 0; j--) {
            fila[j] = fila[j] + fila[j - 1];
        }
    }
    return fila;
}

// Muestra el polinomio expandido en pantalla
void mostrar_polinomio(int n, long long* coefs) {
    printf("(x+1)^%d = ", n);
    for (int i = 0; i <= n; i++) {
        int potencia = n - i;
        long long c = coefs[i];
        
        if (i > 0 && c > 0) printf(" + ");

        if (potencia == 0) {
            printf("%lld", c);
        } else if (potencia == 1) {
            if (c == 1) printf("x");
            else printf("%lldx", c);
        } else {
            if (c == 1) printf("x^%d", potencia);
            else printf("%lldx^%d", c, potencia);
        }
    }
    printf("\n");
}

// Evalúa el polinomio paso a paso para un valor de x dado
void evaluar_paso_a_paso(int n, long long* coefs, double x) {
    printf("\nEvaluando f(x) = (x+1)^%d para x = %.2f:\n", n, x);
    double suma = 0;
    
    for (int i = 0; i <= n; i++) {
        int potencia = n - i;
        long long c = coefs[i];
        
        double x_pot = 1;
        for (int p = 0; p < potencia; p++) {
            x_pot *= x;
        }
        
        double termino = c * x_pot;
        suma += termino;
        printf("  Termino %d: %lld * (%.2f^%d) = %.4f\n", i + 1, c, x, potencia, termino);
    }
    printf("Resultado final f(x) = %.4f\n", suma);
}

// Benchmark comparativo para n = 100
void ejecutar_benchmark() {
    printf("\n--- Benchmark (n = 100) en C ---\n");
    clock_t inicio = clock();
    
    for (int k = 0; k < 1000; k++) {
        long long* coefs = generar_pascal(100);
        free(coefs); // Liberación de memoria en cada iteración
    }
    
    clock_t fin = clock();
    double tiempo_total = ((double)(fin - inicio) * 1000.0) / CLOCKS_PER_SEC;
    
    printf("Tiempo total (1000 iteraciones): %.4f ms\n", tiempo_total);
    printf("Tiempo promedio por generación: %.6f ms\n", tiempo_total / 1000.0);
}

int main() {
    int n;
    double x;

    printf("Ingrese el grado n (no negativo): ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Entrada invalida.\n");
        return 1;
    }

    // Uso de memoria dinámica solicitada en la práctica
    long long* coefs = generar_pascal(n);
    mostrar_polinomio(n, coefs);

    printf("Ingrese el valor de x para evaluar: ");
    if (scanf("%lf", &x) != 1) {
        printf("Entrada invalida.\n");
        free(coefs);
        return 1;
    }

    evaluar_paso_a_paso(n, coefs, x);
    ejecutar_benchmark();

    // Liberación final de la memoria dinámica
    free(coefs);
    return 0;
}