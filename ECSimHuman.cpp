#include "ECSimHuman.h"

//employee
void ECSimEmployee :: SetPayrate(int amount){
    pay = amount;
}

int ECSimEmployee :: Getpayrate() const{
    return pay;
}