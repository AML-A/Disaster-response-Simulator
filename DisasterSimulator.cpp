#include "DisasterSimulator.h"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

// -------- Disaster Base Implementation --------
Disaster::Disaster(string loc, int sev, string time)
    : location(loc), severity(sev), timestamp(time) {
}

Disaster::~Disaster() {}

// -------- Earthquake --------
Earthquake::Earthquake(string loc, int sev, string time)
    : Disaster(loc, sev, time) {
}

void Earthquake::simulateResponse() {
    cout << "\033[1;33m[EARTHQUAKE ALERT]\033[0m\n";
    cout << "Location: " << location << " | Severity: " << severity << " | Time: " << timestamp << "\n";
    countdown();
    cout << "🧑‍🚒 Rescue teams dispatched to earthquake site.\n";
    cout << "🏥 Medical teams en route.\n";
}

string Earthquake::getType() const {
    return "Earthquake";
}

void Earthquake::countdown() {
    cout << "🚨 Dispatching in ";
    for (int i = 3; i > 0; --i) {
        cout << i << "... ";
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "GO!\n";
}

// -------- Flood --------
Flood::Flood(string loc, int sev, string time)
    : Disaster(loc, sev, time) {
}

void Flood::simulateResponse() {
    cout << "\033[1;34m[FLOOD WARNING]\033[0m\n";
    cout << "Location: " << location << " | Severity: " << severity << " | Time: " << timestamp << "\n";
    countdown();
    cout << "🚤 Boats deployed for evacuation.\n";
    cout << "🧑‍⚕️ Emergency medics on standby.\n";
}

string Flood::getType() const {
    return "Flood";
}

void Flood::countdown() {
    cout << "🚨 Dispatching in ";
    for (int i = 3; i > 0; --i) {
        cout << i << "... ";
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "GO!\n";
}

// -------- Fire --------
Fire::Fire(string loc, int sev, string time)
    : Disaster(loc, sev, time) {
}

void Fire::simulateResponse() {
    cout << "\033[1;31m[FIRE EMERGENCY]\033[0m\n";
    cout << "Location: " << location << " | Severity: " << severity << " | Time: " << timestamp << "\n";
    countdown();
    cout << "🚒 Fire brigade on the scene.\n";
    cout << "🧯 Fire suppression systems activated.\n";
}

string Fire::getType() const {
    return "Fire";
}

void Fire::countdown() {
    cout << "🚨 Dispatching in ";
    for (int i = 3; i > 0; --i) {
        cout << i << "... ";
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "GO!\n";
}

// -------- ResponseUnit --------
ResponseUnit::ResponseUnit(string name) : unitName(name), available(true) {}

void ResponseUnit::deploy(const Disaster& d) {
    if (available) {
        cout << "✅ Unit \"" << unitName << "\" deployed to handle " << d.getType() << ".\n";
        available = false;
    }
    else {
        cout << "⛔ Unit \"" << unitName << "\" is currently busy.\n";
    }
}

void ResponseUnit::reset() {
    available = true;
}

// -------- SimulationManager --------
SimulationManager::SimulationManager() {
    units.emplace_back("Rescue Team");
    units.emplace_back("Medical Unit");
    units.emplace_back("Fire Brigade");
}

void SimulationManager::createDisaster(int type, string location, int severity, string time) {
    if (type == 1)
        disasters.push_back(unique_ptr<Disaster>(new Earthquake(location, severity, time)));
    else if (type == 2)
        disasters.push_back(unique_ptr<Disaster>(new Flood(location, severity, time)));
    else if (type == 3)
        disasters.push_back(unique_ptr<Disaster>(new Fire(location, severity, time)));
    else
        cout << "Invalid disaster type.\n";
}

void SimulationManager::runSimulation() {
    if (disasters.empty()) {
        cout << "⚠️ No disasters to simulate.\n";
        return;
    }

    cout << "\n\033[1;36m===== BEGINNING SIMULATION =====\033[0m\n";
    for (auto& disaster : disasters) {
        disaster->simulateResponse();
        for (auto& unit : units) {
            unit.deploy(*disaster);
        }
        cout << "-----------------------------\n";
        this_thread::sleep_for(chrono::seconds(2));
    }

    for (auto& unit : units) {
        unit.reset();
    }

    disasters.clear();
    cout << "\033[1;32m✅ Simulation complete. All units reset.\033[0m\n";
}
