#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <cctype>
#include <algorithm>
#include <windows.h>
#include <iomanip>
#include <sstream>
#include <regex>
#include <fstream>

using namespace std;

// This sets the width of the menu box
constexpr int MENU_WIDTH = 50;

// This helps center text in the middle
void printHeaderCentered(const string& text) {
    auto len = static_cast<int>(text.length());
    if (len >= MENU_WIDTH) 
    {
        cout << text << endl;
    }
    else 
    {
        int padding = (MENU_WIDTH - len) / 2;
        cout << string(padding, ' ') << text << endl;
    }
}

// This prints the menu title with borders
void printHeader(const string& title) {
    system("cls"); 
    cout << string(MENU_WIDTH, '=') << endl;
    printHeaderCentered(title);
    cout << string(MENU_WIDTH, '=') << endl;
}

// This prints a separator line
void printDivider() {
    cout << string(MENU_WIDTH, '-') << endl;
}

// This shows the goodbye message
void showExitMessage() {
    system("cls");
    cout << "\n";
    cout << string(MENU_WIDTH, '=') << endl;
    printHeaderCentered("THANK YOU FOR USING OUR SYSTEM");
    printHeaderCentered("HAVE A GREAT DAY!");
    cout << string(MENU_WIDTH, '=') << endl;
    cout << "\n";
    Sleep(1000);
}

// This ensures the user enters a number
[[nodiscard]] int getIntInput() {
    string line;
    while (true) 
    {
        if (!getline(cin, line)) 
        {
            return 0;
        }
        
        try 
        {
            if (!line.empty()) 
            {
                return stoi(line);
            }
        } 
        catch (...) 
        {
            // Do nothing if conversion fails
        }
        cout << "Invalid input! Please enter a number: ";
    }
}

// This converts text to UPPERCASE
[[nodiscard]] string toUpperStr(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// --- CLASS: TIME ---
class Time {
public:
    int hh = 0;
    int mm = 0;
    int ss = 0;

    // Convert time to seconds for math
    [[nodiscard]] long toSeconds() const {
        return hh * 3600 + mm * 60 + ss;
    }

    // Format time nicely
    [[nodiscard]] string toString() const {
        stringstream ss_stream;
        ss_stream << setfill('0') << setw(2) << hh << ":"
                  << setfill('0') << setw(2) << mm << ":"
                  << setfill('0') << setw(2) << ss;
        return ss_stream.str();
    }

    // Check if time is valid
    [[nodiscard]] static bool isValid(int h, int m, int s) {
        return (h >= 0 && h <= 23 && m >= 0 && m <= 59 && s >= 0 && s <= 59);
    }
};

// --- CLASS: DATE ---
class Date {
public:
    int dd = 0;
    int mm = 0;
    int yy = 0;

    // Format date nicely
    [[nodiscard]] string toString() const {
        stringstream ss_stream;
        ss_stream << setfill('0') << setw(2) << dd << "/"
                  << setfill('0') << setw(2) << mm << "/" << yy;
        return ss_stream.str();
    }

    // Check if date is valid
    [[nodiscard]] static bool isValid(int d, int m, int y) {
        if (m < 1 || m > 12 || d < 1) 
        {
            return false;
        }
        int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        // Check for leap year
        if (m == 2 && ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))) 
        {
            days[2] = 29;
        }
        return d <= days[m];
    }
};

// --- CLASS: VEHICLE ---
class Vehicle {
    int token;
    string owner;
    string vno;
    Time inT;
    Time outT;
    Date d;
    int durationHours;
    bool isCar;

public:
    // Constructor for new vehicles
    Vehicle(int t, bool c) : token(t), durationHours(0), isCar(c) {}

    // Constructor for loading from file
    Vehicle(int t, string o, string v, bool c, int h1, int m1, int s1, int h2, int m2, int s2, int dd, int mm, int yy)
        : token(t), owner(std::move(o)), vno(std::move(v)), durationHours(0), isCar(c) 
    {
        inT.hh = h1;
        inT.mm = m1;
        inT.ss = s1;

        outT.hh = h2;
        outT.mm = m2;
        outT.ss = s2;

        d.dd = dd;
        d.mm = mm;
        d.yy = yy;

        calculateDuration();
    }

    [[nodiscard]] int getToken() const { return token; }
    [[nodiscard]] string getVNo() const { return vno; }
    void setVNo(const string& v) { vno = v; }
    [[nodiscard]] bool getType() const { return isCar; }

    // Check if it is Rush Hour
    [[nodiscard]] static bool isPeakHour(int h) {
        return ((h >= 9 && h <= 11) || (h >= 17 && h <= 20));
    }

    // Calculate parking duration
    void calculateDuration() {
        long diff = outT.toSeconds() - inT.toSeconds();
        if (diff < 0) 
        {
            diff += 24 * 3600;
        }
        durationHours = (diff + 3599) / 3600;
        if (durationHours == 0) 
        {
            durationHours = 1;
        }
    }

    // Calculate the price
    [[nodiscard]] int getFare() const {
        int totalFare = 0;
        int currentClockHour = inT.hh;

        for (int i = 0; i < durationHours; i++) 
        {
            bool isPeak = isPeakHour(currentClockHour);
            if (isCar) 
            {
                if (isPeak) {
                    totalFare += 30;
                } else {
                    totalFare += 20;
                }
            } 
            else 
            {
                if (isPeak) {
                    totalFare += 15;
                } else {
                    totalFare += 10;
                }
            }
            currentClockHour++;
            if (currentClockHour >= 24) 
            {
                currentClockHour = 0;
            }
        }
        return totalFare;
    }

    // Prepare data for saving
    [[nodiscard]] string getFileString() const {
        stringstream ss;
        ss << token << "|" << owner << "|" << vno << "|" << isCar << "|"
           << inT.hh << " " << inT.mm << " " << inT.ss << "|"
           << outT.hh << " " << outT.mm << " " << outT.ss << "|"
           << d.dd << " " << d.mm << " " << d.yy;
        return ss.str();
    }

    // Get input from user
    void inputDetails() {
        cout << "Enter Owner Name: ";
        getline(cin, owner);

        bool validIn = false;
        while (!validIn) 
        {
            cout << "Arrival Time (HH MM SS): ";
            cin >> inT.hh >> inT.mm >> inT.ss;
            cin.ignore(1000, '\n');
            if (Time::isValid(inT.hh, inT.mm, inT.ss)) 
            {
                validIn = true;
            }
        }

        bool validOut = false;
        while (!validOut) 
        {
            cout << "Exit Time (HH MM SS): ";
            cin >> outT.hh >> outT.mm >> outT.ss;
            cin.ignore(1000, '\n');
            if (Time::isValid(outT.hh, outT.mm, outT.ss)) 
            {
                validOut = true;
            }
        }

        bool validDate = false;
        while (!validDate) 
        {
            cout << "Date (DD MM YY): ";
            cin >> d.dd >> d.mm >> d.yy;
            cin.ignore(1000, '\n');
            if (Date::isValid(d.dd, d.mm, d.yy)) 
            {
                validDate = true;
            }
        }
        calculateDuration();
    }

    // Show vehicle details
    void display() const {
        cout << string(MENU_WIDTH, '-') << endl;
        cout << " Token      : " << token << endl;
        cout << " Vehicle No : " << vno << endl;
        cout << " Type       : " << (isCar ? "Car" : "Bike") << endl;
        cout << " Owner      : " << owner << endl;
        cout << " Date       : " << d.toString() << endl;
        cout << " Time       : " << inT.toString() << " -> " << outT.toString() << endl;
        cout << " Duration   : " << durationHours << " Hours" << endl;
        cout << " Total Fare : Rs " << getFare() << endl;
        cout << string(MENU_WIDTH, '-') << endl;
    }
};

// --- CLASS: SECURITY SYSTEM ---
class SecuritySystem {
private:
    string adminPass = "1234";
    string staffPass = "0000";

    // Hide password input
    [[nodiscard]] static string getMaskedInput() {
        string pass;
        while (true) 
        {
            int ch = _getch();
            if (ch == 13) 
            { 
                cout << endl;
                break;
            } 
            else if (ch == 8) 
            { 
                if (!pass.empty()) 
                {
                    pass.pop_back();
                    cout << "\b \b";
                }
            } 
            else if (isprint(static_cast<unsigned char>(ch))) 
            {
                pass.push_back(static_cast<char>(ch));
                cout << "*";
            }
        }
        return pass;
    }

public:
    // Login logic
    [[nodiscard]] int login() const {
        while (true) 
        {
            printHeader("SYSTEM LOGIN");
            cout << "Username (admin/staff): ";
            string user;
            getline(cin, user);
            user = toUpperStr(user);

            if (user != "ADMIN" && user != "STAFF") 
            {
                cout << "\n[!] Invalid Username!\n";
                system("pause");
                continue;
            }

            int attempts = 0;
            while (attempts < 3) 
            {
                printHeader("SYSTEM LOGIN");
                cout << "Username : " << user << endl;
                cout << "Password : ";
                string pass = getMaskedInput();

                if (user == "ADMIN" && pass == adminPass) 
                {
                    return 1;
                }
                if (user == "STAFF" && pass == staffPass) 
                {
                    return 2;
                }

                attempts++;
                cout << "\n[!] Incorrect Password! (" << (3 - attempts) << " attempts left)\n";
                if (attempts >= 3) 
                {
                    cout << "\n[!] Security Lockout. Exiting...\n";
                    exit(0);
                }
                system("pause");
            }
        }
    }

    // Change password logic
    void changePassword() {
        while (true) 
        {
            printHeader("CHANGE PASSWORD");
            cout << "Enter Username (admin/staff) or '0' to Back: ";
            string user;
            getline(cin, user);
            if (user == "0") 
            {
                return;
            }

            user = toUpperStr(user);
            if (user != "ADMIN" && user != "STAFF") 
            {
                cout << "\n[!] Invalid Username!\n";
                system("pause");
                continue;
            }

            int attempts = 0;
            while (true) 
            {
                cout << "Enter Old Password: ";
                string oldP = getMaskedInput();

                if ((user == "ADMIN" && oldP == adminPass) || (user == "STAFF" && oldP == staffPass)) 
                {
                    cout << "Enter New Password: ";
                    string newP = getMaskedInput();
                    if (user == "ADMIN") 
                    {
                        adminPass = newP;
                    } 
                    else 
                    {
                        staffPass = newP;
                    }
                    cout << "\n[+] Password Changed Successfully!\n";
                    system("pause");
                    return;
                } 
                else 
                {
                    attempts++;
                    if (attempts >= 3) 
                    {
                        cout << "\n[!] Too many attempts. Exiting...\n";
                        exit(0);
                    }
                    cout << "[!] Wrong Password!\n";
                }
            }
        }
    }
};

// --- CLASS: PARKING SYSTEM ---
class ParkingSystem {
    vector<Vehicle> vehicles;
    int nextToken = 100;

    // Check if vehicle already exists
    [[nodiscard]] bool isDuplicate(const string& vno) const {
        return any_of(vehicles.begin(), vehicles.end(),
            [&vno](const Vehicle& x) { return x.getVNo() == vno; });
    }

    // Validate number plate format
    [[nodiscard]] static bool isValidPlateFormat(const string& plate) {
        const regex pattern(R"(^[A-Z]{2}[0-9]{2} [A-Z]{1,2} [0-9]{1,7}$)");
        return regex_match(plate, pattern);
    }

    // Save to file
    void saveToFile() const {
        ofstream outFile("parking_data.txt");
        if (!outFile) 
        {
            return;
        }
        for (const auto& v : vehicles) 
        {
            outFile << v.getFileString() << endl;
        }
        outFile.close();
    }

    // Load from file
    void loadFromFile() {
        ifstream inFile("parking_data.txt");
        if (!inFile) 
        {
            return;
        }

        string line;
        while (getline(inFile, line)) 
        {
            stringstream ss(line);
            string segment;
            vector<string> data;
            while (getline(ss, segment, '|')) 
            {
                data.push_back(segment);
            }
            if (data.size() == 7) 
            {
                int t = stoi(data[0]);
                string o = data[1];
                string v = data[2];
                bool c = (data[3] == "1");

                stringstream t1(data[4]);
                int h1;
                int m1;
                int s1;
                t1 >> h1 >> m1 >> s1;

                stringstream t2(data[5]);
                int h2;
                int m2;
                int s2;
                t2 >> h2 >> m2 >> s2;

                stringstream d1(data[6]);
                int dd;
                int mm;
                int yy;
                d1 >> dd >> mm >> yy;

                vehicles.emplace_back(t, o, v, c, h1, m1, s1, h2, m2, s2, dd, mm, yy);
                if (t >= nextToken) 
                {
                    nextToken = t + 1;
                }
            }
        }
        inFile.close();
    }

public:
    // Initialize system
    ParkingSystem() {
        loadFromFile();
    }

    // Show rates
    static void showRates() {
        printHeader("PARKING RATES");
        cout << "  TYPE    | NORMAL (Per Hr) | RUSH HOUR (Per Hr)\n";
        printDivider();
        cout << "  BIKE    |     Rs 10       |      Rs 15      \n";
        cout << "  CAR     |     Rs 20       |      Rs 30      \n";
        printDivider();
        cout << " * Rush Hours: 09:00 - 11:00 & 17:00 - 20:00\n";
        printDivider();
        system("pause");
    }

    // Add vehicle
    void addVehicle() {
        printHeader("ADD NEW VEHICLE");
        cout << "<< CURRENT TOKEN NUMBER: " << nextToken << " >>\n\n";

        cout << "1. Car\n2. Bike\nSelect Type: ";
        int t = getIntInput();
        if (t != 1 && t != 2) 
        {
            cout << "\n[!] Invalid choice!\n";
            system("pause");
            return;
        }

        string vInput;
        bool validPlate = false;
        while (!validPlate) 
        {
            cout << "Enter Vehicle No (Format: XX00 XX 0000): ";
            getline(cin, vInput);
            vInput = toUpperStr(vInput);
            if (isValidPlateFormat(vInput)) 
            {
                validPlate = true;
            } 
            else 
            {
                cout << "[!] Invalid Format! Example: JH05 CJ 5596\n";
            }
        }

        if (isDuplicate(vInput)) 
        {
            cout << "\n[!] Error: Vehicle already parked!\n";
            system("pause");
            return;
        }

        Vehicle v(nextToken, t == 1);
        v.setVNo(vInput);
        v.inputDetails();

        vehicles.push_back(v);
        nextToken++;
        saveToFile();

        cout << "\n[+] Vehicle Parked Successfully! Token: " << v.getToken() << endl;
        system("pause");
    }

    // Search for vehicle
    void searchToken() const {
        printHeader("SEARCH BY TOKEN");
        cout << "Enter Token ID: ";
        int t = getIntInput();
        bool found = false;
        for (const auto& v : vehicles) 
        {
            if (v.getToken() == t) 
            {
                v.display();
                found = true;
                system("pause");
                return;
            }
        }
        if (!found) 
        {
            cout << "\n[!] Vehicle Not Found!\n";
            system("pause");
        }
    }

    // Delete vehicle (Checkout)
    void deleteVehicle() {
        printHeader("VEHICLE CHECKOUT");
        cout << "Enter Token ID(s) separated by space: ";
        string line;
        getline(cin, line);
        stringstream ss(line);
        int t = 0;
        vector<int> tokensToFind;
        while (ss >> t) 
        {
            tokensToFind.push_back(t);
        }

        sort(tokensToFind.begin(), tokensToFind.end());
        tokensToFind.erase(unique(tokensToFind.begin(), tokensToFind.end()), tokensToFind.end());

        if (tokensToFind.empty()) 
        {
            cout << "\n[!] No input provided.\n";
            system("pause");
            return;
        }

        vector<int> validTokens;
        int totalBatchFare = 0;
        cout << "\n======= CHECKOUT SUMMARY =======\n";
        for (int token : tokensToFind) 
        {
            bool found = false;
            for (auto& v : vehicles) 
            {
                if (v.getToken() == token) 
                {
                    v.display();
                    totalBatchFare += v.getFare();
                    validTokens.push_back(token);
                    found = true;
                    break;
                }
            }
            if (!found) 
            {
                cout << "Token " << token << ": Not Found (Skipped)\n";
            }
        }

        if (validTokens.empty()) 
        {
            cout << "\n[!] No valid vehicles found.\n";
            system("pause");
            return;
        }

        printDivider();
        cout << " Vehicles to Remove : " << validTokens.size() << endl;
        cout << " Grand Total Fare   : Rs " << totalBatchFare << endl;
        printDivider();
        cout << "Confirm Checkout ALL? (y/n): ";
        string c;
        getline(cin, c);

        if (toUpperStr(c) == "Y") 
        {
            auto newEnd = remove_if(vehicles.begin(), vehicles.end(),
                [&](const Vehicle& v) {
                    return find(validTokens.begin(), validTokens.end(), v.getToken()) != validTokens.end();
                });
            vehicles.erase(newEnd, vehicles.end());
            saveToFile();
            cout << "\n[+] Checkout Successful!\n";
        } 
        else 
        {
            cout << "\n[-] Operation Cancelled.\n";
        }
        system("pause");
    }

    // Show report
    void report() const {
        printHeader("FULL PARKING REPORT");
        if (vehicles.empty()) 
        {
            cout << "\n[i] No vehicles currently parked.\n";
            system("pause");
            return;
        }

        int cars = 0;
        int bikes = 0;
        int total = 0;
        for (const auto& v : vehicles) 
        {
            v.display();
            if (v.getType()) 
            {
                cars++;
            } 
            else 
            {
                bikes++;
            }
            total += v.getFare();
        }

        printDivider();
        cout << " SUMMARY REPORT\n";
        printDivider();
        cout << " Total Cars    : " << cars << endl;
        cout << " Total Bikes   : " << bikes << endl;
        cout << " Total Revenue : Rs " << total << endl;
        printDivider();
        system("pause");
    }
};

// Shows the opening screen
void showWelcome() {
    system("cls");
    cout << "\n\n";
    cout << string(MENU_WIDTH, '=') << endl;
    printHeaderCentered("WELCOME TO PARKING SYSTEM");
    printHeaderCentered("Manage Vehicles Efficiently");
    cout << string(MENU_WIDTH, '=') << endl;
    printHeaderCentered("System Loading...");
    cout << "\n\n";
    Sleep(1500);
}

// --- MAIN FUNCTION ---
int main() {
    SecuritySystem security;
    ParkingSystem parking;
    int role = 0;
    showWelcome();

    bool appRunning = true;
    while (appRunning) 
    {
        printHeader("MAIN MENU");
        cout << "1. Login\n2. Change Password\n3. View Parking Rates\n4. Exit\n";
        printDivider();
        cout << "Choice: ";
        int choice = getIntInput();

        if (choice == 1) 
        {
            role = security.login();
            bool loggedIn = true;
            while (loggedIn) 
            {
                string roleTitle = (role == 1) ? "ADMIN DASHBOARD" : "STAFF DASHBOARD";
                printHeader(roleTitle);
                cout << "1. Add Vehicle\n2. Search Token\n3. View Rates\n";
                if (role == 1) 
                {
                    cout << "4. Checkout (Delete)\n5. Full Report\n6. Logout\n";
                } 
                else 
                {
                    cout << "4. Full Report\n5. Logout\n";
                }

                printDivider();
                cout << "Choice: ";
                int pChoice = getIntInput();

                if (role == 1) 
                {
                    if (pChoice == 1) parking.addVehicle();
                    else if (pChoice == 2) parking.searchToken();
                    else if (pChoice == 3) ParkingSystem::showRates();
                    else if (pChoice == 4) parking.deleteVehicle();
                    else if (pChoice == 5) parking.report();
                    else if (pChoice == 6) loggedIn = false;
                } 
                else 
                {
                    if (pChoice == 1) parking.addVehicle();
                    else if (pChoice == 2) parking.searchToken();
                    else if (pChoice == 3) ParkingSystem::showRates();
                    else if (pChoice == 4) parking.report();
                    else if (pChoice == 5) loggedIn = false;
                }
            }
        } 
        else if (choice == 2) 
        {
            security.changePassword();
        } 
        else if (choice == 3) 
        {
            ParkingSystem::showRates();
        } 
        else if (choice == 4) 
        {
            showExitMessage();
            appRunning = false;
        } 
        else 
        {
            cout << "\n[!] Invalid Choice\n";
            system("pause");
        }
    }
    return 0;
}
