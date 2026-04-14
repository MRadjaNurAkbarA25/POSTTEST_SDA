#include <iostream>
#include <tabulate/table.hpp>
#include <cmath>
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

struct Tiket {
    string namaPenumpang;
    Kereta kereta;
    Tiket* next;
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
Kereta daftarKereta[MAX] = {
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

Tiket* queueFront = nullptr;
Tiket* queueRear = nullptr;

Tiket* stackTop = nullptr;

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

void tampilJadwal(Kereta* arr, int jumlah) {
    Table table;
    table.add_row({"No", "Nama", "Harga (Rp)", "Asal", "Tujuan", "Jam"});
    for (int i=0; i<jumlah; i++) {
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

void tambahJadwal() {
    if (n>= MAX) {
        cout << "Data penuh! Tidak bisa tambah jadwal\n";
        return;
    }
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

    daftarKereta[n] = {nomorBaru, namaBaru, hargaBaru, asalBaru, tujuanBaru, jamBaru};
    n++;
    cout << "Jadwal berhasil ditambahkan!\n";
}

void linearSearch(Kereta* arr, int jumlah, string asal, string tujuan) {
    Table table;
    table.add_row({"No", "Nama", "Harga (Rp)", "Asal", "Tujuan", "Jam"});

    bool ketemu = false;
    for (int i=0; i<jumlah; i++) {
        if ((arr+i)->asal == asal && (arr+i)->tujuan == tujuan) {
            table.add_row({
                to_string((arr+i)->nomorKereta),
                (arr+i)->namaKereta,
                to_string((arr+i)->hargaTiket),
                (arr+i)->asal,
                (arr+i)->tujuan,
                (arr+i)->jamBerangkat
            });
            ketemu = true;
        }
    }
    if (!ketemu) {
        cout << "Kereta dari " << asal << " ke " << tujuan << " tidak ditemukan!\n";
    } else {
        cout << "\nHasil pencarian: " << asal << " ke " << tujuan << "\n";
        cout << table << "\n";
    }
}

void jumpSearch(Kereta* arr, int jumlah, int x) {
    int step = sqrt(jumlah);
    int prev = 0;

    // Fase jump
    while ((arr+min(step, jumlah)-1)->nomorKereta < x) {
        prev = step;
        step += sqrt(jumlah);
        if (prev >= jumlah) {
            cout << "Kereta tidak ditemukan!\n";
            return;
        }
    }
    // Fase linear
    while ((arr+prev)->nomorKereta < x) {
        prev++;
        if (prev == min(step, jumlah)) {
            cout << "Kereta tidak ditemukan!\n";
            return;
        }
    }
    // Menampilkan hasil dalam tabel
    if ((arr+prev)->nomorKereta == x) {
        Table table;
        table.add_row({"No", "Nama", "Harga (Rp)", "Asal", "Tujuan", "Jam"});
        table.add_row({
            to_string((arr+prev)->nomorKereta),
            (arr+prev)->namaKereta,
            to_string((arr+prev)->hargaTiket),
            (arr+prev)->asal,
            (arr+prev)->tujuan,
            (arr+prev)->jamBerangkat
        });
        cout << "Kereta ditemukan!\n";
        cout << table << "\n";
    } else cout << "Kereta tidak ditemukan!\n";
}

void merge(Kereta* arr, int left, int mid, int right) {
    int n1= mid-left+1;
    int n2= right-mid;

    Kereta* L = new Kereta[n1];
    Kereta* R = new Kereta[n2];

    for (int i=0; i<n1; i++)
        *(L+i) = *(arr+left+i);
    for (int j=0; j<n2; j++)
        *(R+j) = *(arr+mid+1+j);

    int i=0, j=0, k=left;

    while (i<n1 && j<n2) {
        if((L+i)->namaKereta <= (R+j)->namaKereta) {
            *(arr+k) = *(L+i);
            i++;
        } else {
            *(arr+k) = *(R+j);
            j++;
        }
        k++;
    }

    // sisa kiri
    while (i<n1) {
        arr[k] = L[i];
        i++, k++;
    }
    // sisa kanan
    while (j<n2) {
        arr[k] = R[j];
        j++, k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(Kereta* arr, int left, int right) {
    if (left<right) {
        int mid = left + (right- left)/2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void hasilTampilSort(Kereta* arr, int jumlah, string judul) {
    cout << "\n" << judul << "\n";
    Table table;
    table.add_row({"No", "Nama", "Harga (Rp)", "Asal", "Tujuan", "Jam"});
    for (int i = 0; i < jumlah; i++) {
        table.add_row({
            to_string((arr+i)->nomorKereta),
            (arr+i)->namaKereta,
            to_string((arr+i)->hargaTiket),
            (arr+i)->asal,
            (arr+i)->tujuan,
            (arr+i)->jamBerangkat
        });
    }
    cout << table << "\n";
}

void swapKereta(Kereta *a, Kereta *b) {
    Kereta temporary = *a;
    *a = *b;
    *b = temporary;
}

void selectionSort(Kereta* arr, int jumlah, string mode) {
    for (int i=0; i<jumlah; i++) {
        int minIndex = i;

        for (int j=i+1; j<jumlah; j++) {
            if (mode == "nomor") {
                if (arr[j].nomorKereta < arr[minIndex].nomorKereta) 
                    minIndex = j;
            } else if (mode == "harga") {
                if (arr[j].hargaTiket < arr[minIndex].hargaTiket) 
                    minIndex = j;
            }
        }
        if (minIndex != i) {
            swapKereta(&arr[i], &arr[minIndex]);
        }
    }
}

void stackPush(Tiket *&top, Tiket tiket) {
    Tiket *nodeBaru = new Tiket;
    *nodeBaru = tiket;
    nodeBaru->next = top;
    top = nodeBaru;
}

void enqueue(Tiket *&front, Tiket *&rear, Tiket tiket) {
    Tiket *nodeBaru = new Tiket; 
    *nodeBaru = tiket;
    nodeBaru->next = nullptr;
    cout << nodeBaru->namaPenumpang << " masuk antrian\n";

    if (front == nullptr) {
        front = rear = nodeBaru;
        return;
    }
    rear->next = nodeBaru;
    rear = nodeBaru;
}

void dequeue(Tiket *&front, Tiket *&top) {
    if (front == nullptr) {
        cout << "-- Antrian kosong! --\n";
        return;
    }
    Tiket *temp = front;
    front = front->next;

    cout << temp->namaPenumpang << " berhasil diproses!\n";
    cout << "Rute: " << temp->kereta.asal << "->" << temp->kereta.tujuan << "\n";

    stackPush(top, *temp);
    delete temp;
}

void stackPop(Tiket *&top) {
    if (top == nullptr) {
        cout << "-- Riwayat transaksi kosong! --\n";
        return;
    }
    Tiket *temp = top;
    top = top->next;
    cout << "Riwayat tiket: " << temp->namaPenumpang << " dihapus!\n";
    delete temp;
}

void peek(Tiket *front, Tiket *top) {
    // peek queue
    if (front == nullptr) {
        cout << "Antrian kosong!\n";
    } else {
        cout << "Antrian terdepan: " << front->namaPenumpang << 
        "-" << front->kereta.namaKereta << " (" <<
        front->kereta.asal << "->" << front->kereta.tujuan << ")\n";
    }
    
    // peek stack
    if (top == nullptr) {
        cout << "Riwayat transaksi kosong!\n";
    } else {
        cout << "Transaksi terakhir: " << top->namaPenumpang <<
        "-" << top->kereta.namaKereta << " (" <<
        top->kereta.asal << "->" << top->kereta.tujuan << ")\n";
    }
}

void displayQueue(Tiket *front) {
    if (front == nullptr) {
        cout << "Antrian kosong!\n";
        return;
    }
    cout << "Daftar antrian: \n";
    Table table;
    table.add_row({"No", "Nama penumpang", "Nama kereta", "Asal", "Tujuan"});

    Tiket *ptr = front;
    int no = 1;
    while (ptr != nullptr) {
        table.add_row({
            to_string(no),
            ptr->namaPenumpang,
            ptr->kereta.namaKereta,
            ptr->kereta.asal,
            ptr->kereta.tujuan
        });
        no++;
        ptr = ptr->next;
    }
    cout << table << "\n";
}

void displayStack(Tiket *top) {
    if (top == nullptr) {
        cout << "Riwayat transaksi kosong!\n";
        return;
    }
    cout << "Daftar riwayat transaksi: \n";
    Table table;
    table.add_row({"No", "Nama penumpang", "Nama kereta", "Harga(Rp)", "Asal", "Tujuan"});

    Tiket *ptr = top;
    int no = 1;
    while (ptr != nullptr) {
        table.add_row({
            to_string(no),
            ptr->namaPenumpang,
            ptr->kereta.namaKereta,
            to_string(ptr->kereta.hargaTiket),
            ptr->kereta.asal,
            ptr->kereta.tujuan
        });
        no++;
        ptr = ptr->next;
    }
    cout << table << "\n";
}

int main() {
    while (true) {
        cout << "Sistem Manajemen Keberangkatan Kereta Api\n";
        string opsiMenu[] = {"Lihat Jadwal", "Tambah jadwal", "Cari rute kereta",
                            "Cari nomor kereta", "Urutkan nama A-Z", "Urutkan harga tiket",
                            "Antrian beli tiket", "Proses tiket", "Hapus riwayat",
                            "Lihat antrian terdepan & transaksi terakhir",
                            "Tampil antrian", "Tampil transaksi"};
        int pilihan = tampilMenu("Pilih menu: ", opsiMenu, 12);
        switch(pilihan) {
            case 1: {
                tampilJadwal(daftarKereta, n);
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
                system("cls || clear");
                break;
            }
            case 2: {
                tambahJadwal();
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
                system("cls || clear");
                break;
            }
            case 3: {
                int pilihAsal = tampilMenu("Pilih asal kereta: \n", daftarStasiun, 7);
                int pilihTujuan = tampilMenu("Pilih tujuan kereta: \n", daftarStasiun, 7);
                string asal = daftarStasiun[pilihAsal-1];
                string tujuan = daftarStasiun[pilihTujuan-1];
                linearSearch(daftarKereta, n, asal, tujuan);
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
                system("cls || clear");
                break;
            }
            case 4: {
                Kereta temp[MAX];
                for (int i=0; i<n; i++) {
                    temp[i] = daftarKereta[i];
                }
                selectionSort(temp, n, "nomor");
                int x = inputAngka("Masukkan nomor kereta: ", 101, 999);
                jumpSearch(temp, n, x);
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
                system("cls || clear");
                break;
            }
            case 5: {   
                Kereta temp[MAX];
                for (int i=0; i<n; i++) {
                    temp[i] = daftarKereta[i];
                }
                mergeSort(temp, 0, n - 1);
                hasilTampilSort(temp, n, "Jadwal Kereta (A-Z)");
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
                system("cls || clear");
                break;
            }
            case 6: {
                Kereta temp[MAX];
                for (int i=0; i<n; i++) {
                    temp[i] = daftarKereta[i];
                }
                selectionSort(temp, n, "harga");
                hasilTampilSort(temp, n, "Jadwal kereta (termurah)");
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
                system("cls || clear");
                break;
            }
            case 7: {
                string nama = inputStr("Masukkan nama penumpang: ");
                tampilJadwal(daftarKereta, n);
                int pilihKereta = inputAngka("Pilih nomor kereta (101-...): ", 101, 100+n);
                Tiket tiket;
                tiket.namaPenumpang = nama;
                tiket.kereta = daftarKereta[pilihKereta-101];
                tiket.next = nullptr;
                enqueue(queueFront, queueRear, tiket);
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
                system("cls || clear");
                break;
            }
            case 8: {
                dequeue(queueFront, stackTop);
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
                system("cls || clear");
                break;
            }
            case 9: {
                stackPop(stackTop);
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
                system("cls || clear");
                break;
            }
            case 10: {
                peek(queueFront, stackTop);
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
                system("cls || clear");
                break;
            }
            case 11: {
                displayQueue(queueFront);
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
                system("cls || clear");
                break;
            }
            case 12: {
                displayStack(stackTop);
                cout << "Tekan Enter untuk melanjutkan...";
                cin.get();
                system("cls || clear");
                break;
            }
        }
    }

    return 0;
}