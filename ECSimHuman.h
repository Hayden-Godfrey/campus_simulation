//
//  ECSimHuman.h
//  
//  Human related definitions in campus simulation

#ifndef ECSimHuman_h
#define ECSimHuman_h
#include "ECCampusSimulator.h"
//  Place all human related definitions here: ECSimStudent, ECSimEmployee, etc


// ***********************************************************
// Employee

class ECSimEmployee : public ECSimEntity
{
public:
    ECSimEmployee(int idEmployee) : ECSimEntity(idEmployee), pay(0) {}
    
    // payrate: amount paid per day. If not set, not getting paid
    void SetPayrate(int rate);  
    int Getpayrate() const;  
    
private:
    int pay;
    // Your code goes here... 
    
};

// ***********************************************************
// Student

class ECSimStudent : public ECSimEntity
{
public:
    // each student must have a distinct id
    ECSimStudent(int idStudent) : ECSimEntity(idStudent) {}
    
};

#endif /* ECSimHuman_h */
