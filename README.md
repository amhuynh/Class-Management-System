# Class-Management-System

## Author
Amanda Huynh

## Project Description

This project is a **C++  application** that reads student data from three course files and provides several menu-driven operations to analyze the data.

The program stores student information such as **ID, name, and score**, and allows the user to view course lists, identify students enrolled in multiple courses, and display top scores.

This project demonstrates the use of:

* Object-oriented programming (classes)
* Dynamic memory allocation
* File input/output
* Sorting algorithms
* Structured data management in C++

## Features

The program provides a menu with the following options:

1. **Show all course lists (sorting)**
   Displays all students in each course sorted in ascending order by **student ID**.

2. **List students who take all courses**
   Shows students enrolled in **all three courses**, including their scores for each course.

3. **List students who take two courses**
   Displays students enrolled in **exactly two courses** (excluding those enrolled in all three).

4. **Print out top three scores for each course**
   Displays the **top three unique scores** in each course along with the students who achieved them.

5. **Exit**
   Terminates the program.

## Program Structure

### 1. `Student` Class

Represents a student and stores:

* `id` – student ID
* `name` – student name
* `score` – course score

Includes:

* Constructors
* Setters and getters
* Destructor

### 2. `Course` Structure

Represents a course and contains:

* `title` – course name
* `number_of_students` – total students enrolled
* `Student* list` – dynamically allocated array of students

### 3. Main Functions

* `file()` – Reads course data from a file and stores it into a `Course` structure.
* `menu1()` – Displays sorted student lists for each course.
* `menu2()` – Finds students enrolled in **all three courses**.
* `menu3()` – Finds students enrolled in **exactly two courses**.
* `menu4()` – Displays the **top three scores** for each course.

## File Format

Each input file should follow this format:

```
CourseTitle NumberOfStudents
ID Name Score
ID Name Score
ID Name Score
...
```

## How to Compile

Use a C++ compiler such as **g++**.

```bash
g++ -std=c++11 project1.cpp -o project1
```

## How to Run

```bash
./project1
```

The program will prompt you to enter **three filenames**:

```
Enter filename #1 :
Enter filename #2 :
Enter filename #3 :
```

After loading the files, the program will display the **interactive menu**.

## Concepts Demonstrated

* Object-Oriented Programming
* Dynamic Memory Allocation (`new` / `delete`)
* File Handling (`ifstream`)
* Sorting Algorithms (Bubble Sort)
* Multi-dimensional dynamic arrays
* Data comparison across multiple datasets