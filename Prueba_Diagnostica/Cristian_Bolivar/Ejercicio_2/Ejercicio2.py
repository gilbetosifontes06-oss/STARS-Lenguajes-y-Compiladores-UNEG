import sys
import time

def generar_pascal(n):
    """Genera los coeficientes de (x+1)^n usando el triángulo de Pascal."""
    fila = [1]
    for _ in range(n):
        fila = [1] + [fila[i] + fila[i+1] for i in range(len(fila)-1)] + [1]
    return fila

def mostrar_polinomio(n, coefs):
    """Muestra el polinomio expandido."""
    terminos = []
    for i, c in enumerate(coefs):
        potencia = n - i
        if potencia == 0:
            terminos.append(f"{c}")
        elif potencia == 1:
            terminos.append(f"{c}x" if c != 1 else "x")
        else:
            terminos.append(f"{c}x^{potencia}" if c != 1 else f"x^{potencia}")
    
    print(f"(x+1)^{n} = " + " + ".join(terminos))

def evaluar_paso_a_paso(n, coefs, x):
    """Muestra el cálculo paso a paso de f(x) = (x+1)^n."""
    print(f"\nEvaluando f(x) = (x+1)^{n} para x = {x}:")
    resultado_directo = (x + 1) ** n
    
    suma = 0
    for i, c in enumerate(coefs):
        potencia = n - i
        val_termino = c * (x ** potencia)
        suma += val_termino
        print(f"  Paso {i+1}: Coeficiente {c} * ({x}^{potencia}) = {val_termino}")
    
    print(f"Resultado final: {suma} (Comprobación directa: {resultado_directo})")

def ejecutar_benchmark():
    """Mide el tiempo necesario para generar n = 100 en Python."""
    print("\n--- Benchmark (n = 100) en Python ---")
    inicio = time.perf_counter()
    
    for _ in range(1000):
        generar_pascal(100)
        
    fin = time.perf_counter()
    tiempo_total = (fin - inicio) * 1000
    print(f"Tiempo total (1000 iteraciones): {tiempo_total:.4f} ms")
    print(f"Tiempo promedio por generación: {tiempo_total / 1000:.6f} ms")

if __name__ == "__main__":
    try:
        n = int(input("Ingrese el grado n (no negativo): "))
        if n < 0:
            print("Error: n debe ser no negativo.")
            sys.exit(1)
        
        coefs = generar_pascal(n)
        mostrar_polinomio(n, coefs)
        
        x = float(input("Ingrese el valor de x para evaluar: "))
        evaluar_paso_a_paso(n, coefs, x)
        
        ejecutar_benchmark()
    except ValueError:
        print("Por favor, ingrese un número entero válido para n.")