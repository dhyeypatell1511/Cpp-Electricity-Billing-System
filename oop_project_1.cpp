#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ==========================================
// 1. BASE CLASS (Parent)
// ==========================================
class ElectricityConsumer {
protected:
    string consumerID;
    string consumerName;
    double unitsConsumed;

public:
    // Simple Constructor
    ElectricityConsumer(string id, string name, double units) {
        consumerID = id;
        consumerName = name;
        unitsConsumed = units;
    }

    // Virtual functions for Polymorphism
    virtual double calculateBill() = 0;
    virtual string getCategory() = 0;

    // Standard display function
    virtual void displayBill() {
        cout << "ID: " << consumerID 
             << " | Name: " << consumerName 
             << " | Type: " << getCategory() 
             << " | Units: " << unitsConsumed 
             << " | Bill: Rs. " << calculateBill() << "\n";
    }

    virtual ~ElectricityConsumer() {}
};

// ==========================================
// 2. DERIVED CLASSES (Children)
// ==========================================

// Domestic Consumer
class DomesticConsumer : public ElectricityConsumer {
public:
    DomesticConsumer(string id, string name, double units) 
        : ElectricityConsumer(id, name, units) {}

    string getCategory() { 
        return "Domestic"; 
    }

    double calculateBill() {
        double bill = 0.0;
        if (unitsConsumed <= 100) {
            bill = unitsConsumed * 3.00; 
        } else if (unitsConsumed <= 300) {
            bill = (100 * 3.00) + ((unitsConsumed - 100) * 5.00);
        } else {
            bill = (100 * 3.00) + (200 * 5.00) + ((unitsConsumed - 300) * 7.00);
        }
        return bill; 
    }
};

// Commercial Consumer
class CommercialConsumer : public ElectricityConsumer {
private:
    double sanctionedLoadKW;
public:
    CommercialConsumer(string id, string name, double units, double loadKW) 
        : ElectricityConsumer(id, name, units) {
        sanctionedLoadKW = loadKW; // Simple assignment
    }

    string getCategory() { 
        return "Commercial"; 
    }

    double calculateBill() {
        double baseBill = unitsConsumed * 8.00; 
        double demandCharge = sanctionedLoadKW * 200.00; 
        return baseBill + demandCharge;
    }
};

// Industrial Consumer
class IndustrialConsumer : public ElectricityConsumer {
private:
    double powerFactor;
public:
    IndustrialConsumer(string id, string name, double units, double pf) 
        : ElectricityConsumer(id, name, units) {
        powerFactor = pf;
    }

    string getCategory() { 
        return "Industrial"; 
    }

    double calculateBill() {
        double bill = unitsConsumed * 10.00; 
        if (powerFactor < 0.9) {
            bill = bill + (bill * 0.15); // Add 15% penalty
        }
        return bill;
    }
};

// ==========================================
// 3. CONTROLLER CLASS
// ==========================================
class BillingEngine {
private:
    vector<ElectricityConsumer*> activeConsumers; 

public:
    void addDomestic() {
        string id, name; 
        double units;
        cout << "Enter ID, Name, Units: ";
        cin >> id >> name >> units;
        
        DomesticConsumer* newCustomer = new DomesticConsumer(id, name, units);
        activeConsumers.push_back(newCustomer);
        
        cout << "Domestic Consumer Added.\n";
    }

    void addCommercial() {
        string id, name; 
        double units, load;
        cout << "Enter ID, Name, Units, Load(kW): ";
        cin >> id >> name >> units >> load;
        
        CommercialConsumer* newCustomer = new CommercialConsumer(id, name, units, load);
        activeConsumers.push_back(newCustomer);
        
        cout << "Commercial Consumer Added.\n";
    }

    void addIndustrial() {
        string id, name; 
        double units, pf;
        cout << "Enter ID, Name, Units, Power Factor: ";
        cin >> id >> name >> units >> pf;
        
        IndustrialConsumer* newCustomer = new IndustrialConsumer(id, name, units, pf);
        activeConsumers.push_back(newCustomer);
        
        cout << "Industrial Consumer Added.\n";
    }

    void displayAllRecords() {
        if (activeConsumers.size() == 0) {
            cout << "No records found.\n"; 
            return;
        }
        
        cout << "\n--- ALL BILLS ---\n";
        // Classic for-loop, easy to explain
        for (int i = 0; i < activeConsumers.size(); i++) {
            activeConsumers[i]->displayBill(); 
        }
        cout << "-----------------\n";
    }

    ~BillingEngine() {
        for (int i = 0; i < activeConsumers.size(); i++) {
            delete activeConsumers[i]; 
        }
    }
};

// ==========================================
// 4. MAIN PROGRAM
// ==========================================
int main() {
    BillingEngine engine;
    int choice = 0;

    while (choice != 5) {
        cout << "\n1. Add Domestic\n2. Add Commercial\n3. Add Industrial\n4. View Bills\n5. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            engine.addDomestic();
        } else if (choice == 2) {
            engine.addCommercial();
        } else if (choice == 3) {
            engine.addIndustrial();
        } else if (choice == 4) {
            engine.displayAllRecords();
        } else if (choice == 5) {
            cout << "Exiting...\n";
        } else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}