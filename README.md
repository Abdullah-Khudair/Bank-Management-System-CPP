Bank Management System (C++ | OOP)
A console-based banking management system built with C++, applying core Object-Oriented Programming principles through a clean layered architecture.

Overview
This project simulates real-world banking operations — managing clients, processing transactions, handling currency exchange, and controlling user access — all through a structured, multi-layer design that separates concerns between the user interface, business logic, and data storage.

Features
Client Management — add, update, delete, search, and list bank clients
Transactions — deposit, withdraw, and transfer funds between clients with full transfer logging
Currency Exchange — calculate exchange rates and manage supported currencies
User & Permissions System — role-based access control using bitwise permission flags (Admin, Employee, etc.)
Authentication — login/register system with basic password encryption
Persistent Storage — data is saved and loaded from text files (no external database required)
Architecture
The project follows a 3-layer architecture:

UI Layer/ - Console screens & user interaction Logic Layer/ - Core business logic (Bank Client, Bank User, Currency Exchange...) Library/ - Shared utilities (validation, encryption, string helpers, Person base class) Data File/ - Text-file based data storage

Key OOP concepts applied:

Abstraction — ContactService as a pure abstract interface implemented by clsPerson
Inheritance — clsBankClient and clsBankUser inherit from clsPerson
Encapsulation — private data members with controlled access via getters/setters
Polymorphism — virtual functions used across the person/client/user hierarchy
Getting Started
Prerequisites: A C++ compiler supporting C++17 (e.g., g++)

Build & Run: g++ -std=c++17 "Run.c++" -o BankApp ./BankApp

About This Project
Built as a practice project to apply and reinforce Object-Oriented Programming concepts in C++, focusing on real-world software design patterns like layered architecture and role-based access control.

License
This project is licensed under the MIT License.
