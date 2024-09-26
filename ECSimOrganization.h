//
//  ECSimOrganization.h
//  
//
//  Created by Yufeng Wu on 2/21/23.
//

#ifndef ECSimOrganization_h
#define ECSimOrganization_h

#include "ECCampusSimulator.h"
//  Place simulation organization related code here...
//  Consider adding base class here...

// ***********************************************************
// University bursar office: handling enrollment related matters

class ECSimBursar  : public ECSimEntity
{
public:
    // each organization has an unique ID
    ECSimBursar(int bid) : ECSimEntity(bid) {}
    
    // set tuition rate; same tuition for everyone; tuition is form the entire simulation period (say semester)
    virtual void SetTuition(int tuitionIn);
    virtual int GetTuition() const;

    // your code goes here
private:
    int tuition;    
};

// ***********************************************************
// Human resource (HR)

class ECSimHR : public ECSimEntity
{
public:
    // each organization has an unique ID
    ECSimHR(int tid) : ECSimEntity(tid) {}
    
};

// ***********************************************************
// Dining hall

class ECSimDiningHall : public ECSimEntity
{
public:
    // each organization has an unique ID
    ECSimDiningHall(int tid) : ECSimEntity(tid) {}

    virtual int GetEmployeeCost() const;

    virtual int GetStudentCost() const;

    // your code goes here
private:
    int employeePrice = 10;
    int studentPrice = 5;

};

// ***********************************************************
// Rec center

class ECSimRecCenter : public ECSimEntity
{
public:
    // each organization has an unique ID
    ECSimRecCenter(int tid) : ECSimEntity(tid) {}

    virtual int GetEmployeeCost() const;

    virtual int GetStudentCost() const;

private:
    int employeePrice = 20;
    int studentPrice = 10;
};

// ***********************************************************
// Library

class ECSimLibrary : public ECSimEntity
{
public:
    // each organization has an unique ID
    ECSimLibrary(int bid) : ECSimEntity(bid) {}
    
    // your code goes here
};

#endif /* ECSimOrganization_h */
