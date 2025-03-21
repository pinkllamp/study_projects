#include <iostream>
#include <iomanip>
#include <cstdlib> 
#include <ctime>

using namespace std;

void P1(double** MATRIX, int j, int i){
    cin >> MATRIX[j][i]; //считали с клавиатуры
}
void P2(double** MATRIX, int j, int i){
    MATRIX[j][i] = (rand() % 2001 - 1000) / 100.0;  // рандомное вещественное -10.0 до 10.0
}
void P3(double** MATRIX, int j, int i, int size){
    MATRIX[j][i] = 1 + j + i*size; //движемся по матрице по столбцам
}

void fill_matrix (double** MATRIX,int size ){
    cout << "Если хотите ввести матрицу вручную, нажмите 1, если заполнить случайными числами 2, если натуральным рядом 3.";
    short ans;
    cin >> ans; //считали номер способа
    for (int i=0; i<size; i++){ //итерируемся по матрице заданного размера и заполняем каждый элемент
        for (int j=0; j<size; j++){
            switch(ans){
                case 1: P1(MATRIX,j,i); break;
                case 2: P2(MATRIX,j,i); break;
                case 3: P3(MATRIX,j,i,size); break;
            }
        }
    }
}
void print_MATRIX(double** MATRIX, int size){
    cout << " ";    
    for (int i = 1; i < size+1; i++){   //выводим номера столбцов
        cout << "          " << i;
    }
    for (int i=0; i<size; i++){     //проходимся по строкам, выводим номер строки
        if (i==9) cout << "\n" << 10;   //делаем красивый пробел перед всеми, кроме 10
        else cout << "\n " << i+1;
        for (int j=0; j<size; j++){
            cout << setw(11) << scientific << setprecision(2) << MATRIX[i][j]; //экспоненциальная форма, 2 знака после запятой
        }
    }
}

void Minor(double** matrix, double**minor, int size, int col, int str = 0){
    int tec_col = 0, tec_str = 0;
    for (int i = 0; i<size; i++){
        if (i != str){
            for (int j = 0; j<size; j++)
                if (j != col) minor[tec_str][tec_col++] = matrix[i][j];
            tec_str++;
            tec_col = 0;
        }
    }
}

double recurs (double** matrix, int size, int str = 0){
    double det = 0;
    if (size == 1) return matrix[0][0]; //ответ для матрицы из 1 символа 
    if (size == 2) return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]; //ответ для матрицы из 2 символов
    if (size > 2){
        //выделяем динамическую память для минора
        double **minor = new double* [size];  
        for (int i=0; i<size; i++){
            minor[i] = new double[size];
        }

        for (int col = 0; col < size; col++){   //двигаемся по столбцам заданной строки
            double A = ((col+str)%2)? -matrix[str][col] : matrix[str][col]; // учет знака элемента
            Minor(matrix, minor, size, col, str);   //находим минор 
            det = det + A* recurs(minor, size-1);   //рекурсивно находим определитель
        }
        //удаление из динамической памяти
        for (int i=0; i<size; i++){
            delete [] minor[i];
        }
        delete [] minor;
    }
    return det;
}

double Gaus(double** matrix, int size){
    double det = 1;
    for (int COL = 0; COL < size; COL++){   
        
        if (abs(matrix[COL][COL]) < 1e-11) {    // Проверка на нулевой ведущий элемент
            bool swapped = false;
            for (int row = COL + 1; row < size; row++) {
                if (matrix[row][COL] != 0 and !swapped) { 
                    swap(matrix[COL], matrix[row]);     // Меняем строки местами
                    det = -det;  
                    swapped = true;
                }
            }
            if (!swapped) { print_MATRIX(matrix,size); return 0;} // Если вся колонка нулевая, то det = 0
        }
        det = det * matrix[COL][COL];   //произведение диагональных элементов
        for (int str = COL+1; str < size; str++){
            for (int col = COL+1; col < size; col++){
                matrix[str][col] = -(matrix[str][COL]/matrix[COL][COL]) * matrix[COL][col] + matrix[str][col]; //изменяем значение элементов, справа от главной диагонали
            }
            matrix[str][COL] = 0;
        }
    }
    print_MATRIX(matrix,size);
    return det;
}
void chek(int size, int str){
    if (size>10 or size<1){
        cout << "Размер матрицы от 1 до 10.";
        exit(1);
    }
    if (str>size or str<1){
        cout << "Номер строки от 1 до размера матрицы.";
        exit(2);
    }
}
void dinam(double** matrix, int size, char new_del){
    if (new_del)
        for (int i=0; i<size; i++){
            matrix[i] = new double[size];
        }
    else
        for (int i=0; i<size; i++){
            delete [] matrix[i];
        }

}

int main() {
    //1
    int size, str;
    cout << "Введите размер матрицы и строку для разложения: ";
    cin >> size >> str;
    chek(size,str);
    cout << "Размер матрицы: " << size << "\nСтрока: " << str-- << endl;

    //2
    //выделяем динамическую память для матрицы
    double **MATRIX = new double* [size];  
    dinam(MATRIX,size,1);
    //заполняем матрицу
    fill_matrix (MATRIX, size );
    
    //3
    print_MATRIX(MATRIX,size);

    //4
    double det;
    clock_t start1 = clock();
    det = recurs(MATRIX, size, str);
    clock_t end1 = clock();
    cout << "\ndet_1 = " << setprecision(10) << det << endl;
    
    //5
    clock_t start2 = clock();
    double det_gaus = Gaus(MATRIX,size);
    clock_t end2 = clock();
    cout << "\ndet_2 = " << setprecision(10)<< det_gaus << endl;
    //7
    double delta = det - det_gaus; 
    cout << "Разница det_1 - det_2 = " << scientific << setprecision(7) << abs(delta);

    //8
    double elapsed = double(end1 - start1) / CLOCKS_PER_SEC *1000;  // Перевод в милисекунды
    cout << "\nВремя выполнения рекурсивно: " << fixed << elapsed << "мс" << endl;
    elapsed = double(end2 - start2) / CLOCKS_PER_SEC *1000;  
    cout << "Время выполнения методом Гаусса: " << elapsed << "мс" << endl;

    //2 - удаление из динамической памяти
    dinam(MATRIX,size,0);
    delete [] MATRIX;
    return 0;
}