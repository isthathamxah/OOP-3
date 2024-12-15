#include <iostream>
#include <vector>
using namespace std;

class Employee { // Base class Employee
protected:
    string name;
    int id;
    float baseSalary;

public:
    Employee(string n, int i, float b) : name(n), id(i), baseSalary(b) {}

    virtual float calculateSalary() = 0; // Virtual function to be overridden in derived classes
    virtual void displayInfo() { // Virtual function for displaying information
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
    }

    virtual ~Employee() {} // Virtual destructor
};

class Manager : public Employee { // Derived class Manager
private:
    float bonus;

public:
    Manager(string n, int i, float b, float bonusAmount) : Employee(n, i, b), bonus(bonusAmount) {}

    float calculateSalary() override {
        return baseSalary + bonus;
    }

    void displayInfo() override {
        Employee::displayInfo();
        cout << "Role: Manager" << endl;
        cout << "Base Salary: " << baseSalary << endl;
        cout << "Bonus: " << bonus << endl;
        cout << "Total Salary: " << calculateSalary() << endl;
    }
};

class Developer : public Employee { // Derived class Developer
private:
    int overtimeHours;
    float hourlyRate;

public:
    Developer(string n, int i, float b, int hours, float rate) : Employee(n, i, b), overtimeHours(hours), hourlyRate(rate) {}

    float calculateSalary() override {
        return baseSalary + (overtimeHours * hourlyRate);
    }

    void displayInfo() override {
        Employee::displayInfo();
        cout << "Role: Developer" << endl;
        cout << "Base Salary: " << baseSalary << endl;
        cout << "Overtime Hours: " << overtimeHours << endl;
        cout << "Hourly Rate: " << hourlyRate << endl;
        cout << "Total Salary: " << calculateSalary() << endl;
    }
};

class Intern : public Employee { // Derived class Intern
private:
    float stipend;

public:
    Intern(string n, int i, float s) : Employee(n, i, 0), stipend(s) {} // No baseSalary for Interns

    float calculateSalary() override {
        return stipend;
    }

    void displayInfo() override {
        Employee::displayInfo();
        cout << "Role: Intern" << endl;
        cout << "Stipend: " << stipend << endl;
        cout << "Total Salary: " << calculateSalary() << endl;
    }
};

int main() {
    vector<Employee*> employees; // Vector to store pointers to Employee objects
    int choice;

    while (true) {
        cout << "\nChoose Employee Type to Add:\n";
        cout << "1. Manager\n";
        cout << "2. Developer\n";
        cout << "3. Intern\n";
        cout << "4. Exit\n";
        cin >> choice;

        if (choice == 4) {
            break; // Exit loop if user chooses 'Exit'
        }

        string name;
        int id;
        float baseSalary;

        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter ID: ";
        cin >> id;

        switch (choice) {
        case 1: {
            float bonus;
            cout << "Enter Base Salary: ";
            cin >> baseSalary;
            cout << "Enter Bonus: ";
            cin >> bonus;
            employees.push_back(new Manager(name, id, baseSalary, bonus));
            break;
        }
        case 2: {
            int overtimeHours;
            float hourlyRate;
            cout << "Enter Base Salary: ";
            cin >> baseSalary;
            cout << "Enter Overtime Hours: ";
            cin >> overtimeHours;
            cout << "Enter Hourly Rate: ";
            cin >> hourlyRate;
            employees.push_back(new Developer(name, id, baseSalary, overtimeHours, hourlyRate));
            break;
        }
        case 3: {
            float stipend;
            cout << "Enter Stipend: ";
            cin >> stipend;
            employees.push_back(new Intern(name, id, stipend));
            break;
        }
        default:
            cout << "Invalid choice!\n";
            break;
        }
    }

    // Display details and calculate salaries using polymorphism
    for (Employee* emp : employees) {
        emp->displayInfo();
        cout << "Calculated Salary: " << emp->calculateSalary() << endl;
        cout << "-----------------------" << endl;
    }

    // Clean up dynamic memory
    for (Employee* emp : employees) {
        delete emp;
    }

    return 0;
}
