// LAB-11.4.cpp
// Сушинський Ігор
// Лабораторія №11.4
// Опрацювання бінарного файлу.
// Варіант 18

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці

using namespace std;

struct Price
{
	string tovar;
	string shop;
	float price;
};

void Create(Price* p, const int N, char* fname);
void Print(Price* p, const int N, char* fname);
void Sort(Price* p, const int N, char* fname);
void SearchPrice(Price* p, const int N, char* fname);

int main()
{
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	char fname[100]; // ім'я файлу
	cout << "Ввести ім'я файлу: "; cin >> fname;

	int N;
	cout << "Введіть кількість товарів N: "; cin >> N;

	Price* p = new Price[N];

	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування даних" << endl;
		cout << " [4] - вивід інформації про товар" << endl << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N, fname);
			break;
		case 2:
			Print(p, N, fname);
			break;
		case 3:
			Sort(p, N, fname);
			break;
		case 4:
			SearchPrice(p, N, fname);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}

void Create(Price* p, const int N, char* fname)
{
	ofstream fout(fname, ios::binary);	// відкрили файл для запису
	for (int i = 0; i < N; i++)
	{
		cout << "Товар № " << i + 1 << ":" << endl;

		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

		cout << " назва товару: "; getline(cin, p[i].tovar); fout << p[i].tovar;
		cout << " назва магазину: "; getline(cin, p[i].shop); fout << p[i].shop;
		cout << " вартість товару: "; cin >> p[i].price; fout << p[i].price;
		cout << endl;
	}
}

void Print(Price* p, const int N, char* fname)
{
	ifstream fin(fname, ios::binary); // відкрили файл для зчитування
	cout << "=========================================="
		 << endl;
	cout << "|  №  |   Товар   |  Магазин  | Вартість |"
		 << endl;
	cout << "------------------------------------------"
		 << endl;

	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1;
		cout << " | " << setw(9) << right << p[i].tovar
			 << " | " << setw(9) << right << p[i].shop
			 << " | " << setw(8) << right << p[i].price << " |";
		cout << endl;
	}
	cout << "=========================================="
		 << endl;
	cout << endl;
}

void Sort(Price* p, const int N, char* fname) // неповністю готова, функція не впорядковує файл
{
	fstream fin(fname, ios::binary); // відкрили файл для зчитування і запису
	Price tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод «бульбашки»
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if (p[i1].shop > p[i1 + 1].shop)
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}

void SearchPrice(Price* p, const int N, char* fname)
{
	ifstream fin(fname, ios::binary); // відкрили файл для зчитування
	string tovar;
	int k = 0;

	cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
	cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

	cout << " назва товару: "; getline(cin, tovar);

	for (int i = 0; i < N; i++)
	{
		k++;
		if (p[i].tovar == tovar)
		{
			cout << "=========================================="
				 << endl;
			cout << "|  №  |   Товар   |  Магазин  | Вартість |"
				 << endl;
			cout << "------------------------------------------"
				 << endl;
			cout << "| " << setw(3) << k << " | " << setw(9) << p[i].tovar << " | "
				 << setw(9) << p[i].shop << " | " << setw(8) << p[i].price << " |"
				 << endl;
			cout << "=========================================="
				 << endl;
			cout << endl;
		}
	}
}