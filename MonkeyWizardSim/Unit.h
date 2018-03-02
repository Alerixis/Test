#ifndef _UNIT_H_
#define _UNIT_H_

#include <string>
using namespace std;

class Unit{

 public:
  Unit(); //Unit Constructor
  ~Unit(); //Destructor

  void Attack(Unit &target);
  int TakeDamage(int damageTaken);
  
  //Setters for priv vars
  void SetName(string name);
  void SetType(string type);
  void SetDPH(int damage);
  void SetHealth(int health);
  void AddToDamageTotal(int damageDone);
  void SetPrefTarget(string pTarget);
  void SetAtkStatus(bool hasActed);
  void SetPlayerID(int ID);
  
  //Getters for priv vars
  string GetName();
  string GetType();
  int GetDPH();
  int GetHealth();
  int GetDamageDone();
  string GetPrefTarget();
  bool GetAtkStatus();
  int GetPlayerID();
  
 private:
 
  string m_name;
  string m_type;
  int m_damagePerHit;
  int m_health;
  int m_damageDone;
  string m_preferredTarget;
  bool m_hasAttacked;
  int m_playerID;
};

#endif //Guards

