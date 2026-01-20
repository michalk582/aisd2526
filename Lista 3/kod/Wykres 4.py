import matplotlib.pyplot as plt
import csv
import os

# 1. ZMIANA: Nazwa pliku wygenerowanego przez Zadanie 5
FILENAME = "dane_lcs.csv"

def znajdz_plik_smart():
    print(f"Szukam pliku '{FILENAME}'...")
    print(f"Katalog roboczy Pythona to: {os.getcwd()}")

    sciezki = [
        FILENAME,
        os.path.join("cmake-build-debug", FILENAME),
        os.path.join("..", "cmake-build-debug", FILENAME),
        os.path.join("..", FILENAME)
    ]

    for sciezka in sciezki:
        if os.path.exists(sciezka):
            print(f"--> SUKCES! Znaleziono plik tutaj: {sciezka}")
            return sciezka

    return None

file_path = znajdz_plik_smart()

if not file_path:
    print(f"BŁĄD: Nie znaleziono pliku '{FILENAME}'. Uruchom najpierw C++ (Zadanie_5)!")
    exit(1)

sizes = []
iter_times = []
rec_times = []

try:
    with open(file_path, 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            n = int(row['n'])
            t_iter = float(row['iter'])
            t_rec = float(row['rec'])

            sizes.append(n)
            iter_times.append(t_iter)

            # W C++ zapisywaliśmy -1.0 dla pominiętych testów rekurencji
            if t_rec > 0:
                rec_times.append(t_rec)
            else:
                rec_times.append(None)

except KeyError:
    print("BŁĄD DANYCH: Plik CSV ma złe nagłówki (oczekiwano: n, iter, rec).")
    exit(1)

# --- RYSOWANIE WYKRESU ---
plt.figure(figsize=(10, 6))

# 2. ZMIANA: Etykieta dla wersji Iteracyjnej (Tablicowanie)
plt.plot(sizes, iter_times, 'g-o', label='Iteracyjna (Tablicowanie) O(n^2)')

# Filtrujemy dane dla rekurencji (usuwamy None)
clean_n_rec = [s for s, t in zip(sizes, rec_times) if t is not None]
clean_t_rec = [t for t in rec_times if t is not None]

# 3. ZMIANA: Etykieta dla wersji Rekurencyjnej (Memoizacja)
plt.plot(clean_n_rec, clean_t_rec, 'b--x', label='Rekurencyjna (Memoizacja) O(n^2)')

# 4. ZMIANA: Tytuły i opisy osi
plt.title('Porównanie wydajności: Longest Common Subsequence (LCS)')
plt.xlabel('Długość napisów (n)')
plt.ylabel('Czas (s)')

plt.legend()
plt.grid(True, which="both", ls="-", alpha=0.4)

print("Wyświetlam wykres...")
plt.show()