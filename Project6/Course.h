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


    // Precondition: os is a valid output stream (defaults to cout).
    // Postcondition: Writes the column headers for the student table to os.
    void printHeader(ostream& os = cout) const {
        os << "\n\t" << left << setw(10) << "ID"
            << setw(30) << "Name" << setw(8) << "Score"
            << setw(6) << "Grade" << "\n";
        os << "\t" << string(60, char(196)) << "\n";
    }

    // Precondition: i is a valid index (0 ≤ i < studentIDs.getSize()).
    // Postcondition: Writes the row of student data at index i to cout.
    void printRow(int i) const { printRow(cout, i); }


    // Precondition: os is a valid output stream; i is a valid index.
// Postcondition: Writes the row of student data at index i to os.
    void printRow(ostream& os, int i) const {
        os << "\t" << left << setw(10) << studentIDs[i]
            << setw(30) << studentNames[i]
            << setw(8) << fixed << setprecision(1) << studentScores[i]
            << setw(6) << studentGrades[i] << "\n";



    }

public:
    // Precondition: none.
    // Postcondition: Creates an empty Course object with no code, name, or students.
    Course() = default;

    // Precondition: c and n are valid strings.
   // Postcondition: Creates a Course object with code=c 
    Course(const string& c, const string& n) : code(c), name(n) {}

    // Precondition: none.
    // Postcondition: Releases any resources held by the Course object.
    ~Course() = default;

    // Precondition: c is a valid course code string.
   // Postcondition: The course code is set to c.
    void setCode(const string& c) { code = c; }

    // Precondition: n is a valid course name string.
    // Postcondition: The course name is set to n.
    void setName(const string& n) { name = n; }

    // Precondition: none.
    // Postcondition: Returns a const reference to the course code.
    const string& getCode() const { return code; }

    // Precondition: none.
    // Postcondition: Returns a const refe
    const string& getName() const { return name; }

    // add a student automatically computing grade
    // Precondition: id is a student ID (preferably unique);
    //               studentName is a non-empty string;
    //               score ≥ 0.
    // Postcondition: A student record (id, studentName, score, letter grade)
    //                is appended to all student data containers.
    void addStudent(int id, const string& studentName, double score) {
        char letter = computeLetterGrade(score);

        studentIDs.insert(id);
        studentNames.insert(studentName);
        studentScores.insert(score);
        studentGrades.insert(letter);
    }
    // Precondition: There may be zero or more students in the course.
    // Postcondition: Computes the average score of all students.
    //                Returns the average score as a double.
    //                If no students are present, returns 0.0.
    double getAverageScore() const {
        if (studentScores.getSize() == 0) return 0.0;
        double sum = 0.0;
        for (int i = 0; i < studentScores.getSize(); ++i)
        {
            sum += studentScores[i];
        }
        return sum / studentScores.getSize();
    }


    // load from file (first line = code name, rest = id,name,score)
    // Precondition: filename is the name of a text file with correct format:
    //   first line = course code + course name
    //   subsequent lines = id,name,score
    // Postcondition: Sets course code and name from file;
    //                loads all student records into the course;
    //                returns true if loaded successfully, false if file could not be opened.
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
        // Read each non-empty line after the first header line
        while (getline(fin, line))
        {
            // Skip blank lines
            if (line.empty())
                continue;

            // Break the current line into fields separated by commas
            stringstream ls(line);

            // Strings to hold each field temporarily
            string idStr;
            string nameStr;
            string scoreStr;

            // Extract fields: ID, Name, Score
            getline(ls, idStr, ',');    // up to first comma
            getline(ls, nameStr, ',');  // up to second comma
            getline(ls, scoreStr);      // rest of the line

            // Trim leading space from name if present
            if (!nameStr.empty() && nameStr[0] == ' ')
                nameStr.erase(0, 1);

            // Convert strings to correct types
            int id = stoi(idStr);            // string → int
            double score = stod(scoreStr);   // string → double

            // Add the student to the course
            addStudent(id, nameStr, score);
        }
        return true;
    }

    // find index by ID
    // Precondition: id is any integer.
    // Postcondition: Returns the index of the student with the given id,
    //                or -1 if no such student exists.
    int findIndexByID(int id) const {
        for (int i = 0; i < studentIDs.getSize(); ++i)
            if (studentIDs[i] == id) return i;
        return -1;
    }

    // remove by index
    // Precondition: idx is a valid index (0 ≤ idx < studentIDs.getSize()).
    // Postcondition: Removes the student record at index idx from all student containers.
    void removeStudentByIndex(int idx) {
        studentIDs.remove(idx);
        studentNames.remove(idx);
        studentScores.remove(idx);
        studentGrades.remove(idx);
    }

    // search by ID
    // Precondition: id is any integer.
    // Postcondition: Prints the record of the student with id to cout
    //                or prints a message if no such student exists.
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
    // Precondition: key is a string to search within student names.
    // Postcondition: Prints all student records containing key (case-insensitive)
    //                or prints a message if none are found.
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
    // Precondition: none.
    // Postcondition: Prints the course code, name, and all student records to cout.
    void display() const {
        cout << "\n\t" << code << " " << name << "\n";
        printHeader();
        for (int i = 0; i < studentIDs.getSize(); ++i)
            printRow(i);

    }

    // Precondition: score >= 0.
    // Postcondition: Returns the letter grade corresponding to the score.
    char computeLetterGrade(double score) const
    {
        if (score >= 90) return 'A';
        else if (score >= 80) return 'B';
        else if (score >= 70) return 'C';
        else if (score >= 60) return 'D';
        else return 'F';
    }

    // friend operator<< prints full table
     // Precondition: os is a valid output stream.
    // Postcondition: Writes the full table of the course to os.
    friend ostream& operator<<(ostream& os, const Course& c)
    {
        os << "\n\t" << c.code << " " << c.name << "\n";
        c.printHeader(os);
        for (int i = 0; i < c.studentIDs.getSize(); ++i)
            c.printRow(os, i);


        // print average once at the end
        double avg = c.getAverageScore();
        char letter = c.computeLetterGrade(avg);
        os << "\n\tAverage score and grade: "
            << fixed << setprecision(1) << avg
            << "(" << letter << ")\n\n";
        return os;

    }
};