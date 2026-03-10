#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

string getCurrentTimestamp() {
    time_t now = time(nullptr);
    char   buf[25];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}

class Vehicle {
private:
    string plateNumber;
    string ownerName;
    string vehicleType;
    bool   hasFasTag;

public:
    Vehicle() : plateNumber(""), ownerName(""), vehicleType(""), hasFasTag(false) {}

    Vehicle(string plate, string owner, string type, bool fasTag)
        : plateNumber(plate), ownerName(owner), vehicleType(type), hasFasTag(fasTag) {}

    string getPlate()  const { return plateNumber; }
    string getOwner()  const { return ownerName;   }
    string getType()   const { return vehicleType;  }
    bool   getFasTag() const { return hasFasTag;    }

    void display() const {
        cout << "  Plate No     : " << plateNumber << "\n";
        cout << "  Owner        : " << ownerName   << "\n";
        cout << "  Vehicle Type : " << vehicleType  << "\n";
        cout << "  FASTag       : " << (hasFasTag ? "Yes" : "No") << "\n";
    }
};


class TollBooth {
private:
    int    boothId;
    string location;
    double totalRevenue;
    int    vehicleCount;

public:
    TollBooth() : boothId(0), location(""), totalRevenue(0.0), vehicleCount(0) {}

    TollBooth(int id, string loc)
        : boothId(id), location(loc), totalRevenue(0.0), vehicleCount(0) {}

    void addRevenue(double amount) {
        totalRevenue += amount;
        vehicleCount++;
    }

    int    getId()           const { return boothId;      }
    string getLocation()     const { return location;     }
    double getTotalRevenue() const { return totalRevenue; }
    int    getVehicleCount() const { return vehicleCount; }

    void display() const {
        cout << fixed << setprecision(2);
        cout << "  Booth-" << boothId
             << "\t" << location
             << "\tVehicles: " << vehicleCount
             << "\tRevenue: INR " << totalRevenue << "\n";
    }
};

class TollSystem {
private:
    Vehicle   vehicles[100];
    TollBooth booths[5];
    int       vehicleCount;
    int       boothCount;

    double calculateToll(const string& type) const {
        if      (type == "Motorcycle") return  30.0;
        else if (type == "Car")        return  60.0;
        else if (type == "SUV")        return  80.0;
        else if (type == "Bus")        return 120.0;
        else if (type == "Truck")      return 150.0;
        else                           return   0.0;
    }

    bool isPeakHour() const {
        time_t now = time(nullptr);
        tm*    lt  = localtime(&now);
        int    h   = lt->tm_hour;
        return (h >= 7 && h < 10) || (h >= 17 && h < 20);
    }

    int findVehicle(const string& plate) const {
        for (int i = 0; i < vehicleCount; i++) {
            if (vehicles[i].getPlate() == plate)
                return i;
        }
        return -1;
    }

    int findBooth(int id) const {
        for (int i = 0; i < boothCount; i++) {
            if (booths[i].getId() == id)
                return i;
        }
        return -1;
    }

    void logTransaction(const string& plate, const string& type,
                        int boothId, double amount, const string& mode) {
        ofstream file("transactions.txt", ios::app);
        if (file.is_open()) {
            file << fixed << setprecision(2);
            file << getCurrentTimestamp()
                 << "\t" << plate
                 << "\t" << type
                 << "\tBooth-" << boothId
                 << "\tINR " << amount
                 << "\t" << mode << "\n";
            file.close();
        }
    }

    void generateReceipt(const Vehicle& v, int bi,
                         double baseToll, double finalToll,
                         bool peakHour, const string& timestamp) {

        int    boothId       = booths[bi].getId();
        string boothLocation = booths[bi].getLocation();
        double surcharge     = peakHour      ? baseToll * 0.5                    : 0.0;
        double discount      = v.getFasTag() ? (baseToll + surcharge) * 0.10 : 0.0;

        // Print to screen
        cout << "\n";
        cout << "  ================================================\n";
        cout << "         SMART TOLL COLLECTION RECEIPT\n";
        cout << "  ================================================\n";
        cout << "  Date & Time  : " << timestamp                              << "\n";
        cout << "  Booth        : BOOTH-" << boothId << " - " << boothLocation << "\n";
        cout << "  ------------------------------------------------\n";
        cout << "  Plate No     : " << v.getPlate()                           << "\n";
        cout << "  Owner        : " << v.getOwner()                           << "\n";
        cout << "  Vehicle Type : " << v.getType()                            << "\n";
        cout << "  FASTag       : " << (v.getFasTag() ? "Yes" : "No")        << "\n";
        cout << "  ------------------------------------------------\n";
        cout << fixed << setprecision(2);
        cout << "  Base Toll    : INR " << baseToll                           << "\n";
        if (peakHour)
            cout << "  Peak Surcharge: INR " << surcharge                     << "\n";
        if (v.getFasTag())
            cout << "  FASTag Disc  : -INR " << discount                      << "\n";
        cout << "  ------------------------------------------------\n";
        cout << "  TOTAL PAID   : INR " << finalToll                          << "\n";
        cout << "  Payment Mode : " << (v.getFasTag() ? "FASTag" : "Cash")   << "\n";
        cout << "  ================================================\n";
        cout << "          Thank you! Drive Safe!\n";
        cout << "  ================================================\n";

        // Save to file
        string filename = "receipt_" + v.getPlate() + ".txt";
        ofstream file(filename);
        if (file.is_open()) {
            file << fixed << setprecision(2);
            file << "================================================\n";
            file << "       SMART TOLL COLLECTION RECEIPT\n";
            file << "================================================\n";
            file << "Date & Time  : " << timestamp                              << "\n";
            file << "Booth        : BOOTH-" << boothId << " - " << boothLocation << "\n";
            file << "------------------------------------------------\n";
            file << "Plate No     : " << v.getPlate()                          << "\n";
            file << "Owner        : " << v.getOwner()                          << "\n";
            file << "Vehicle Type : " << v.getType()                           << "\n";
            file << "FASTag       : " << (v.getFasTag() ? "Yes" : "No")       << "\n";
            file << "------------------------------------------------\n";
            file << "Base Toll    : INR " << baseToll                          << "\n";
            if (peakHour)
                file << "Peak Surcharge: INR " << surcharge                    << "\n";
            if (v.getFasTag())
                file << "FASTag Disc  : -INR " << discount                     << "\n";
            file << "------------------------------------------------\n";
            file << "TOTAL PAID   : INR " << finalToll                         << "\n";
            file << "Payment Mode : " << (v.getFasTag() ? "FASTag" : "Cash")  << "\n";
            file << "================================================\n";
            file << "        Thank you! Drive Safe!\n";
            file << "================================================\n";
            file.close();
            cout << "\n  Receipt saved -> " << filename << "\n";
        }
    }

public:
    TollSystem() : vehicleCount(0), boothCount(3) {
        booths[0] = TollBooth(1, "NH-48 Entry Gate");
        booths[1] = TollBooth(2, "Mumbai-Pune Expressway");
        booths[2] = TollBooth(3, "Outer Ring Road");
    }

    void registerVehicle() {
        cout << "\n  --- Register New Vehicle ---\n";

        if (vehicleCount >= 100) {
            cout << "  Error: Vehicle limit reached.\n";
            return;
        }

        string plate, owner, type;
        int    typeChoice;
        char   ft;

        cout << "  Enter Plate Number : "; cin >> plate;

        if (findVehicle(plate) >= 0) {
            cout << "  Error: Plate already registered.\n";
            return;
        }

        cin.ignore();
        cout << "  Owner Name         : "; getline(cin, owner);

        cout << "\n  Vehicle Types:\n";
        cout << "  1. Motorcycle\n";
        cout << "  2. Car\n";
        cout << "  3. SUV\n";
        cout << "  4. Bus\n";
        cout << "  5. Truck\n";

        do {
            cout << "  Choice (1-5)       : "; cin >> typeChoice;
            if (typeChoice < 1 || typeChoice > 5)
                cout << "  Invalid. Enter 1 to 5.\n";
        } while (typeChoice < 1 || typeChoice > 5);

        switch (typeChoice) {
            case 1: type = "Motorcycle"; break;
            case 2: type = "Car";        break;
            case 3: type = "SUV";        break;
            case 4: type = "Bus";        break;
            case 5: type = "Truck";      break;
        }

        cout << "  Has FASTag? (y/n)  : "; cin >> ft;
        bool fasTag = (ft == 'y' || ft == 'Y');

        vehicles[vehicleCount++] = Vehicle(plate, owner, type, fasTag);

        cout << "\n  Vehicle registered successfully!\n";
        cout << "  ----------------------------\n";
    }

    void processToll() {
        cout << "\n  --- Process Toll ---\n";

        cout << "\n  Available Booths:\n";
        cout << "  --------------------\n";
        for (int i = 0; i < boothCount; i++)
            booths[i].display();
        cout << "  --------------------\n";

        int boothId;
        cout << "  Select Booth ID : "; cin >> boothId;

        int bi = findBooth(boothId);
        if (bi < 0) {
            cout << "  Error: Booth not found.\n";
            return;
        }

        string plate;
        cout << "  Enter Plate No  : "; cin >> plate;

        int vi = findVehicle(plate);
        if (vi < 0) {
            cout << "  Error: Vehicle not registered.\n";
            return;
        }

        Vehicle& v        = vehicles[vi];
        double   baseToll = calculateToll(v.getType());
        double   toll     = baseToll;
        bool     peak     = isPeakHour();

        if (peak)          toll *= 1.5;
        if (v.getFasTag()) toll *= 0.9;

        string timestamp = getCurrentTimestamp();

        booths[bi].addRevenue(toll);
        logTransaction(plate, v.getType(), boothId, toll,
                       v.getFasTag() ? "FASTag" : "Cash");
        generateReceipt(v, bi, baseToll, toll, peak, timestamp);
    }

    void searchVehicle() {
        cout << "\n  --- Search Vehicle ---\n";

        string plate;
        cout << "  Enter Plate No: "; cin >> plate;

        int vi = findVehicle(plate);
        if (vi < 0) {
            cout << "  Error: Vehicle not found.\n";
            return;
        }

        cout << "\n";
        cout << "  --------------------\n";
        vehicles[vi].display();
        cout << "  --------------------\n";
    }

    void viewBoothStats() {
        cout << "\n  --- Booth Statistics ---\n";
        cout << "  --------------------\n";
        for (int i = 0; i < boothCount; i++)
            booths[i].display();
        cout << "  --------------------\n";
    }

    void viewTransactions() {
        cout << "\n  --- Transaction Log ---\n";
        cout << "  --------------------\n";

        ifstream file("transactions.txt");
        if (!file.is_open()) {
            cout << "  No transactions recorded yet.\n";
            return;
        }

        string line;
        int    count = 0;
        while (getline(file, line)) {
            cout << "  " << line << "\n";
            count++;
        }
        file.close();

        cout << "  --------------------\n";
        if (count == 0)
            cout << "  No transactions found.\n";
        else
            cout << "  Total transactions: " << count << "\n";
    }

    void viewAllVehicles() {
        cout << "\n  --- All Registered Vehicles ---\n";

        if (vehicleCount == 0) {
            cout << "  No vehicles registered yet.\n";
            return;
        }

        for (int i = 0; i < vehicleCount; i++) {
            cout << "\n  [" << (i + 1) << "]\n";
            vehicles[i].display();
            cout << "  --------------------\n";
        }
        cout << "  Total: " << vehicleCount << " vehicle(s)\n";
    }
};

int main() {

    TollSystem system;
    int        choice;

    cout << "\n";
    cout << "  ================================================\n";
    cout << "       SMART TOLL COLLECTION SYSTEM\n";
    cout << "  ================================================\n";

    do {
        cout << "\n";
        cout << "  ================\n";
        cout << "     MAIN MENU\n";
        cout << "  ================\n";
        cout << "  1. Register Vehicle\n";
        cout << "  2. Process Toll\n";
        cout << "  3. Search Vehicle\n";
        cout << "  4. Booth Statistics\n";
        cout << "  5. Transaction Log\n";
        cout << "  6. All Registered Vehicles\n";
        cout << "  7. Exit\n";
        cout << "  ----------------\n";

        do {
            cout << "  Enter choice (1-7): ";
            cin >> choice;
            if (choice < 1 || choice > 7)
                cout << "  Invalid. Please enter a number between 1 and 7.\n";
        } while (choice < 1 || choice > 7);

        switch (choice) {
            case 1: system.registerVehicle(); break;
            case 2: system.processToll();     break;
            case 3: system.searchVehicle();   break;
            case 4: system.viewBoothStats();  break;
            case 5: system.viewTransactions();break;
            case 6: system.viewAllVehicles(); break;
            case 7:
                cout << "\n  ------------------------------------------------\n";
                cout << "  Thank you for using the Toll System. Goodbye!\n";
                cout << "  ------------------------------------------------\n";
                break;
        }

    } while (choice != 7);

    return 0;
}



