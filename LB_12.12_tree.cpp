#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct Employee {
    string lastName;
    string initials;
    string position;
    int startYear;
    double salary;
    Employee* left;
    Employee* right;
};

class BinaryTree {
private:
    Employee* root;

    Employee* addEmployeeUtil(Employee* node, string lastName, string initials, string position, int startYear, double salary);
    Employee* deleteEmployeeUtil(Employee* node, string lastName);
    Employee* findMinNode(Employee* node);
    Employee* editEmployeeUtil(Employee* node, string lastName);
    void displayEmployeeInfoUtil(Employee* node, string lastName);
    void displayInOrderUtil(Employee* node);
    void saveToFileUtil(Employee* node, ofstream& outFile);
    Employee* loadFromFileUtil(ifstream& inFile);
    void deleteTree(Employee* node);

public:
    BinaryTree();
    ~BinaryTree();

    void addEmployee(string lastName, string initials, string position, int startYear, double salary);
    void deleteEmployee(string lastName);
    void editEmployee(string lastName);
    void sortEmployeesByName();
    void sortEmployeesBySalary();
    void sortEmployeesByStartYear();
    void displayEmployeeInfo(string lastName);
    void displayMenu();
    void saveToFile(string filename);
    void loadFromFile(string filename);
};

BinaryTree::BinaryTree() {
    root = nullptr;
}

BinaryTree::~BinaryTree() {
    deleteTree(root);
}

void BinaryTree::deleteTree(Employee* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

Employee* BinaryTree::addEmployeeUtil(Employee* node, string lastName, string initials, string position, int startYear, double salary) {
    if (node == nullptr) {
        Employee* newNode = new Employee;
        newNode->lastName = lastName;
        newNode->initials = initials;
        newNode->position = position;
        newNode->startYear = startYear;
        newNode->salary = salary;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    if (lastName < node->lastName)
        node->left = addEmployeeUtil(node->left, lastName, initials, position, startYear, salary);
    else
        node->right = addEmployeeUtil(node->right, lastName, initials, position, startYear, salary);

    return node;
}

void BinaryTree::addEmployee(string lastName, string initials, string position, int startYear, double salary) {
    root = addEmployeeUtil(root, lastName, initials, position, startYear, salary);
}

Employee* BinaryTree::deleteEmployeeUtil(Employee* node, string lastName) {
    if (node == nullptr) return node;

    if (lastName < node->lastName)
        node->left = deleteEmployeeUtil(node->left, lastName);
    else if (lastName > node->lastName)
        node->right = deleteEmployeeUtil(node->right, lastName);
    else {
        if (node->left == nullptr) {
            Employee* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            Employee* temp = node->left;
            delete node;
            return temp;
        }

        Employee* temp = findMinNode(node->right);
        node->lastName = temp->lastName;
        node->initials = temp->initials;
        node->position = temp->position;
        node->startYear = temp->startYear;
        node->salary = temp->salary;
        node->right = deleteEmployeeUtil(node->right, temp->lastName);
    }
    return node;
}

void BinaryTree::deleteEmployee(string lastName) {
    root = deleteEmployeeUtil(root, lastName);
}

Employee* BinaryTree::findMinNode(Employee* node) {
    Employee* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

Employee* BinaryTree::editEmployeeUtil(Employee* node, string lastName) {
    if (node == nullptr) return node;

    if (lastName < node->lastName)
        node->left = editEmployeeUtil(node->left, lastName);
    else if (lastName > node->lastName)
        node->right = editEmployeeUtil(node->right, lastName);
    else {
        // Found the employee
        cout << "Enter new data for employee " << node->lastName << ":" << endl;
        cout << "Initials: ";
        cin >> node->initials;
        cout << "Position: ";
        cin >> node->position;
        cout << "Start Year: ";
        cin >> node->startYear;
        cout << "Salary: ";
        cin >> node->salary;
    }
    return node;
}

void BinaryTree::editEmployee(string lastName) {
    root = editEmployeeUtil(root, lastName);
}

void BinaryTree::displayEmployeeInfoUtil(Employee* node, string lastName) {
    if (node == nullptr) {
        cout << "Employee with last name " << lastName << " not found." << endl;
        return;
    }

    if (lastName < node->lastName)
        displayEmployeeInfoUtil(node->left, lastName);
    else if (lastName > node->lastName)
        displayEmployeeInfoUtil(node->right, lastName);
    else {
        // Found the employee
        cout << "Employee Information:" << endl;
        cout << "Last Name: " << node->lastName << endl;
        cout << "Initials: " << node->initials << endl;
        cout << "Position: " << node->position << endl;
        cout << "Start Year: " << node->startYear << endl;
        cout << "Salary: " << node->salary << endl;
    }
}

void BinaryTree::displayEmployeeInfo(string lastName) {
    displayEmployeeInfoUtil(root, lastName);
}

void BinaryTree::displayInOrderUtil(Employee* node) {
    if (node != nullptr) {
        displayInOrderUtil(node->left);
        cout << "Last Name: " << node->lastName << ", Salary: " << node->salary << ", Start Year: " << node->startYear << endl;
        displayInOrderUtil(node->right);
    }
}

void BinaryTree::sortEmployeesByName() {
    cout << "Employees sorted by last name:" << endl;
    displayInOrderUtil(root);
}

void BinaryTree::sortEmployeesBySalary() {
    cout << "Employees sorted by salary:" << endl;
    // Реалізуємо сортування за зарплатою
}

void BinaryTree::sortEmployeesByStartYear() {
    cout << "Employees sorted by start year:" << endl;
    // Реалізуємо сортування за роком прийому на роботу
}

void BinaryTree::displayMenu() {
    cout << "Binary Tree Employee Management System" << endl;
    cout << "1. Add Employee" << endl;
    cout << "2. Delete Employee" << endl;
    cout << "3.Edit Employee " << endl;
    cout << "4. Display Employee Information " << endl;
    cout << "5. Sort Employees by Last Name " << endl;
    cout << "6. Sort Employees by Salary " << endl;
    cout << "7. Sort Employees by Start Year " << endl;
    cout << "8. Save to File " << endl;
    cout << "9. Load from File " << endl;
    cout << "10. Exit" << endl;
}

void BinaryTree::saveToFileUtil(Employee* node, ofstream& outFile) {
    if (node != nullptr) {
        saveToFileUtil(node->left, outFile);
        outFile << node->lastName << " " << node->initials << " " << node->position << " " << node->startYear << " " << node->salary << endl;
        saveToFileUtil(node->right, outFile);
    }
}

void BinaryTree::saveToFile(string filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error: Unable to open file." << endl;
        return;
    }
    saveToFileUtil(root, outFile);
    outFile.close();
    cout << "Data saved to file successfully." << endl;
}

Employee* BinaryTree::loadFromFileUtil(ifstream& inFile) {
    if (!inFile.eof()) {
        Employee* newNode = new Employee;
        inFile >> newNode->lastName >> newNode->initials >> newNode->position >> newNode->startYear >> newNode->salary;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }
    return nullptr;
}

void BinaryTree::loadFromFile(string filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error: Unable to open file." << endl;
        return;
    }
    root = loadFromFileUtil(inFile);
    inFile.close();
    cout << "Data loaded from file successfully." << endl;
}

int main() {
    BinaryTree tree;
    string filename;

    while (true) {
        tree.displayMenu();
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
        case 1: {
            string lastName, initials, position;
            int startYear;
            double salary;
            cout << "Enter last name: ";
            getline(cin, lastName);
            cout << "Enter initials: ";
            getline(cin, initials);
            cout << "Enter position: ";
            getline(cin, position);
            cout << "Enter start year: ";
            cin >> startYear;
            cout << "Enter salary: ";
            cin >> salary;
            tree.addEmployee(lastName, initials, position, startYear, salary);
            break;
        }
        case 2: {
            string lastName;
            cout << "Enter last name of employee to delete: ";
            getline(cin, lastName);
            tree.deleteEmployee(lastName);
            break;
        }
        case 3: {
            string lastName;
            cout << "Enter last name of employee to edit: ";
            getline(cin, lastName);
            tree.editEmployee(lastName);
            break;
        }
        case 4: {
            string lastName;
            cout << "Enter last name of employee to display info: ";
            getline(cin, lastName);
            tree.displayEmployeeInfo(lastName);
            break;
        }
        case 5:
            tree.sortEmployeesByName();
            break;
        case 6:
            tree.sortEmployeesBySalary();
            break;
        case 7:
            tree.sortEmployeesByStartYear();
            break;
        case 8:
            cout << "Enter filename to save data: ";
            getline(cin, filename);
            tree.saveToFile(filename);
            break;
        case 9:
            cout << "Enter filename to load data: ";
            getline(cin, filename);
            tree.loadFromFile(filename);
            break;
        case 10:
            cout << "Exiting program." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
