#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Student
{
    int rollNo;
    string name;
    int age;
    string branch;
};

string fileName = "students.txt";

// Read all students from file
vector<Student> loadStudents()
{
    vector<Student> students;
    ifstream file(fileName);

    string line;

    while(getline(file, line))
    {
        stringstream ss(line);
        Student s;
        string temp;

        getline(ss, temp, ',');
        s.rollNo = stoi(temp);

        getline(ss, s.name, ',');

        getline(ss, temp, ',');
        s.age = stoi(temp);

        getline(ss, s.branch);

        students.push_back(s);
    }

    file.close();
    return students;
}

// Save all students to file
void saveStudents(vector<Student>& students)
{
    ofstream file(fileName);

    for(auto s : students)
    {
        file << s.rollNo << ","
             << s.name << ","
             << s.age << ","
             << s.branch << endl;
    }

    file.close();
}

// Add student
void addStudent()
{
    vector<Student> students = loadStudents();

    Student s;

    cout << "\nEnter Roll Number: ";
    cin >> s.rollNo;

    // Check duplicate roll number
    for(auto st : students)
    {
        if(st.rollNo == s.rollNo)
        {
            cout << "Roll number already exists!\n";
            return;
        }
    }

    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, s.name);

    cout << "Enter Age: ";
    cin >> s.age;

    cin.ignore();

    cout << "Enter Branch: ";
    getline(cin, s.branch);

    ofstream file(fileName, ios::app);

    file << s.rollNo << ","
         << s.name << ","
         << s.age << ","
         << s.branch << endl;

    file.close();

    cout << "\nStudent added successfully.\n";
}

// Display all students
void displayStudents()
{
    vector<Student> students = loadStudents();

    if(students.empty())
    {
        cout << "\nNo records found.\n";
        return;
    }

    cout << "\n------ Student Records ------\n";

    for(auto s : students)
    {
        cout << "\nRoll No : " << s.rollNo;
        cout << "\nName    : " << s.name;
        cout << "\nAge     : " << s.age;
        cout << "\nBranch  : " << s.branch;
        cout << "\n-------------------------";
    }
}

// Search student
void searchStudent()
{
    int roll;

    cout << "\nEnter Roll Number: ";
    cin >> roll;

    vector<Student> students = loadStudents();

    for(auto s : students)
    {
        if(s.rollNo == roll)
        {
            cout << "\nStudent Found\n";

            cout << "Roll No : " << s.rollNo << endl;
            cout << "Name    : " << s.name << endl;
            cout << "Age     : " << s.age << endl;
            cout << "Branch  : " << s.branch << endl;

            return;
        }
    }

    cout << "Student not found.\n";
}

// Update student
void updateStudent()
{
    int roll;

    cout << "\nEnter Roll Number to Update: ";
    cin >> roll;

    vector<Student> students = loadStudents();

    bool found = false;

    for(auto &s : students)
    {
        if(s.rollNo == roll)
        {
            found = true;

            cin.ignore();

            cout << "Enter New Name: ";
            getline(cin, s.name);

            cout << "Enter New Age: ";
            cin >> s.age;

            cin.ignore();

            cout << "Enter New Branch: ";
            getline(cin, s.branch);

            break;
        }
    }

    if(found)
    {
        saveStudents(students);
        cout << "Record updated.\n";
    }
    else
    {
        cout << "Student not found.\n";
    }
}

// Delete student
void deleteStudent()
{
    int roll;

    cout << "\nEnter Roll Number to Delete: ";
    cin >> roll;

    vector<Student> students = loadStudents();
    vector<Student> updatedList;

    bool found = false;

    for(auto s : students)
    {
        if(s.rollNo == roll)
        {
            found = true;
        }
        else
        {
            updatedList.push_back(s);
        }
    }

    if(found)
    {
        saveStudents(updatedList);
        cout << "Record deleted.\n";
    }
    else
    {
        cout << "Student not found.\n";
    }
}

// Count students
void totalStudents()
{
    vector<Student> students = loadStudents();

    cout << "\nTotal Students = "
         << students.size()
         << endl;
}

int main()
{
    int choice;

    do
    {
        cout << "\n\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Total Students\n";
        cout << "7. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                totalStudents();
                break;

            case 7:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while(choice != 7);

    return 0;
}