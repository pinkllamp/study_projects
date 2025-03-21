#include <iostream>
#include <iomanip>
#include <cstdlib>  // atoi
#include <cstring> 
#include <fstream> 

using namespace std;

const char * name_month [] = {"","Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"};
const char * name_day [] = {"ПН","ВТ","СР","ЧТ","ПТ","СБ","ВС"};
const int max_days[]= {0,31,28,31,30,31,30,31,31,30,31,30,31};

int DayWeek(int Day, int Month, int Year) {
    int DaysInYears, AllDays, DaysInMonths, Weeks, DayWeek;
    if (Month < 3) {
        Month = Month+12;
        Year = Year-1;
    }
    Month = Month+1;
    DaysInMonths = Month*30.6;
    DaysInYears = Year*365.25;
    AllDays = DaysInMonths+DaysInYears+Day-114;
    Weeks = AllDays/7;
    DayWeek = AllDays - Weeks*7-1;
    if (DayWeek == -1) DayWeek = 6;
    return DayWeek;
}

void print_kalendar(short Kalendar[7][6], int month, char zero = ' '){
    cout << '\n' << setw(18) << name_month[month];
    for (char i=0; i<7; i++){
        cout << '\n' << setw(3) << name_day[i];
        for (char j=0; j<6; j++)
            if (Kalendar[i][j] == 0) cout << setw(3) << zero;
            else cout << setw(3) << Kalendar[i][j];
    }
}

int fill_Kalendar(short Kalendar[7][6], int first, int all_days = 31, int year = 1){
    int today, row = first, column = 0;
    if (all_days == 28 and ((year%4==0 and year%100!=0) or (year%400 == 0))) all_days++;

    for (today = 1; today <= all_days; today++){
        Kalendar[row++][column] = today;
        if (row == 7) {
            row = 0;
            column++;
        } 
    }
    return row; 
}


int main(int narg, char *arg[]){
    // cout << "Тест для функции DayWeek: \n";
    // for (int i = 1; i < 8; i++)
    //     cout << DayWeek(i, 10, 2011)<< ' ';

    // short Kalendar [7][6];
    // for (char i=0; i<7; i++){
    //     for (char j=0; j<6; j++)
    //         Kalendar[i][j] = 0;
    // }

    // print_kalendar(Kalendar, 0,'0');

    // int first = DayWeek(1,7,2004);
    // fill_Kalendar (Kalendar, first);
    // print_kalendar(Kalendar);

    int month=-1, year=-1;
    char NameFile [100];
    bool flag_f = false;
    for (int i = 1; i< narg; i++){
        if (strncmp(arg[i],"/M",2)==0) month = atoi(arg[i]+2);
        if (strncmp(arg[i],"/Y",2)==0) year = atoi(arg[i]+2);
        if (strncmp(arg[i],"/F",2)==0) {strcpy(NameFile,arg[i]+2); flag_f = true;}
        if (strcmp(arg[i],"/S")==0) cout << "\nЭта программа выводит календарь, начиная с заданного месяца и года. Вы можете ввести месяц и год в командную строку с помощью ключей /M и /Y. Задать имя файла для вывода календаря /F. Получить справку /S.\n";
    }
    //если отсутствуют в командной строке интерактивный ввод:
    if (month == -1){
        cout << "\nВведите месяц (число от 1 до 12): ";
        cin>>month;
    }
    //ошибки ввода:
    if (month<1 || month>12){
        cout << "Ошибка: недопустимое значение месяца";
        exit(1);
    }

    if (year == -1){
        cout << "Введите год (в формате ГГГГ): ";
        cin>>year;
    }
    if (year<1){
        cout << "Ошибка: недопустимое значение года";
        exit(2);
    }
    
    // fill_Kalendar(Kalendar, DayWeek(1,month,year), max_all_days(month, year));
    // print_kalendar(Kalendar,month);
    
    //четырехмерный массив календаря на год
    short ALL_MONTH [4][3][7][6], last;
    char NStr, NCol;

    //заполним 0
    for (NStr = 0; NStr < 4; NStr++){
        for (char i=0; i<7; i++){
            for (NCol= 0; NCol < 3; NCol++ ){
                for (char j=0; j<6; j++)
                    ALL_MONTH[NStr][NCol][i][j] = 0;
            }
        }
    }

    last = DayWeek(1,month,year); //для первого месяца (последний день предыдущего месяца + 1)
    for (NStr = 0; NStr < 4; NStr++){
        for (NCol= 0; NCol < 3; NCol++ ){
            last = fill_Kalendar(ALL_MONTH[NStr][NCol], last, max_days[month], year);
            month++;
            if (month == 13){
                month = 1;
                year++;
            }
        }
    }

    //куда выводить
    bool fileOUT = true;
    int ans;
    if (flag_f){
        if (strcmp(NameFile,"CON") == 0) fileOUT = false;
    }else{
        cout << "Хотите вывести календарь в файл? [Да:1 , Нет:0]\n";
        cin>> ans;
        if (ans){
            cout << "Введите название файла: ";
            cin >> NameFile;
        }else{
            fileOUT = false;
        }
    }

    short real_month, first_month = month;
    bool holiday = false;   //праздник?
    short holidays[6][2] = {{12,31}, {2,23},{3,8},{5,1},{5,9},{7,13}};

    if (!fileOUT){
    //вывод массива целого года
    for (NStr = 0; NStr < 4; NStr++){
        cout  << '\n' << setw(18) << name_month[month];
        month = (month == 12)? 1: ++month;
        cout << setw(29) << name_month[month];
        month = (month == 12)? 1: ++month;
        cout << setw(29) << name_month[month];
        for (char i=0; i<7; i++){
            cout << '\n';
            for (NCol= 0; NCol < 3; NCol++ ){
                cout << setw(3) << name_day[i];
                real_month = first_month + NStr*3 + NCol;   //Находим месяц из которого сейчас будем выводить
                real_month = (real_month>12)? real_month-12 : real_month;
                for (char j=0; j<6; j++){
                    if (ALL_MONTH[NStr][NCol][i][j] == 0) cout << setw(3) << ' ';
                    else {
                        for (char t=0;t<6;t++){
                            if (holidays[t][0] == real_month){
                                if (holidays[t][1] == ALL_MONTH[NStr][NCol][i][j]){
                                    cout <<  "\033[31m" << setw(3) << ALL_MONTH[NStr][NCol][i][j]<< "\033[0m";
                                    holiday = true;
                                }
                            }
                        }
                        if (!holiday) cout << setw(3) << ALL_MONTH[NStr][NCol][i][j];
                    }
                holiday = false;    
                }
                cout << "   ";
            }
        }
        month = (month == 12)? 1: month+1;
        cout << endl;
    }
    }else{
        ofstream File;
        File.open(NameFile, ios_base::out);
        for (NStr = 0; NStr < 4; NStr++){
            File  << '\n' << setw(18) << name_month[month];
            month = (month == 12)? 1: ++month;
            File << setw(29) << name_month[month];
            month = (month == 12)? 1: ++month;
            File << setw(29) << name_month[month];
            for (char i=0; i<7; i++){
                File << '\n';
                for (NCol= 0; NCol < 3; NCol++ ){
                    File << setw(3) << name_day[i];
                    for (char j=0; j<6; j++)
                        if (ALL_MONTH[NStr][NCol][i][j] != 0) File << setw(3) << ALL_MONTH[NStr][NCol][i][j];
                        else File << setw(3) << ' ';
                    File << "   ";
                }
            }
            month = (month == 12)? 1: month+1;
            File << endl;
        File.close();
    }
    }
    return 0;
}