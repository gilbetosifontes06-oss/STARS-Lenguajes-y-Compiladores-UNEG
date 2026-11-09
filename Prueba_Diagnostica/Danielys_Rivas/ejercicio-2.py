import time
import math

# Si n = 100 para todo el planteamiento:
n = 100
x_dado = 1  # Valor de x para evaluar

# Generar coeficientes del polinomio (x+1)^100 usando Pascal
coeficientes = [math.comb(n, i) for i in range(n + 1)]

print(f"Coeficientes para n = {n} ")
print(f"Total de coeficientes generados: {len(coeficientes)}")
print(f"Coeficiente principal (x^{n}): {coeficientes[0]}")
print(f"Coeficiente del término lineal (x): {coeficientes[-2]}")

# Parte B: Cálculo para un x dado
# (Para n=100 se muestra el resultado directo o los primeros/últimos pasos por salubridad en consola)
print(f"\n Evaluacion de f(x) para x= {x_dado}")
resultado_directo = (x_dado + 1) ** n
print(f"Resultado de f({x_dado}) = ({x_dado} + 1)^{n} = {resultado_directo}")

# Prueba de eficiencia final solicitado para n=100
inicio = time.time()
for j in range(1000):
    j = [math.comb(n, i) for i in range(n + 1)]
fin = time.time()

print(f"\nPrueba de eficiencia (Medición de tiempo para n={n})")
print(f"Python - Tiempo (1000 iteraciones): {fin - inicio:.6f} segundos")