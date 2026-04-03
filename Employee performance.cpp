#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    int id;
    string name;
    float salary;
    int tasks;
    float hours;
    float focus;

public:
    void input() {
        cout << "\nEnter ID: ";
        cin >> id;

        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Base Salary: ";
        cin >> salary;

        cout << "Enter Tasks Completed: ";
        cin >> tasks;

        cout << "Enter Hours Worked: ";
        cin >> hours;

        cout << "Enter Focus Level (0-10): ";
        cin >> focus;
    }

    float performance() {
        return (tasks * 2 + hours * 1.5 + focus * 5) / 3;
    }

    string getRating() {
        float p = performance();

        if (p >= 80) return "Excellent";
        else if (p >= 60) return "Good";
        else if (p >= 40) return "Average";
        else return "Poor";
    }

    float finalSalary() {
        float p = performance();

        if (p >= 80) return salary * 1.2;
        else if (p >= 60) return salary * 1.1;
        else if (p >= 40) return salary;
        else return salary * 0.9;
    }

    void display() {
        cout << "\nID: " << id;
        cout << "\nName: " << name;
        cout << "\nPerformance: " << performance();
        cout << "\nRating: " << getRating();
        cout << "\nFinal Salary: " << finalSalary() << endl;
    }
};

class Company {
private:
    Employee* emp;
    int count;

public:
    void inputEmployees() {
        cout << "Enter number of employees today: ";
        cin >> count;

        emp = new Employee[count];

        for (int i = 0; i < count; i++) {
            cout << "\n--- Employee " << i + 1 << " ---";
            emp[i].input();
        }
    }

    void displayEmployees() {
        cout << "\n\n=== All Employee Reports ===\n";

        for (int i = 0; i < count; i++) {
            emp[i].display();
        }
    }

    ~Company() {
        delete[] emp;
    }
};

int main() {
    Company c;

    c.inputEmployees();
    c.displayEmployees();

    return 0;
}