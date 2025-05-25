#ifndef DISASTERSIMULATOR_H
#define DISASTERSIMULATOR_H

#include <string>
#include <vector>
#include <memory>
using namespace std;

// Abstract Base Class
class Disaster {
protected:
    string location;
    int severity;
    string timestamp;

public:
    Disaster(string loc, int sev, string time);
    virtual void simulateResponse() = 0;
    virtual string getType() const = 0;
    virtual ~Disaster();
};

// Earthquake
class Earthquake : public Disaster {
public:
    Earthquake(string loc, int sev, string time);
    void simulateResponse() override;
    string getType() const override;
private:
    void countdown();
};

// Flood
class Flood : public Disaster {
public:
    Flood(string loc, int sev, string time);
    void simulateResponse() override;
    string getType() const override;
private:
    void countdown();
};

// Fire
class Fire : public Disaster {
public:
    Fire(string loc, int sev, string time);
    void simulateResponse() override;
    string getType() const override;
private:
    void countdown();
};

// Response Unit
class ResponseUnit {
private:
    string unitName;
    bool available;

public:
    ResponseUnit(string name);
    void deploy(const Disaster& d);
    void reset();
};

// Simulation Manager
class SimulationManager {
private:
    vector<unique_ptr<Disaster>> disasters;
    vector<ResponseUnit> units;

public:
    SimulationManager();
    void createDisaster(int type, string location, int severity, string time);
    void runSimulation();
};

#endif
