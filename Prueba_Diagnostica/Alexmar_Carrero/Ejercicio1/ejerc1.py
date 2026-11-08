import sys
import time
import os

# --- CONSTANTES DE FORMATO ---
SEPARADOR = "============================================================"

EJEMPLOS = [
    ("a1", 4, "Kc2 Kd4 Kb3 Kc5"),
    ("a1", 4, "Kc2 Kd4 Kb4 Kc5"),
    ("a2", 5, "Kc3 Ke4 Kf6 Ke8 Kg7"),
    ("a2", 5, "Kc8 Ke4 Kf6 Ke8 Kg7"),
    ("a8", 2, "Kb6 Kd7"),
    ("a8", 2, "Kb6 Kb7"),
    ("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Kb4"),
    ("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Qb4"),
    ("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kh6 Kb4")
]

# --- LÓGICA DEL JUEGO ---

def es_posicion_valida(pos):
    """Verifica si una posición tipo 'a1' es válida en el tablero."""
    if len(pos) != 2:
        return False
    col, fila = pos[0], pos[1]
    return 'a' <= col <= 'h' and '1' <= fila <= '8'

def es_salto_de_caballo(desde, hasta):
    """Verifica si el movimiento es un salto de caballo válido."""
    dif_col = abs(ord(desde[0]) - ord(hasta[0]))
    dif_fila = abs(int(desde[1]) - int(hasta[1]))
    return (dif_col == 1 and dif_fila == 2) or (dif_col == 2 and dif_fila == 1)

def verificar(ak, n, secuencia):
    """Valida toda la secuencia de movimientos y retorna un string con el resultado."""
    if not es_posicion_valida(ak):
        return "INCORRECTO: posicion inicial invalida."

    movimientos = secuencia.strip().split()

    if len(movimientos) != n:
        return f"INCORRECTO: se esperaban {n} movimientos y se recibieron {len(movimientos)}."

    posicion_actual = ak

    # enumerate(..., start=1) nos da el índice empezando desde 1
    for i, mov in enumerate(movimientos, start=1):
        pieza = mov[0]

        if pieza != 'K':
            return f"INCORRECTO falla letra {pieza} no pertenece a un caballo."

        nueva_posicion = mov[1:]

        if not es_posicion_valida(nueva_posicion):
            return f"INCORRECTO falla en el movimiento {i}."

        if not es_salto_de_caballo(posicion_actual, nueva_posicion):
            return f"INCORRECTO falla en el movimiento {i}."

        posicion_actual = nueva_posicion

    return "movimiento CORRECTO."

# --- INTERFAZ Y PRESENTACIÓN ---

def mostrar_titulo(titulo):
    espacios = max(0, (len(SEPARADOR) - len(titulo)) // 2)
    print(f"\n{SEPARADOR}")
    print(f"{' ' * espacios}{titulo}")
    print(f"{SEPARADOR}")

def mostrar_resultado(resultado):
    print(f"  Resultado        : {resultado}")

def ejecutar_benchmark():
    mostrar_titulo("BENCHMARK")

    archivo = "movimientos_500.txt"
    if not os.path.exists(archivo):
        print(f"No se pudo leer el archivo {archivo}")
        return

    with open(archivo, "r", encoding="utf-8") as f:
        secuencia = f.read()

    print(f"  Archivo          : {archivo}")
    print("  Posicion inicial : a2")
    print("  Movimientos      : 500")
    print("  Repeticiones     : 10\n")

    tiempo_total = 0.0
    ultimo_resultado = ""

    for i in range(10):
        # perf_counter es el equivalente preciso a nanoTime en Python
        inicio = time.perf_counter()
        ultimo_resultado = verificar("a2", 500, secuencia)
        fin = time.perf_counter()

        tiempo_ms = (fin - inicio) * 1000
        tiempo_total += tiempo_ms

        print(f"Iteracion {i+1:2d}/10 -> {ultimo_resultado} | Tiempo: {tiempo_ms:.4f} ms")

    print(f"\n{SEPARADOR}")
    print(f"{'RESUMEN':^60}")
    print(f"{SEPARADOR}")
    print(f"  Resultado final  : {ultimo_resultado}")
    print(f"  Tiempo total     : {tiempo_total:.4f} ms")
    print(f"  Tiempo promedio  : {tiempo_total / 10:.4f} ms\n")

# --- PUNTO DE ENTRADA ---

if __name__ == "__main__":
    # Si se pasan argumentos por consola (ej: python ejercicio1.py a1 4 "Kc2 Kd4")
    if len(sys.argv) >= 4:
        ak = sys.argv[1]
        n = int(sys.argv[2])
        secuencia = " ".join(sys.argv[3:])
        mostrar_resultado(verificar(ak, n, secuencia))
        sys.exit(0)

    # Flujo normal (Ejemplos y Benchmark)
    mostrar_titulo("EJERCICIO 1")
    mostrar_titulo("EJEMPLOS DEL ENUNCIADO")

    for i, (ak, n, secuencia) in enumerate(EJEMPLOS, start=1):
        print(f"Caso {i}/{len(EJEMPLOS)}")
        print(f"  Posicion inicial : {ak}")
        print(f"  Movimientos      : {n}")
        print(f"  Secuencia        : {secuencia}")
        mostrar_resultado(verificar(ak, n, secuencia))
        print()

    ejecutar_benchmark()