#include <iostream>
using namespace std;

void reverseArray(int* array, int n) {
    int *start = array; //start menunjukkan alamat indeks pertama
    int *end = array + n-1; //end menunjukkan alamat dari indeks terakhir

    while (start < end) {
        int temporary = *start; //Var temporary menyimpan nilai yang ditunjuk start
        *start = *end;
        *end = temporary;

        start++;
        end--;
    }
}

int main() {
    int array[] = {2, 3, 5, 7, 11, 13, 17};
    int n = 7;

    cout << "Array sebelum dibalik: ";
    for (int i = 0; i < n; i++)  
        cout << array[i] << " ";
    cout << endl;
    
    reverseArray(array, n);

    cout << "Array setelah dibalik: ";
    for (int i = 0; i < n; i++)  
        cout << array[i] << " ";
    cout << endl;

    int *p = array;
    cout << "\n\nAlamat memori setiap elemen" << endl;
    while ( p < array + n) {
        cout << "Nilai: " << *p << ", " << "Alamat: " << p << endl;
        p++;
    }
    return 0;
}