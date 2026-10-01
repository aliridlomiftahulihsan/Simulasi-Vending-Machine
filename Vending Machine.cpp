#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

const int BARIS = 3;
const int KOLOM = 3;

struct Produk {
    string nama;
    int harga;
    int stok;
};

int inputAngkaValid(string pesan) {
    int nilai;
    while (true) {
        cout << pesan;
        if (cin >> nilai) {
            return nilai;
        }
        else {
            cout << "Input tidak valid! Harus berupa angka. Silakan coba lagi.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void TampilkanVendingMachine(Produk rak[BARIS][KOLOM]) {
    cout << "\n===========================================================\n";
    cout << "                    VENDING MACHINE                       \n";
    cout << "===========================================================\n";

    for (int i = 0; i < BARIS; i++) {
        for (int j = 0; j < KOLOM; j++) {
            cout << "[" << i + 1 << "," << j + 1 << "] "
                << setw(10) << left << rak[i][j].nama
                << " Rp" << rak[i][j].harga
                << " (Stok: " << rak[i][j].stok << ")\t";
        }
        cout << "\n\n";
    }
    cout << "-----------------------------------------------------------\n";
}

int main() {
    Produk rak[BARIS][KOLOM] = {
        {{"Cola", 5000, 3},    {"Sprite", 5000, 2},   {"Fanta", 5000, 5}},
        {{"Kopi", 7000, 4},    {"Teh", 4000, 1},      {"Air Mineral", 3000, 10}},
        {{"Chips", 8000, 2},   {"Cokelat", 10000, 3}, {"Biskuit", 6000, 4}}
    };

    char pilihan;
    int inputBaris, inputKolom, uang;

    while (true) {
        TampilkanVendingMachine(rak);

        cout << "Apakah Anda ingin membeli produk? (y/n): ";
        cin >> pilihan;

        if (pilihan == 'n' || pilihan == 'N') {
            break;
        }
        else if (pilihan != 'y' && pilihan != 'Y') {
            cout << "\nPilihan tidak valid! Masukkan 'y' atau 'n'.\n";
            continue;
        }

        cout << "\nPilih produk yang ingin dibeli:\n";
        inputBaris = inputAngkaValid("Masukkan Baris (1-3): ");
        inputKolom = inputAngkaValid("Masukkan Kolom (1-3): ");

        if (inputBaris < 1 || inputBaris > BARIS || inputKolom < 1 || inputKolom > KOLOM) {
            cout << "\n[!] Posisi produk tidak ada! Pilih baris & kolom antara 1 - 3.\n";
        }
        else {
            int b = inputBaris - 1;
            int k = inputKolom - 1;

            if (rak[b][k].stok <= 0) {
                cout << "\n[!] Maaf, stok " << rak[b][k].nama << " sedang HABIS!\n";
            }
            else {
                cout << "\nAnda memilih: " << rak[b][k].nama << " (Harga: Rp" << rak[b][k].harga << ")\n";
                uang = inputAngkaValid("Masukkan uang Anda: Rp");

                if (uang < rak[b][k].harga) {
                    cout << "\n[!] Uang tidak cukup! Transaksi dibatalkan.\n";
                }
                else {
                    rak[b][k].stok--;
                    int kembalian = uang - rak[b][k].harga;

                    cout << "\n--- TRANSAKSI BERHASIL ---";
                    cout << "\nSilakan ambil " << rak[b][k].nama << " Anda.";
                    cout << "\nKembalian: Rp" << kembalian << "\n";
                }
            }
        }
    }

    cout << "\nTerima kasih telah berkunjung!\n";
    return 0;
}