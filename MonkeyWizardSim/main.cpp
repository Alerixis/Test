#include <iostream>
using namespace std;

#include "Unit.h"
#include "Game.h"

int main(){

  cout << "\nMonkey Wizards Battle Royale!\n";
  Game G;

  G.BuildArmies();
  cout << "\nArmy 1 - Initial troops: \n";
  G.PrintArmy(G.m_armyA);
  
  cout << "\nArmy 2 - Initial troops: \n";
  G.PrintArmy(G.m_armyB);

  cout << "\nBATTLE!\n";
  G.Battle();
  
  return 0;
}
