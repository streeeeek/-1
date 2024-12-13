#include <iostream>
#include <fstream>
#include <limits> 

using namespace std;

// Ввод элементов матрицы
void inputMatrix(int** matrix, int size) {
    cout << "Введите элементы матрицы (" << size << "x" << size << "):" << endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cin >> matrix[i][j];
        }
    }
}

// Вывод матрицы на экран
void outputMatrix(int** matrix, int size, char label) {
    cout << "Матрица " << label << " (" << size << "x" << size << "):" << endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Интерактивное редактирование элементов матриц
void editMatrix(int** matrix, int size) {
    char choice;
    do {
        int row, col, value;
        cout << "Введите индекс строки и столбца для редактирования (0-" << size - 1 << "): ";
        cin >> row >> col;
        if (row >= 0 && row < size && col >= 0 && col < size) {
            cout << "Введите новое значение: ";
            cin >> value;
            matrix[row][col] = value;
        }
        else {
            cout << "Неверный индекс!" << endl;
        }

        cout << "Хотите редактировать еще? (1. Да / 2. Нет): ";
        cin >> choice;
    } while (choice == '1');
}

// Сохранение матрицы в файл
void saveMatrixToFile(const string& filename, int** matrix, int size) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                file << matrix[i][j] << " ";
            }
            file << endl;
        }
        file.close();
        cout << "Матрица сохранена в файл: " << filename << endl;
    }
    else {
        cout << "Не удалось открыть файл для записи." << endl;
    }
}

// Файловый ввод
void loadMatrixFromFile(int** matrix, const string& filename, int size) {
    ifstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                file >> matrix[i][j];
            }
        }
        file.close();
        cout << "Матрица загружена из файла: " << filename << endl;
    }
    else {
        cout << "Не удалось открыть файл для чтения." << endl;
    }
}

// Поиск номеров всех строк матрицы С, в которых все элементы превышают сумму соответствующих элементов матриц А и В
void findRowsInC(int** C, int** A, int** B, int size) {
    cout << "Номера строк матрицы C, где все элементы строго больше суммы соответствующих элементов матриц A и B:" << endl;
    for (int i = 0; i < size; i++) {
        int sumA = 0, sumB = 0;

        for (int j = 0; j < size; j++) {
            sumA += A[i][j];
            sumB += B[i][j];
        }

        bool allGreater = true;
        for (int j = 0; j < size; j++) {
            if (C[i][j] <= sumA || C[i][j] <= sumB) {
                allGreater = false;
                break;
            }
        }

        if (allGreater) {
            cout << "Строка " << (i + 1) << endl;
        }
    }
}

// Основная функция
int main() {
    setlocale(LC_ALL, "Russian");

    int size;
    while (true) {
        cout << "Введите размерность квадратных матриц: ";
        cin >> size;

        // Проверка на корректность ввода
        if (cin.fail() || size <= 0) {
            cout << "Ошибка: введите положительное целое число." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }

    // Динамическое выделение памяти для матриц
    int** A = new int* [size];
    int** B = new int* [size];
    int** C = new int* [size];
    for (int i = 0; i < size; ++i) {
        A[i] = new int[size];
        B[i] = new int[size];
        C[i] = new int[size];
    }

    int choice;
    do {
        cout << "\nМеню:\n"
            << "1. Консольный ввод данных о матрице А\n"
            << "2. Консольный ввод данных о матрице B\n"
            << "3. Консольный ввод данных о матрице C\n"
            << "4. Файловый вводданных о матрице А\n"
            << "5. Файловый вводданных о матрице B\n"
            << "6. Файловый вводданных о матрице C\n"
            << "7. Интерактивное редактирование элементов матриц\n"
            << "8. номера всех строк матрицы С, в которых все элементы превышают сумму соответствующих элементов матриц А и В\n"
            << "9. Вывод матриц\n"
            << "10. Сохранение матрицы A в файл\n"
            << "11. Сохранение матрицы B в файл\n"
            << "12. Сохранение матрицы C в файл\n"
            << "13. Выход\n"
            << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1: inputMatrix(A, size); break;
        case 2: inputMatrix(B, size); break;
        case 3: inputMatrix(C, size); break;
        case 4: loadMatrixFromFile(A, "A.txt", size); break;
        case 5: loadMatrixFromFile(B, "B.txt", size); break;
        case 6: loadMatrixFromFile(C, "C.txt", size); break;
        case 7: {
            char matrixChoice;
            do {
                cout << "Выберите матрицу для редактирования (1 - A; 2 - B; 3 - C; 4 - Выход): ";
                cin >> matrixChoice;
                if (matrixChoice == '1') editMatrix(A, size);
                else if (matrixChoice == '2') editMatrix(B, size);
                else if (matrixChoice == '3') editMatrix(C, size);
            } while (matrixChoice != '4');
            break;
        }
        case 8: findRowsInC(C, A, B, size); break;
        case 9: {
            outputMatrix(A, size, 'A');
            outputMatrix(B, size, 'B');
            outputMatrix(C, size, 'C');
            break;
        }
        case 10: saveMatrixToFile("A.txt", A, size); break;
        case 11: saveMatrixToFile("B.txt", B, size); break;
        case 12: saveMatrixToFile("C.txt", C, size); break;
        case 13: cout << "Выход из программы." << endl; break;
        default: cout << "Неверный выбор! Пожалуйста, попробуйте еще раз." << endl;
        }
    } while (choice != 13);

    // Освобождение памяти
    for (int i = 0; i < size; ++i) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}