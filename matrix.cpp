#include <iostream>
using namespace std;
#include <iomanip> 

const int k = 5;
float A[k][k],B[k][k];

// TEST1
//float A[k][k] = {{1,2,3,4,5}, {1,2,3,4,5}, {1,2,3,4,5}, {1,2,3,4,5}, {1,2,3,4,5}};

// TEST2
// float A[k][k] = {{1,5,7,6,3}, {4,-2,-1,7,2}, {5,8,-9,11,-10}, {6,4,3,-2,5}, {1,12,3,7,8}};

// TEST3
//float A[k][k] = {{0.5,-0.3,0.6,0.7,-0.11}, {1.0,1.3,2.5,2.7,3.8}, {-3.8,-3.5,-4.7,-3.2,-5.1}, {5.0,6.7,-8.2,-1.1,-3.2}, {2.3,2.7,-3.8,-4.9,5.0}};

int main() {

    //ввод матрицы А по столбцам
    int i=0, j=0;
    while (j<k){
        cout << j << " столбец" << endl;
        i = 0;      //обнулили i чтобы начинать с 1 строки
        while (i<k){
            cout << i << " строка ";
            cin >> A[i][j];
            i++;
        }
        j++; 
    }

    //вывод матрицы A
    cout <<"A   1    2    3    4    5" << endl;
    i=0;
    do {
        cout << i + 1;
        j = 0;
        do{
            cout << setw(4) << A[i][j] << ' ';
            j++;
        }
        while (j<k);
        cout << endl;
        i++;
    }
    while (i<k);

    // поиск контрольного значения в матрице A
    float max_elem = -10000000.9;
    for (i = 0; i < 5; i++) {
        j = 4 -i;
        if (abs(A[i][j]) > max_elem) max_elem = abs(A[i][j]);
    }

    // значения В одинаковые с А
    for (j=1; j<k; j++){
        for (i=5-j; i<k; i++)
            B[i][j] = A[i][j];
    }

    // значения контрольного значения
    for (j = 0; j < k; j++){
        for (i = 0; i<= 4-j; i++) {
            B[i][j] = max_elem;
        }
    }

    // вывод матрицы B
    cout << endl;
    cout <<"B   1    2    3    4    5" << endl;
    i=0;
    do {
        cout << i + 1;
        j = 0;
        do{
            cout << setw(4) << B[i][j] << ' ';
            j++;
        }
        while (j<k);
        cout << endl;
        i++;
    }while (i<k);
}