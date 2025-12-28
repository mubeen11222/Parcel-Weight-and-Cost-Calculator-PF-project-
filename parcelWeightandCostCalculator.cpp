#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int MAX = 20;
int countRecords = 0;

/* ---------- Nested Structures ---------- */
struct Address {
    char city[20];
    char phone[15];
};

struct Parcel {
    int parcelID;
    Address sender;
    Address receiver;
    float weight;
    float distance;
    float cost;
};

/* ---------- Function Prototypes ---------- */
void menu();
void addParcel(Parcel parcels[]);
void displayParcels(Parcel parcels[]);
void searchParcel(Parcel parcels[]);
void updateParcel(Parcel parcels[]);
void saveToFile(Parcel parcels[]);
void loadFromFile(Parcel parcels[]);
float calculateCost(float weight, float distance);

/* ---------- Main Function ---------- */
int main() {
    Parcel parcels[MAX];
    int choice;

    loadFromFile(parcels);

    do {
        menu();
        cin >> choice;

        switch (choice) {
        case 1:
            addParcel(parcels);
            break;
        case 2:
            displayParcels(parcels);
            break;
        case 3:
            searchParcel(parcels);
            break;
        case 4:
            updateParcel(parcels);
            break;
        case 5:
            saveToFile(parcels);
            cout << "Data saved successfully.\n";
            break;
        case 0:
            saveToFile(parcels);
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}

/* ---------- Menu Function ---------- */
void menu() {
    cout << "\n====== Parcel Weight & Cost Calculator ======\n";
    cout << "1. Add Parcel\n";
    cout << "2. Display All Parcels\n";
    cout << "3. Search Parcel\n";
    cout << "4. Update Parcel\n";
    cout << "5. Save Data\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

/* ---------- Add Parcel ---------- */
void addParcel(Parcel parcels[]) {
    if (countRecords >= MAX) {
        cout << "Parcel limit reached!\n";
        return;
    }

    Parcel &p = parcels[countRecords];

    cout << "Enter Parcel ID: ";
    cin >> p.parcelID;

    cout << "Sender City: ";
    cin >> p.sender.city;
    cout << "Sender Phone: ";
    cin >> p.sender.phone;

    cout << "Receiver City: ";
    cin >> p.receiver.city;
    cout << "Receiver Phone: ";
    cin >> p.receiver.phone;

    do {
        cout << "Enter Weight (kg): ";
        cin >> p.weight;
    } while (p.weight <= 0);

    do {
        cout << "Enter Distance (km): ";
        cin >> p.distance;
    } while (p.distance <= 0);

    p.cost = calculateCost(p.weight, p.distance);

    countRecords++;
    cout << "Parcel added successfully!\n";
}

/* ---------- Cost Calculation ---------- */
float calculateCost(float weight, float distance) {
    float rate = 5.0; // base rate
    return (weight * 10) + (distance * rate);
}

/* ---------- Display Parcels ---------- */
void displayParcels(Parcel parcels[]) {
    if (countRecords == 0) {
        cout << "No records found.\n";
        return;
    }

    for (int i = 0; i < countRecords; i++) {
        cout << "\nParcel ID: " << parcels[i].parcelID;
        cout << "\nSender City: " << parcels[i].sender.city;
        cout << "\nReceiver City: " << parcels[i].receiver.city;
        cout << "\nWeight: " << parcels[i].weight << " kg";
        cout << "\nDistance: " << parcels[i].distance << " km";
        cout << "\nCost: Rs. " << parcels[i].cost << endl;
    }
}

/* ---------- Search Parcel ---------- */
void searchParcel(Parcel parcels[]) {
    int id;
    cout << "Enter Parcel ID to search: ";
    cin >> id;

    for (int i = 0; i < countRecords; i++) {
        if (parcels[i].parcelID == id) {
            cout << "Parcel Found!\n";
            cout << "Cost: Rs. " << parcels[i].cost << endl;
            return;
        }
    }
    cout << "Parcel not found.\n";
}

/* ---------- Update Parcel ---------- */
void updateParcel(Parcel parcels[]) {
    int id;
    cout << "Enter Parcel ID to update: ";
    cin >> id;

    for (int i = 0; i < countRecords; i++) {
        if (parcels[i].parcelID == id) {
            cout << "Enter new weight: ";
            cin >> parcels[i].weight;
            cout << "Enter new distance: ";
            cin >> parcels[i].distance;

            parcels[i].cost = calculateCost(parcels[i].weight, parcels[i].distance);
            cout << "Parcel updated successfully!\n";
            return;
        }
    }
    cout << "Parcel not found.\n";
}

/* ---------- File Save ---------- */
void saveToFile(Parcel parcels[]) {
    ofstream file("parcels.txt");
    file << countRecords << endl;

    for (int i = 0; i < countRecords; i++) {
        file << parcels[i].parcelID << " "
             << parcels[i].sender.city << " "
             << parcels[i].sender.phone << " "
             << parcels[i].receiver.city << " "
             << parcels[i].receiver.phone << " "
             << parcels[i].weight << " "
             << parcels[i].distance << " "
             << parcels[i].cost << endl;
    }
    file.close();
}

/* ---------- File Load ---------- */
void loadFromFile(Parcel parcels[]) {
    ifstream file("parcels.txt");

    if (!file)
        return;

    file >> countRecords;

    for (int i = 0; i < countRecords; i++) {
        file >> parcels[i].parcelID
             >> parcels[i].sender.city
             >> parcels[i].sender.phone
             >> parcels[i].receiver.city
             >> parcels[i].receiver.phone
             >> parcels[i].weight
             >> parcels[i].distance
             >> parcels[i].cost;
    }
    file.close();
}
