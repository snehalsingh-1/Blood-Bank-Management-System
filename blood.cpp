#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Donor {
    string name;
    int age;
    string bloodGroup;
    string contact;

    void display() const {
        cout << left << setw(20) << name
             << setw(6) << age
             << setw(10) << bloodGroup
             << setw(15) << contact << endl;
    }
};

const string FILENAME = "donors.txt";

void saveDonor(const Donor& donor) {
    ofstream file(FILENAME, ios::app);
    file << donor.name << "," << donor.age << "," << donor.bloodGroup << "," << donor.contact << "\n";
    file.close();
}

vector<Donor> loadDonors() {
    vector<Donor> donors;
    ifstream file(FILENAME);
    string line;
    while (getline(file, line)) {
        Donor d;
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);

        d.name = line.substr(0, pos1);
        d.age = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        d.bloodGroup = line.substr(pos2 + 1, pos3 - pos2 - 1);
        d.contact = line.substr(pos3 + 1);
        donors.push_back(d);
    }
    file.close();
    return donors;
}

void writeAllDonors(const vector<Donor>& donors) {
    ofstream file(FILENAME);
    for (const auto& d : donors) {
        file << d.name << "," << d.age << "," << d.bloodGroup << "," << d.contact << "\n";
    }
    file.close();
}

void registerDonor() {
    Donor donor;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, donor.name);
    cout << "Enter Age: ";
    cin >> donor.age;
    cout << "Enter Blood Group: ";
    cin >> donor.bloodGroup;
    cout << "Enter Contact: ";
    cin >> donor.contact;

    saveDonor(donor);
    cout << "Donor registered successfully!\n";
}

void viewDonors() {
    vector<Donor> donors = loadDonors();
    if (donors.empty()) {
        cout << "No donor records found.\n";
        return;
    }

    cout << left << setw(20) << "Name"
         << setw(6) << "Age"
         << setw(10) << "BloodGroup"
         << setw(15) << "Contact" << "\n";
    cout << string(55, '-') << "\n";

    for (const auto& d : donors)
        d.display();
}

void searchByBloodGroup() {
    string bg;
    cout << "Enter blood group to search: ";
    cin >> bg;

    vector<Donor> donors = loadDonors();
    bool found = false;

    for (const auto& d : donors) {
        if (d.bloodGroup == bg) {
            if (!found) {
                cout << left << setw(20) << "Name"
                     << setw(6) << "Age"
                     << setw(10) << "BloodGroup"
                     << setw(15) << "Contact" << "\n";
                cout << string(55, '-') << "\n";
            }
            d.display();
            found = true;
        }
    }

    if (!found) {
        cout << "No donors found with blood group " << bg << ".\n";
    }
}

void updateDonor() {
    string name;
    cout << "Enter the name of the donor to update: ";
    cin.ignore();
    getline(cin, name);

    vector<Donor> donors = loadDonors();
    bool found = false;

    for (auto& d : donors) {
        if (d.name == name) {
            cout << "Enter new Age: ";
            cin >> d.age;
            cout << "Enter new Blood Group: ";
            cin >> d.bloodGroup;
            cout << "Enter new Contact: ";
            cin >> d.contact;
            found = true;
            break;
        }
    }

    if (found) {
        writeAllDonors(donors);
        cout << "Donor information updated.\n";
    } else {
        cout << "Donor not found.\n";
    }
}

void deleteDonor() {
    string name;
    cout << "Enter the name of the donor to delete: ";
    cin.ignore();
    getline(cin, name);

    vector<Donor> donors = loadDonors();
    vector<Donor> updatedDonors;
    bool found = false;

    for (const auto& d : donors) {
        if (d.name != name) {
            updatedDonors.push_back(d);
        } else {
            found = true;
        }
    }

    if (found) {
        writeAllDonors(updatedDonors);
        cout << "Donor deleted.\n";
    } else {
        cout << "Donor not found.\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n==== Blood Bank Management System ====\n";
        cout << "1. Register Donor\n";
        cout << "2. View Donors\n";
        cout << "3. Search by Blood Group\n";
        cout << "4. Update Donor\n";
        cout << "5. Delete Donor\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: registerDonor(); break;
            case 2: viewDonors(); break;
            case 3: searchByBloodGroup(); break;
            case 4: updateDonor(); break;
            case 5: deleteDonor(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
