#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "RU");
	double x, y;
	bool sh = false;
	
	if (argc <= 1 || strcmp(argv[1], "false") != 0) {
		sh = true;
	}
	if (sh) {
		cout << "Дан треугольник, вершины которого имеют координаьты (0, 0) (0, 4) (3, 0).\n";
		cout << "Введите через пробел координату по оси x, а затем по оси y, чтобы узнать, попала ли данная точка в треугольник. Учтите, что не целые числа стоит писать с точкой. \n";
	}
	do {
		if (sh) {
			cout << "Введите кординаты точки: \n";
		}
		cin >> x;
		cin	>> y;
		if (x == 0 && y == 0) {
			break;
		}
		if (!cin) {
			if (sh) {
				cout << "Ошибка. \n";
			}
			break;
		}
		if (x > 0 ) {
			if (y > 0 && y <= (-4 * x / 3 + 4)) {
				if (sh) {
					cout << "Точка с координатами, которые Вы ввели, попала в треугольник. \n";
				}
				else {
					cout << "YES \n";
				}
			}
			else {
				if (sh) {
					cout << "Точка с координатами, которые Вы ввели, не попала в треугольник. \n";
				}
				else {
					cout << "NO \n";
				}
			}
		}
	}
	while (x != 0 || y != 0);
	if (sh) {
		cout << "Конец программы. \n";
		system("pause");
		return 0;
	}
	else {
		return 0;
	}
}