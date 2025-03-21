#include <iostream>
#include <cstring>
using namespace std;

int main(){
    const int length = 20;
    char s[length],ch;
    //1
    double chislo = 0.0, ves=0.5;
    short int cifra, i = 2;  

    cout<<"Введите двоичное вещественное число: ";
    //2 вещественное рассматриваем после запятой
    cin.get(s,3);   //считали 0,
    // проверка, что число < 1
    if (s[0]!='0'){
        cout << "Введите число < 1!";
        return 0;
    }
    cin.get(ch);
    //3 ввод значимых цифр
    while((ch!='\n')&&(i<length)){
        if (ch=='0' or ch=='1'){    //4
            cifra = ch-48;          //5
            chislo+=cifra*ves;

            ves = ves/2.0;
            cin.get(ch);    //6
            i++;
        }
        else{
            cout << "Это не двоичное число!";
            return 0;
        }
    }
    
    cout <<"Число в десятчной системе счисления: " << chislo<< endl;

    //7 перевод в обратную сторону
    char outs[length]={'0','.'};
    i=2;
    do{
        cifra=chislo*2;     //8 взяли целую часть для новой цифры числа в 2СС
        outs[i]=cifra+48;   //9

        chislo = chislo*2 - cifra;  //10
        i++;
    }while((chislo!=0)&&(i<length-1));  //11
    outs[i]='\0';                       //12
    cout << "Обратно преобразовали в двоичную СС: " << outs << endl;
    
    //сравним строки на входе и на выходе
    if (bool(strcmp(s,outs))){
        cout<< "Вывод: получили одинаковые строки";
    }
    else{
        cout<< "Вывод: получили разные строки";
    }
}