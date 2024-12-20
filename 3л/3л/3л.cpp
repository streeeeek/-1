#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#define NOMINMAX
#include <Windows.h>

using namespace std;

// Функция для проверки, является ли число степенью двойки (побитовое)
bool isPowerOfTwo(int num) {
    return (num > 0) && (num & (num - 1)) == 0;
}

// Функция для вычисления значения F в зависимости от x, a, b, c
double calculateF(double x, double a, double b, double c) {
    if (x < 0 && b != 0) {
        return a * x * x + b;
    }
    else if (x > 0 && b == 0) {
        return (x - a) / (x - c);
    }
    else if (c == 0) {
        return (x >= 0) ? INFINITY : -INFINITY; // Возврат inf для деления на ноль
    }
    else {
        return x / c;
    }
}

// Функция для вывода массивов в табличном формате (равном. распред. x)
void displayTable(double arr1[], double arr2[], double x1, double x2, int size) {
    // Вывод первого массива
    cout << "Первый массив:" << endl;
    cout << string(25, '-') << endl;
    cout << "|" << setw(6) << "x" << setw(7) << "|" << setw(6) << "F" << setw(5) << "|" << endl;
    cout << string(25, '-') << endl;

    for (int i = 0; i < size; ++i) {
        double x = x1 + (x2 - x1) * i / (size - 1);
        cout << "| " << setw(10) << fixed << setprecision(2) << x << " | "
            << setw(8) << fixed << setprecision(2) << arr1[i] << " |" << endl;
    }
    cout << string(25, '-') << endl;

    // Вывод второго массива
    cout << "Второй массив:" << endl;
    cout << string(25, '-') << endl;
    cout << "|" << setw(6) << "x" << setw(7) << "|" << setw(6) << "F" << setw(5) << "|" << endl;
    cout << string(25, '-') << endl;

    for (int i = 0; i < size; ++i) {
        double x = -x2 + (x1 - (-x2)) * i / (size - 1);
        cout << "| " << setw(10) << fixed << setprecision(2) << x << " | "
            << setw(8) << fixed << setprecision(2) << arr2[i] << " |" << endl;
    }

    cout << string(25, '-') << endl;
}

// Функция для округления значений массивов в зависимости от a, b, c
void roundArrays(double arr1[], double arr2[], int size, int a_int, int b_int, int c_int) {
    if (((a_int | b_int) & (a_int | c_int)) == 0) {
        for (int i = 0; i < size; ++i) {
            arr1[i] = round(arr1[i]);
            arr2[i] = round(arr2[i]);
        }
    }
    else {
        for (int i = 0; i < size; ++i) {
            arr1[i] = round(arr1[i] * 100) / 100.0;
            arr2[i] = round(arr2[i] * 100) / 100.0;
        }
    }
}

// Функция для сортировки массива по возрастанию
void sortArray(double arr[], int size) {
    for (int i = 1; i < size; ++i) {
        for (int r = 0; r < size - i; r++) {
            if (arr[r] > arr[r + 1]) {
                double temp = arr[r];
                arr[r] = arr[r + 1];
                arr[r + 1] = temp;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    // Установка кодировки консоли для корректного отображения символов
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "");

    bool isHuman = (argc <= 1 || strcmp(argv[1], "false") != 0);

    if (isHuman) {
        cout << "Введите пять действительных чисел (x1, x2, a, b, c):" << endl;
    }

    double x1, x2, a, b, c;
    cin >> x1 >> x2 >> a >> b >> c; 

    // Проверка на нулевое значение c
    if (c == 0) {
        cout << "Значение c не должно быть равно нулю." << endl;
    }

    const int size = 15; 
    double arr1[size], arr2[size];
    double step = (x2 - x1) / (size - 1); // Шаг для заполнения массивов

    // Заполнение первого массива значениями функции F
    for (int i = 0; i < size; ++i) {
        double x = x1 + i * step; // Вычисление текущего значения x
        arr1[i] = calculateF(x, a, b, c); // Вычисление значения F
    }

    // Заполнение второго массива значениями функции F для диапазона [-x2, -x1]
    for (int i = 0; i < size; ++i) {
        double x = -x2 + i * step; // Вычисление текущего значения x
        arr2[i] = calculateF(x, a, b, c); // Вычисление значения F
    }

    int a_int = static_cast<int>(a);
    int b_int = static_cast<int>(b);
    int c_int = static_cast<int>(c);

    // Округление значений в массивах
    roundArrays(arr1, arr2, size, a_int, b_int, c_int);

    // Вывод массивов в табличном формате
    if (isHuman) {
        displayTable(arr1, arr2, x1, x2, size);
    }
    else {
        for (int i = 0; i < size - 1; ++i) {
            cout << arr1[i] << " ";
        }
        cout << arr1[14] << endl;
        for (int i = 0; i < size - 1; ++i) {
            cout << arr2[i] << " ";
        }
        cout << arr2[14] << endl;
    }

    // Вычисление минимумов пятерок элементов первого массива
    if (isHuman) {
        cout << "Минимумы пятерок первого массива:" << endl;
    }
    for (int i = 0; i < 14; i += 5) {
        double min_val = min({ arr1[i], arr1[i + 1], arr1[i + 2], arr1[i + 3], arr1[i + 4] });
        cout << min_val << endl; 
    }

    int index = -1; // Индекс для степеней двойки

    // Поиск индекса, начиная с которого размещаются степени числа 2
    for (int i = 0; i < 15; i++) {
        if (isPowerOfTwo(static_cast<int>(arr1[i])) && (arr1[i] < arr1[i + 1])) {
            bool found = true;
            for (int j = i; j < 15; ++j) {
                if (!isPowerOfTwo(static_cast<int>(arr1[j]))) {
                    found = false; // Если встречаем не степень двойки, прекращаем поиск
                    break;
                }
            }
            if (found) {
                index = i; // Устанавливаем индекс
                break;
            }
        }
    }

    // Вывод отсортированного массива по возрастанию
    if (isHuman) {
        cout << "Элементы первого массива, упорядоченные по возрастанию:" << endl;
    }
    double sortedArr1[15];
    for (int i = 0; i < 15; ++i) {
        sortedArr1[i] = arr1[i]; // Копируем массив для сортировки
    }
    sortArray(sortedArr1, size); // Сортируем массив
    for (int i = 0; i < size - 1; ++i) {
        cout << sortedArr1[i] << " "; // Вывод отсортированного массива
    }
    cout << sortedArr1[14] << endl;

    // Подсчет количества значений, встречающихся более одного раза
    bool counted[15] = { false }; // Массив для отслеживания уже посчитанных значений
    int count = 0; // Счетчик повторений

    for (int i = 0; i < size; ++i) {
        if (counted[i]) continue; // Пропускаем уже посчитанные значения
        int occ = 0; // Счетчик для текущего значения
        for (int j = 0; j < size; j++) {
            if (arr1[i] == arr1[j]) {
                occ++; // Увеличиваем счетчик, если значение повторяется
            }
        }
        if (occ > 1) {
            count++; // Увеличиваем общий счетчик, если значение встречается более одного раза
        }
        // Отмечаем все вхождения как посчитанные
        for (int j = 0; j < size; ++j) {
            if (arr1[i] == arr1[j]) {
                counted[j] = true;
            }
        }
    }
    if (isHuman) {
        cout << "Количество значений, встречающихся в массиве более одного раза:" << endl;
    }
    cout << count << endl; // Вывод количества повторяющихся значений

    // Вывод номера элемента, начиная с которого в массиве непрерывно размещаются степени числа 2
    if (isHuman) {
        cout << "Номер элемента, начиная с которого в массиве непрерывно размещаются степени числа 2 в порядке возрастания:" << endl;
    }
    cout << index << endl;

    // Перераспределение положительных и отрицательных значений
    double positive[15], negative[15];
    int p = 0, o = 0;

    // Заполнение массива положительными значениями
    for (int i = 0; i < 15; ++i) {
        if (arr1[i] > 0) {
            positive[p++] = arr1[i]; // Добавляем положительное значение
            arr1[i] = 0; // Убираем его из первого массива
        }
    }

    // Заполнение массива отрицательными значениями
    for (int i = 0; i < 15; ++i) {
        if (arr2[i] < 0) {
            negative[o++] = arr2[i]; // Добавляем отрицательное значение
            arr2[i] = 0; // Убираем его из второго массива
        }
    }

    o = 0; // Сброс счетчика для отрицательных значений
    p = 0; // Сброс счетчика для положительных значений

    // Заполнение первого массива отрицательными значениями
    for (int i = 0; i < 15; ++i) {
        if (arr1[i] == 0 && o < 15) {
            arr1[i] = negative[o++]; // Заполняем нули из первого массива отрицательными значениями
        }
    }
    // Заполнение второго массива положительными значениями
    for (int i = 0; i < 15; ++i) {
        if (arr2[i] == 0 && p < 15) {
            arr2[i] = positive[p++]; // Заполняем нули из второго массива положительными значениями
        }
    }

    // Вывод перераспределенных массивов
    if (isHuman) {
        cout << "Перераспределенные массивы:" << endl;
    }
    for (int i = 0; i < size - 1; ++i) {
        cout << arr1[i] << " "; // Вывод первого перераспределенного массива
    }
    cout << arr1[14] << endl;

    for (int i = 0; i < size - 1; ++i) {
        cout << arr2[i] << " "; // Вывод второго перераспределенного массива
    }
    cout << arr2[14] << endl;

    return 0; // Завершение программы
}
