#pragma once
#include "Weapon.h"
#include "Armor.h"

class Character {
protected:
	std::string m_name;
	int m_health;
	Weapon m_weapon;
	Armor m_armor;

public:
	Character();
	Character(std::string name, int health, Weapon weapon, Armor armor);
	Character(std::string name, Weapon weapon, Armor armor);

	virtual ~Character();

	//	Setters
	void SetName(std::string name) { m_name = name; };
	void SetHealth(int health) { m_health = health; };
	void SetWeapon(Weapon weapon) { m_weapon = weapon; };
	void SetArmor(Armor armor);

	//	Getters
	std::string GetName() { return m_name; };
	int GetHealth() { return m_health; };
	Weapon GetWeapon() { return m_weapon; };
	Armor GetArmor(Armor armor) { return m_armor; };

	//	Member functions
	void GetStatus();
	int ChooseWeapon(bool choice);
	int ChooseArmor(bool choice);
};