# Browser History Management System

## 1. Project Overview

The **Browser History Management System** is a console-based application developed using the C programming language. It simulates the basic working of a web browser by maintaining browsing history and supporting Back and Forward navigation.

This project demonstrates the practical implementation of Data Structures and Algorithms (DSA).

## 2. Objectives

- To understand Doubly Linked Lists.
- To implement Stack operations.
- To perform searching and deletion operations.
- To manage browsing history efficiently.
- To understand dynamic memory allocation in C.

## 3. Features

- Visit a new website using its URL.
- Navigate to the previous page using Back.
- Navigate to the next page using Forward.
- Display complete browsing history.
- Search websites by URL or title.
- Delete a particular history entry.
- Clear complete browsing history.
- Display website title and visit date/time.
- Add, search, display and delete bookmarks.
- Save and load browsing history using files.

## 4. Data Structures Used

### A. Doubly Linked List
Used to store browsing history. Each node contains website information and pointers to the previous and next nodes.

### B. Stack
Two stacks are implemented:
- Back Stack: Stores previously visited pages.
- Forward Stack: Stores pages available for forward navigation.

### C. Singly Linked List
Used to maintain the bookmarks.

## 5. Technologies Used

- Programming Language: C
- IDE: Visual Studio Code
- Compiler: GCC
- Operating System: Windows

## 6. Project File Structure

```text
Browser-History-Management/
│
├── browser.h
├── main.c
├── visit.c
├── navigation.c
├── history.c
├── deletion.c
├── bookmarks.c
├── file_manager.c
└── README.md
```

## 7. Compilation and Execution

Open the VS Code terminal in the project folder.

Compile the project:

```bash
gcc -std=c11 -Wall -Wextra main.c visit.c navigation.c history.c deletion.c bookmarks.c file_manager.c -o browser_history.exe
```

Run the program in PowerShell:

```powershell
.\browser_history.exe
```

## 8. Applications

- Understanding browser history management.
- Learning linked list and stack operations.
- Practicing memory management in C.
- Understanding file handling concepts.

## 9. Conclusion

The Browser History Management System demonstrates how different data structures can be combined to develop a practical application. It provides hands-on experience with linked lists, stacks, searching, deletion and file handling.

## 10. Project Type

**DSA Lab Project – B.Tech**

