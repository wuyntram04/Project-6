#include<iostream>
#include "input.h"
using namespace std;

void mainMenu();
void subMenu();
void nonTemplateFuntion();
void TemplateFuntion();
void ApplicationMenu();
void ApplicationFuntion();



int main()
{
	do
	{
		system("cls");

		mainMenu();

		switch (inputInteger("\n\t\tOption: "))
		{
		case 1: nonTemplateFuntion();
			break;
		case 2: TemplateFuntion();	
			break;
		case 3: ApplicationFuntion();
			break;
		case 0: exit(0);

		default:
			cout << "\n\tERROR: Invalid input.";
			break;
		}

		cout << "\n\t";
		system("pause");
	} while (true);

	return EXIT_SUCCESS;
}

void mainMenu()
{
	cout << "\n\tCMPR131 Chapter 6: non-template and template Container by Thi Ho, Thi Ngoc Pham, Khang Quach (9/30/25)";
	cout << "\n\t" << string(100, char(205));
	cout << "\n\t\t1> Non-template MyBag container of int";
	cout << "\n\t\t2> Template MyBag<double> container";
	cout << "\n\t\t3> Application using MyBag container";
	cout << "\n\t" << string(100, char(196));
	cout << "\n\t\t0> Exit";
	cout << "\n\t" << string(100, char(205));

}

void subMenu()
{
	cout << "\n\t" << string(100, char(205));
	cout << "\n\t\tA> clear";
	cout << "\n\t\tB> insert";
	cout << "\n\t\tC> search";
	cout << "\n\t\tD> remove";
	cout << "\n\t\tE> sort";
	cout << "\n\t\tF> display";
	cout << "\n\t" << string(100, char(196));
	cout << "\n\t\t0> return";
	cout << "\n\t" << string(100, char(205));
}

void ApplicationMenu()
{
	cout << "\n\t3> Courses using MyBags of integers, strings, doubles, and chars";
	cout << "\n\t" << string(100, char(205));
	cout << "\n\t\t1> Specify the number of courses";
	cout << "\n\t\t2> Read in data file and insert into courses";
	cout << "\n\t\t3> Search for a student record from a course";
	cout << "\n\t\t4> Remove a student record from a course";
	cout << "\n\t\t5> Display course(s)";
	cout << "\n\t" << string(100, char(196));
	cout << "\n\t\t0> return";
	cout << "\n\t" << string(100, char(205));
}

void nonTemplateFuntion()
{
	do
	{
		system("cls");
		cout << "\n\t1> Non-template MyBag container of int";
		subMenu();
		switch (toupper(inputChar("\n\t\tOption: ")))
		{
		case 'A':
			break;
		case 'B':
			break;
		case 'C':
			break;
		case 'D':
			break;
		case 'E':
			break;
		case 'F':
			break;
		case '0': return;
		default:
			cout << "\n\tERROR: Invalid input.";
			break;
		}

		cout << "\n\t";
		system("pause");

	} while (true);
}

void TemplateFuntion()
{
	do
	{
		system("cls");
		cout << "\n\t2> Template MyBag<double> container";
		subMenu();
		switch (toupper(inputChar("\n\t\tOption: ")))
		{
		case 'A':
			break;
		case 'B':
			break;
		case 'C':
			break;
		case 'D':
			break;
		case 'E':
			break;
		case 'F':
			break;
		case '0': return;
		default:
			cout << "\n\tERROR: Invalid input.";
			break;
		}

		cout << "\n\t";
		system("pause");

	} while (true);
}

void ApplicationFuntion()
{
	do
	{
		system("cls");
		ApplicationMenu();

		switch (inputInteger("\n\t\tOption: "))
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 0: return;
		default:
			cout << "\n\tERROR: Invalid input.";
			break;
		}

		cout << "\n\t";
		system("pause");

	} while (true);
}