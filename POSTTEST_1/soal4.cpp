#include <iostream>
using namespace std;

void swap(int *a, int *b) {
    int temporary = *a;
    *a = *b;
    *b = temporary;
}

int main() {
    int x;
    int y;

    cout << "Masukkan nilai satu: ";
    cin >> x;
    cout << "Masukkan nilai dua: ";
    cin >> y;

    cout << "Nilai sebelum pertukaran" << endl; 
    cout << "x = " << x << " " << "y = " << y;

    swap(&x, &y);

    cout << "\nNilai setelah pertukaran" << endl;
    cout << "x = " << x << " " << "y = " << y;
    return 0;
}
