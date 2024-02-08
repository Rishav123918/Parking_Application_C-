# Vehicle Parking Reservation System

This is a simple vehicle parking reservation system implemented in C++. It allows users to manage the arrival, departure, and display of parked vehicles, along with calculating the total amount collected for parking.

## Prerequisites
- C++ compiler
- IDE (Integrated Development Environment) or text editor

## Instructions

### Compilation and Execution
1. Clone the repository or download the source code files.
2. Compile the source code using a C++ compiler.
3. Run the compiled executable file.

### Usage
1. Upon running the program, you will be presented with a menu of options:
   - Arrival of a vehicle
   - Total number of vehicles parked
   - Departure of vehicle
   - Total amount collected
   - Display
   - Exit

2. Choose an option by entering the corresponding number.

3. Follow the prompts to perform the desired operation:
   - Add vehicles (car or bike) to the parking lot.
   - Check the total number of cars and bikes parked.
   - Remove a vehicle from the parking lot upon departure.
   - View the total amount collected from parking.
   - Display details of parked vehicles.

4. Exit the program when done.

## Implementation Details
- The program uses vectors to store information about parked vehicles.
- It utilizes file I/O to save and read vehicle data to and from files (`file1.dat` and `file2.dat`).
- Vehicles are represented by classes `vehicle`, `date`, and `time`.
- The main functionality includes adding vehicles, calculating total collections, displaying vehicle details, and deleting vehicles.
- The system supports both car and bike parking.

