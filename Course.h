#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "MyBag.h"
using namespace std;
using namespace TemplateVersion;
 

class Course
{
private:
    string code;
    string name;

    MyBagT<int> studentIDs;
    MyBagT<string> studentNames;
    MyBagT<double> studentScores;
    MyBagT<char> studentGrades;

public:
    Course() = default;
    Course(const string& c, const string& n) : code(c), name(n) {}
    ~Course() = default;

    void setCode(const string& c) { code = c; }
    void setName(const string& n) { name = n; }
    const string& getCode() const { return code; }
    const string& getName() const { return name; }

    // add a student automatically computing grade
    void addStudent(int id, const string& studentName, double score) {
        char letter;
        if (score >= 90) letter = 'A';
        else if (score >= 80) letter = 'B';
        else if (score >= 70) letter = 'C';
        else if (score >= 60) letter = 'D';
        else letter = 'F';

        studentIDs.insert(id);
        studentNames.insert(studentName);
        studentScores.insert(score);
        studentGrades.insert(letter);
    }

    // load from file (first line = code name, rest = id,name,score)
    bool loadFromFile(const string& filename)
    {
        ifstream fin(filename);
        if (!fin) return false;

        string firstLine;
        getline(fin, firstLine);
        stringstream ss(firstLine);
        ss >> code;
        getline(ss, name);
        if (!name.empty() && name[0] == ' ') name.erase(0, 1);

        string line;
        while (getline(fin, line)) {
            if (line.empty()) continue;
            stringstream ls(line);
            string idStr, nameStr, gradeStr;
            getline(ls, idStr, ',');
            getline(ls, nameStr, ',');
            getline(ls, gradeStr);
            if (!nameStr.empty() && nameStr[0] == ' ') nameStr.erase(0, 1);
            int id = stoi(idStr);
            double score = stod(gradeStr);
            addStudent(id, nameStr, score);
        }
        return true;
    }

    // find index by ID
    int findIndexByID(int id) const {
        for (int i = 0; i < studentIDs.getSize(); ++i)
            if (studentIDs[i] == id) return i;
        return -1;
    }

    // remove by index
    void removeStudentByIndex(int idx) {
        studentIDs.remove(idx);
        studentNames.remove(idx);
        studentScores.remove(idx);
        studentGrades.remove(idx);
    }

    // search by ID
    void searchByID(int id) const {
        int idx = findIndexByID(id);
        if (idx == -1) {
            cout << "\n\tNo student found with ID " << id << "\n";
            return;
        }
        printHeader();
        printRow(idx);
    }

    // search by name
    void searchByName(const string& key) const {
        string lowerKey = key;
        for (auto& c : lowerKey) c = tolower(c);
        bool found = false;
        printHeader();
        for (int i = 0; i < studentIDs.getSize(); ++i) {
            string lowerName = studentNames[i];
            for (auto& c : lowerName) c = tolower(c);
            if (lowerName.find(lowerKey) != string::npos) {
                printRow(i);
                found = true;
            }
        }
        if (!found) cout << "\n\tNo student found with name containing '" << key << "'\n";
    }

    // display entire course
    void display() const {
        cout << "\n\t" << code << " " << name << "\n";
        printHeader();
        for (int i = 0; i < studentIDs.getSize(); ++i)
            printRow(i);
    }

    // friend operator<< prints full table
    friend ostream& operator<<(ostream& os, const Course& c) {
        os << "\n\t" << c.code << " " << c.name << "\n";
        c.printHeader(os);
        for (int i = 0; i < c.studentIDs.getSize(); ++i)
            c.printRow(os, i);
        return os;
    }

private:
    void printHeader(ostream& os = cout) const {
        os << "\n\t" << left << setw(10) << "ID"
            << setw(30) << "Name" << setw(8) << "Score"
            << setw(6) << "Grade" << "\n";
        os << "\t" << string(60, char(196)) << "\n";
    }

    void printRow(int i) const { printRow(cout, i); }

    void printRow(ostream& os, int i) const {
        os << "\t" << left << setw(10) << studentIDs[i]
            << setw(30) << studentNames[i]
            << setw(8) << fixed << setprecision(1) << studentScores[i]
            << setw(6) << studentGrades[i] << "\n";
    }
};