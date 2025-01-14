# Candy Company Management System 🍬

## Description:
This is a management system for a gummy candy company, written in **C**. The system is designed to help the employees of the company be more productive by providing a user-friendly interface for managing projects and team members. It utilizes **dynamic memory allocation** to store and manage employees, projects, and assignments efficiently. 

Every action, such as adding or removing an employee or project, ensures proper memory management. When an employee or project is removed, the allocated memory is properly deallocated to prevent memory leaks.

The program implements concepts such as:
- **Recursion** 🔄
- **Memory allocation and deallocation** 💾
- **Linked lists** 🔗
- **Loops** 🔁
- **Functions** 🧑‍💻

## Menu:
Upon running the program, the user will be presented with the following menu options:

```
Welcome!
Please select the desired option:
1. Join the company
2. Open a new project
3. Join an existing project
4. See what projects are in work
5. See which people are in what projects
6. Work on existing project
7. Leave the company
8. Exit
Enter your choice:
```

Each option will prompt the user for input, allowing them to interact with the system as they see fit.

## Features:
- **Join the company**: Allows users to become employees of the company.
- **Open a new project**: Enables the creation of a new project within the company.
- **Join an existing project**: Allows users to become part of an ongoing project.
- **See what projects are in work**: Displays a list of all current projects.
- **See which people are in what projects**: Shows which employees are working on which projects.
- **Work on existing project**: Enables employees to contribute to ongoing projects.
- **Leave the company**: Removes an employee from the company and frees any dynamically allocated memory related to them.
- **Exit**: Exits the program and ensures that all dynamically allocated memory is deallocated before the program terminates.

## Memory Management:
The project is designed to avoid memory leaks. All data structures, such as employees and projects, are dynamically allocated using `malloc` and `free`. Each time an employee or project is removed, the corresponding memory is freed to ensure efficient memory usage. This is particularly important to prevent memory leaks, which could affect the program's performance over time.

## Requirements:
This project is the final exercise for the **"Introduction to Computer Science"** course at the university. It demonstrates the following concepts:
- **Recursion** 🔄
- **Memory management** (allocation and deallocation) 💾
- **Linked lists** 🔗
- **Loops** 🔁
- **Functions** 🧑‍💻

## Usage:
To compile and run the program:
1. Compile the program with `gcc -o candy_company candy_company.c`.
2. Run the program with `./candy_company`.

Follow the on-screen prompts to navigate through the various options in the menu.
