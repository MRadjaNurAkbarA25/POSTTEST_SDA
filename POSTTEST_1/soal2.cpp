#include <iostream>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

int main() {
    int n = 5;
    Mahasiswa daftarMhs[n];
    for (int i = 0; i < n; i++) {
        if (i > 0) cin.ignore(100, '\n'); //Abaikan hingga 100 karakter atau sampai ketemu newline
        cout << "Masukkan data mahasiswa ke- " << i + 1 << endl;
        cout << "Nama : ";
        getline(cin, daftarMhs[i].nama);
        cout << "Nim : ";
        getline(cin, daftarMhs[i].nim);
        cout << "IPK : ";
        cin >> daftarMhs[i].ipk;
    }

    float max = daftarMhs[0].ipk;
    for (int i = 1; i < n; i++) {
        if (daftarMhs[i].ipk > max) {
            max = daftarMhs[i].ipk;
        }
    }

    cout << "===Daftar Mahasiswa===" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Nama : " << daftarMhs[i].nama << ", " << "NIM : " << daftarMhs[i].nim << ", " << "IPK : " << daftarMhs[i].ipk << endl;
    }
    cout << "\n\nMahasiswa dengan IPK tertinggi: " << endl;
    for (int i = 0; i < n; i++) {
        if (daftarMhs[i].ipk == max) {
            cout << "Nama : " << daftarMhs[i].nama << ", " << "NIM : " << daftarMhs[i].nim << ", " << "IPK : " << daftarMhs[i].ipk << endl;
        }
    }
    return 0;
}