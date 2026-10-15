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

    calculateAverages(students, studentCount, testCount);

    // Temporary output to verify the calculations
    cout << "First student: " << students[0].lastName << endl;
    cout << "Student ID: " << students[0].studentID << endl;
    cout << "First test score: " << students[0].scores[0] << endl;
    cout << fixed << setprecision(2);
    cout << "Average: " << students[0].average << endl;

    assignLetterGrades(students, studentCount);
    
    //Temporary output to verify the letter grade
    cout << "Letter Grade: " << students[0].letterGrade << endl;
    
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

void calculateAverages(Student students[], int studentCount, int testCount)
{
    for (int student = 0; student < studentCount; student++)
    {
        double total = 0;

        for (int test = 0; test < testCount; test++)
        {
            total += students[student].scores[test];
        }

        students[student].average = total / testCount;
    }
}

void assignLetterGrades(Student students[], int studentCount)
{
    for (int student = 0; student < studentCount; student++)
    {
        double average = students[student].average;

        if (average >= 90)
        {
            students[student].letterGrade = 'A';
        }
        else if (average >= 80)
        {
            students[student].letterGrade = 'B';
        }
        else if (average >= 70)
        {
            students[student].letterGrade = 'C';
        }
        else if (average >= 60)
        {
            students[student].letterGrade = 'D';
        }
        else
        {
            students[student].letterGrade = 'F';
        }
    }
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