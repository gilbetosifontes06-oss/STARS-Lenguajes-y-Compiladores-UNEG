import time

N_BENCHMARK = 100
REPETICIONES = 1000


def crear_coeficientes(n):
    coef = [0] * (n + 1)
    coef[0] = 1

    for i in range(1, n + 1):
        coef[i] = 1
        for j in range(i - 1, 0, -1):
            coef[j] += coef[j - 1]

    return coef


def mostrar_polinomio(coef):
    terminos = []
    n = len(coef) - 1

    for k in range(n, -1, -1):
        c = coef[k]

        if c == 0:
            continue

        if k == 0:
            terminos.append(str(c))
        elif k == 1:
            terminos.append("x" if c == 1 else f"{c}x")
        else:
            terminos.append(f"x^{k}" if c == 1 else f"{c}x^{k}")

    return " + ".join(terminos) if terminos else "0"


def evaluar_pasos(coef, x):
    n = len(coef) - 1
    resultado = coef[n]

    print(f"Inicio: {resultado}")

    paso = 1
    for k in range(n - 1, -1, -1):
        anterior = resultado
        resultado = resultado * x + coef[k]
        print(f"Paso {paso}: {anterior} * {x} + {coef[k]} = {resultado}")
        paso += 1

    print(f"f({x}) = {resultado}")


def benchmark():
    crear_coeficientes(N_BENCHMARK)

    inicio = time.perf_counter()

    for _ in range(REPETICIONES):
        crear_coeficientes(N_BENCHMARK)

    fin = time.perf_counter()
    tiempo_total = (fin - inicio) * 1000
    tiempo_promedio = tiempo_total / REPETICIONES

    print("BENCHMARK")
    print(f"Generando todas las filas 0..{N_BENCHMARK} de forma acumulativa")
    print(f"Repeticiones: {REPETICIONES}")
    print(f"Tiempo total: {tiempo_total:.4f} ms")
    print(f"Tiempo promedio: {tiempo_promedio:.4f} ms")


def main():
    try:
        n = int(input("Ingrese n (entero >= 0): "))
        x = int(input("Ingrese x (entero >= 0): "))
    except ValueError:
        print("Entrada invalida.")
        return

    if n < 0 or x < 0:
        print("n y x deben ser enteros no negativos.")
        return

    if x >= 1_000_000_000:
        print("x debe ser menor que 1000000000.")
        return

    coef = crear_coeficientes(n)

    print()
    print(f"n = {n}, x = {x}")
    print(f"Coeficientes: {coef}")
    print(f"Polinomio: {mostrar_polinomio(coef)}")
    print()
    evaluar_pasos(coef, x)
    print()
    benchmark()


if __name__ == "__main__":
    main()
