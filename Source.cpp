#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці
using namespace std;
enum Fahoviy { PROGRAMUVANNA, CHSLMETOD, PEDAGOGIKA };
string predmetStr[] = { "Програмування  ", "Чисельні методи", "Педагогіка     " };
struct Student
{
	string prizv;
	string kurs;
	int fizyka{};
	int matematyka{};
	Fahoviy specialnist{};
	int programuvanna{};
	int chslmetod{};
	int pedagogika{};
};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int BinSearch(Student* p, const int N, const string prizv, string Kurs, double average);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int main()
{ // забезпечення відображення кирилиці:
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу
	int N;
	cout << "Введіть кількість працівників N: "; cin >> N;
	Student* p = new Student[N];
	Fahoviy posada{};
	string prizv, Kurs;
	double proc = 0, avg = 0, average;
	int found;
	char filename[100]{};
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування даних" << endl;
		cout << " [4] - бінарний пошук студента за посадою та прізвищем" << endl;
		cout << " [5] - індексне впорядкування та вивід даних" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;

		case 2:
			Print(p, N);
			break;

		case 3:
			Sort(p, N);
			break;
		case 4:
			cout << "Введіть ключі пошуку:" << endl;
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
			cout << "Введіть прізвище: "; getline(cin, prizv);
			cout << endl;
			cout << "Введіть оцінку з математики: ";
			cin >> Kurs;
			cout << "Введіть середній бал: ";
			cin >> average;
			if ((found = BinSearch(p, N, prizv, Kurs, average)) != -1)
				cout << "Знайдено студента в позиції " << found + 1 << endl;
			else
				cout << "Шуканого студента не знайдено" << endl;
			break;
		case 5:
			PrintIndexSorted(p, IndexSort(p, N), N);
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
void Create(Student* p, const int N)
{
	int Predmet;
	for (int i = 0; i < N; i++)
	{
		int n = 0;
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи 
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок 

		cout << " Прізвище: "; getline(cin, p[i].prizv);
		cout << " Курс: "; getline(cin, p[i].kurs);

		cout << " Бал з фізики: "; cin >> p[i].fizyka;
		cout << " Бал з математики: "; cin >> p[i].matematyka;
		cout << " Спеціальність (0 - програмування, 1 - чисельні методи, 2 - педагогіка): ";
		cin >> Predmet;
		p[i].specialnist = (Fahoviy)Predmet;
		switch (p[i].specialnist)
		{
		case PROGRAMUVANNA:
			cout << " Бал з програмування : "; cin >> p[i].programuvanna;
			break;
		case CHSLMETOD:
			cout << " Бал з чисельних методів : "; cin >> p[i].chslmetod;
			break;
		case PEDAGOGIKA:
			cout << " Бал з педагогіки : "; cin >> p[i].pedagogika;
			break;
		}
		cout << endl;
	}
}
void Print(Student* p, const int N)
{
	cout << "===================================================================================================================="
		<< endl;
	cout << "__________________________________________|                               Бали                                     |"
		<< endl;
	cout << "|  №  |  Прізвище  | Курс | Спеціальність |  Фізика  |  Математика  | Програмування | Чисельні методи | Педагогіка |"
		<< endl;
	cout << "--------------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(3) << left << p[i].prizv << "     "
			<< "| " << setw(3) << right << p[i].kurs << "  "
			<< "| " << setw(11) << left << predmetStr[p[i].specialnist] << " "
			<< "| " << setw(7) << right << p[i].fizyka << "  "
			<< "| " << setw(10) << right << p[i].matematyka << " ";
		switch (p[i].specialnist)
		{
		case PROGRAMUVANNA:
			cout << "| " << setw(13) << setprecision(2) << right
				<< p[i].programuvanna << " |" << setw(11) << right << "|" << setw(11) << right << "|" << endl;
			break;
		case CHSLMETOD:
			cout << "|" << setw(13) << setprecision(2) << right << "|" << " " << setw(8) << right
				<< p[i].chslmetod << "|" << setw(11) << right << "|" << endl;
			break;
		case PEDAGOGIKA:
			cout << "| " << setw(13) << setprecision(2) << right << "|" << " " << setw(11) << right
				<< "| " << " " << setw(15) << right << p[i].pedagogika << " |" << endl;
			break;
		}
	}
	cout << "===================================================================================================================="
		<< endl;
	cout << endl;
}

void Sort(Student* p, const int N)
{
	Student tmp;
	double avg1, avg2;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
		{
			avg1 = (p[i1].fizyka + p[i1].matematyka + p[i1].programuvanna) / 3.0;
			avg2 = (p[i1 + 1].fizyka + p[i1 + 1].matematyka + p[i1 + 1].programuvanna) / 3.0;;
			if (avg1 < avg2
				||
				(avg1 == avg2 &&
					p[i1].kurs < p[i1 + 1].kurs)
				||
				(avg1 == avg2 &&
					p[i1].kurs == p[i1 + 1].kurs &&
					p[i1].prizv > p[i1 + 1].prizv))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
		}
}


int BinSearch(Student* p, const int N, const string prizv, string Kurs, double average)
{
	int L = 0, R = N - 1, m;
	double avg;
	{
		for (int i = 0; i < N; i++)
		{

		}
		do {
			m = (L + R) / 2;
			avg = (p[m].fizyka + p[m].matematyka + p[m].programuvanna) / 3.0;
			if (p[m].prizv == prizv && avg == average && p[m].kurs == Kurs)
				return m;
			if ((avg < average)
				||
				(avg == average &&
					p[m].kurs < Kurs)
				||
				(avg == average) &&
				p[m].kurs == Kurs &&
				p[m].prizv < prizv)
			{
				L = m + 1;
			}
			else
			{
				R = m - 1;
			}
		} while (L <= R);
		return -1;

	}
}
int* IndexSort(Student* p, const int N)
{
	int* I = new int[N];
	double avgIi, avgIj;
	for (int i = 0; i < N; i++)
		I[i] = i; // заповнили його початковими даними
	int i, j, value; // починаємо сортувати масив індексів
	for (i = 1; i < N; i++)
	{
		value = I[i];
		avgIi = (p[I[i]].fizyka + p[I[i]].matematyka + p[I[i]].programuvanna) / 3.0;

		for (j = i - 1;
			avgIj = ((p[I[j]].fizyka + p[I[j]].matematyka + p[I[j]].programuvanna + p[I[j]].chslmetod + p[I[j]].pedagogika) / 3.0),
			j >= 0 && ((avgIj > avgIi) ||
				(avgIj == avgIi &&
					p[I[j]].kurs < p[value].kurs) ||
				(avgIj == avgIi &&
					p[I[j]].kurs == p[value].kurs) &&
				(p[I[j]].prizv < p[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}
void PrintIndexSorted(Student* p, int* I, const int N)
{

	cout << "===================================================================================================================="
		<< endl;
	cout << "__________________________________________|                               Бали                                     |"
		<< endl;
	cout << "|  №  |  Прізвище  | Курс | Спеціальність |  Фізика  |  Математика  | Програмування | Чисельні методи | Педагогіка |"
		<< endl;
	cout << "--------------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[I[i]].prizv
			<< "| " << setw(4) << right << p[I[i]].kurs << " "
			<< "| " << setw(11) << left << predmetStr[p[i].specialnist] << " "
			<< "| " << setw(4) << right << p[I[i]].fizyka << " "
			<< "| " << setw(4) << right << p[I[i]].matematyka << " ";

		switch (p[i].specialnist)
		{
		case PROGRAMUVANNA:
			cout << "| " << setw(9) << setprecision(2) << right
				<< p[I[i]].programuvanna << " |" << setw(11) << right << "|" << setw(11) << right << "|" << endl;
			break;
		case CHSLMETOD:
			cout << "| " << setw(11) << right << "|" << " " << setw(8) << right
				<< p[I[i]].chslmetod << " |" << setw(11) << right << "|" << endl;
			break;
		case PEDAGOGIKA:
			cout << "| " << setw(11) << right << "|" << " " << setw(11) << right
				<< "| " << " " << setw(15) << right << p[I[i]].pedagogika << " |" << endl;
			break;
		}
		cout << "===================================================================================================================="
			<< endl;

		cout << endl;
	}
}
