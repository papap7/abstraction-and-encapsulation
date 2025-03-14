#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <regex>
#include <unordered_map>

using namespace std;

class Employee {
private:
    string id;
    string name;
    double salary;

public:
    Employee(string empId, string empName, double empSalary) : id(empId), name(empName), salary(empSalary) {}

    virtual void calculateSalary() = 0;

    void setId(const string& empId) { 
        id = empId; 
    }
    void setName(const string& empName) { 
        name = empName;
    }
    void setSalary(const double& empSalary) {
        salary = empSalary;
    }

    string getId() const {
        return id;
    }
    string getName() const {
        return name;
    }
    double getSalary() const {
        return salary;
    }
};

unordered_map<string, Employee*> employees;

bool isValidNum(const string& input) {
    if (input.empty()) return false;
    regex pattern("^[0-9]+(\\.[0-9]{1,2})?$");
    return regex_match(input, pattern);
}

bool isValidString(const string& input) {
    if (input.empty()) return false;
    regex pattern("^[A-Za-z ]+$");
    return regex_match(input, pattern);
}

bool isValidId(const string& input) {
    if (input.length() != 3) return false;
    if ((isdigit(input[0]) && isdigit(input[1]) && isdigit(input[2])) ||
        (isupper(input[0]) && isupper(input[1]) && isupper(input[2]))) {
        return true;
    }
    return false;
}

class fTimeEmployee : public Employee {
public:
    fTimeEmployee(string id, string name, double salary) : Employee(id, name, salary) {}

    void calculateSalary() override {

        string tempId, tempName, tempSalary;

        cout << "\n------ Full-time Employee ------\n";
        for (;;) {
            cout << "Input a 3-digit ID (000 | ABC): ";
            getline(cin, tempId);
            if (!isValidId(tempId)) {
                cout << "Invalid ID. Please enter a valid 3-digit number or uppercase letters.\n";
                continue;
            }
            if (employees.find(tempId) != employees.end()) {
                cout << "ID already exists. Please enter a different ID.\n";
                continue;
            }
            break;
        }
        setId(tempId);

        for (;;) {
            cout << "Input your name (letters only): ";
            getline(cin, tempName);
            if (isValidString(tempName)) {
                setName(tempName);
                break;
            }
            cout << "Invalid name. Please enter letters only.\n";
        }

        for (;;) {
            cout << "Input salary: $";
            getline (cin, tempSalary);
            if (!isValidNum(tempSalary)) {
                cout << "Invalid salary. Please enter a valid number.\n";
                continue;
            }
            setSalary(stod(tempSalary));
            break;
        }

        cout << "Salary: $" << getSalary() << "\n";
        employees.insert({getId(), new fTimeEmployee(getId(), getName(), getSalary())});
    }
};

class pTimeEmployee : public Employee {
private:
    double hourlyWage;
    int workHours;

public:
    pTimeEmployee(string id, string name, double salary, double hourlyWage, int workHours) : Employee(id, name, salary), hourlyWage(hourlyWage), workHours(workHours) {}

    void setHourlyWage(double hourlyWage) {
        this->hourlyWage = hourlyWage;
    }
    void setWorkHours(int workHours) {
        this->workHours = workHours;
    }

    double getHourlyWage() const {
        return hourlyWage;
    }
    int getWorkHours() const {
        return workHours;
    }

    void calculateSalary() override {

        string tempId, tempName, tempSalary, tempHourlyWage, tempWorkHours;

        cout << "\n------ Part-time Employee ------\n";
        for (;;) {
            cout << "Input a 3-digit ID (000 | ABC): ";
            getline(cin, tempId);
            if (!isValidId(tempId)) {
                cout << "Invalid ID. Please enter a valid 3-digit number or uppercase letters.\n";
                continue;
            }
            if (employees.find(tempId) != employees.end()) {
                cout << "ID already exists. Please enter a different ID.\n";
                continue;
            }
            break;
        }
        setId(tempId);

        for (;;) {
            cout << "Input your name (letters only): ";
            getline(cin, tempName);
            if (isValidString(tempName)) {
                setName(tempName);
                break;
            }
            cout << "Invalid name. Please enter letters only.\n";
        }

        for (;;) {
            cout << "Input Hourly Wage: $";
            getline (cin, tempHourlyWage);
            if (!isValidNum(tempHourlyWage)) {
                cout << "Invalid input. Please enter a valid hourly wage.\n";
                continue;
            }
            setHourlyWage(stod(tempHourlyWage));
            break;
        }

        for (;;) {
            cout << "Input number of hours worked: ";
            getline (cin, tempWorkHours);
            if (!isValidNum(tempWorkHours)) {
                cout << "Invalid input. Please enter a valid hours work.\n";
                continue;
            }
            setWorkHours(stoi(tempWorkHours));
            break;
        }

        setSalary(getHourlyWage() * getWorkHours());
        cout << "Total Salary: $" << getSalary() << "\n";
        employees.insert({getId(), new pTimeEmployee(getId(), getName(), getSalary(), getHourlyWage(), getWorkHours())});
    }
};

class contractEmployee : public Employee {
private:
    double contractPayment;
    int numProject;

public:
    contractEmployee(string id, string name, double salary, double contractPayment, int numProject) : Employee(id, name, salary), contractPayment(contractPayment), numProject(numProject) {}

    void setContractPayment(double contractPayment) { 
        this->contractPayment = contractPayment;
    }
    void setNumProject(int numProject) { 
        this->numProject = numProject;
    }

    double getContractPayment() const { 
        return contractPayment;
    }
    int getNumProject() const { 
        return numProject;
    }

    void calculateSalary() override {

        string tempId, tempName, tempSalary, tempContractPayment, tempNumProject;

        cout << "\n------ Contractual Employee ------\n";
        for (;;) {
            cout << "Input a 3-digit ID (000 | ABC): ";
            getline(cin, tempId);
            if (!isValidId(tempId)) {
                cout << "Invalid ID. Please enter a valid 3-digit number or uppercase letters.\n";
                continue;
            }
            if (employees.find(tempId) != employees.end()) {
                cout << "ID already exists. Please enter a different ID.\n";
                continue;
            }
            break;
        }
        setId(tempId);

        for (;;) {
            cout << "Input your name (letters only): ";
            getline(cin, tempName);
            if (isValidString(tempName)) {
                setName(tempName);
                break;
            }
            cout << "Invalid name. Please enter letters only.\n";
        }

        for (;;) {
            cout << "Input Contract Payment per Project: $";
            getline (cin, tempContractPayment);
            if (!isValidNum(tempContractPayment)) {
                cout << "Invalid input. Please enter a contract payment.\n";
                continue;
            }
            setContractPayment(stod(tempContractPayment));
            break;
        }

        for (;;) {
            cout << "Input number of project: ";
            getline (cin, tempNumProject);
            if (!isValidNum(tempNumProject)) {
                cout << "Invalid input. Please enter a valid number of project.\n";
                continue;
            }
            setNumProject(stoi(tempNumProject));
            break;
        }

        setSalary(getContractPayment() * getNumProject());
        cout << "Total Salary: $" << getSalary() << "\n";
        employees.insert({getId(), new contractEmployee(getId(), getName(), getSalary(), getContractPayment(), getNumProject())});
    }
};

void displayPayrollReport() {
    cout << "\n------ Employee Payroll Report ------\n";
    if (employees.empty()) {
        cout << "No employee data available.\n";
        return;
    }
    for (const auto& pair : employees) {
        if (fTimeEmployee* emp = dynamic_cast<fTimeEmployee*>(pair.second)) {
            cout << "\nEmployee: " << emp->getName() << " (ID: " << emp->getId() << ")\n";
            cout << "Fixed Monthly Salary: $" << emp->getSalary() << "\n";
        } else if (pTimeEmployee* emp = dynamic_cast<pTimeEmployee*>(pair.second)) {
            cout << "\nEmployee: " << emp->getName() << " (ID: " << emp->getId() << ")\n";
            cout << "Hourly Wage: $" << emp->getHourlyWage() << "\n";
            cout << "Hours Worked: " << emp->getWorkHours() << "\n";
            cout << "Total Salary: $" << emp->getSalary() << "\n";
        } else if (contractEmployee* emp = dynamic_cast<contractEmployee*>(pair.second)) {
            cout << "\nEmployee: " << emp->getName() << " (ID: " << emp->getId() << ")\n";
            cout << "Contract Payment per Project: $" << emp->getContractPayment() << "\n";
            cout << "Projects Completed: " << emp->getNumProject() << "\n";
            cout << "Total Salary: $" << emp->getSalary() << "\n";
        }
    }
}

void clearMemory() {
    for (const auto& pair : employees) {
        delete pair.second;
    }
    employees.clear();
}

void displayMenu();

void displayEmployeeType(int choice) {
    switch (choice) {
        case 1: {
            fTimeEmployee fTimeEmp("", "", 0);
            fTimeEmp.calculateSalary();
            displayMenu();
            break;
        }
        case 2: {
            pTimeEmployee pTimeEmp("", "", 0, 0, 0);
            pTimeEmp.calculateSalary();
            displayMenu();
            break;
        }
        case 3: {
            contractEmployee contractEmp("", "", 0, 0, 0);
            contractEmp.calculateSalary();
            displayMenu();
            break;
        }
        case 4: {
            displayPayrollReport();
            displayMenu();
            break;
        }
        case 5: {
            cout << "Exiting program...\n";
            clearMemory();
            exit(0);
        }
        default: {
            cout << "Invalid choice. Please enter a valid number.\n";
            displayMenu();
            break;
        }
    }
}    
      
void displayMenu() {
    cout << "\n- - - - - - - - - - - Menu - - - - - - - - - - -\n";
    cout << "1. Full-time Employee\n2. Part-time Employee\n3. Contractual Employee\n4. Display Payroll Report\n5. Exit\n";
    for (;;) {
        cout << "Input number of choice: ";
        string choice;
        getline(cin, choice);
        if (!isValidNum(choice)) {
            cout << "Invalid input. Please enter a valid choice.\n";
            continue;
        }
        int numChoice = stoi(choice);
        if (numChoice < 1 || numChoice > 5) {
            cout << "Invalid choice. Please enter a number between 1 and 5.\n";
            continue;
        }
        displayEmployeeType(numChoice);
        if (numChoice == 5) break;
    }
}

int main() {
    displayMenu();
    return 0;
}
