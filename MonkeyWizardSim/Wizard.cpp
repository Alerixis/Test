#include <iostream>
#include <sstream>
using namespace std;

#include "Wizard.h"

Wizard::Wizard(){
  SetName("Wizard");
  SetType("Ground");
  SetDPH(6);
  SetHealth(60);
  SetPrefTarget("All");
}
