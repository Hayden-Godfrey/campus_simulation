//  ECCampusSimulator.h
//  
//
//  Created by Yufeng Wu on 2/21/23.
//

#ifndef ECCampusSimulator_h
#define ECCampusSimulator_h

#include <vector>
#include <map>
using namespace std;

// ***********************************************************
// Simulation script: a sequence of events to simulate

class ECSimEntity
{
public:
    ECSimEntity(int id) : id(id), balance(0) {}
    virtual ~ECSimEntity();
    virtual void Paid(int amount);
    virtual void Charged(int amount);
    virtual int GetBalance() const;
    virtual int GetID() const;
    virtual void SetBudgetForDay(int amount);
    virtual int GetBudgetForDay() const;
private:
    int balance;
    int budget = 0;
    int id;
};

class ECCampusSimScript
{
public:
    ECCampusSimScript();
    // Mark the end of a day; unitl calling it again, any events before are the current day
    void EndofDay();
    // Add a simulation event. An event is from a sender (with type and id) to a receiver (with type and id). Also evtCode is the code of the type of event between these two kinds of entities. For example, a student (sender) enrolls (event code 0) in univerisity (receiver)
    void AddSimEvt(int idSender, int idReceiver);
    
    vector<pair<int, int>> GetEvents();
    // Your code here...
private:
    vector<pair<int, int>> events;
};

// ***********************************************************
// Simulator

class ECCampusSimulator
{
public:
    ECCampusSimulator();
    ~ECCampusSimulator();
    virtual void Simulate(ECCampusSimScript &script);
    
    // Add a new sim item
    virtual void AddSimItem(ECSimEntity *pe);

    // Your code goes here..
private:
    vector<ECSimEntity*> vecE;
    map<int, ECSimEntity*> mapE;
};

#endif /* ECCampusSimulator_h */
