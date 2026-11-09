#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Funcion para generar los coeficientes usando memoria dinamica
double* generar_pascal_dinamico(int n) {
    double *fila = (double*) malloc((n + 1) * sizeof(double));
    if (!fila) {
        return NULL;
    }

    fila[0] = 1.0;
    for (int i = 1; i <= n; i++) {
        fila[i] = fila[i - 1] * (n - i + 1) / i;
    }
    return fila;
}

int main() {
    int n = 100;
    int x_dado = 1;  // Valor de x

    //Generar coeficientes del polinomio usando memoria dinamica
    double *coeficientes = generar_pascal_dinamico(n);
    if (coeficientes == NULL) return 1;

    printf("Coeficiente para n = %d ---\n", n);
    printf("Total de coeficientes generados: %d\n", n + 1);
    printf("Coeficiente principal (x^%d): %.0f\n", n, coeficientes[0]);
    printf("Coeficiente del termino lineal (x): %.0f\n", coeficientes[n - 1]);

    // Calculo para un x dado
    printf("\n Evaluar f(x) para x = %.0f ---\n", x_dado);
    double resultado_directo = pow(x_dado + 1.0, (double)n);
    printf("Resultado de f(%.0f) = (%.0f + 1)^%d = %.0f\n", x_dado, x_dado, n, resultado_directo);

    // Prueba de eficiencia final solicitada para n=100
    clock_t inicio = clock();
    double *coef_bench = NULL;

    for (int iter = 0; iter < 1000; iter++) {
        if (coef_bench) free(coef_bench);
        coef_bench = generar_pascal_dinamico(n);
    }

    clock_t fin = clock();
    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("\n--- Prueba de eficiencia (Medicion de tiempo para n=%d)\n", n);
    printf("C - Tiempo (1000 iteraciones): %.6f segundos\n", tiempo);

    // Liberar la memoria dinamica utilizada
    free(coeficientes);
    if (coef_bench) free(coef_bench);

    return 0;
}
