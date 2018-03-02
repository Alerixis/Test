#ifndef _GAME_H_
#define _GAME_H_

using namespace std;

class Unit;
#include "linked.h"


class Game {

 public:
  Game();
  ~Game();

  void BuildArmies();
  void PrintArmy(LinkedList* army);
  void FinalArmyPrint(LinkedList* army);
  void Battle();
  void ResetArmies();
  void RemoveDead(LinkedList* army);
  Unit* OutstandingTroop(LinkedList* army);
  
  void AddToArmy(int armyID, Unit *uPtr);
  
  LinkedList *m_armyA;
  LinkedList *m_armyB;

};
#endif
