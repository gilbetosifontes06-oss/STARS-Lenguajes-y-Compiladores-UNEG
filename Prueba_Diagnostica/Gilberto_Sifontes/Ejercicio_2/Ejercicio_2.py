import time

def crear_coeficientes(n):
    """Devuelve la lista de n+1 coeficientes binomiales de (x + 1)^n."""
    coef = [1]*(n+1)

    for i in range(1, n+1):
        coef[i] = coef[i-1]*(n - i + 1)//i

    return coef


def mostrar_polinomio(n, coef):
    """Imprime el polinomio desarrollado a partir de sus coeficientes."""
    print("\n------------------------------------------------------------")
    print("POLINOMIO")
    print("------------------------------------------------------------")
    print(f"(x + 1)^{n} = ", end="")

    terminos = []

    for i in range(n+1):
        potencia = n-i
        c = coef[i]

        if c==0:
            continue

        parte_coef = "" if (c==1 and potencia>0) else str(c)

        if potencia==0:
            parte_var=""
        elif potencia==1:
            parte_var= "x"
        else:
            parte_var = f"x^{potencia}"

        terminos.append(f"{parte_coef}{parte_var}")

    print(" + ".join(terminos))

def evaluar_pasos(n, coef, x):
    """Evalúa el polinomio en x mostrando el cálculo término a término."""
    print("\n------------------------------------------------------------")
    print(f"EVALUACION PASO A PASO (x = {x:.2f})")
    print("------------------------------------------------------------")
    print(f"  {'Termino':<8} {'Coeficiente':>12} {'x^potencia':>13} {'Valor':>10}")
    print(f"  {'-------':<8} {'-----------':>12} {'-----------':>13} {'---------':>10}")
    result = 0

    for i in range(n+1):
        potencia = n-i
        termino_x = x**potencia
        valor_termino = coef[i]*termino_x
        result += valor_termino
        print(f"  {i+1:>7} {coef[i]:>12} {termino_x:>13.4f} {valor_termino:>10.4f}")

    print("  --------------------------------------------------------")
    print(f"  Resultado final: f({x:.2f}) = {result:.4f}")


if __name__ == "__main__":
    print("=" * 60)
    print("        EVALUACION DEL POLINOMIO (x + 1)^n")
    print("        Realizado por Gilberto Sifontes - V-32.416.786")
    print("=" * 60)

    try:
        n = int(input("\nIngrese un valor entero n: "))

        if n<0:
            print("El valor no puede ser negativo")
            exit(1)

        x = float(input("Ingrese un valor x: "))
    except ValueError:
        print("Entrada invalida")
        exit(1)

    coeficientes = crear_coeficientes(n)

    mostrar_polinomio(n,coeficientes)

    evaluar_pasos(n,coeficientes,x)

    n_prueba = 100
    print("\n------------------------------------------------------------")
    print("RENDIMIENTO")
    print("------------------------------------------------------------")
    print(f"  Midiendo 1000 iteraciones para n = {n_prueba}...")

    inicio = time.perf_counter()

    for i in range(1000):
        crear_coeficientes(n_prueba)

    fin = time.perf_counter()

    tiempo_seg = fin - inicio
    print(f"  n = {n_prueba} | iteraciones = 1000 | tiempo = {tiempo_seg:.6f} s ({tiempo_seg*1000:.3f} ms)")
    print("=" * 60)
