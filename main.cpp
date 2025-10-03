#include<iostream>
#include<vector>
#include <sstream>
#include <fstream>
#include<iomanip>
#include "input.h"
#include "MyBag.h"
#include "Course.h"

using namespace std;

///////////////========================PROTOTYPE=====================//////////////////////
void mainMenu();
void subMenu();
void nonTemplateFuntion();
void TemplateFuntion();
void ApplicationMenu();
void ApplicationFunction();




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
		case 3: ApplicationFunction();
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
	nonTemplate::MyBag bag;

	do
	{
		system("cls");
		cout << "\n\t1> Non-template MyBag container of int";
		subMenu();
		switch (toupper(inputChar("\n\t\tOption: ")))
		{
		case 'A':
		{
			bag.clear();
			cout << "\n\t\tMyBag is cleared of all elements.";
		}
		break;
		case 'B': bag.insert(inputInteger("\n\t\tEnter a value and insert into MyBag: "));
			break;
		case 'C':
		{
			if (bag.isEmpty())
			{
				cout << "\n\t\tMyBag is Empty.";
			}
			else
				bag.search(inputInteger("\n\t\tEnter a value to search from MyBag: "));
		}
		break;
		case 'D':
		{
			if (bag.isEmpty())
			{
				cout << "\n\t\tMyBag is Empty.";
			}
			else
				bag.remove(inputInteger("\n\t\tEnter an index(subscript) from MyBag to be deleted: "));
		}
		break;
		case 'E':
		{
			if (bag.isEmpty())
			{
				cout << "\n\t\tMyBag is Empty.";
			}
			else
				bag.sortAscending();
		}
		break;
		case 'F': cout << bag;
			break;
		case '0': return;
		default:
			cout << "\n\tERROR: Invalid input.";
			break;
		}

		cout << "\n\n\t";
		system("pause");

	} while (true);
}

void TemplateFuntion()
{
	TemplateVersion::MyBagT<double> dbag;
	do
	{
		system("cls");
		cout << "\n\t2> Template MyBag<double> container";
		subMenu();
		switch (toupper(inputChar("\n\t\tOption: ")))
		{
		case 'A':
		{
			dbag.clear();
			cout << "\n\t\tMyBag is cleared of all elements.";
		}
		break;
		case 'B': dbag.insert(inputDouble("\n\t\tEnter a value and insert into MyBag: "));
			break;
		case 'C':
		{
			if (dbag.isEmpty())
			{
				cout << "\n\t\tMyBag is Empty.";
			}
			else
				dbag.search(inputDouble("\n\t\tEnter a value to search from MyBag: "));
		}
		break;
		case 'D':
		{
			if (dbag.isEmpty()) {
				cout << "\n\t\tMyBag is Empty.";
			}
			else {
				int idx = inputInteger("\n\t\tEnter an index(subscript) from MyBag to be deleted: ");
				cout << "\n\t\tValue " << dbag[idx] << " has been deleted from MyBag.";
				dbag.remove(idx);
			}
			break;
		case 'E':
		{
			if (dbag.isEmpty())
			{
				cout << "\n\t\tMyBag is Empty.";
			}
			else
				dbag.sortAscending();
		}
		break;
		case 'F':  cout << dbag;
			break;
		case '0': return;
		default:
			cout << "\n\tERROR: Invalid input.";
			break;
		}

	
		}

		cout << "\n\n\t";
		system("pause");

	} while (true);
}

void ApplicationFunction()
	{
		static Course* courses = nullptr; // dynamic array of Course
		static int courseCount = 0;       // how many courses allocated

		do {
			system("cls");
			ApplicationMenu();

			switch (inputInteger("\n\t\tOption: ")) {

			case 1: { // specify number of courses
				int n = inputInteger("\n\t\t1> Enter the number of courses (1-100): ", 1, 100);
				delete[] courses;                // free any previous allocation
				courses = new Course[n];         // allocate new dynamic array
				courseCount = n;
				cout << "\n\t\t" << n << " Course(s) has been created..";
				break;
			}

			case 2: { // read in data files
				if (courseCount == 0) { cout << "\n\tNo courses yet."; break; }

				for (int i = 0; i < courseCount; ++i) {
					while (true) {
						string filename = inputString("\n\t\t2> Enter a data file name for Course[" + to_string(i) + "] (STOP - return): ", true);
						if (filename == "STOP" || filename == "stop") {
							i = courseCount; // break outer for loop
							break;
						}
						if (!courses[i].loadFromFile(filename)) {
							cout << "\n\tERROR: file, " << filename << ", cannot be found. Please re-specify.\n";
							continue; // loop again asking for the same Course[i]
						}
						cout << "\n\tData from file, " << filename
							<< ", has been read and stored into Course[" << i << "].\n";
						break; // go to next course index
					}
				}
				break;
			}

			case 3: { // search for a student record from a course
				if (courseCount == 0) { cout << "\n\tNo courses yet."; break; }

				// list courses first
				cout << "\n\t3> Course(s)";
				cout << "\n\t" << string(80, char(196));
				for (int i = 0; i < courseCount; ++i) {
					cout << "\n\t " << (i + 1) << ". " << courses[i].getCode() << " " << courses[i].getName();
				}
				cout << "\n\t" << string(80, char(196));
				int choice = inputInteger("\n\tSelect course to search: ", 1, courseCount);
				Course& selected = courses[choice - 1];

				do {
					cout << "\n\t3> Search by";
					cout << "\n\t" << string(55, char(196));
					cout << "\n\t\t1. ID Number";
					cout << "\n\t\t2. Name";
					cout << "\n\t\t0. return";
					cout << "\n\t" << string(55, char(196));
					int searchMode = inputInteger("\n\t Option: ", 0, 2);
					if (searchMode == 0) break; // exit search menu

					if (searchMode == 1) {
						int searchID = inputInteger("\n\t\tEnter StudentID to search: ");
						selected.searchByID(searchID);
					}
					else {
						string searchName = inputString("\n\t\tEnter name (full or partial) to search: ", true);
						selected.searchByName(searchName);
					}

				} while (true);
				break;
			}

			case 4:
			{ // remove a student record from a course
				if (courseCount == 0) { cout << "\n\tNo courses yet."; break; }

				// list courses first
				cout << "\n\tCourse";
				cout << "\n\t" << string(80, char(196));
				for (int i = 0; i < courseCount; ++i) {
					cout << "\n\t " << (i + 1) << ". " << courses[i].getCode() << " " << courses[i].getName();
				}
				cout << "\n\t" << string(80, char(196));
				int choice = inputInteger("\n\tSelect course to delete from: ", 1, courseCount);
				Course& selected = courses[choice - 1];

				int delID = inputInteger("\n\tEnter a student ID to search and delete: ");
				int idx = selected.findIndexByID(delID);
				if (idx == -1) {
					cout << "\n\tNo student found with ID " << delID << "\n";
				}
				else {
					selected.removeStudentByIndex(idx);
					cout << "\n\tID: " << delID
						<< " has been found in Course '"
						<< selected.getCode() << " " << selected.getName()
						<< "' and has been removed.\n";
				}
				break;
			}

			case 5:
			{ // display
				if (courseCount == 0) { cout << "\n\tNo courses yet."; break; }

				cout << "\n\tCourse";
				cout << "\n\t" << string(80, char(196));
				for (int i = 0; i < courseCount; ++i) {
					cout << "\n\t " << (i + 1) << ". " << courses[i].getCode() << " " << courses[i].getName();
				}
				cout << "\n\t " << (courseCount + 1) << ". all";
				cout << "\n\t" << string(80, char(196));
				int choice = inputInteger("\n\t Option: ", 1, courseCount + 1);

				if (choice == courseCount + 1) {
					for (int i = 0; i < courseCount; ++i) cout << courses[i];
				}
				else {
					cout << courses[choice - 1];
				}
				break;
			}

			case 0:
				delete[] courses; // free before exit
				return;

			default:
				cout << "\n\tERROR: Invalid input.";
				break;
			}

			cout << "\n\n\t";
			system("pause");

		} while (true);
	}

