# Banking-ATM-System
A console-based Bank Management System in C++ featuring account creation, deposits, withdrawals, balance inquiry, and ATM simulation. Built with core OOP concepts—encapsulation, inheritance, abstraction, and polymorphism—and uses file handling for persistent data storage.

 Project Overview
This is a console-based Bank Management System developed in C++. It simulates real-world banking operations by offering functionalities like:

- Account creation

- Deposits and withdrawals

- Balance inquiry

- ATM simulation

- Data storage using file handling

- Secure and structured design using OOP principles

💎 Functionalities
Feature	Description
- Account Creation	Allows users to create a new bank account by entering name, ID, and address
- Deposit	Enables users to deposit money into their account
- Withdrawal	Enables users to withdraw funds if the balance is sufficient
- Balance Inquiry	Shows current account balance based on ID
- ATM Simulation	Mimics basic ATM features for fast transactions
- Data Persistence	All data is saved and retrieved from files using file streams

🔧 Technologies & Concepts Used
✅ C++ Programming
- Core syntax and structure of C++

- File input/output using <fstream>

✅ Object-Oriented Programming (OOP)
This project demonstrates all four pillars of OOP:

-> Encapsulation

- Data members like name, address, and balance are kept private or protected.

- Access is controlled through public getter/setter methods.

 Example: setname(), getbalance()

-> Inheritance

- Base classes like Person and User are inherited by Account.

- Promotes code reuse and logical class hierarchy.

Example: class Account : public Person, public User

-> Abstraction

- The user interacts with high-level functions without worrying about internal implementations.

- Methods like createAccount(), withdraw(), or ATMmenu() abstract the core logic.

-> Polymorphism

- Function overriding is used where child classes redefine base class methods.

- If virtual functions are used, runtime polymorphism is demonstrated.

💾 File Handling
All account data is read from and written to files using:

- ifstream for reading

- ofstream or fstream for writing/updating

- Ensures data persistence between sessions.

- Functions like getline() and seekg()/seekp() help navigate file contents.

