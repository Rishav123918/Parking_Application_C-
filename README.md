**Parking Management System (C++ Console Application)**

A role-based, file-persistent Parking Management System built in C++ for managing car and bike entries with automated fare calculation and secure login access.

This console application simulates a real-world parking facility with Admin and Staff dashboards, token-based vehicle tracking, rush-hour pricing, and persistent storage using file handling.

---

### 🚗 Core Features

* **Role-Based Access Control**

  * Admin and Staff login
  * Password masking
  * Change password functionality
  * Security lockout after failed attempts

* **Vehicle Management**

  * Add new vehicles (Car/Bike)
  * Auto-generated token system
  * Duplicate vehicle detection
  * Number plate format validation (Regex-based)
  * Batch checkout with confirmation

* **Smart Fare Calculation**

  * Time-based duration computation
  * Automatic hourly rounding
  * Rush hour pricing logic (09:00–11:00 & 17:00–20:00)
  * Separate rates for cars and bikes

* **Data Persistence**

  * File storage (`parking_data.txt`)
  * Automatic load on startup
  * Continuous data saving after updates

* **Reporting & Search**

  * Search vehicle by token
  * Full parking report
  * Revenue summary
  * Car/Bike count breakdown

* **Input Validation**

  * Date validation with leap year handling
  * Time validation
  * Numeric input validation
  * Structured console UI layout

---

### 🧠 Technical Highlights

* Object-Oriented Design
  Classes: `Vehicle`, `Time`, `Date`, `SecuritySystem`, `ParkingSystem`
* STL usage: `vector`, `algorithm`, `regex`, `sstream`
* Windows-specific enhancements:

  * `_getch()` for masked password input
  * `Sleep()` for UI transitions
  * `system("cls")` for screen control

---

### 📌 Pricing Model

| Type | Normal (Per Hour) | Rush Hour (Per Hour) |
| ---- | ----------------- | -------------------- |
| Bike | Rs 10             | Rs 15                |
| Car  | Rs 20             | Rs 30                |

Rush Hours:

* 09:00 – 11:00
* 17:00 – 20:00

---

### 🛠 Technologies Used

* C++17
* Standard Template Library (STL)
* File Handling
* Regex Validation
* Windows Console API

---

### 🎯 Use Case

Ideal for:

* Academic mini-projects
* OOP practice
* File handling demonstrations
* Console UI design practice
* Logic-heavy system simulations

---

A structured, real-world inspired parking solution that blends OOP principles, validation logic, security handling, and file persistence into one cohesive console-based system.
