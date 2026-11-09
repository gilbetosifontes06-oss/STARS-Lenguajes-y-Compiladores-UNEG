import time

def validar_secuencia(pos_inicial, movimientos):
    col_map = {'a': 1, 'b': 2, 'c': 3, 'd': 4, 'e': 5, 'f': 6, 'g': 7, 'h': 8}
    curr_c = col_map[pos_inicial[0]]
    curr_f = int(pos_inicial[1])

    for i, mov in enumerate(movimientos):
        if len(mov) < 3 or mov[0] != 'K':
            return False, f"falla letra {mov[0] if len(mov)>0 else ''} no pertenece a un caballo", i + 1
        
        c_dest, f_dest = mov[1], mov[2]
        if c_dest not in col_map or not f_dest.isdigit() or not (1 <= int(f_dest) <= 8):
            return False, "fuera de limites", i + 1

        nc, nf = col_map[c_dest], int(f_dest)
        dc, df = abs(nc - curr_c), abs(nf - curr_f)

        if not ((dc == 1 and df == 2) or (dc == 2 and df == 1)):
            return False, "falla en el movimiento", i + 1

        curr_c, curr_f = nc, nf

    return True, "movimiento CORRECTO", 0

# Lista completa de los 500 movimientos indicados en la prueba (movimiento inicial a2)
movimientos_500 = [
    "Kb4", "Ka6", "Kc5", "Ka4", "Kc3", "Ka2", "Kc1", "Ke2", "Kg1", "Kh3", "Kg5", "Ke6", "Kc7", "Ka8", "Kc7", "Kb5", "Kd6", "Kb7", "Ka5", "Kc4",
    "Ka3", "Kc2", "Ka1", "Kc2", "Kb4", "Ka6", "Kb8", "Kd7", "Kb6", "Ka8", "Kc7", "Ka6", "Kc5", "Ka4", "Kc3", "Ka2", "Kc1", "Ke2", "Kg3", "Kh5",
    "Kg7", "Ke8", "Kc7", "Ka8", "Kc7", "Kb5", "Kd4", "Kb3", "Ka1", "Kc2", "Ka3", "Kc4", "Ka5", "Kc6", "Ka7", "Kc8", "Ka7", "Kc6", "Ka5", "Kc4",
    "Ka3", "Kc2", "Ka1", "Kc2", "Kb4", "Kd5", "Kb6", "Ka8", "Kc7", "Ka6", "Kc5", "Ka4", "Kc3", "Ka2", "Kc1", "Ke2", "Kg1", "Kh3", "Kg5", "Ke6",
    "Kc5", "Ka4", "Kc3", "Ka2", "Kc1", "Ke2", "Kg3", "Kh5", "Kg7", "Ke8", "Kc7", "Ka8", "Kc7", "Kb5", "Kd6", "Kb7", "Ka5", "Kc4", "Ka3", "Kc2",
    "Ka1", "Kc2", "Kb4", "Ka6", "Kb8", "Kd7", "Kb6", "Ka8", "Kc7", "Ka6", "Kc5", "Ka4", "Kc3", "Ka2", "Kc1", "Ke2", "Kg3", "Kh5", "Kg7", "Ke8",
    "Kc7", "Ka8", "Kc7", "Kb5", "Kd4", "Kb3", "Ka1", "Kc2", "Ka3", "Kc4", "Ka5", "Kc6", "Ka7", "Kc8", "Ka7", "Kc6", "Ka5", "Kc4", "Ka3", "Kc2",
    "Ka1", "Kc2", "Kb4", "Kd5", "Kb6", "Ka8", "Kc7", "Ka6", "Kc5", "Ka4", "Kc3", "Ka2", "Kc1", "Ke2", "Kg1", "Kh3", "Kg5", "Ke6", "Kc5", "Ka4",
    "Kc3", "Ka2", "Kc1", "Ke2", "Kg3", "Kh5", "Kg7", "Ke8", "Kc7", "Ka8", "Kc7", "Kb5", "Kd6", "Kb7", "Ka5", "Kc4", "Ka3", "Kc2", "Ka1", "Kc2",
    "Kb4", "Ka6", "Kb8", "Kd7", "Kb6", "Ka8", "Kc7", "Ka6", "Kc5", "Ka4", "Kc3", "Ka2", "Kc1", "Ke2", "Kg3", "Kh5", "Kg7", "Ke8", "Kc7", "Ka8",
    "Kc7", "Kb5", "Kd4", "Kb3", "Ka1", "Kc2", "Ka3", "Kc4", "Ka5", "Kc6", "Ka7", "Kc8", "Ka7", "Kc6", "Ka5", "Kc4", "Ka3", "Kc2", "Ka1", "Kc2",
    "Kb4", "Kd5", "Kb6", "Ka8", "Kc7", "Ka6", "Kc5", "Ka4", "Kc3", "Ka2", "Kc1", "Ke2", "Kg1", "Kh3", "Kg5", "Ke6", "Kc5", "Ka4", "Kc3", "Ka2",
    "Kc1", "Ke2", "Kg3", "Kh5", "Kg7", "Ke8", "Kc7", "Ka8", "Kc7", "Kb5", "Kd6", "Kb7", "Ka5", "Kc4", "Ka3", "Kc2", "Ka1", "Kc2", "Kb4", "Ka6",
    "Kb8", "Kd7", "Kb6", "Ka8", "Kc7", "Ka6", "Kc5", "Ka4", "Kc3", "Ka2", "Kc1", "Ke2", "Kg3", "Kh5", "Kg7", "Ke8", "Kc7", "Ka8", "Kc7", "Kb5",
    "Kd4", "Kb3", "Ka1", "Kc2", "Ka3", "Kc4", "Ka5", "Kc6", "Ka7", "Kc8", "Ka7", "Kc6", "Ka5", "Kc4", "Ka3", "Kc2", "Ka1", "Kc2", "Kb4", "Kd5",
    "Kb6", "Ka8", "Kc7", "Ka6", "Kc5", "Ka4", "Kc3", "Ka2", "Kc1", "Ke2", "Kg1", "Kh3", "Kg5", "Ke6", "Kc5", "Ka4", "Kc3", "Ka2", "Kc1", "Ke2",
    "Kg3", "Kh5", "Kg7", "Ke8", "Kc7", "Ka8", "Kc7", "Kb5", "Kd6", "Kb7", "Ka5", "Kc4", "Ka3", "Kc2", "Ka1", "Kc2", "Kb4", "Ka6", "Kb8", "Kd7",
    "Kb6", "Ka8", "Kc7", "Ka6", "Kc5", "Ka4", "Kc3", "Ka2", "Kc1", "Ke2", "Kg3", "Kh5", "Kg7", "Ke8", "Kc7", "Ka8", "Kc7", "Kb5", "Kd4", "Kb3",
    "Ka1", "Kc2", "Ka3", "Kc4", "Ka5", "Kc6", "Ka7", "Kc8", "Ka7", "Kc6", "Ka5", "Kc4", "Ka3", "Kc2", "Ka1", "Kc2", "Kb4", "Kd5", "Kb6", "Ka8",
    "Kc7", "Ka6", "Kc5", "Ka4"
]

inicio = time.time()
for _ in range(10):
    valido, mensaje, idx = validar_secuencia("a2", movimientos_500)
fin = time.time()

tiempo_total = fin - inicio
print(f"Estado de validacion: {mensaje} (Indice de falla: {idx})")
print(f"Tiempo total al verificar 10 veces los 500 movimientos: {tiempo_total:.6f} segundos")