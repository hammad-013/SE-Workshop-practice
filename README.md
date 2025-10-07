# Student Record Management System

A simple, console-based C++ application for managing student records. Built collaboratively using Git and GitHub as part of a software engineering workshop. This system allows teachers or admins to add, view, update, delete, search, and sort student data, with persistent storage in a CSV file.

## Features
- **Add Student**: Input name, roll number (unique validation), department, GPA (0-4), and contact info.
- **View Records**: Display all students in a formatted table or view details by roll number.
- **Update Student**: Edit existing records (name, department, GPA, contact) by roll number.
- **Delete Student**: Remove a record by roll number.
- **Search**: Filter students by name or department (case-insensitive partial match).
- **Sort**: Order records by GPA (descending) or roll number (ascending).
- **Data Persistence**: Automatically saves/loads data from `data/students.txt` (CSV format) on start/exit.

## Installation & Setup
1. **Prerequisites**:
   - C++ compiler (e.g., g++ from GCC).
   - Git (for cloning).

2. **Clone the Repository**:
   ```bash
   git clone https://github.com/YOUR_USERNAME/Student-Record-Management-System.git
   cd Student-Record-Management-System

3. **Build**:
   `g++ main.cpp -o student_mgr`

    - On Windows: g++ main.cpp -o student_mgr.exe.
    - Ensure C++11+ standard (default in modern g++).

4. **Run**:
   ```bash
    ./student_mgr  # Linux/Mac
    # or
    student_mgr.exe  # Windows
   ```

5. **Usage**:
Launch the program to see the menu. Navigate using numbers (0-7). Here's a quick walkthrough:
    ```bash
    =========================
    Student Management System
    =========================
    1. Add Student
    2. View All
    3. View by Roll Number
    4. Update Student
    5. Delete Student
    6. Search
    7. Sort
    0. Exit
    =========================
    Enter your choice: 1

    Enter name: John Doe
    Enter roll number: 123
    Enter department: Computer Science
    Enter GPA (0-4): 3.8
    Enter contact: john@email.com
    Student added!

    Enter your choice: 2

    Name           Roll     Dept      GPA   Contact
    John Doe       123      Computer Science 3.8   john@email.com

    Enter your choice: 0
    Goodbye!
    ```
    - Data persists: Rerun the program—your students are still there!


 6. **File Format (CSV)**:

    `data/students.txt` uses simple CSV:
    ```bash
    Name,RollNumber,Department,GPA,Contact
    John Doe,123,Computer Science,3.8,john@email.com
    ```

## Team & Collaboration
This project was developed collaboratively by a 3-member team using Git/GitHub:

    - Group Lead: Repository setup, PR reviews, integration.
    - Munawar: File handling (load/save) and CRUD operations (add/update/delete).
    - Samra: Display, search, sort, and user interface (menu/formatting).