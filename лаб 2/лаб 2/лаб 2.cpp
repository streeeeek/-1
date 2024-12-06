#include <iostream>
#include <cmath>
using namespace std;

bool is_prime(int num) {
	if (num < 2) return false;
	if (num == 2) return true;
	if (num % 2 == 0) return false;
	int cor = sqrt(num);
	for (int i = 3; i <= cor; i += 2) {
		if (num % i == 0) return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "RU");

	bool isHuman = false;
	if (argc <= 1 || strcmp(argv[1], "false") != 0)
	{
		isHuman = true;
	}

	double n;
	if (isHuman) {
		cout << "Введите количество чисел последовательности (числа последовательности должны быть целыми и положительными): " << endl;
	}
	cin >> n;
	double sum = 0;
	int count_powof_2 = 0;
	int count_greater_than_sum = 0;
	int count_of_5 = 0;
	int prev1 = 0, prev2 = 0;
	int number;
	int max_num = INT_MIN;
	int min_num = INT_MAX;
	int dif = 0;
	for (int i = 0; i < n; i++) {
		if (isHuman) {
			cout << "Введите число: " << endl;
		}
		cin >> number;
		sum += number;
		if (is_prime(number)) {
			if (isHuman) {
				cout << number << " простое число" << endl;
			}
			else {
				cout << number << endl;
			}
		}
		if (number % 5 == 0) {
			count_of_5++;
		}
		if ((number >= 1) && (number & (number - 1)) == 0) {
			count_powof_2++;
		}
		if (i >= 2 && number > (prev1 + prev2)) {
			count_greater_than_sum++;
		}
		prev2 = prev1;
		prev1 = number;
		max_num = max(max_num, number);
		min_num = min(min_num, number);
		dif = max_num - min_num;
	}
	double average = sum / n;
	if (isHuman) {
		cout << "Среднее арифмитическое введёных чисел: " << round(average * 100) / 100 << endl;
	}
	else {
		cout << average << endl;
	}
	if (isHuman) {
		cout << "Разница между максимумом и минимумом: " << dif << endl;
	}
	else {
		cout << dif << endl;
	}
	if (isHuman) {
		cout << "Количество чисел, кратных числу 5: " << count_of_5 << endl;
	}
	else {
		cout << count_of_5 << endl;
	}
	if (isHuman) {
		cout << "Количество чисел, являющихся степенью двойки: " << count_powof_2 << endl;
	}
	else {
		cout << count_powof_2 << endl;
	}
	if (isHuman) {
		cout << "Количество чисел, превышающих сумму двух предшествующих членов последовательности: " << count_greater_than_sum << endl;
	}
	else {
		cout << count_greater_than_sum << endl;
	}
	return 0;
}
