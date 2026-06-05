#include <iostream>
#include <fstream>
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
    if (jumlahGame >= MAX) { cout << "Kapasitas toko penuh!" << endl; return; }
    Game* baru = new Game;
    baru->id = id; baru->judul = judul; baru->platform = platform;
    baru->tahun = tahun; baru->stok = stok;
    toko[jumlahGame++] = baru;
    cout << "Game berhasil ditambahkan!" << endl;
}


Game* linearSearchRekursif(string keyword, int indeks) {
    if (indeks >= jumlahGame) return nullptr;                          
    if (toko[indeks]->judul.find(keyword) != string::npos)
        return toko[indeks];                                            
    return linearSearchRekursif(keyword, indeks + 1);                  
}

Game* binarySearchRekursif(int targetId, int kiri, int kanan) {
    if (kiri > kanan) return nullptr;                                   
    int tengah = (kiri + kanan) / 2;
    if (toko[tengah]->id == targetId) return toko[tengah];             
    if (toko[tengah]->id < targetId)
        return binarySearchRekursif(targetId, tengah + 1, kanan);      
    return binarySearchRekursif(targetId, kiri, tengah - 1);           
}

int hitungTotalStokRekursif(int indeks) {
    if (indeks >= jumlahGame) return 0;                                 
    return toko[indeks]->stok + hitungTotalStokRekursif(indeks + 1);   
}


void tampilGameByPlatformRekursif(string platform, int indeks, int& ditemukan) {
    if (indeks >= jumlahGame) return;                                   
    if (toko[indeks]->platform == platform) {
        tampilGame(toko[indeks]);
        tampilGaris();
        ditemukan++;
    }
    tampilGameByPlatformRekursif(platform, indeks + 1, ditemukan);     
}


void sortById() {
    for (int i = 0; i < jumlahGame - 1; i++)
        for (int j = 0; j < jumlahGame - i - 1; j++)
            if (toko[j]->id > toko[j+1]->id) {
                Game* temp = toko[j]; toko[j] = toko[j+1]; toko[j+1] = temp;
            }
}

void bubbleSort() {
    for (int i = 0; i < jumlahGame - 1; i++)
        for (int j = 0; j < jumlahGame - i - 1; j++)
            if (toko[j]->tahun > toko[j+1]->tahun) {
                Game* temp = toko[j]; toko[j] = toko[j+1]; toko[j+1] = temp;
            }
    cout << "Game diurutkan berdasarkan tahun rilis (lama ke baru)." << endl;
}

void selectionSort() {
    for (int i = 0; i < jumlahGame - 1; i++) {
        int idxMin = i;
        for (int j = i + 1; j < jumlahGame; j++)
            if (toko[j]->judul < toko[idxMin]->judul) idxMin = j;
        if (idxMin != i) {
            Game* temp = toko[i]; toko[i] = toko[idxMin]; toko[idxMin] = temp;
        }
    }
    cout << "Game diurutkan berdasarkan judul (A-Z)." << endl;
}

void hapusGame() {
    if (jumlahGame == 0) { cout << "Toko masih kosong." << endl; return; }
    cout << "\n== HAPUS GAME ==" << endl;
    tampilSemuaGame();
    int id;
    cout << "Masukkan ID game yang ingin dihapus: "; cin >> id;
    int idxHapus = -1;
    for (int i = 0; i < jumlahGame; i++)
        if (toko[i]->id == id) { idxHapus = i; break; }
    if (idxHapus == -1) { cout << "Game dengan ID " << id << " tidak ditemukan." << endl; return; }
    cout << "\nGame yang akan dihapus:" << endl;
    tampilGaris(); tampilGame(toko[idxHapus]); tampilGaris();
    char k;
    cout << "Yakin ingin menghapus? (y/n): "; cin >> k;
    if (k == 'y' || k == 'Y') {
        delete toko[idxHapus];
        for (int i = idxHapus; i < jumlahGame - 1; i++) toko[i] = toko[i+1];
        toko[jumlahGame - 1] = nullptr;
        jumlahGame--;
        cout << "Game berhasil dihapus!" << endl;
    } else {
        cout << "Penghapusan dibatalkan." << endl;
    }
}


void simpanKeFile(string namaFile) {
    ofstream file(namaFile);
    if (!file.is_open()) {
        cout << "Gagal membuka/membuat file \"" << namaFile << "\"." << endl;
        return;
    }
    file << jumlahGame << "\n";          
    for (int i = 0; i < jumlahGame; i++) {
        file << toko[i]->id       << "\n"
             << toko[i]->judul    << "\n"
             << toko[i]->platform << "\n"
             << toko[i]->tahun    << "\n"
             << toko[i]->stok     << "\n";
    }
    file.close();
    cout << "Data berhasil disimpan ke \"" << namaFile << "\". (" << jumlahGame << " game)" << endl;
}


void muatDariFile(string namaFile) {
    ifstream file(namaFile);
    if (!file.is_open()) {
        cout << "File \"" << namaFile << "\" tidak ditemukan." << endl;
        return;
    }
    
    for (int i = 0; i < jumlahGame; i++) { delete toko[i]; toko[i] = nullptr; }
    jumlahGame = 0;

    int n;
    file >> n;
    file.ignore();
    for (int i = 0; i < n; i++) {
        Game* g = new Game;
        file >> g->id;
        file.ignore();
        getline(file, g->judul);
        getline(file, g->platform);
        file >> g->tahun >> g->stok;
        file.ignore();
        toko[jumlahGame++] = g;
    }
    file.close();
    cout << "Data berhasil dimuat dari \"" << namaFile << "\". (" << jumlahGame << " game)" << endl;
}

void menuFile() {
    int pilihan;
    cout << "\n== MENU FILE ==" << endl;
    cout << "1. Simpan data ke file" << endl;
    cout << "2. Muat data dari file" << endl;
    cout << "Pilihan: "; cin >> pilihan; cin.ignore();
    string namaFile;
    cout << "Masukkan nama file (contoh: data_game.txt): ";
    getline(cin, namaFile);
    if      (pilihan == 1) simpanKeFile(namaFile);
    else if (pilihan == 2) muatDariFile(namaFile);
    else cout << "Pilihan tidak valid." << endl;
}


void menuCari() {
    int pilihan;
    do {
        cout << "\n== MENU PENCARIAN ==" << endl;
        cout << "1. Cari berdasarkan Judul    (Linear Search Rekursif)" << endl;
        cout << "2. Cari berdasarkan ID       (Binary Search Rekursif)" << endl;
        cout << "3. Cari berdasarkan Platform (Rekursif)" << endl;
        cout << "0. Kembali ke Menu Utama" << endl;
        cout << "Pilihan: "; cin >> pilihan; cin.ignore();

        if (pilihan == 1) {
            string keyword;
            cout << "Masukkan kata kunci judul: "; getline(cin, keyword);
            Game* hasil = linearSearchRekursif(keyword, 0);
            if (hasil) { cout << "\nGame ditemukan!" << endl; tampilGaris(); tampilGame(hasil); tampilGaris(); }
            else cout << "Game tidak ditemukan." << endl;

        } else if (pilihan == 2) {
            int id; cout << "Masukkan ID game: "; cin >> id;
            sortById();
            Game* hasil = binarySearchRekursif(id, 0, jumlahGame - 1);
            if (hasil) { cout << "\nGame ditemukan!" << endl; tampilGaris(); tampilGame(hasil); tampilGaris(); }
            else cout << "Game dengan ID " << id << " tidak ditemukan." << endl;

        } else if (pilihan == 3) {
            string platform;
            cout << "Masukkan nama platform (contoh: PS5, PC, Xbox): "; getline(cin, platform);
            int ditemukan = 0;
            cout << endl; tampilGaris();
            tampilGameByPlatformRekursif(platform, 0, ditemukan);
            if (ditemukan == 0) cout << "Tidak ada game untuk platform \"" << platform << "\"." << endl;
            else cout << "Total ditemukan: " << ditemukan << " game." << endl;

        } else if (pilihan != 0) {
            cout << "Pilihan tidak valid, silakan coba lagi." << endl;
        }
    } while (pilihan != 0);
}


void menuSort() {
    int pilihan;
    cout << "\n== MENU SORTING ==" << endl;
    cout << "1. Urutkan berdasarkan Tahun Rilis (Bubble Sort)" << endl;
    cout << "2. Urutkan berdasarkan Judul A-Z   (Selection Sort)" << endl;
    cout << "Pilihan: "; cin >> pilihan;
    if      (pilihan == 1) bubbleSort();
    else if (pilihan == 2) selectionSort();
    else { cout << "Pilihan tidak valid." << endl; return; }
    tampilSemuaGame();
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


void tampilStatistik() {
    if (jumlahGame == 0) { cout << "Toko masih kosong." << endl; return; }
    int totalStok = hitungTotalStokRekursif(0);
    cout << "\n== STATISTIK TOKO ==" << endl;
    tampilGaris();
    cout << "Jumlah game terdaftar : " << jumlahGame << endl;
    cout << "Total stok seluruh game: " << totalStok << endl;
    tampilGaris();
}


void bebaskanMemori() {
    for (int i = 0; i < jumlahGame; i++) { delete toko[i]; toko[i] = nullptr; }
}


int main() {
    tambahGame(101, "Elden Ring",            "PS5",  2022, 5);
    tambahGame(104, "God of War Ragnarok",   "PS5",  2022, 3);
    tambahGame(102, "The Witcher 3",         "PC",   2015, 4);
    tambahGame(106, "Cyberpunk 2077",        "PC",   2020, 2);
    tambahGame(103, "Red Dead Redemption 2", "Xbox", 2018, 6);
    tambahGame(105, "Hogwarts Legacy",       "PS4",  2023, 3);

    int pilihan;
    do {
        cout << "\n=============================================" << endl;
        cout << "      SISTEM MANAJEMEN TOKO GAME & CD" << endl;
        cout << "=============================================" << endl;
        cout << "1. Tampilkan Semua Game" << endl;
        cout << "2. Tambah Game Baru" << endl;
        cout << "3. Cari Game" << endl;
        cout << "4. Urutkan Game" << endl;
        cout << "5. Hapus Game" << endl;
        cout << "6. Statistik Toko (Rekursif)" << endl;
        cout << "7. Simpan / Muat File" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: "; cin >> pilihan;

        switch (pilihan) {
            case 1: cout << "\n== DAFTAR GAME ==" << endl; tampilSemuaGame(); break;
            case 2: cout << "\n== TAMBAH GAME BARU ==" << endl; inputGameBaru(); break;
            case 3: menuCari(); break;
            case 4: menuSort(); break;
            case 5: hapusGame(); break;
            case 6: tampilStatistik(); break;
            case 7: menuFile(); break;
            case 0: cout << "Terima kasih! Program selesai." << endl; break;
            default: cout << "Pilihan tidak valid, coba lagi." << endl;
        }
    } while (pilihan != 0);

    bebaskanMemori();
    return 0;
}
