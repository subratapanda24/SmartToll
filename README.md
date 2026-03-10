# 🚗 Smart Toll Collection System (C++)

A console-based **Smart Toll Collection System** developed in **C++** that simulates the working of a highway toll plaza.

The system allows vehicle registration, toll calculation based on vehicle type, transaction logging, and receipt generation.

This project demonstrates the use of **Object-Oriented Programming (OOP)** and **file handling in C++** to model a real-world toll management system.

---

## 📌 Features

- **Vehicle Registration** – Store vehicle details such as plate number, owner name, and vehicle type.
- **Multiple Toll Booths** – Simulates different toll booths with unique IDs and locations.
- **Automatic Toll Calculation** – Calculates toll charges based on vehicle category.
- **Receipt Generation** – Generates a receipt for each toll transaction.
- **Transaction Logging** – Stores toll transaction history in a file.
- **Booth Statistics** – Displays number of vehicles processed and total revenue collected.
- **Menu Driven Interface** – Simple console interface for easy navigation.

---

## 🧠 Concepts Used

This project demonstrates several **C++ programming concepts**:

- Object-Oriented Programming (Classes & Objects)
- File Handling (`fstream`)
- Arrays
- Functions
- Menu-driven programming
- Conditional statements
- Time and date handling

---

## 🏗 System Architecture

The system is built using three main classes.

### Vehicle Class
Stores vehicle details:
- Plate Number  
- Owner Name  
- Vehicle Type  

### TollBooth Class
Represents a toll booth and tracks:
- Booth ID  
- Location  
- Total Revenue  
- Vehicle Count  

### TollSystem Class
Controls the main operations of the system:
- Vehicle registration  
- Toll processing  
- Transaction logging  
- Receipt generation  
- Booth statistics  

---

## 🚦 Toll Rates

| Vehicle Type | Toll Fee |
|--------------|----------|
| Motorcycle | ₹30 |
| Car | ₹60 |
| SUV | ₹80 |
| Bus | ₹120 |
| Truck | ₹150 |

---

## 📂 Project Structure

```
Smart-Toll-Collection-System/
│
├── smart_toll.cpp                 # Main C++ source file
│
├── documentation/
│   ├── Smart_Toll_Report.pdf      # Case study report
│   └── Smart_Toll_Presentation.pptx
│
├── .gitignore                     # Ignore generated files
│
└── README.md                      # Project documentation
```

---

## 📄 .gitignore Example

```
# Compiled C++ binaries
*.exe
*.out
*.o
*.obj

# Mac system files
.DS_Store

# Generated program files
transactions.txt
receipt_*.txt

# Build folders
build/
bin/

# Temporary files
*.log
*.tmp
```

---

## ▶️ How to Run

### Compile the program

```bash
g++ smart_toll.cpp -o tollsystem
```

### Run the program

```bash
./tollsystem
```

---

## 📷 Example Menu

```
SMART TOLL COLLECTION SYSTEM

1. Register Vehicle
2. Process Toll
3. Search Vehicle
4. Booth Statistics
5. Transaction Log
6. All Registered Vehicles
7. Exit
```

---

## 🎯 Learning Outcomes

Through this project the following concepts were applied:

- Designing real-world systems using **Object-Oriented Programming**
- Managing data using **arrays and classes**
- Recording system data using **file handling**
- Creating a **menu-driven application**
- Writing structured and modular C++ code

---

## 🔮 Future Improvements

Possible enhancements include:

- Database integration
- Graphical user interface
- Online payment integration
- RFID-based vehicle detection
- Real-time multi-booth network system

---

## Author

**Subrata Panda**  
B.Tech Computer Science  
School of Future Tech  
ITM Skills University