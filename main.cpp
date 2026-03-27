#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// ==========================================
// 1. CUSTOM EXCEPTION HANDLING
// ==========================================
class InvalidInputException {
    string message;
public:
    InvalidInputException(string msg) : message(msg) {}
    void display() { cout << "Error: " << message << endl; }
};

// ==========================================
// 2. BASE CLASSES & ENCAPSULATION
// ==========================================
class CarbonEntity {
protected:
    string entityID;
public:
    CarbonEntity(string id) : entityID(id) {}
    virtual void calculateImpact() = 0; // Pure Virtual Function (Abstraction)
    virtual ~CarbonEntity() {}
};

// Interface-like class for Multiple Inheritance
class Certifiable {
public:
    void showCertification() {
        cout << "[System] This route is ISO 14064 Carbon Neutral Certified." << endl;
    }
};

// ==========================================
// 3. INHERITANCE (Single, Multilevel, Multiple)
// ==========================================
class Vehicle : public CarbonEntity {
protected:
    float fuelEfficiency; // Liters per 100km or kWh per 100km
public:
    Vehicle(string id, float eff) : CarbonEntity(id), fuelEfficiency(eff) {}
};

// Multilevel Inheritance: CarbonEntity -> Vehicle -> ElectricVehicle
class ElectricVehicle : public Vehicle {
private:
    float batteryHealth;
public:
    // Constructor Overloading
    ElectricVehicle() : Vehicle("EV-000", 15.0), batteryHealth(100.0) {}
    ElectricVehicle(string id, float eff, float health) : Vehicle(id, eff), batteryHealth(health) {}

    void calculateImpact() override {
        cout << "EV " << entityID << " Impact: " << (fuelEfficiency * 0.5) << " kg CO2/km (Grid avg)." << endl;
    }
};

// Multiple Inheritance: Truck inherits from Vehicle AND Certifiable
class GreenTruck : public Vehicle, public Certifiable {
public:
    GreenTruck(string id, float eff) : Vehicle(id, eff) {}
    void calculateImpact() override {
        cout << "GreenTruck " << entityID << " Impact: " << (fuelEfficiency * 2.3) << " kg CO2/km." << endl;
    }
};

// ==========================================
// 4. POLYMORPHISM & OPERATOR OVERLOADING
// ==========================================
class Shipment {
private:
    float weight;
    string description;
public:
    Shipment(string desc = "", float w = 0.0) : description(desc), weight(w) {}

    // Operator Overloading (+) to combine shipment weights
    Shipment operator+(const Shipment& s) {
        return Shipment("Combined Cargo", this->weight + s.weight);
    }

    // Function Overloading
    void displayShipment() {
        cout << "Cargo: " << description << " | Weight: " << weight << "kg" << endl;
    }
    void displayShipment(int priority) {
        cout << "Priority [" << priority << "] Cargo: " << description << " | Weight: " << weight << "kg" << endl;
    }

    float getWeight() const { return weight; }
};

// ==========================================
// 5. CORE SYSTEM LOGIC (Arrays, Pointers, Control Structures)
// ==========================================
class LogisticsManager {
private:
    // 2D Array: Distance Matrix between 3 major Distribution Hubs
    // Hubs: 0: New York, 1: Chicago, 2: Los Angeles
    int distanceMap[3][3] = {
        {0, 1200, 3900},
        {1200, 0, 2800},
        {3900, 2800, 0}
    };

    string hubNames[3] = {"New York", "Chicago", "Los Angeles"};

public:
    void run() {
        int choice;
        bool running = true;

        while (running) {
            cout << "\n--- GreenRoute Eco-Logistics Optimizer ---" << endl;
            cout << "1. Calculate Route Impact (2D Array Logic)" << endl;
            cout << "2. Manage Shipments (Operator Overloading)" << endl;
            cout << "3. Fleet Diagnostics (Polymorphism)" << endl;
            cout << "4. Exit" << endl;
            cout << "Select option: ";
            
            try {
                if (!(cin >> choice)) throw InvalidInputException("Integer input required.");

                switch (choice) {
                    case 1: {
                        int h1, h2;
                        cout << "Hubs: 0:NY, 1:CHI, 2:LA. Enter Origin and Destination indices: ";
                        cin >> h1 >> h2;
                        if(h1 < 0 || h1 > 2 || h2 < 0 || h2 > 2) throw InvalidInputException("Invalid Hub Index.");
                        
                        int dist = distanceMap[h1][h2];
                        cout << "Distance between " << hubNames[h1] << " and " << hubNames[h2] << " is " << dist << "km." << endl;
                        
                        // Selection using ternary operator
                        dist > 2000 ? cout << "Suggestion: Use Rail/GreenTruck for long haul.\n" : cout << "Suggestion: EV Truck sufficient.\n";
                        break;
                    }
                    case 2: {
                        // Using Pointers and Operator Overloading
                        Shipment* s1 = new Shipment("Electronics", 500.5);
                        Shipment* s2 = new Shipment("Textiles", 300.2);
                        Shipment total = *s1 + *s2; // Uses overloaded +
                        
                        total.displayShipment();
                        delete s1; // Pointer cleanup
                        delete s2;
                        break;
                    }
                    case 3: {
                        // Demonstrating Polymorphism with an array of pointers
                        CarbonEntity* fleet[2];
                        fleet[0] = new ElectricVehicle("EV-Telsa-01", 18.5, 98.0);
                        fleet[1] = new GreenTruck("Volvo-Bio-09", 25.0);

                        for(int i = 0; i < 2; i++) {
                            fleet[i]->calculateImpact(); // Dynamic Binding
                        }
                        
                        // Testing Multiple Inheritance access
                        GreenTruck* gt = dynamic_cast<GreenTruck*>(fleet[1]);
                        if(gt) gt->showCertification();

                        delete fleet[0];
                        delete fleet[1];
                        break;
                    }
                    case 4:
                        running = false;
                        break;
                    default:
                        cout << "Invalid selection." << endl;
                }
            }
            catch (InvalidInputException& e) {
                e.display();
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
    }
};

// ==========================================
// 6. MAIN FUNCTION
// ==========================================
int main() {
    // Basic Structure: Output statements and Program Entry
    cout << "==========================================" << endl;
    cout << "   GREENROUTE LOGISTICS SYSTEM INITIALIZING" << endl;
    cout << "==========================================" << endl;

    LogisticsManager system;
    system.run();

    cout << "System shutting down safely..." << endl;
    return 0;
}
