#include <iostream>
#include <sstream>
using namespace std;

#include "Balloon.h"

Balloon::Balloon(){
  SetName("Balloon");
  SetType("Air");
  SetDPH(8);
  SetHealth(55);
  SetPrefTarget("Ground");
}
