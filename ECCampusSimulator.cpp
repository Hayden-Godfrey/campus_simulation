#include "ECCampusSimulator.h"
#include "ECSimHuman.h"
#include "ECSimOrganization.h"
#include <string>
#include <vector>
using namespace std;

ECSimEntity :: ~ECSimEntity(){
}

void ECSimEntity :: Paid(int amount){
    balance += amount;
}

void ECSimEntity :: Charged(int amount){
    if(balance - amount >= 0){
        balance -= amount;
    }
    else{
        throw std :: string("BANKRUPT");
        }
    }
int ECSimEntity :: GetBalance() const{
    return balance;
    }

int ECSimEntity :: GetID() const{
    return id;
}

void ECSimEntity :: SetBudgetForDay(int amount){
    budget = amount;
}

int ECSimEntity :: GetBudgetForDay() const{
    return budget;
}

//Script

ECCampusSimScript :: ECCampusSimScript(){
}

void ECCampusSimScript :: EndofDay(){
    events.push_back(make_pair(-1, -1));
}
void ECCampusSimScript :: AddSimEvt(int idSender, int idReceiver){
    events.push_back(make_pair(idSender, idReceiver));
}

vector<pair<int, int>> ECCampusSimScript :: GetEvents(){
    return events;
}
//Sim

ECCampusSimulator :: ECCampusSimulator(){
}

ECCampusSimulator :: ~ECCampusSimulator(){
    vecE.clear();
}

void ECCampusSimulator :: AddSimItem(ECSimEntity* p){
    vecE.push_back(p);
    mapE[p->GetID()] = p;
}

void ECCampusSimulator :: Simulate(ECCampusSimScript &script)
{
    
    auto events = script.GetEvents();

    for (auto i: events) {        
        int sID = i.first;
        int rID = i.second;
        ECSimEntity* s = nullptr;
        ECSimEntity* r = nullptr;

        if(sID == -1) {
            for (auto i: mapE) {
                auto j = i.second;
                if(!dynamic_cast<ECSimStudent*>(j)){
                    if(!dynamic_cast<ECSimEmployee*>(j)){
                        j->Charged(j->GetBudgetForDay());
                    }
                }
            }
            continue;
        }

        for(auto i: mapE) {
            auto k = i.second;
            if (k->GetID() == sID) {
                s = k;
            }
            if (k->GetID() == rID) {
                r = k;
            }
        }

        //brute force Bad Requests (check piazza for post abt this)
        if(s == nullptr || r == nullptr || s->GetID() == r->GetID() ||((dynamic_cast<ECSimBursar*>(s) && dynamic_cast<ECSimEmployee*>(r)) || 
        (dynamic_cast<ECSimHR*>(s) && (dynamic_cast<ECSimDiningHall*>(r) || dynamic_cast<ECSimHR*>(r) ||
            dynamic_cast<ECSimRecCenter*>(r) || dynamic_cast<ECSimStudent*>(r))) ||
        (dynamic_cast<ECSimRecCenter*>(s) && (dynamic_cast<ECSimDiningHall*>(r) || dynamic_cast<ECSimHR*>(r) ||
            dynamic_cast<ECSimRecCenter*>(r) || dynamic_cast<ECSimStudent*>(r) ||
            dynamic_cast<ECSimEmployee*>(r))) ||
        (dynamic_cast<ECSimDiningHall*>(s) && (dynamic_cast<ECSimDiningHall*>(r) || dynamic_cast<ECSimHR*>(r) ||
            dynamic_cast<ECSimRecCenter*>(r) || dynamic_cast<ECSimStudent*>(r) ||
            dynamic_cast<ECSimEmployee*>(r)))))
        throw std::string("BAD REQUEST");

        //from student to bur
        if (dynamic_cast<ECSimBursar*>(r) && dynamic_cast<ECSimStudent*>(s)) {
            ECSimBursar* bur = dynamic_cast<ECSimBursar*>(r);
            s->Charged(bur->GetTuition());
            r->Paid(bur->GetTuition());
        }
        //from studetn to rec
        else if (dynamic_cast<ECSimRecCenter*>(r) && dynamic_cast<ECSimStudent*>(s)) {
            ECSimRecCenter* rec = dynamic_cast<ECSimRecCenter*>(r);
            s->Charged(rec->GetStudentCost());
            r->Paid(rec->GetStudentCost());
        }
        //from emp to rec
        else if (dynamic_cast<ECSimRecCenter*>(r) && dynamic_cast<ECSimEmployee*>(s)) {
            ECSimRecCenter* rec = dynamic_cast<ECSimRecCenter*>(r);
            s->Charged(rec->GetEmployeeCost());
            r->Paid(rec->GetEmployeeCost());
        }

        //is "r" a DiningHall object
        else if (dynamic_cast<ECSimDiningHall*>(r) && dynamic_cast<ECSimStudent*>(s)) {
            ECSimDiningHall* dining = dynamic_cast<ECSimDiningHall*>(r);
            s->Charged(dining->GetStudentCost());
            r->Paid(dining->GetStudentCost());
        }

        //from emp to dining hall
        else if (dynamic_cast<ECSimDiningHall*>(r) && dynamic_cast<ECSimEmployee*>(s)) {
            ECSimDiningHall* dining = dynamic_cast<ECSimDiningHall*>(r);
            s->Charged(dining->GetEmployeeCost());
            r->Paid(dining->GetEmployeeCost());
        }
        //to bur
        else if (dynamic_cast<ECSimBursar*>(r)){
            r->Charged(s->GetBudgetForDay());
            s->Paid(s->GetBudgetForDay());
        }
        //from student to bur
        else if (dynamic_cast<ECSimBursar*>(s) && dynamic_cast<ECSimStudent*>(r)) {
            r->Paid(1000);
            s->Charged(1000);
        }

        else if (dynamic_cast<ECSimBursar*>(s) && !dynamic_cast<ECSimLibrary*>(r)) {
            s->Paid(r->GetBalance());
            r->Charged(r->GetBalance());
        }
        
        //from student to hr
        else if (dynamic_cast<ECSimEmployee*>(s) && dynamic_cast<ECSimHR*>(r)) {
            ECSimEmployee* emp = dynamic_cast<ECSimEmployee*>(s);
            s->Paid(emp->Getpayrate());
            r->Charged(emp->Getpayrate());
        }

        //from hr to emp
        else if(dynamic_cast<ECSimHR*>(s) && dynamic_cast<ECSimEmployee*>(r)) {
            r->Paid(2000);
            s->Charged(2000);
        }
    }
}
