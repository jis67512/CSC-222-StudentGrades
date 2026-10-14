#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct Student
{
    string lastName;
    int studentID;
    double* scores = nullptr;
    double average;
    char letterGrade;
};

bool readGradeData(Student*& students, int& studentCount, int& testCount);

void calculateAverages(Student students[], int studentCount, int testCount);

void assignLetterGrades(Student students[], int studentCount);

void displayReport(const Student students[], int studentCount, int testCount);

void releaseMemory(Student*& students, int studentCount);

int main()
{
    Student* students = nullptr;

    int studentCount = 0;
    int testCount = 0;

    readGradeData(students, studentCount, testCount);
    
    return 0;
}

bool readGradeData(Student*& students, int& studentCount, int& testCount)
{
    ifstream inputFile("student_data.txt");

    if (!inputFile)
    {
        cout << "Error opening student_data.txt" << endl;
        return false;
    }

    if (!(inputFile >> studentCount >> testCount) ||
        studentCount <= 0 || testCount <= 0)
    {
        cout << "Invalid file header." << endl;
        return false;
    }

    cout << "Students: " << studentCount << endl;
    cout << "Tests: " << testCount << endl;

    return true; // Temporary: header validation test only
}