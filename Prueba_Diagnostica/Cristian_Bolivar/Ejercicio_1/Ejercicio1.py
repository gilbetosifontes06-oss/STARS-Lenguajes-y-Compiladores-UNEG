import sys
import time


SECUENCIA_500 = """
Kb4 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2
Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8
Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5
Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5
Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6
Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6
Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1
Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3
Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7
Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4
Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1
Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4
Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5
Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2
Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4
Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4
Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6
Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3
Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5
Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7
Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1
Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5
Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4
"""


CASOS_ENTRADA = [
    ("a1", 4, "Kb3 Kd4 Kf5 Kh6"),
    ("h1", 10, "Kf2 Kd3 Kc5 Ka4 Kb6 Kc8 Ka7 Kb5 Kd6 Kf7"),
    ("a1", 6, "Kc2 Kd4 Kf5 Kf6 Kh7 Kg5"),
    ("a1", 5, "Kb3 Kc5 Kb7 Ka9 Kc8"),
    ("a1", 8, "Kc2 Kd4 Kf5 Kh6 Mf7 Kd8 Kb7 Kc5"),
]


def convertir_casilla(texto):
    # Convierte la notacion de ajedrez (ej. a1) a coordenadas numericas de la matriz
    if len(texto) < 2:
        raise ValueError("casilla incompleta")

    columna = texto[0].lower()
    if columna < "a" or columna > "h":
        raise ValueError("columna fuera de rango")

    fila_texto = texto[1:]
    if not fila_texto.isdigit():
        raise ValueError("fila no numerica")

    fila = int(fila_texto)
    if fila < 1 or fila > 8:
        raise ValueError("fila fuera de rango")

    return (ord(columna) - ord("a") + 1, fila)


def es_salto_de_caballo(origen, destino):
    # Verifica si el salto cumple con el movimiento en 'L' caracteristico del caballo
    diferencia_columna = abs(destino[0] - origen[0])
    diferencia_fila = abs(destino[1] - origen[1])
    return (diferencia_columna, diferencia_fila) in ((1, 2), (2, 1))


def validar_recorrido(inicio, n, cadena):
    try:
        actual = convertir_casilla(inicio)
    except ValueError:
        return "ERROR: posicion inicial invalida"

    movimientos = cadena.split()

    if len(movimientos) != n:
        return f"ERROR: n={n} pero se recibieron {len(movimientos)} movimientos"

    # Recorre cada movimiento uno a uno aplicando parada temprana si hay un error
    for numero, token in enumerate(movimientos, start=1):
        if token[0] != "K":
            return f"movimiento INCORRECTO falla letra {token[0]} no pertenece a un caballo"

        try:
            destino = convertir_casilla(token[1:])
        except ValueError:
            return f"INCORRECTO falla en el movimiento {numero}"

        if not es_salto_de_caballo(actual, destino):
            return f"INCORRECTO falla en el movimiento {numero}"

        actual = destino

    return "movimiento CORRECTO"


def ejecutar_pruebas():
    print("Parte 1: casos de entrada")
    print("=" * 40)

    for numero, (inicio, n, cadena) in enumerate(CASOS_ENTRADA, start=1):
        resultado = validar_recorrido(inicio, n, cadena)
        print(f"Caso {numero}")
        print(f"  Inicio: {inicio} | n={n}")
        print(f"  Secuencia: {cadena}")
        print(f"  Resultado: {resultado}")
        print()


def ejecutar_benchmark():
    print("Parte 2: medicion de tiempo")
    print("=" * 40)

    movimientos = SECUENCIA_500.split()

    if len(movimientos) != 500:
        print(f"ERROR: la secuencia debe tener 500 movimientos y tiene {len(movimientos)}.")
        return False

    resultado_previo = validar_recorrido("a2", 500, SECUENCIA_500)

    if resultado_previo != "movimiento CORRECTO":
        print(f"ERROR: la secuencia de 500 movimientos no es valida: {resultado_previo}")
        return False

    resultados = []
    # Toma el tiempo inicial de alta precision para la prueba de rendimiento
    inicio = time.perf_counter()

    for _ in range(10):
        resultados.append(validar_recorrido("a2", 500, SECUENCIA_500))

    fin = time.perf_counter()

    correctas = sum(1 for resultado in resultados if resultado == "movimiento CORRECTO")
    total_ms = (fin - inicio) * 1000
    promedio_ms = total_ms / 10

    print("Secuencia verificada: 500 movimientos")
    print(f"Verificaciones correctas: {correctas}/10")
    print(f"Tiempo total (10 ejecuciones): {total_ms:.4f} ms")
    print(f"Tiempo promedio por ejecucion: {promedio_ms:.4f} ms")

    if correctas != 10:
        print("ERROR: alguna verificacion no devolvio 'movimiento CORRECTO'.")
        return False

    return True


def main():
    if len(sys.argv) > 1:
        modo = sys.argv[1].lower()

        if modo == "pruebas":
            ejecutar_pruebas()
            return

        if modo == "benchmark":
            ejecutar_benchmark()
            return

        print(f"Modo no reconocido: {sys.argv[1]}")
        print("Uso: python Ejercicio1.py [pruebas|benchmark]")
        return

    print("Validacion de movimientos de caballo")
    print("=" * 40)

    inicio = input("Posicion inicial (ej. a1): ").strip()

    try:
        n = int(input("Cantidad de movimientos (n): ").strip())
    except ValueError:
        print("ERROR: n debe ser un numero entero.")
        return

    cadena = input("Movimientos separados por espacios: ").strip()

    print()
    print(validar_recorrido(inicio, n, cadena))


if __name__ == "__main__":
    main()