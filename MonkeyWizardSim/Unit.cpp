#include <iostream>
#include <string>
using namespace std;

#include "Unit.h"

//Base Unit Constructor
Unit::Unit(){
  m_damageDone = 0;
  m_hasAttacked = false;
}

//Destructor
Unit::~Unit(){
}
//--------------------------------------------------

void Unit::Attack(Unit &target){

  //No attack if the target is already dead.
  //Though this should never happen. Worth a check.
  if(target.GetHealth() <= 0){
    return;
  }
  
  else{

    //Mark Unit as having attacked
    m_hasAttacked = true;
    int damageDealt = GetDPH();

    //Ignore target type check for Wizard or added classes with no
    //target preference
    if(GetPrefTarget() != "All"){

      //Check if the target is not of the unit's preferred attack type
      if(target.GetType() != GetPrefTarget()){
	damageDealt = damageDealt / 2; //Damage is halved if this is true
      }
    }

    //If the target has less health than incoming damage.
    //Only hit for the HP the target has left
    if(target.GetHealth() < damageDealt){
      damageDealt = target.GetHealth();
    }

    //Throw the attack and add damage done to Unit's total
    AddToDamageTotal(target.TakeDamage(damageDealt));

    //Printing output of attacks and possible kills
    cout << "Player " << GetPlayerID() << "'s ";
    cout << GetName() << " hits Player " << target.GetPlayerID();
    cout << "'s " << target.GetName() << " for ";
    cout << damageDealt << "HP\n";

    //If the target was killed print an extra message
    if(target.GetHealth() == 0){
      cout << "Player " << GetPlayerID() << "'s " << GetName();
      cout << " has killed Player " << target.GetPlayerID() << "'s ";
      cout << target.GetName() << "\n";
    }
  }
}

int Unit::TakeDamage(int damageTaken){

  //Check if health is lower than incoming attack
  //if so, only take damage to 0
  int currentHealth = GetHealth();

  //Take the health off and set it to save
  currentHealth -= damageTaken;
  SetHealth(currentHealth);
  
  //Return the damage done to the attacker
  return damageTaken;
}


//------------------------------------------------------------------
//Setter Functions for Private Vars of Unit Characters
void Unit::SetName(string name){
  m_name = name;
}
void Unit::SetType(string type){
  m_type = type;
}
void Unit::SetDPH(int damage){
  m_damagePerHit = damage;
}
void Unit::SetHealth(int health){
  m_health = health;
}
void Unit::AddToDamageTotal(int damageDone){
  m_damageDone += damageDone;
}
void Unit::SetPrefTarget(string pTarget){
  m_preferredTarget = pTarget;
}
void Unit::SetAtkStatus(bool hasActed){
  m_hasAttacked = hasActed;
}
void Unit::SetPlayerID(int ID){
  m_playerID = ID;
}
//Getter Functions for Private Variables of Unit Characters
string Unit::GetName(){
  return m_name;
}
string Unit::GetType(){
  return m_type;
}
int Unit::GetDPH(){
  return m_damagePerHit;
}
int Unit::GetHealth(){
  return m_health;
}
int Unit::GetDamageDone(){
  return m_damageDone;
}
string Unit::GetPrefTarget(){
  return m_preferredTarget;
}
bool Unit::GetAtkStatus(){
  return m_hasAttacked;
}
int Unit::GetPlayerID(){
  return m_playerID;
}
