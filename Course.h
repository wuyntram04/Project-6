#include"MyBag.h"

#pragma once
class Course
{
private:
	string course = "unknown";
	TemplateVersion::MyBagT<int> id;
	TemplateVersion::MyBagT<string> name;
	TemplateVersion::MyBagT<double> score;
	TemplateVersion::MyBagT<char> grade;

public:

	void setCourse(string n)
	{
		course = n;
	}

	void addStudent(int i, string n, double s)
	{
		id.insert(i);
		name.insert(n);
		score.insert(s);

		char g = 'n';

		if (s >= 89)
		{
			g = 'A';
		}
		else if (s >= 79)
		{
			g = 'B';
		}
		else if (s >= 69)
		{
			g = 'C';
		}
		else if (s >= 59)
		{
			g = 'D';
		}

		grade.insert(g);
	}
};

