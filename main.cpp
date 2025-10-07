#include <iostream>   
#include <string>      
#include <vector>      
#include <fstream>     
#include <sstream>     
#include <algorithm>   
#include <iomanip>     

struct Student {
    std::string name;
    std::string rollNumber;
    std::string department;
    double gpa;        
    std::string contactInfo;
};
std::vector<Student> students;
void loadData() {
    std::ifstream file("data/students.txt");
    if (!file.is_open()) {
        return;  
    }
    std::string line;
    std::getline(file, line);  
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        Student s;
        std::getline(ss, s.name, ',');
        std::getline(ss, s.rollNumber, ',');
        std::getline(ss, s.department, ',');
        std::string gpaStr;
        std::getline(ss, gpaStr, ',');
        try {
            s.gpa = std::stod(gpaStr);
        } catch (...) {
            continue;  
        }
        std::getline(ss, s.contactInfo, ',');
        students.push_back(s);
    }
    file.close();
}
void saveData() {
    std::ofstream file("data/students.txt");
    if (!file.is_open()) {
        std::cout << "Save failed!" << std::endl;
        return;
    }
    file << "Name,RollNumber,Department,GPA,Contact\n";
    for (const auto& s : students) {
        file << s.name << "," << s.rollNumber << "," << s.department << ","
             << s.gpa << "," << s.contactInfo << "\n";
    }
    file.close();
}
bool isValidRollNumber(const std::string& roll) {
    for (const auto& s : students) {
        if (s.rollNumber == roll) return false;
    }
    return !roll.empty();
}
void addStudent() {
    Student s;
    std::cout << "Enter name: "; std::getline(std::cin, s.name);
    std::cout << "Enter roll number: "; std::getline(std::cin, s.rollNumber);
    std::cout << "Enter department: "; std::getline(std::cin, s.department);
    std::cout << "Enter GPA (0-4): "; std::cin >> s.gpa; std::cin.ignore();
    std::cout << "Enter contact: "; std::getline(std::cin, s.contactInfo);
    if (!isValidRollNumber(s.rollNumber)) {
        std::cout << "Roll must be unique!" << std::endl;
        return;
    }
    students.push_back(s);
    std::cout << "Student added!" << std::endl;
}
void updateStudent() {
    std::string roll;
    std::cout << "Enter roll to update: "; std::getline(std::cin, roll);
    size_t i = 0;
    for (; i < students.size(); ++i) {
        if (students[i].rollNumber == roll) break;
    }
    if (i == students.size()) {
        std::cout << "Not found!" << std::endl;
        return;
    }
    Student& s = students[i];
    std::cout << "Enter new name: "; std::getline(std::cin, s.name);
    std::cout << "Enter new department: "; std::getline(std::cin, s.department);
    std::cout << "Enter new GPA (0-4): "; std::cin >> s.gpa; std::cin.ignore();
    std::cout << "Enter new contact: "; std::getline(std::cin, s.contactInfo);
    std::cout << "Updated!" << std::endl;
}
void deleteStudent() {
    std::string roll;
    std::cout << "Enter roll to delete: "; std::getline(std::cin, roll);
    size_t i = 0;
    for (; i < students.size(); ++i) {
        if (students[i].rollNumber == roll) break;
    }
    if (i == students.size()) {
        std::cout << "Not found!" << std::endl;
        return;
    }
    students.erase(students.begin() + i);
    std::cout << "Deleted!" << std::endl;
}
void viewAll() {
    if (students.empty()) {
        std::cout << "No students yet." << std::endl;
        return;
    }
    std::cout << std::left << std::setw(15) << "Name" << std::setw(10) << "Roll"
              << std::setw(10) << "Dept" << std::setw(5) << "GPA" << "Contact" << std::endl;
    for (const auto& s : students) {
        std::cout << std::left << std::setw(15) << s.name << std::setw(10) << s.rollNumber
                  << std::setw(10) << s.department << std::setw(5) << s.gpa << s.contactInfo << std::endl;
    }
}
void viewByRoll(const std::string& roll) {
    for (const auto& s : students) {
        if (s.rollNumber == roll) {
            std::cout << "Name: " << s.name << ", Roll: " << s.rollNumber
                      << ", Department: " << s.department << ", GPA: " << s.gpa
                      << ", Contact: " << s.contactInfo << std::endl;
            return;
        }
    }
    std::cout << "Student not found." << std::endl;
}
void searchStudents() {
    char type;
    std::cout << "Search by name (n) or department (d)? ";
    std::cin >> type;
    std::cin.ignore();
    std::string term;
    std::cout << "Enter term: ";
    std::getline(std::cin, term);
    bool found = false;
    std::cout << std::left << std::setw(15) << "Name" << std::setw(10) << "Roll"
              << std::setw(10) << "Dept" << std::setw(5) << "GPA" << "Contact" << std::endl;
    for (const auto& s : students) {
        if ((type == 'n' && s.name.find(term) != std::string::npos) ||
            (type == 'd' && s.department.find(term) != std::string::npos)) {
            std::cout << std::left << std::setw(15) << s.name << std::setw(10) << s.rollNumber
                      << std::setw(10) << s.department << std::setw(5) << s.gpa << s.contactInfo << std::endl;
            found = true;
        }
    }
    if (!found) std::cout << "No matches." << std::endl;
}
void sortRecords() {
    char type;
    std::cout << "Sort by GPA (g) or Roll (r)? ";
    std::cin >> type;
    std::cin.ignore();
    if (type == 'g') {
        std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.gpa > b.gpa;
        });
        std::cout << "Sorted by GPA!" << std::endl;
    } else if (type == 'r') {
        std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.rollNumber < b.rollNumber;
        });
        std::cout << "Sorted by Roll!" << std::endl;
    } else {
        std::cout << "Invalid sort type." << std::endl;
    }
}
void showMenu() {
    std::cout << "=========================" << std::endl;
    std::cout << "Student Management System" << std::endl;
    std::cout << "=========================" << std::endl;
    std::cout << "1. Add Student" << std::endl;
    std::cout << "2. View All" << std::endl;
    std::cout << "3. View by Roll Number" << std::endl;
    std::cout << "4. Update Student" << std::endl;
    std::cout << "5. Delete Student" << std::endl;
    std::cout << "6. Search" << std::endl;
    std::cout << "7. Sort" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "=========================" << std::endl;
}
int main() {
    loadData();  
    int choice;
    do {
        showMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); 

        if (choice == 1) {
            addStudent();
        } else if (choice == 2) {
            viewAll();
        } else if (choice == 3) {
            std::string roll;
            std::cout << "Enter roll number: ";
            std::getline(std::cin, roll);
            viewByRoll(roll);
        } else if (choice == 4) {
            updateStudent();
        } else if (choice == 5) {
            deleteStudent();
        } else if (choice == 6) {
            searchStudents();
        } else if (choice == 7) {
            sortRecords();
        } else if (choice == 0) {
            std::cout << "Goodbye!" << std::endl;
        } else {
            std::cout << "Invalid choice !!!! >>>> try again." << std::endl;

        }
    } while (choice != 0);

    saveData(); 
    return 0;
}