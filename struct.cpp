#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

int main ( )
{
    // Перечисление для оценок
    enum Grade {удовл = 3,  хор = 4, отл = 5};

    //# pragma pack(push, 1)
    struct Student{
        char surname[20]; // 20 байт фамилия
        struct Sub{       // 18 бит -> 3 байт оценки по предметам и 1 padding
            Grade algebra : 3;     
            Grade geometry : 3;     
            Grade russian : 3;      
            Grade literature : 3;   
            Grade informatics : 3;  
            Grade geography : 3;    
        } grades;
        double sr;        // 8 байт средний балл
    };
    //#pragma pack(pop)
   
    // cout << "Выравнивание структуры студент: " << alignof() << endl;
    // cout << "Размер структуры студент: " << sizeof(Student) << endl;
    // cout << offsetof(Student, surname) << endl;
    // cout << offsetof(Student, grades) << endl;
    // cout << offsetof(Student, sr) << endl;

    // максимальное число студентов в группе
    const int countMax=25;
    // группа студентов
    Student gruppa [countMax];
    
    int countStud, Num; // количество студентов и порядковый номер (рабочий)

    cout << " Число студентов (до " << countMax+1 << "): ";
    cin >> countStud;
    // Защита от неправильного ввода количества студентов
    if (countStud>countMax) countStud = countMax;
    if (countStud<1) countStud=1;

    // ввод данных
    for (Num=0; Num<countStud; Num++) {
        cout << "Студент №" << Num+1 << endl << "Фамилия: ";
        cin >> gruppa[Num].surname;
        cout << "Введите оценки по предметам: " << endl;
        
        cout << "Алгебра ";
        unsigned int a, g, r, l, i, j;
        cin >> a; 
        if (a>=3 && a<=5) gruppa[Num].grades.algebra = Grade(a);
        else{cout<<"Неправильной ввод оценки"; return 0;}
        
        cout << "Геометрия ";
        cin >> g;
        if (g>=3 && g<=5) gruppa[Num].grades.geometry = Grade(g);
        else{cout<<"Неправильной ввод оценки"; return 0;}

        cout << "Русский язык ";
        cin >> r; 
        if (r>=3 && r<=5) gruppa[Num].grades.russian = Grade(r);
        else{cout<<"Неправильной ввод оценки"; return 0;}

        cout << "Литература ";
        cin >> l; 
        if (l>=3 && l<=5) gruppa[Num].grades.literature = Grade(l);
        else{cout<<"Неправильной ввод оценки"; return 0;}

        cout << "Информатика ";
        cin >> i; 
        if (i>=3 && i<=5) gruppa[Num].grades.informatics = Grade(i);
        else{cout<<"Неправильной ввод оценки"; return 0;}

        cout << "География ";
        cin >> j; 
        if (j>=3 && j<=5) gruppa[Num].grades.geography = Grade(j);
        else{cout<<"Неправильной ввод оценки"; return 0;}

        double sum = (a+g+r+l+i+j)/6.0;
        gruppa[Num].sr = sum;
    }

    //поиск максимального балла аттестата sr
    double MAXsr = 0.0;
    for (Num=0; Num<countStud; Num++) {
        if (MAXsr < gruppa[Num].sr)
            MAXsr = gruppa[Num].sr;
    }

    cout << endl;
    cout << setw(14) << "Фамилия         Алгебра Геометрия Русский язык Литература Информатика География Средний балл" << endl;
    for (Num=0; Num<countStud; Num++) {
        cout << setw(15) << left<< gruppa[Num].surname << setw(8) << right << gruppa[Num].grades.algebra 
             << setw(10) << gruppa[Num].grades.geometry << setw(13) << gruppa[Num].grades.russian
             << setw(11) << gruppa[Num].grades.literature << setw(12) << gruppa[Num].grades.informatics
             << setw(10) << gruppa[Num].grades.geography << setw(13) << gruppa[Num].sr << endl;
    }

    //вывод ответа
    cout << endl;
    cout << "Максимальный балл аттестата = " << MAXsr << endl;
    cout << "Максимальный балл аттестата у студента(ов):" << endl;
    for (Num=0; Num<countStud; Num++) {
        if (MAXsr == gruppa[Num].sr)
            cout << gruppa[Num].surname << endl;
    } 
    cout << endl;
    return 0;
}