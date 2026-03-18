#include <iostream>
#include <tabulate/table.hpp>
using namespace std;
using namespace tabulate;

struct Kereta{
    int nomorKereta;
    string namaKereta;
    int hargaTiket;
    string asal;
    string tujuan;
    string jamBerangkat;
};

string daftarNama[] {
    "Annesburg Express",
    "Emerald Crossroads",
    "Grizzlies Mail Train",
    "Heartland Express",
    "Rhodes Flyer",
    "Riggs Connector",
    "Saint Denis Limited",
    "Scarlet Meadows Line",
    "Valentine Star",
    "Wallace Night Rider"
};

string daftarStasiun[] {
    "Annesburg",
    "Emerald Ranch",
    "Rhodes",
    "Riggs Station",
    "Saint Denis",
    "Valentine",
    "Wallace Station"
};

const int MAX = 100;
Kereta data[MAX];

int tampilMenu(string judul, string opsi[], int jumlah) {
    int pilih;
    Table table;
    table.add_row({judul});
    for (int i=0; i < jumlah; i++) {
        table.add_row({to_string(i+1) + ". " + opsi[i]});
    }
    cout << table << "\n";
    cout << "Pilih: ";
    while (!(cin >> pilih) || pilih < 1 || pilih > jumlah) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Tidak valid!\n";
    }
    cin.ignore(100, '\n');
    return pilih;
}

bool isAngka(string s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return !s.empty();
}

int inputAngka(string pesan, int minValue, int maxValue) {
    string input;
    while (true) {
        cout << pesan;
        getline(cin, input);
        if (!isAngka(input)) {
            cout << "Harus berupa angka!\n";
        } else {
            int nilai = stoi(input);
            if (nilai < minValue) {
                cout << "Tidak boleh kurang dari " << minValue << " !\n";
            } else if (nilai > maxValue) {
                cout << "Tidak boleh lebih dari " << maxValue << " !\n";
            } else {
                return nilai;
            }
        }
    }
}

string isiJam(string pesan) {
    cout << pesan;
    int jam = inputAngka("Masukkan jam (0-23): ", 0, 23);
    int menit = inputAngka("Masukkan menit (0-59): ", 0, 59);

    string strJam = (jam < 10 ? "0" : "") + to_string(jam);
    string strMenit = (menit < 10 ? "0" : "") + to_string(menit);

    return strJam + ":" + strMenit;
}

string inputStr(string pesan) {
    string hasil;
    while (true) {
        cout << pesan;
        getline(cin, hasil);
        if (hasil != "") return hasil;
        cout << "Tidak boleh kosong!\n";
    }
}

void tampilJadwal(Kereta * arr, int n) {
    Table table;
    table.add_row({"No", "Nama", "Harga (Rp)", "Asal", "Tujuan", "Jam"});
    for (int i=0; i<n; i++) {
        table.add_row({
            to_string((arr+i)->nomorKereta),
            (arr+i)->namaKereta,
            to_string((arr+i)->hargaTiket),
            (arr+i)->asal,
            (arr+i)->tujuan,
            (arr+i)->jamBerangkat
        });
    }
    cout << table << endl;
}

void tambahJadwal(Kereta data[], int &n) {
    int nomorBaru = 100 + n + 1;

    int pilihNama = tampilMenu("Pilih nama kereta: \n", daftarNama, 10);
    string namaBaru = daftarNama[pilihNama-1];

    int hargaBaru = inputAngka("Masukkan harga tiket: ", 1, 2000000000);

    int pilihAsal = tampilMenu("Pilih asal kereta: \n", daftarStasiun, 7);
    string asalBaru = daftarStasiun[pilihAsal-1];

    int pilihTujuan;
    string tujuanBaru;
    while (true) {
        pilihTujuan = tampilMenu("Pilih tujuan kereta: \n", daftarStasiun, 7);
        if (pilihAsal == pilihTujuan) {
            cout << "Asal dan tujuan tidak boleh sama!\n";
            continue;
        }
        tujuanBaru = daftarStasiun[pilihTujuan - 1];
        break;
    }

    string jamBaru = isiJam("Masukkan waktu keberangkatan: \n");

    data[n] = {nomorBaru, namaBaru, hargaBaru, asalBaru, tujuanBaru, jamBaru};
    n++;
    cout << "Jadwal berhasil ditambahkan!\n";
}

int main() {
    Kereta data[MAX] = {
    //  nomor   nama                    harga   asal                tujuan              jam
        {101, "Annesburg Express",      45000, "Annesburg",       "Emerald Ranch",   "08:00"},
        {102, "Rhodes Flyer",           30000, "Rhodes",          "Riggs Station",   "17:00"},
        {103, "Emerald Crossroads",     35000, "Emerald Ranch",   "Emerald Rhodes",  "15:30"},
        {104, "Riggs Connector",        25000, "Riggs Station",   "Saint Denis",     "06:00"},
        {105, "Saint Denis Limited",    55000, "Saint Denis",     "Valentine",       "09:15"},
        {106, "Valentine Star",         40000, "Valentine",       "Wallace Station", "20:00"},
        {107, "Wallace Night Rider",    30000, "Wallace Station", "Annesburg",       "11:45"},
        {108, "Heartland Express",      20000, "Valentine",       "Saint Denis",     "05:30"},
        {109, "Scarlet Meadows Line",   35000, "Rhodes",          "Valentine",       "13:00"},
        {110, "Grizzlies Mail Train",   50000, "Annesburg",       "Riggs Station",   "07:20"},
    };
    int n = 10;
    while (true) {
        cout << "Sistem Manajemen Keberangkatan Kereta Api\n";
        string opsiMenu[] = {"Lihat Jadwal", "Tambah jadwal"};
        int pilihan = tampilMenu("Pilih menu: ", opsiMenu, 2);
        switch(pilihan) {
            case 1: {
                tampilJadwal(data, n);
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
                system("cls || clear");
                break;
            }
            case 2: {
                tambahJadwal(data, n);
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
                system("cls || clear");
                break;
            }
        }
    }

    return 0;
}