#include "ECCampusSimulator.h"
#include "ECSimHuman.h"
#include "ECSimOrganization.h"
#include <iostream>
#include <string> 

using namespace std;

template<class T>
void ASSERT_EQ(T x, T y)
{
  if( x == y )
  {
    cout << "Test passed: equal: " << x << "  " << y << endl;
  }
  else
  {
    cout << "Test FAILED: equal: " << x << "  " << y << endl;
  }
}

// setup campus entities
// IDs 
const int BURSAR = 1;
const int REC = 2;
const int DINING = 3;
const int HR = 4;
const int LIBRARY = 5;
const int E1 = 11;
const int E2 = 12;
const int S1 = 101;
const int S2 = 102;
const int S3 = 103;
const int S4 = 104;

// dolloar amounts
const int TUITION = 10000;
const int SALARY = 5000;	// employee salary
const int REC_EXP = 500;	// Rec center daily expenses
const int DINING_EXP = 200;	// Dining hall daily expenses
const int LIB_EXP = 100;	// Library daily expenses
const int MISC_EXP_STUDENT = 1000;  // Misc expense of student
const int MEAL_COST = 5;
const int REC_COST_STUDENT = 10;
const int HR_BLOCK_FUND = 10000;

void Test1()
{
  cout << "*** Test1\n";
  // Bursar and two students: two students enroll
  ECCampusSimulator sim;
  // Bursar, two students
  ECSimBursar b(BURSAR);
  b.SetTuition(TUITION);
  sim.AddSimItem( &b );
  ECSimStudent s1(S1);
  s1.Paid( TUITION + MISC_EXP_STUDENT );
  sim.AddSimItem( &s1 );
  ECSimStudent s2(S2);
  s2.Paid( TUITION + MISC_EXP_STUDENT );
  sim.AddSimItem( &s2 );

  ECCampusSimScript script;
  script.AddSimEvt(S1, BURSAR);  
  script.AddSimEvt(S2, BURSAR);
  sim.Simulate(script);
  // S1 and S2 only have misc-exp left after enrolling; bursar got tuition dollars
  ASSERT_EQ( s1.GetBalance(), MISC_EXP_STUDENT);  
  ASSERT_EQ( s2.GetBalance(), MISC_EXP_STUDENT);  
  ASSERT_EQ( b.GetBalance(), 2*TUITION);  
}

void Test2()
{
  cout << "*** Test2\n";
  // Bursar, dining hall, rec-center library and two students
  ECCampusSimulator sim;
  // Bursar, two students
  ECSimBursar b(BURSAR);
  b.SetTuition(TUITION);
  sim.AddSimItem( &b );

  // dining hall
  ECSimDiningHall din(DINING);
  din.SetBudgetForDay(DINING_EXP);
  sim.AddSimItem( &din );

  // rec center
  ECSimRecCenter rec(REC);
  rec.SetBudgetForDay(REC_EXP);
  sim.AddSimItem( &rec );

  // library
  ECSimLibrary lib(LIBRARY);
  lib.SetBudgetForDay(LIB_EXP);
  sim.AddSimItem( &lib );

  // two students
  ECSimStudent s1(S1);
  s1.Paid( TUITION + MISC_EXP_STUDENT );
  sim.AddSimItem( &s1 );
  ECSimStudent s2(S2);
  s2.Paid( TUITION + MISC_EXP_STUDENT );
  sim.AddSimItem( &s2 );

  ECCampusSimScript script;
  // two students enroll
  script.AddSimEvt(S1, BURSAR);  
  script.AddSimEvt(S2, BURSAR);

  // Bursar provides budget to Dining and rec center
  // Note: bursar is the receiver since you are asking for money!
  script.AddSimEvt(DINING, BURSAR);
  script.AddSimEvt(REC, BURSAR);

  // S1 use library
  script.AddSimEvt(S1, LIBRARY);
  // S1 use rec center
  script.AddSimEvt(S1, REC);
  // S2 use dining
  script.AddSimEvt(S2, DINING);

  try
  {
    sim.Simulate(script);
  }
  catch( std::string ex )
  {
    cout << "WARNING: simulation aborted with message: " << ex << endl;
  }
  // S1 and S2 only have misc-exp left after enrolling; bursar got tuition dollars
  ASSERT_EQ( s1.GetBalance(), MISC_EXP_STUDENT-REC_COST_STUDENT);  
  ASSERT_EQ( s2.GetBalance(), MISC_EXP_STUDENT-MEAL_COST);  
  ASSERT_EQ( b.GetBalance(), 2*TUITION-DINING_EXP-REC_EXP);
  ASSERT_EQ( din.GetBalance(), DINING_EXP + MEAL_COST );
  ASSERT_EQ( rec.GetBalance(), REC_COST_STUDENT + REC_EXP );
  ASSERT_EQ( lib.GetBalance(), 0);  // library didn't receive budget, so remain at 0  
}

// Same campus setting, with end-of-day  
void Test3()
{
  cout << "*** Test3\n";
  // Bursar, dining hall, rec-center library and two students
  ECCampusSimulator sim;
  // Bursar, two students
  ECSimBursar b(BURSAR);
  b.SetTuition(TUITION);
  sim.AddSimItem( &b );

  // dining hall
  ECSimDiningHall din(DINING);
  din.SetBudgetForDay(DINING_EXP);
  sim.AddSimItem( &din );

  // rec center
  ECSimRecCenter rec(REC);
  rec.SetBudgetForDay(REC_EXP);
  sim.AddSimItem( &rec );

  // library
  ECSimLibrary lib(LIBRARY);
  lib.SetBudgetForDay(LIB_EXP);
  sim.AddSimItem( &lib );

  // two students
  ECSimStudent s1(S1);
  s1.Paid( TUITION + MISC_EXP_STUDENT );
  sim.AddSimItem( &s1 );
  ECSimStudent s2(S2);
  s2.Paid( TUITION + MISC_EXP_STUDENT );
  sim.AddSimItem( &s2 );

  ECCampusSimScript script;
  
  // ------ DAY ONE
  // two students enroll
  script.AddSimEvt(S1, BURSAR);  
  script.AddSimEvt(S2, BURSAR);
  // Bursar provides budget to Dining and rec center
  // Note: bursar is the receiver since you are asking for money!
  script.AddSimEvt(DINING, BURSAR);
  script.AddSimEvt(REC, BURSAR);
  // S1 use library
  script.AddSimEvt(S1, LIBRARY);
  // S1 use rec center
  script.AddSimEvt(S1, REC);
  // S2 use dining
  script.AddSimEvt(S2, DINING);
  // Library has no budget, so it will abort!
  script.EndofDay();

  try
  {
    sim.Simulate(script);
    ASSERT_EQ( 0, 1);
  }
  catch( std::string ex )
  {
    cout << "WARNING: simulation aborted with message: " << ex << endl;
    ASSERT_EQ( ex, string("BANKRUPT") );
  }
}

// Same campus setting, library provided with fund, two days schedule 
void Test4()
{
  cout << "*** Test4\n";
  // Bursar, dining hall, rec-center library and two students
  ECCampusSimulator sim;
  // Bursar, two students
  ECSimBursar b(BURSAR);
  b.SetTuition(TUITION);
  sim.AddSimItem( &b );

  // dining hall
  ECSimDiningHall din(DINING);
  din.SetBudgetForDay(DINING_EXP);
  sim.AddSimItem( &din );

  // rec center
  ECSimRecCenter rec(REC);
  rec.SetBudgetForDay(REC_EXP);
  sim.AddSimItem( &rec );

  // library
  ECSimLibrary lib(LIBRARY);
  lib.SetBudgetForDay(LIB_EXP);
  sim.AddSimItem( &lib );

  // two students
  ECSimStudent s1(S1);
  s1.Paid( TUITION + MISC_EXP_STUDENT );
  sim.AddSimItem( &s1 );
  ECSimStudent s2(S2);
  s2.Paid( TUITION + MISC_EXP_STUDENT );
  sim.AddSimItem( &s2 );

  ECCampusSimScript script;
  
  // ------ DAY ONE
  // two students enroll
  script.AddSimEvt(S1, BURSAR);  
  script.AddSimEvt(S2, BURSAR);
  // Bursar provides budget to Dining and rec center
  // Note: bursar is the receiver since you are asking for money!
  script.AddSimEvt(DINING, BURSAR);
  script.AddSimEvt(REC, BURSAR);
  script.AddSimEvt(LIBRARY, BURSAR);
  // S1 use library
  script.AddSimEvt(S1, LIBRARY);
  // S1 use rec center
  script.AddSimEvt(S1, REC);
  // S2 use dining
  script.AddSimEvt(S2, DINING);
  // Library has no budget, so it will abort!
  script.EndofDay();

  // ------ DAY TWO
  // S1 use dining
  script.AddSimEvt(S1, DINING);
  // S2 use library
  script.AddSimEvt(S2, LIBRARY);
  // Dining passes revenue back to Bursar. Note: bursar asks for money so it is the sender of this request
  script.AddSimEvt(BURSAR, DINING);

  try
  {
    sim.Simulate(script);
    
    ASSERT_EQ( s1.GetBalance(), MISC_EXP_STUDENT-REC_COST_STUDENT-MEAL_COST);  
    ASSERT_EQ( s2.GetBalance(), MISC_EXP_STUDENT-MEAL_COST);  
    ASSERT_EQ( b.GetBalance(), 2*TUITION-DINING_EXP-REC_EXP-LIB_EXP+2*MEAL_COST);
    // Note: daily budget deducted at the end of day
    ASSERT_EQ( din.GetBalance(), 0 );
    ASSERT_EQ( rec.GetBalance(), REC_COST_STUDENT );
    ASSERT_EQ( lib.GetBalance(), 0);  // library didn't receive budget, so remain at 0  
  }
  catch( std::string ex )
  {
    cout << "WARNING: simulation aborted with message: " << ex << endl;
    ASSERT_EQ( ex, string("BANKRUPT? NO!") );
  }
}

void Test5()
{
  cout << "*** Test5\n";
  // Bursar, two students, HR, one employee 
  ECCampusSimulator sim;
  // Bursar, two students
  ECSimBursar b(BURSAR);
  b.SetTuition(TUITION);
  sim.AddSimItem( &b );
  ECSimStudent s1(S1);
  s1.Paid( TUITION + MISC_EXP_STUDENT );
  sim.AddSimItem( &s1 );
  ECSimStudent s2(S2);
  s2.Paid( TUITION + MISC_EXP_STUDENT );
  sim.AddSimItem( &s2 );
  // HR budget: 
  ECSimHR h(HR);
  h.SetBudgetForDay(HR_BLOCK_FUND);
  sim.AddSimItem(&h);
  // One employee
  ECSimEmployee e(E1);
  e.SetPayrate(SALARY);
  sim.AddSimItem(&e);

  ECCampusSimScript script;
  script.AddSimEvt(S1, BURSAR);  
  script.AddSimEvt(S2, BURSAR);
  // HR requests fund (assume to be fixed amount, $10,000)
  script.AddSimEvt(HR, BURSAR);
  // Employee needs to be paid
  script.AddSimEvt(E1, HR);
  sim.Simulate(script);
  // S1 and S2 only have misc-exp left after enrolling; bursar got tuition dollars
  ASSERT_EQ( s1.GetBalance(), MISC_EXP_STUDENT);  
  ASSERT_EQ( s2.GetBalance(), MISC_EXP_STUDENT);  
  ASSERT_EQ( b.GetBalance(), 2*TUITION-HR_BLOCK_FUND);
  ASSERT_EQ( h.GetBalance(), HR_BLOCK_FUND-SALARY);
  ASSERT_EQ( e.GetBalance(), SALARY);  
}

int main()
{
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
}

