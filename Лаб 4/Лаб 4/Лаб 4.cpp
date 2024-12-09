﻿#include <iostream>

using namespace std;

void inputMatrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> matrix[i][j];

        }
    }
}

void printMatrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << (j < cols - 1 ? " " : "");
        }
        cout << endl;
    }
}

bool multiplyMatrices(double** A, int A_rows, int A_cols,
    double** B, int B_rows, int B_cols,
    double**& result, int& result_rows, int& result_cols) {
    if (A_cols != B_rows) {
        return false;
    }
    result = new double* [A_rows];
    for (int i = 0; i < A_rows; ++i) {
        result[i] = new double[B_cols];
        for (int j = 0; j < B_cols; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < A_cols; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    result_rows = A_rows;
    result_cols = B_cols;
    return true;
}

bool powerMatrix(double** A, int N, int exp, double**& result) {
    if (N <= 0 || exp < 1) {
        return false;
    }
    result = new double* [N];
    for (int i = 0; i < N; ++i) {
        result[i] = new double[N];
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[i][j] = A[i][j];
        }
    }

    double** temp;
    for (int i = 1; i < exp; ++i) {
        if (!multiplyMatrices(result, N, N, A, N, N, temp, N, N)) {
            return false;
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                result[i][j] = temp[i][j];
            }
        }
        for (int k = 0; k < N; ++k) {
            delete[] temp[k];
        }
        delete[] temp;
    }
    return true;
}

int main(int argc, char* argv[]) {

    setlocale(LC_ALL, "Russian");

    bool isHuman = false;
    if (argc <= 1 || strcmp(argv[1], "false") != 0) {
        isHuman = true;
    }

    int N, M;

    if (isHuman) {
        cout << "Введите элементы матрицы A1 (N строк, M чисел в каждой): " << endl;
    }
    cin >> N >> M;
    double** A1 = new double* [N];
    for (int i = 0; i < N; ++i) {
        A1[i] = new double[M];
    }
    inputMatrix(A1, N, M);
    while (true) {

        int command;
        if (isHuman) {
            cout << "Введите команду (0 - выход, 1 - вывод A1, 2 - A1 = A1 * A2, 3 - A1 = A1^x): ";
        }
        cin >> command;

        if (command == 0) {
            break;
        }

        else if (command == 1) {
            if (isHuman) {
                cout << "Матрица А1: " << endl;
            }
            printMatrix(A1, N, M);
        }

        else if (command == 2) {
            int K;
            if (isHuman) {
                cout << "Введите размер K для матрицы A2: ";
            }
            cin >> K;
            if (isHuman) {
                cout << "Введите элементы матрицы A2 (M строк, K чисел в каждой):" << endl;
            }
            double** A2 = new double* [M];
            for (int i = 0; i < M; ++i) {
                A2[i] = new double[K];
            }

            inputMatrix(A2, M, K);
            double** result;
            int result_rows, result_cols;
            if (!multiplyMatrices(A1, N, M, A2, M, K, result, result_rows, result_cols)) {
                cout << "NO" << endl;
            }
            else {
                for (int i = 0; i < N; ++i) {
                    delete[] A1[i];
                }
                delete[] A1;

                N = result_rows;
                M = result_cols;
                A1 = result;
            }
            for (int i = 0; i < M; ++i) {
                delete[] A2[i];
            }
            delete[] A2;
        }
        else if (command == 3) {
            if (N != M) {
                cout << "NO" << endl;
                continue;
            }
            int x;
            if (isHuman) cout << "Введите натуральное число x (степень): ";
            cin >> x;
            double** result;
            if (!powerMatrix(A1, N, x, result)) {
                cout << "NO" << endl;
            }
            else {
                for (int i = 0; i < N; ++i) {
                    delete[] A1[i];
                }
                delete[] A1;

                A1 = result;
            }
        }
        else {
            cout << "Такой команды не существует, повторите попытку, выбрав одну из трёх команд." << endl;
        }
    }
    for (int i = 0; i < N; ++i) {
        delete[] A1[i];
    }
    delete[] A1;

    return 0;
}