import matplotlib.pyplot as plt
import csv
import os

FILENAME = "dane_act_dp.csv"

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
    print(f"BŁĄD: Nie znaleziono pliku '{FILENAME}'. Uruchom najpierw kod C++!")
    exit(1)

sizes = []
iter_times = []
rec_times = []
dp_times = []

try:
    with open(file_path, 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            sizes.append(int(row['n']))
            iter_times.append(float(row['iter']))
            rec_times.append(float(row['rec']))
            dp_times.append(float(row['dp']))

except KeyError as e:
    print(f"BŁĄD DANYCH: Plik CSV ma złe nagłówki lub brakuje kolumny. Szczegóły: {e}")
    exit(1)


plt.figure(figsize=(10, 6))
plt.plot(sizes, iter_times, 'g-o', label='Iterative O(n log n)', linewidth=2)
plt.plot(sizes, rec_times, 'b--s', label='Recursive O(n log n)', alpha=0.7)
plt.plot(sizes, dp_times, 'r-.x', label='Dynamic Programming O(n^2)', linewidth=2)
plt.title('Activity Selection: Porównanie Greedy vs DP')
plt.xlabel('Liczba zadań (n)')
plt.ylabel('Czas (s)')
plt.legend()
plt.grid(True, which="both", ls="-", alpha=0.4)
print("wykres 6...")
plt.show()