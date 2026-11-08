#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BASE 1000000000ULL
#define N_BENCHMARK 100
#define REPETICIONES 1000

typedef struct {
    uint32_t *digitos;
    int len;
    int cap;
} BigInt;

static void error_memoria(void) {
    printf("Error: no se pudo reservar memoria.\n");
    exit(1);
}

static void bi_init(BigInt *a) {
    a->cap = 1;
    a->len = 1;
    a->digitos = (uint32_t *)malloc(sizeof(uint32_t));
    if (a->digitos == NULL) {
        error_memoria();
    }
    a->digitos[0] = 0;
}

static void bi_free(BigInt *a) {
    free(a->digitos);
    a->digitos = NULL;
    a->len = 0;
    a->cap = 0;
}

static void bi_reservar(BigInt *a, int capacidad) {
    if (a->cap >= capacidad) {
        return;
    }

    int nueva_capacidad = a->cap > 0 ? a->cap : 1;
    while (nueva_capacidad < capacidad) {
        nueva_capacidad *= 2;
    }

    uint32_t *nuevos = (uint32_t *)realloc(a->digitos, (size_t)nueva_capacidad * sizeof(uint32_t));
    if (nuevos == NULL) {
        error_memoria();
    }

    a->digitos = nuevos;
    a->cap = nueva_capacidad;
}

static void bi_set_u64(BigInt *a, unsigned long long valor) {
    a->len = 0;

    if (valor == 0) {
        bi_reservar(a, 1);
        a->digitos[0] = 0;
        a->len = 1;
        return;
    }

    while (valor > 0) {
        bi_reservar(a, a->len + 1);
        a->digitos[a->len] = (uint32_t)(valor % BASE);
        a->len++;
        valor /= BASE;
    }
}

static void bi_copiar(BigInt *destino, const BigInt *origen) {
    bi_reservar(destino, origen->len);
    memcpy(destino->digitos, origen->digitos, (size_t)origen->len * sizeof(uint32_t));
    destino->len = origen->len;
}

static void bi_sumar(BigInt *a, const BigInt *b) {
    int mayor = a->len > b->len ? a->len : b->len;
    bi_reservar(a, mayor + 1);

    unsigned long long acarreo = 0;

    for (int i = 0; i < mayor; i++) {
        unsigned long long suma = acarreo;

        if (i < a->len) {
            suma += a->digitos[i];
        }
        if (i < b->len) {
            suma += b->digitos[i];
        }

        a->digitos[i] = (uint32_t)(suma % BASE);
        acarreo = suma / BASE;
    }

    a->len = mayor;

    if (acarreo > 0) {
        a->digitos[a->len] = (uint32_t)acarreo;
        a->len++;
    }
}

static void bi_multiplicar_pequeno(BigInt *a, unsigned long long multiplicador) {
    if (multiplicador == 0) {
        bi_set_u64(a, 0);
        return;
    }

    unsigned long long acarreo = 0;

    for (int i = 0; i < a->len; i++) {
        unsigned long long producto = (unsigned long long)a->digitos[i] * multiplicador + acarreo;
        a->digitos[i] = (uint32_t)(producto % BASE);
        acarreo = producto / BASE;
    }

    while (acarreo > 0) {
        bi_reservar(a, a->len + 1);
        a->digitos[a->len] = (uint32_t)(acarreo % BASE);
        a->len++;
        acarreo /= BASE;
    }
}

static int bi_es_cero(const BigInt *a) {
    return a->len == 1 && a->digitos[0] == 0;
}

static int bi_es_uno(const BigInt *a) {
    return a->len == 1 && a->digitos[0] == 1;
}

static void bi_imprimir(const BigInt *a) {
    printf("%u", (unsigned)a->digitos[a->len - 1]);

    for (int i = a->len - 2; i >= 0; i--) {
        printf("%09u", (unsigned)a->digitos[i]);
    }
}

static BigInt *crear_coeficientes(int n) {
    BigInt *coef = (BigInt *)malloc((size_t)(n + 1) * sizeof(BigInt));
    if (coef == NULL) {
        error_memoria();
    }

    for (int i = 0; i <= n; i++) {
        bi_init(&coef[i]);
    }

    bi_set_u64(&coef[0], 1);

    for (int i = 1; i <= n; i++) {
        bi_set_u64(&coef[i], 1);

        for (int j = i - 1; j >= 1; j--) {
            bi_sumar(&coef[j], &coef[j - 1]);
        }
    }

    return coef;
}

static void liberar_coeficientes(BigInt *coef, int n) {
    for (int i = 0; i <= n; i++) {
        bi_free(&coef[i]);
    }
    free(coef);
}

static void mostrar_polinomio(const BigInt *coef, int n) {
    int primero = 1;

    for (int k = n; k >= 0; k--) {
        const BigInt *c = &coef[k];

        if (bi_es_cero(c)) {
            continue;
        }

        if (!primero) {
            printf(" + ");
        }

        if (k == 0) {
            bi_imprimir(c);
        } else {
            if (!bi_es_uno(c)) {
                bi_imprimir(c);
            }
            printf("x");

            if (k > 1) {
                printf("^%d", k);
            }
        }

        primero = 0;
    }

    if (primero) {
        printf("0");
    }
}

static void evaluar_pasos(const BigInt *coef, int n, unsigned long long x) {
    BigInt resultado;
    BigInt anterior;

    bi_init(&resultado);
    bi_init(&anterior);
    bi_copiar(&resultado, &coef[n]);

    printf("Inicio: ");
    bi_imprimir(&resultado);
    printf("\n");

    int paso = 1;

    for (int k = n - 1; k >= 0; k--) {
        bi_copiar(&anterior, &resultado);
        bi_multiplicar_pequeno(&resultado, x);
        bi_sumar(&resultado, &coef[k]);

        printf("Paso %d: ", paso);
        bi_imprimir(&anterior);
        printf(" * %llu + ", x);
        bi_imprimir(&coef[k]);
        printf(" = ");
        bi_imprimir(&resultado);
        printf("\n");

        paso++;
    }

    printf("f(%llu) = ", x);
    bi_imprimir(&resultado);
    printf("\n");

    bi_free(&anterior);
    bi_free(&resultado);
}

static void benchmark(void) {
    BigInt *calentamiento = crear_coeficientes(N_BENCHMARK);
    liberar_coeficientes(calentamiento, N_BENCHMARK);

    clock_t inicio = clock();

    for (int r = 0; r < REPETICIONES; r++) {
        BigInt *coef = crear_coeficientes(N_BENCHMARK);
        liberar_coeficientes(coef, N_BENCHMARK);
    }

    clock_t fin = clock();
    double tiempo_total = (double)(fin - inicio) * 1000.0 / CLOCKS_PER_SEC;
    double tiempo_promedio = tiempo_total / REPETICIONES;

    printf("BENCHMARK\n");
    printf("Generando todas las filas 0..%d de forma acumulativa\n", N_BENCHMARK);
    printf("Repeticiones: %d\n", REPETICIONES);
    printf("Tiempo total: %.4f ms\n", tiempo_total);
    printf("Tiempo promedio: %.4f ms\n", tiempo_promedio);
}

int main(void) {
    int n;
    long long x_leido;

    printf("Ingrese n (entero >= 0): ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("n invalido.\n");
        return 1;
    }

    printf("Ingrese x (entero >= 0): ");
    if (scanf("%lld", &x_leido) != 1 || x_leido < 0 || x_leido >= (long long)BASE) {
        printf("x debe ser un entero entre 0 y %llu.\n", BASE - 1);
        return 1;
    }

    unsigned long long x = (unsigned long long)x_leido;
    BigInt *coef = crear_coeficientes(n);

    printf("\n");
    printf("n = %d, x = %llu\n", n, x);
    printf("Coeficientes: [");

    for (int k = 0; k <= n; k++) {
        bi_imprimir(&coef[k]);

        if (k < n) {
            printf(", ");
        }
    }

    printf("]\n");
    printf("\nPolinomio: ");
    mostrar_polinomio(coef, n);
    printf("\n\n");

    evaluar_pasos(coef, n, x);
    printf("\n");
    liberar_coeficientes(coef, n);

    benchmark();
    return 0;
}
