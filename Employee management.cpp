#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Employee {
private:
    int id;
    char name[50];
    char department[50];
    float salary;

public:
    void addEmployee();
    void displayEmployee() const;
    int getId() const;
    void updateEmployee();
};

// Add Employee
void Employee::addEmployee() {
    cout << "Enter Employee ID: ";
    cin >> id;
    cin.ignore();

    cout << "Enter Name: ";
    cin.getline(name, 50);

    cout << "Enter Department: ";
    cin.getline(department, 50);

    cout << "Enter Salary: ";
    cin >> salary;
}

// Display Employee
void Employee::displayEmployee() const {
    cout << left << setw(10) << id
         << setw(20) << name
         << setw(15) << department
         << setw(10) << salary << endl;
}

int Employee::getId() const {
    return id;
}

// Update Employee
void Employee::updateEmployee() {
    cin.ignore();
    cout << "Enter New Name: ";
    cin.getline(name, 50);

    cout << "Enter New Department: ";
    cin.getline(department, 50);

    cout << "Enter New Salary: ";
    cin >> salary;
}

// Function Declarations
void addRecord();
void displayAll();
void searchRecord();
void updateRecord();
void deleteRecord();

// Add Record
void addRecord() {
    Employee emp;
    ofstream file("employees.dat", ios::binary | ios::app);

    emp.addEmployee();
    file.write((char*)&emp, sizeof(emp));

    file.close();
    cout << "\nEmployee Added Successfully!\n";
}

// Display All Records
void displayAll() {
    Employee emp;
    ifstream file("employees.dat", ios::binary);

    cout << "\n-------------------------------------------------------------\n";
    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(15) << "Dept"
         << setw(10) << "Salary" << endl;
    cout << "-------------------------------------------------------------\n";

    while (file.read((char*)&emp, sizeof(emp))) {
        emp.displayEmployee();
    }

    file.close();
}

// Search Record
void searchRecord() {
    Employee emp;
    ifstream file("employees.dat", ios::binary);

    int searchId;
    cout << "Enter Employee ID to Search: ";
    cin >> searchId;

    bool found = false;

    while (file.read((char*)&emp, sizeof(emp))) {
        if (emp.getId() == searchId) {
            cout << "\nRecord Found:\n";
            emp.displayEmployee();
            found = true;
        }
    }

    if (!found)
        cout << "Record Not Found!\n";

    file.close();
}

// Update Record
void updateRecord() {
    fstream file("employees.dat", ios::binary | ios::in | ios::out);
    Employee emp;

    int searchId;
    cout << "Enter Employee ID to Update: ";
    cin >> searchId;

    bool found = false;

    while (file.read((char*)&emp, sizeof(emp))) {
        if (emp.getId() == searchId) {
            cout << "\nEnter New Details:\n";
            emp.updateEmployee();

            int pos = -1 * sizeof(emp);
            file.seekp(pos, ios::cur);
            file.write((char*)&emp, sizeof(emp));

            cout << "Record Updated Successfully!\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Record Not Found!\n";

    file.close();
}

// Delete Record
void deleteRecord() {
    Employee emp;
    ifstream file("employees.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    int deleteId;
    cout << "Enter Employee ID to Delete: ";
    cin >> deleteId;

    bool found = false;

    while (file.read((char*)&emp, sizeof(emp))) {
        if (emp.getId() != deleteId) {
            temp.write((char*)&emp, sizeof(emp));
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("employees.dat");
    rename("temp.dat", "employees.dat");

    if (found)
        cout << "Record Deleted Successfully!\n";
    else
        cout << "Record Not Found!\n";
}

// Main Function
int main() {
    int choice;

    do {
        cout << "\n===== Employee Management System =====\n";
        cout << "1. Add Employee\n";
        cout << "2. Display All Employees\n";
        cout << "3. Search Employee\n";
        cout << "4. Update Employee\n";
        cout << "5. Delete Employee\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addRecord(); break;
        case 2: displayAll(); break;
        case 3: searchRecord(); break;
        case 4: updateRecord(); break;
        case 5: deleteRecord(); break;
        case 6: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}