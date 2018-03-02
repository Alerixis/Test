#include <iostream>
#include <stdlib.h>

using namespace std;

#include "Game.h"
#include "Unit.h"
#include "Balloon.h"
#include "Monkey.h"
#include "FlyingMonkey.h"
#include "Wizard.h"

//Game Constructor
Game::Game(){
  //Initialize the starting size of each Army to 20.
  int armySize = 20;
  m_armyA = new LinkedList[armySize];
  m_armyB = new LinkedList[armySize];
}

//Destructor
Game::~Game(){
  //Delete each Army since theyre dynamically allocated
  delete [] m_armyA;
  delete [] m_armyB;
}
//----------------------------------------------------------------------------
void Game::AddToArmy(int armyID, Unit *uPtr){

  //Adds a new Unit ptr to the corresponding army (1 or 2)
  if(armyID == 1){
    m_armyA->Add(uPtr);
    return;
  }
  m_armyB->Add(uPtr);
  return;
}

void Game::BuildArmies(){
  //Add 5 blocks of 4 troops to each army
  for(int i = 0; i < 19; i += 4){

    //Army 1: 4 Unit Rotation: Monkey, FlyingMonkey, Wizard, Balloon
    //Added backwards into linked list due to front loading.
    Balloon *addBalloon1 = new Balloon;
    addBalloon1->SetPlayerID(1);
    AddToArmy(1, addBalloon1);

    Wizard *addWizard1 = new Wizard;
    addWizard1->SetPlayerID(1);
    AddToArmy(1, addWizard1);

    FlyingMonkey *addFMonkey1 = new FlyingMonkey;
    addFMonkey1->SetPlayerID(1);
    AddToArmy(1, addFMonkey1);

    Monkey *addMonkey1 = new Monkey;
    addMonkey1->SetPlayerID(1);
    AddToArmy(1, addMonkey1);
    //---------------------------
    //Army 2: 4 Unit Rotation:FlyingMonkey, Wizard, Balloon, Monkey 
    Monkey *addMonkey2 = new Monkey;
    addMonkey2->SetPlayerID(2);
    AddToArmy(2, addMonkey2);

    Balloon *addBalloon2 = new Balloon;
    addBalloon2->SetPlayerID(2);
    AddToArmy(2, addBalloon2);

    Wizard *addWizard2 = new Wizard;
    addWizard2->SetPlayerID(2);
    AddToArmy(2, addWizard2);

    FlyingMonkey *addFMonkey2 = new FlyingMonkey;
    addFMonkey2->SetPlayerID(2);
    AddToArmy(2, addFMonkey2);
  }
}
//-----------------------------------------------------------------------------
void Game::PrintArmy(LinkedList* army){
  Node *current;

  current = army->m_head;
  int count = 1;

  //Step through Army list and print each unit
  while(current->m_next != NULL){
    current = current->m_next;
    cout << count << ". " << current->m_ptr->GetName() << endl;
    count++;
  }
  cout << endl;
}

void Game::FinalArmyPrint(LinkedList* army){
  Node *current;

  current = army->m_head;
  int count = 1;

  //Like previous function but adds DamageTotal and Health
  while(current->m_next != NULL){
    current = current->m_next;
    cout << count << ". " << current->m_ptr->GetName();
    cout << ", health=" << current->m_ptr->GetHealth();
    cout << ", totalDamage=" << current->m_ptr->GetDamageDone() << "\n";
    count++;
  }
  cout << endl;
}
//-------------------------------------------------------------------------

//Removes army of all dead units
void Game::RemoveDead(LinkedList* army){
  LinkedList copy;
  Node *ptr;

  //Pop each node and check if it's Unit is dead
  while ( (ptr = army->Pop() ) != NULL){

    //If so delete it to free up memory
    if( ptr->m_ptr->GetHealth() == 0) {
      delete ptr;
    }
    //Move it to the new list to be rebuilt
    else{
      copy.AddNode(ptr);
    }
  }
  //Copy the new list back to the address of army
  army->ShallowCopy(copy);
}

//Resets attack status of Armies if the full rotation
//of the longest list(s) is finished.
void Game::ResetArmies(){

  //Reset Army A Statuses
  Node *current = m_armyA->m_head;
  
  while(current->m_next != NULL){
    current = current->m_next;
    current->m_ptr->SetAtkStatus(false);
  }
  
  //Reset Army B Statuses
  current = m_armyB->m_head;

  while(current->m_next != NULL){
    current = current->m_next;
    current->m_ptr->SetAtkStatus(false);
  }
}
//----------------------------------------------------------------------------

//Find the troop with the most consecutive 1's in
// its binary representation.
Unit* Game::OutstandingTroop(LinkedList* army){

  Node *current = army->m_head;
  Unit* outstanding = NULL;
  int consec1 = 0; //Max number of consecutive 1's found

  //Traverse army
  while(current->m_next != NULL){

    current = current->m_next;
 
    int count = 0;
    int damageDealt = current->m_ptr->GetDamageDone();

    while(damageDealt != 0){
      
      //This takes the number and performs bitwise AND on itself
      //with itself shifted. This knocks off the trailing 1 on
      // any line of 1's. The number of times it does this (count)
      // is the max amount of consecutive 1's
      damageDealt = (damageDealt & (damageDealt << 1));
      count++;
    }

    //Replace max found and assign the Unit pointer
    //to be returned. Ties are given to the new found object
    //so if a result happens to have all 0's for count. There
    // will always be a unit returned.
    if(count >= consec1){
      consec1 = count;
      outstanding = current->m_ptr;
    }
  }
  return outstanding;
}
//----------------------------------------------------------------------------

//Main Game Loop for the Battle
void Game::Battle(){
  
  Node *currentA, *currentB;
  bool battling = true;
  int roundCount = 1;

  //Grab starts of each Army List
  currentA = m_armyA->m_head;
  currentB = m_armyB->m_head;

  while(battling){
    //-------------------------------------------------------------------
    //If an army has to be wrapped from tail to head, check if any dead need
    //removed. If army is still in it's rotation, no need to check yet.
    if(currentA == m_armyA->m_head){
      RemoveDead(m_armyA);
    }    
    if(currentB == m_armyB->m_head){
      RemoveDead(m_armyB);
    }
    
    //Traverse both armys and fight until one or both army lists must
    // wrap back to their head.
    while(currentA->m_next != NULL && currentB->m_next != NULL){
      
      currentA = currentA->m_next;
      currentB = currentB->m_next;

      //For ease of reference: the fighter of each army
      Unit *attackerA = currentA->m_ptr;
      Unit *attackerB = currentB->m_ptr;

      //Opening Print for Round:
      //Form:
      //Round#:Player 1 Unit (health, damage) vs Player 2 Unit (health, damage)
      cout << "\n\nRound " << roundCount << ": Player 1: ";
      cout << attackerA->GetName() << " (health=" << attackerA->GetHealth();
      cout << ", totalDamage=" << attackerA->GetDamageDone() << ") vs ";
      cout << "Player 2: " << attackerB->GetName() << " (health=";
      cout << attackerB->GetHealth() << ", totalDamage=";
      cout << attackerB->GetDamageDone() << ")\n";

      //Attack is the attacker has not attacked yet.
      if(attackerA->GetAtkStatus() == false){
	attackerA->Attack(*attackerB);
      }
      if(attackerB->GetAtkStatus() == false){
	attackerB->Attack(*attackerA);
      }
      roundCount++;
    }
    
    //If one or both lists has ended, reset their current node state
    //as well as Attack Status
    if(currentA->m_next == NULL && currentB->m_next == NULL){
      currentA = m_armyA->m_head;
      currentB = m_armyB->m_head;
      ResetArmies();
    }
    else if(currentA->m_next == NULL){
      currentA = m_armyA->m_head;
      if((m_armyA->m_size) > (m_armyB->m_size)){
	ResetArmies();
      }
    }
    else if(currentB->m_next == NULL){
      currentB = m_armyB->m_head;
      if((m_armyB->m_size) > (m_armyA->m_size)){
	ResetArmies();
      }
    }

    //Check for winner if any and find its Outstanding Troop
    if(m_armyA->m_size == 0 && m_armyB->m_size == 0){
      cout << "\nTie Battle! No Remaining Troops in either Army!\n\n";
    }

    else if(m_armyA->m_size == 0){
      cout << "\nArmy 2 is the winner! Remaining Troops:\n";
      battling = false;
      FinalArmyPrint(m_armyB);
      Unit* outstanding = OutstandingTroop(m_armyB);
      
      cout << "The Most Outstanding Troop is: \n";
      cout << outstanding->GetName() << ", health=" << outstanding->GetHealth();
      cout << ", totalDamage= " << outstanding->GetDamageDone() << "\n\n";
    }

    else if(m_armyB->m_size == 0){
      cout << "\nArmy 1 is the winner! Remaining Troops:\n";
      battling = false;
      FinalArmyPrint(m_armyA);
      Unit* outstanding = OutstandingTroop(m_armyA);
     
      cout << "The Most Outstanding Troop is: \n";
      cout << outstanding->GetName() << ", health=" << outstanding->GetHealth();
      cout << ", totalDamage=" << outstanding->GetDamageDone() << "\n\n";
    }
  }
}
