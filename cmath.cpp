#include <iostream>
#include <cmath>
#include <iomanip> 
using namespace std;

int main()
{
    double x, eps, tec, cos_t, pr_t = 1, pr_math = 1;
    int num, n, i;

//Ввод данных
    cout << "Задайте погрешность для ряда Тейлора Eps: ";
    cin >> eps;
    cout << "Введите аргумент X в радианах: ";
    cin >> x;
    cout << "Введите количество множителей: ";
    cin >> n;

    cout.setf(ios::right); 
    cout.fill(' ');   
    cout << setw(5) << "номер" << setw(20)<<"слагаемых"<< setw(20)<< "cos Тейлора"
    << setw(25)<< "cos библиотека" << setw(20) << "разница" << endl;

// Цикл для поиска произведения
    for (i = 1; i <= n; i++){
        
        tec = - (i*x)*(i*x)/2;
        cos_t = 1;      //первый член ряда
        num = 1;        

        do{
            cos_t+=tec;
            num ++;
            tec = tec * (-1)* (i*x)*(i*x)/((2*num - 1)*2*num); // следующее слагаемое
        }
        while (eps <= abs(tec/cos_t));      //проверка следующего слагаемого

        pr_t = pr_t * cos_t;
        double cos_math = cos(x*i);
        pr_math = pr_math * cos_math;
        cout << setw(5) << i << setw(11) << num << setw(13) << cos_t << setw(15) 
        << cos_math << setw(15) << abs(cos_t - cos_math) << endl;
    }
    
    cout << "Произведение по Тейлору: " << pr_t << endl;
    cout << "Произведение библиотеки: " << pr_math << endl;
    cout << "Разница: " << abs(pr_t - pr_math);

    return 0;

}
