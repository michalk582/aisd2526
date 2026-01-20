import matplotlib.pyplot as plt
import csv
import os


FILENAME = "dane_cut_rod.csv"
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
    print(f"błąd")
    exit(1)

sizes = []
naive_times = []
memo_times = []
iter_times = []

try:
    with open(file_path, 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            n = int(row['n'])
            t_naive = float(row['naive'])
            t_memo = float(row['memo'])
            t_iter = float(row['iter'])
            sizes.append(n)
            memo_times.append(t_memo)
            iter_times.append(t_iter)
            if t_naive > 0:
                naive_times.append(t_naive)
            else:
                naive_times.append(None)

except KeyError as e:
    print(f"BLAD DANYCH: Nie znaleziono kolumny {e}. Sprawdź plik CSV.")
    exit(1)

plt.figure(figsize=(10, 6))
clean_n_naive = [s for s, t in zip(sizes, naive_times) if t is not None]
clean_t_naive = [t for t in naive_times if t is not None]

if clean_n_naive:
    plt.plot(clean_n_naive, clean_t_naive, 'r-o', label='Naiwna')

plt.plot(sizes, memo_times, 'b-x', label='Memoized')
plt.plot(sizes, iter_times, 'g-s', label='Iteracyjna')

plt.title('Porównanie wydajności: Cięcie Pręta (Cut Rod)')
plt.xlabel('Długość pręta (n)')
plt.ylabel('Czas (s) (używamy skali logarytmicznej)')
plt.yscale('log')
plt.legend()
plt.grid(True, which="both", ls="-", alpha=0.4)
print("wykres 2...")
plt.show()