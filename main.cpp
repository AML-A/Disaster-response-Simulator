#include <iostream>
#include <string>
#include "DisasterSimulator.h"

using namespace std;

int main() {
    SimulationManager manager;
    int choice;
    string location, time;
    int severity;

    cout << "\033[1;35m====== Disaster Response Simulator ======\033[0m\n";

    do {
        cout << "\nChoose Disaster Type to Simulate:\n";
        cout << "1. Earthquake\n2. Flood\n3. Fire\n4. Run Simulation\n0. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 3) {
            cout << "Enter location: ";
            cin.ignore();
            getline(cin, location);
            cout << "Enter severity (1-10): ";
            cin >> severity;
            cout << "Enter timestamp (e.g., 2025-05-20 14:00): ";
            cin.ignore();
            getline(cin, time);

            manager.createDisaster(choice, location, severity, time);
        }
        else if (choice == 4) {
            manager.runSimulation();
        }

    } while (choice != 0);

    cout << "\033[1;32mSimulation ended. Stay safe!\033[0m\n";
    return 0;
}
