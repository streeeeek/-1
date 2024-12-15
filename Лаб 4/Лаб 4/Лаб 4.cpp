#include <iostream>
#include <cstring>
#include <limits> 
using namespace std;

void MulMat(double** Mat1, double** Mat2, double** result, int N, int M, int K) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            result[i][j] = 0.0;
            for (int k = 0; k < M; k++) {
                result[i][j] += Mat1[i][k] * Mat2[k][j];
            }
        }
    }
}

void powMat(double** Mat, double** result, int x, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                result[i][j] = 1.0;
            }
            else {
                result[i][j] = 0.0;
            }
        }
    }

    for (int p = 0; p < x; p++) {
        double** temp = new double* [N];
        for (int i = 0; i < N; i++)
            temp[i] = new double[N]();

        MulMat(result, Mat, temp, N, N, N);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                result[i][j] = temp[i][j];

        for (int i = 0; i < N; i++)
            delete[] temp[i];
        delete[] temp;
    }
}

void prtMat(double** matrix, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << matrix[i][j];
            if (j != M - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

void inputMatrix(double** matrix, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> matrix[i][j];
        }
    }
}

int readPositiveInteger() {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail() || value <= 0) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Ошибка: введите положительное целое число." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return value;
        }
    }
}

void readMatrixDimensions(int& N, int& M) {
    while (true) {
        cout << "введите кол-во строк и столбцов Матрицы 1:" << endl;
        cin >> N >> M;
        if (cin.fail() || N <= 0 || M <= 0) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Ошибка: введите два положительных целых числа." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            break; 
        }
    }
}

int readMatrixColumns() {
    int columns;
    while (true) {
        cout << "введите кол-во столбцов матрицы A2:" << endl;
        columns = readPositiveInteger(); 
        return columns; 
    }
}

int main(int argc, char* argv[]) {
    bool isHuman = false;
    if (argc <= 1 || strcmp(argv[1], "false") != 0) {
        isHuman = true;
    }

    setlocale(LC_ALL, "RU");
    int N, M;

    readMatrixDimensions(N, M); 

    double** A1 = new double* [N];
    for (int i = 0; i < N; i++)
        A1[i] = new double[M];

    if (isHuman) cout << "введите элементы матрицы построчно:" << endl;
    inputMatrix(A1, N, M);

    int command;

    while (true) {
        if (isHuman) cout << "Выберите команду: 0 - выход из команды; 1 - актуальное значение матрицы; 2 - умножение двух матриц; 3 - возведение квадратной матрицы в степень: " << endl;
        cin >> command;

        if (command == 0) {
            break;
        }
        else if (command == 1) {
            prtMat(A1, N, M);
        }
        else if (command == 2) {
            int K = readMatrixColumns(); 

            double** A2 = new double* [M]; 
            for (int i = 0; i < M; i++)
                A2[i] = new double[K]; 

            if (isHuman) cout << "введите элементы матрицы A2:" << endl;
            inputMatrix(A2, M, K);

            double** result = new double* [N];
            for (int i = 0; i < N; i++)
                result[i] = new double[K];

            MulMat(A1, A2, result, N, M, K); 

            for (int i = 0; i < N; i++)
                delete[] A1[i];
            delete[] A1;

            A1 = new double* [N];
            for (int i = 0; i < N; i++)
                A1[i] = new double[K];

            for (int i = 0; i < N; i++)
                for (int j = 0; j < K; j++)
                    A1[i][j] = result[i][j];

            cout << "Умножение завершено. Результат сохранен в матрице A1." << endl;

            for (int i = 0; i < N; i++)
                delete[] result[i];
            delete[] result;

            for (int i = 0; i < M; i++)
                delete[] A2[i];
            delete[] A2;

            M = K; 
        }
        else if (command == 3) {
            if (N != M) {
                cout << "NO" << endl;
                continue;
            }
            int x;
            if (isHuman) cout << "степень: " << endl;
            x = readPositiveInteger(); 

            double** result = new double* [N];
            for (int i = 0; i < N; i++)
                result[i] = new double[N];

            powMat(A1, result, x, N);

            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    A1[i][j] = result[i][j];

            for (int i = 0; i < N; i++)
                delete[] result[i];
            delete[] result;
        }
        else {
            if (isHuman) { cout << "ошибка " << endl; }
            else { cout << "NO" << endl; }
        }
    }

    for (int i = 0; i < N; i++)
        delete[] A1[i];
    delete[] A1;

    return 0;
}
