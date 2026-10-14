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

    if (!readGradeData(students, studentCount, testCount))
    {
        releaseMemory(students, studentCount);
        return 1;
    }

    releaseMemory(students, studentCount);

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

    // Allocate the Student array
    students = new Student[studentCount];

    cout << "Allocated memory for " << studentCount << " students." << endl;

    // Allocate a score array for each student
    for (int student = 0; student < studentCount; student++)
    {
        students[student].scores = new double[testCount];
    }

    cout << "Allocated score arrays for " << studentCount << " students." << endl;

    for (int student = 0; student < studentCount; student++)
{
    // Read the student's name and ID
    if (!(inputFile >> students[student].lastName
                    >> students[student].studentID))
    {
        cout << "Error reading student information." << endl;
        return false;
    }

    // Read the student's test scores
    for (int test = 0; test < testCount; test++)
    {
        if (!(inputFile >> students[student].scores[test]))
        {
            cout << "Error reading test scores." << endl;
            return false;
        }
    }
}

    return true; // Temporary: allocation test only
}

void releaseMemory(Student*& students, int studentCount)
{
    if (students == nullptr)
    {
        return;
    }

    for (int student = 0; student < studentCount; student++)
    {
        delete[] students[student].scores;
        students[student].scores = nullptr;
    }

    delete[] students;
    students = nullptr;
}