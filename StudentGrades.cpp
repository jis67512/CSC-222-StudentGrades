/*
    CSC 222 - Student Grades Project
    Author: James Scott
    Date: October 14, 2026

    Description:
    This program reads student information and test scores
    from an input file. It uses dynamic memory allocation
    to store student records and their test scores,
    calculates each student's average, assigns a letter
    grade, and displays a formatted report.

    The program releases all dynamically allocated memory
    before terminating.
*/

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

    assignLetterGrades(students, studentCount);
    
    displayReport( students, studentCount, testCount);
    
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

    

    // Allocate the Student array
    students = new Student[studentCount];


    // Allocate a score array for each student
    for (int student = 0; student < studentCount; student++)
    {
        students[student].scores = new double[testCount];
    }

    for (int student = 0; student < studentCount; student++)
{
    // Read the student's name and ID
    if (!(inputFile >> students[student].lastName >> students[student].studentID))
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

    return true; 
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

void displayReport(const Student students[], int studentCount, int testCount)
{
    cout << fixed << setprecision(2);

    cout << left << setw(15) << "Last Name" << setw(12) << "Student ID";

    for (int test = 0; test < testCount; test++)
    {
        cout << right << setw(10) << ("Test " + to_string(test + 1));
    }

    cout << setw(12) << "Average" << setw(10) << "Grade" << endl;

// Display every student
for (int student = 0; student < studentCount; student++)
{
    cout << left << setw(15) << students[student].lastName << setw(12) << students[student].studentID;
    // Display student's scores
    for (int test = 0; test < testCount; test++)
    {
        cout << right << setw(10) << students[student].scores[test];
    }

    cout << setw(12) << students[student].average << setw(10) << students[student].letterGrade << endl;
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