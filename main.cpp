#include <iostream>    // For input/output
#include <string>      // For strings
#include <vector>      // For list of students
#include <fstream>     // For file reading/writing
#include <sstream>     // For parsing CSV lines
#include <algorithm>   // For sorting
#include <iomanip>     // For table formatting (e.g., setw)
// ===== SHARED: Student Data =====
// Don't edit this—use it in your functions
struct Student {
    std::string name;
    std::string rollNumber;
    std::string department;
    double gpa;          // 0.0 to 4.0
    std::string contactInfo;
};
// Shared list of all students (add/remove here in your code)
std::vector<Student> students;
// ===== MEMBER 2: FILE HANDLING & CRUD (Save/Load + Add/Update/Delete) =====
// Goal: Load from file on start, save on exit. Add/update/delete with validation.
// Format: CSV in data/students.txt (e.g., "John,123,CS,3.5,john@email.com")
// Replace the code inside each function (keep the function name/line).
void loadData() {
    std::ifstream file("data/students.txt");
    if (!file.is_open()) {
        return;  // File missing or empty, start empty
    }
    std::string line;
    std::getline(file, line);  // Skip header
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
            continue;  // Skip invalid GPA
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
// Helper: Don't edit—checks if roll is unique and not empty.
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
// ===== END MEMBER 2 =====
// ===== MEMBER 3: DISPLAY/SEARCH & INTERFACE (View/Search/Sort + Menu) =====
// Goal: Print tables nicely, search/filter, sort. Make menu user-friendly.
// Use <iomanip> for tables: #include <iomanip> (already at top).
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
// ===== END MEMBER 3 =====
// ===== MAIN: Program Loop (Group Lead: Review/Tweak if Needed) =====
int main() {
    loadData();  // Start by loading saved data
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