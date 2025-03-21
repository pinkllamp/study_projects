#include <iostream>
using namespace std;

float A, B, C, D, F, X, Y, Z;

void Kvadrat () {
    Y = X*X; // X,Y - глобальные
}
void Summa (float & Z) {
    Z = X + Y; // X,Y - глобальные
}

int main() {
    cout << "Введите 4 целых числа: ";
    cin >> A >> B >> C >> D;
    cout << "A = " << A << ", B = " << B << ", C = " << C << ", D = " << D << endl;

    cout << "1) A^2 = " << A << "^2 = ";
    X = A; Kvadrat (); A = Y;   //A = A^2
    cout << A << endl;

    cout << "2) B^2 = " << B << "^2 = ";
    X = B; Kvadrat (); B = Y;   //B = B^2
    cout << B << endl;

    cout << "3) A^2 + B^2 = " << A << " + " << B << " = ";
    X = A; Summa(A);        // A = A^2 + B^2
    cout << A << endl;

    cout << "4) (A^2 + B^2)^2 = " << A << "^2 = ";
    X = A; Kvadrat (); A = Y;   //A = (A^2 + B^2)^2
    cout << A << endl << "\n";

    cout << "5) C^2 = " << C << "^2 = ";
    X = C; Kvadrat (); C = Y;   //C = C^2
    cout << C << endl;

    cout << "6) D^2 = " << D << "^2 = ";
    X = D; Kvadrat (); D = Y;   //D = D^2
    cout << D << endl;

    cout << "7) C^2 + D^2 = " << C << " + " << D << " = ";
    X = C; Summa(C);        // C = C^2 + D^2
    cout << C << endl;

    cout << "8) (C^2 + D^2)^2 = " << C << "^2 = ";
    X = C; Kvadrat (); C = Y;   //C = (C^2 + D^2)^2
    cout << C << endl;

    cout << "\nF = (A^2 + B^2)^2 + (C^2 + D^2)^2 = " << A << " + " << C << " = ";
    X = A; Summa(F);
   cout << F;
}
