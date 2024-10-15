#include <iostream> // переделанный н
using namespace std;
int main(int argc, char* argv[])
{
	bool isHuman = false;
	if (argc <= 1 || strcmp(argv[1], "false") != 0)
	{
		isHuman = true;
	}
	double x, y;
	if (isHuman)
	{
		setlocale(LC_ALL, "");
		cout << "Есть треугольник, вершины котрого имеют координаты (0, 0) (3, 0) (0, 4). \n";
		cout << "Чтобы проверить, входит ли точка в данный треугольнике, введите через пробел координату по оси x, а затем по оси y. Если число не является целым, то писать его стоит через точку. \n";
	}
	do
	{
		if (isHuman)
		{
			cout << "Введите координаты точки:" << endl;
		}
		cin >> x >> y;
		if (!cin)
		{
			if (isHuman)
			{
				cout << "Ошибка." << endl;
			}
			break;
		}
		if (x == 0 and y == 0)
		{
			break;
		}
		if (x >= 0)
		{
			if (y >= 0 && y <= (-4 * x / 3 + 4))
			{
				if (isHuman)
				{
					cout << "Точка входит в треугольник." << endl;
				}
				else
				{
					cout << "YES" << endl;
				}
			}
			else
			{
				if (isHuman)
				{
					cout << "Точка не входит в треугольник. \n";
				}
				else
				{
					cout << "NO" << endl;
				}
			}
		}
		else
		{
			if (isHuman)
			{
				cout << "Точка не входит в треугольник. \n";
			}
			else
			{
				cout << "NO" << endl;
			}
		}
	} while (x != 0 or y != 0);
	if (isHuman)
	{
		cout << "Конец программы. \n";
		system("pause");
		return 0;
	}
	else
	{
		return 0;
	}
}
