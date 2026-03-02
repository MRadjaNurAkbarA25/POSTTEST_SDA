#include <iostream>
using namespace std;

int FindMin (int arr[], int ukuran, int &indeksMin) {
    int min = arr[0]; //Flag nilai terkecil
    indeksMin =0; //Flag indeks dari nilai terkecil

    for (int i = 1; i < ukuran; i++)
    {
        if (arr[i] < min) //Perbandingan nilai
        {
            min = arr[i]; //Ganti nilai min setiap kali perbandingan true
            indeksMin = i; //Ganti juga indeksnya
        }
    }
    return min;

}

int main()
{
    int A[8] = {1, 1, 2, 3, 5, 8, 13, 21}; //Ukuran array dan elemen
    int indeksMin = 0;
    /* Analisis Kompleksitas Waktu Berdasarkan Tabel dan Hitung Manual:
        Tmin    = C1 + C2 + C3n + C4n-C4 + 0 + C6n-C6 + C7n + C8 + C9
                = (C3 + C4 + C6 + C7)n + (C1 + C2 + C8 + C9 – C4 – C6)
                = 4n + 2 (fungsi linear => O(n)
        Tmax    = C1 + C2 + C3n + C4n-C4+ C5n-c5 + C6n-C6 + C7n + C8 + C9
                = (C3 + C4 + C5 + C6 + C7)n + (C1 + C2 + C8 + C9 – C4 – C5 – C6)
                = 5n + 1 (fungsi linear => O(n)
        
        Best Case  : Fungsi linear ==> O(n)
        Worst Case : Fungsi linear ==> O(n)
        Best case jika urutan pada array menaik, worst case jika urutan pada array menurun */
    int min = FindMin(A, 8, indeksMin);
    cout << "Array : ";
    for (int x : A) cout << x << " ";

    cout << "\n\nNilai mininum: " << min << endl;
    cout << "Pada indeks: " << indeksMin << endl;
    return 0;
}