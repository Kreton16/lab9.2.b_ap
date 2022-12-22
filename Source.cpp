#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> // ������������ ����������� ��������
using namespace std;
enum Fahoviy { PROGRAMUVANNA, CHSLMETOD, PEDAGOGIKA };
string predmetStr[] = { "�������������  ", "������� ������", "���������     " };
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
{ // ������������ ����������� ��������:
	SetConsoleCP(1251); // ������������ ������� win-cp1251 � ���� �����
	SetConsoleOutputCP(1251); // ������������ ������� win-cp1251 � ���� ������
	int N;
	cout << "������ ������� ���������� N: "; cin >> N;
	Student* p = new Student[N];
	Fahoviy posada{};
	string prizv, Kurs;
	double proc = 0, avg = 0, average;
	int found;
	char filename[100]{};
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [3] - ������� ������������� �����" << endl;
		cout << " [4] - ������� ����� �������� �� ������� �� ��������" << endl;
		cout << " [5] - �������� ������������� �� ���� �����" << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
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
			cout << "������ ����� ������:" << endl;
			cin.get(); // ������� ����� ��������� � �� ����������� �������
			cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����
			cout << "������ �������: "; getline(cin, prizv);
			cout << endl;
			cout << "������ ������ � ����������: ";
			cin >> Kurs;
			cout << "������ ������� ���: ";
			cin >> average;
			if ((found = BinSearch(p, N, prizv, Kurs, average)) != -1)
				cout << "�������� �������� � ������� " << found + 1 << endl;
			else
				cout << "�������� �������� �� ��������" << endl;
			break;
		case 5:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;


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
		cout << "������� � " << i + 1 << ":" << endl;
		cin.get(); // ������� ����� ��������� � �� ����������� ������� 
		cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� ����� 

		cout << " �������: "; getline(cin, p[i].prizv);
		cout << " ����: "; getline(cin, p[i].kurs);

		cout << " ��� � ������: "; cin >> p[i].fizyka;
		cout << " ��� � ����������: "; cin >> p[i].matematyka;
		cout << " ������������ (0 - �������������, 1 - ������� ������, 2 - ���������): ";
		cin >> Predmet;
		p[i].specialnist = (Fahoviy)Predmet;
		switch (p[i].specialnist)
		{
		case PROGRAMUVANNA:
			cout << " ��� � ������������� : "; cin >> p[i].programuvanna;
			break;
		case CHSLMETOD:
			cout << " ��� � ��������� ������ : "; cin >> p[i].chslmetod;
			break;
		case PEDAGOGIKA:
			cout << " ��� � ��������� : "; cin >> p[i].pedagogika;
			break;
		}
		cout << endl;
	}
}
void Print(Student* p, const int N)
{
	cout << "===================================================================================================================="
		<< endl;
	cout << "__________________________________________|                               ����                                     |"
		<< endl;
	cout << "|  �  |  �������  | ���� | ������������ |  Գ����  |  ����������  | ������������� | ������� ������ | ��������� |"
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
	for (int i0 = 0; i0 < N - 1; i0++) // ����� "���������"
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
		I[i] = i; // ��������� ���� ����������� ������
	int i, j, value; // �������� ��������� ����� �������
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
	cout << "__________________________________________|                               ����                                     |"
		<< endl;
	cout << "|  �  |  �������  | ���� | ������������ |  Գ����  |  ����������  | ������������� | ������� ������ | ��������� |"
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
