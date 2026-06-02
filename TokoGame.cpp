#include <iostream>
#include <string>
using namespace std;

struct Game {
    int    id;
    string judul;
    string platform;
    int    tahun;
    int    stok;
};

const int MAX = 100;
Game* toko[MAX];
int jumlahGame = 0;

void tampilGaris() {
    cout << "------------------------------------------------------------" << endl;
}

void tampilGame(Game* g) {
    cout << "ID       : " << g->id << endl;
    cout << "Judul    : " << g->judul << endl;
    cout << "Platform : " << g->platform << endl;
    cout << "Tahun    : " << g->tahun << endl;
    cout << "Stok     : " << g->stok << endl;
}

void tampilSemuaGame() {
    if (jumlahGame == 0) { cout << "Toko masih kosong." << endl; return; }
    tampilGaris();
    for (int i = 0; i < jumlahGame; i++) {
        cout << "[" << i+1 << "] " << toko[i]->id << " | "
             << toko[i]->judul << " | " << toko[i]->platform
             << " | " << toko[i]->tahun
             << " | Stok: " << toko[i]->stok << endl;
    }
    tampilGaris();
}

void tambahGame(int id, string judul, string platform, int tahun, int stok) {
    Game* baru = new Game;
    baru->id = id; baru->judul = judul; baru->platform = platform;
    baru->tahun = tahun; baru->stok = stok;
    toko[jumlahGame++] = baru;
    cout << "Game berhasil ditambahkan!" << endl;
}

Game* linearSearch(string keyword) {
    for (int i = 0; i < jumlahGame; i++)
        if (toko[i]->judul.find(keyword) != string::npos)
            return toko[i];
    return nullptr;
}

void sortById() {
    for (int i = 0; i < jumlahGame - 1; i++)
        for (int j = 0; j < jumlahGame - i - 1; j++)
            if (toko[j]->id > toko[j+1]->id) {
                Game* temp = toko[j];
                toko[j] = toko[j+1];
                toko[j+1] = temp;
            }
}

Game* binarySearch(int targetId) {
    sortById();
    int kiri = 0, kanan = jumlahGame - 1;
    while (kiri <= kanan) {
        int tengah = (kiri + kanan) / 2;
        if (toko[tengah]->id == targetId) return toko[tengah];
        else if (toko[tengah]->id < targetId) kiri = tengah + 1;
        else kanan = tengah - 1;
    }
    return nullptr;
}

void bubbleSort() {
    for (int i = 0; i < jumlahGame - 1; i++)
        for (int j = 0; j < jumlahGame - i - 1; j++)
            if (toko[j]->tahun > toko[j+1]->tahun) {
                Game* temp = toko[j];
                toko[j] = toko[j+1];
                toko[j+1] = temp;
            }
    cout << "Game berhasil diurutkan berdasarkan tahun rilis (lama ke baru)." << endl;
}

void selectionSort() {
    for (int i = 0; i < jumlahGame - 1; i++) {
        int idxMin = i;
        for (int j = i + 1; j < jumlahGame; j++)
            if (toko[j]->judul < toko[idxMin]->judul) idxMin = j;
        if (idxMin != i) {
            Game* temp = toko[i];
            toko[i] = toko[idxMin];
            toko[idxMin] = temp;
        }
    }
    cout << "Game berhasil diurutkan berdasarkan judul (A-Z)." << endl;
}

void hapusGame() {
    if (jumlahGame == 0) { cout << "Toko masih kosong, tidak ada game yang bisa dihapus." << endl; return; }
    cout << "\n== HAPUS GAME ==" << endl;
    tampilSemuaGame();
    int id;
    cout << "Masukkan ID game yang ingin dihapus: "; cin >> id;
    int idxHapus = -1;
    for (int i = 0; i < jumlahGame; i++) {
        if (toko[i]->id == id) { idxHapus = i; break; }
    }
    if (idxHapus == -1) {
        cout << "Game dengan ID " << id << " tidak ditemukan." << endl;
        return;
    }
    cout << "\nGame yang akan dihapus:" << endl;
    tampilGaris();
    tampilGame(toko[idxHapus]);
    tampilGaris();
    char konfirmasi;
    cout << "Yakin ingin menghapus game ini? (y/n): "; cin >> konfirmasi;
    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        delete toko[idxHapus];
        for (int i = idxHapus; i < jumlahGame - 1; i++)
            toko[i] = toko[i + 1];
        toko[jumlahGame - 1] = nullptr;
        jumlahGame--;
        cout << "Game berhasil dihapus!" << endl;
    } else {
        cout << "Penghapusan dibatalkan." << endl;
    }
}

void inputGameBaru() {
    int id, tahun, stok; string judul, platform;
    cout << "Masukkan ID Game    : "; cin >> id; cin.ignore();
    cout << "Masukkan Judul      : "; getline(cin, judul);
    cout << "Masukkan Platform   : "; getline(cin, platform);
    cout << "Masukkan Tahun Rilis: "; cin >> tahun;
    cout << "Masukkan Stok       : "; cin >> stok;
    tambahGame(id, judul, platform, tahun, stok);
}

void menuCari() {
    int pilihan;
    cout << "\n== MENU PENCARIAN ==" << endl;
    cout << "1. Cari berdasarkan Judul (Linear Search)" << endl;
    cout << "2. Cari berdasarkan ID    (Binary Search)" << endl;
    cout << "Pilihan: "; cin >> pilihan; cin.ignore();
    if (pilihan == 1) {
        string keyword;
        cout << "Masukkan kata kunci judul: "; getline(cin, keyword);
        Game* hasil = linearSearch(keyword);
        if (hasil) { cout << "\nGame ditemukan!" << endl; tampilGaris(); tampilGame(hasil); tampilGaris(); }
        else cout << "Game tidak ditemukan." << endl;
    } else if (pilihan == 2) {
        int id; cout << "Masukkan ID game: "; cin >> id;
        Game* hasil = binarySearch(id);
        if (hasil) { cout << "\nGame ditemukan!" << endl; tampilGaris(); tampilGame(hasil); tampilGaris(); }
        else cout << "Game dengan ID " << id << " tidak ditemukan." << endl;
    } else cout << "Pilihan tidak valid." << endl;
}

void menuSort() {
    int pilihan;
    cout << "\n== MENU SORTING ==" << endl;
    cout << "1. Urutkan berdasarkan Tahun Rilis (Bubble Sort)" << endl;
    cout << "2. Urutkan berdasarkan Judul A-Z   (Selection Sort)" << endl;
    cout << "Pilihan: "; cin >> pilihan;
    if (pilihan == 1) bubbleSort();
    else if (pilihan == 2) selectionSort();
    else { cout << "Pilihan tidak valid." << endl; return; }
    tampilSemuaGame();
}

void bebaskanMemori() {
    for (int i = 0; i < jumlahGame; i++) { delete toko[i]; toko[i] = nullptr; }
}

int main() {
    tambahGame(101, "Elden Ring",            "PS5",   2022, 5);
    tambahGame(104, "God of War Ragnarok",   "PS5",   2022, 3);
    tambahGame(102, "The Witcher 3",         "PC",    2015, 4);
    tambahGame(106, "Cyberpunk 2077",        "PC",    2020, 2);
    tambahGame(103, "Red Dead Redemption 2", "Xbox",  2018, 6);
    tambahGame(105, "Hogwarts Legacy",       "PS4",   2023, 3);

    int pilihan;
    do {
        cout << "\n============================================" << endl;
        cout << "      SISTEM MANAJEMEN TOKO GAME & CD" << endl;
        cout << "==============================================" << endl;
        cout << "1. Tampilkan Semua Game" << endl;
        cout << "2. Tambah Game Baru" << endl;
        cout << "3. Cari Game" << endl;
        cout << "4. Urutkan Game" << endl;
        cout << "5. Hapus Game" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: "; cin >> pilihan;
        switch (pilihan) {
            case 1: cout << "\n== DAFTAR GAME ==" << endl; tampilSemuaGame(); break;
            case 2: cout << "\n== TAMBAH GAME BARU ==" << endl; inputGameBaru(); break;
            case 3: menuCari(); break;
            case 4: menuSort(); break;
            case 5: hapusGame(); break;
            case 0: cout << "Terima kasih! Program selesai." << endl; break;
            default: cout << "Pilihan tidak valid, coba lagi." << endl;
        }
    } while (pilihan != 0);

    bebaskanMemori();
    return 0;
}
