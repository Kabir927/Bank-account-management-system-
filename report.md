Bank Management System – Project Report

1. Title Page
Project Title: Bank Management System
 Course: Object-Oriented Programming (OOP)
 Roll Number: [24k-0927(Kabir) 24k-1042(Abdullah hakro) 24k-1043(rameez)]
 Instructor: Talha shahid
 Date: 11 may 2025

2. Abstract
This project is a graphical Bank Management System developed using C++ and Qt framework. It allows users to interact with banking functions such as creating accounts, depositing/withdrawing money, and viewing account details through a user-friendly GUI. The system demonstrates key Object-Oriented Programming principles like encapsulation, inheritance, and abstraction.

3. Introduction
Managing customer accounts and transactions efficiently is vital for any banking system. This project simulates a basic bank management application, featuring a Qt-based graphical user interface and back-end logic built with C++. It provides an intuitive environment for users to manage bank account operations.

4. Objectives
Implement real-world OOP concepts in C++.


Design a user-friendly GUI for basic banking operations.


Ensure data encapsulation and class-based modularity.


Gain hands-on experience with the Qt framework.



5. Tools & Technologies Used
Programming Language: C++


Framework: Qt (for GUI)


IDE: Qt Creator


Libraries: Standard Template Library (STL), QtCore, QtWidgets



6. System Design
The system consists of two primary components:
Frontend (GUI): Built using Qt Designer (mainwindow.ui) and managed by mainwindow.cpp.


Backend (Logic): Handled via custom C++ classes like Account which encapsulate data and functions.


Key class:
cpp
CopyEdit
class Account {
    QString name;
    int accountNumber;
    double balance;
    // Functions for deposit, withdraw, display, etc.
};


7. Features
Account creation


Balance inquiry


Deposit and withdrawal functionality


Account data validation


Error handling with message dialogs


Persistent user-friendly interface



8. Code Structure
main.cpp: Launches the Qt application.


mainwindow.cpp/h: Handles UI logic and slots.


mainwindow.ui: Designed in Qt Designer for interface layout.


Account.h: Contains class for account handling.




9. Conclusion
The Bank Management System successfully fulfills the requirements of a basic banking simulation using OOP in C++ with a GUI interface. It helped in deepening the understanding of GUI design and event-driven programming in C++.

10. Future Scope
Add login/authentication system for different users.


Integrate with file/database system for persistent data storage.


Include transaction history logs and statements.

