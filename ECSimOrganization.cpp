#include "ECSimOrganization.h"

//bursar
void ECSimBursar :: SetTuition(int tuitionIn){
    tuition = tuitionIn;
}

int ECSimBursar :: GetTuition() const{
    return tuition;
}

//diningHall
int ECSimDiningHall :: GetStudentCost() const{
    return studentPrice;
}

int ECSimDiningHall :: GetEmployeeCost() const{
    return employeePrice;
}

//recCenter
int ECSimRecCenter :: GetStudentCost() const{
    return studentPrice;
}

int ECSimRecCenter :: GetEmployeeCost() const{
    return employeePrice;
}

