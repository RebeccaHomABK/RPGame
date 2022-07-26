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
	void SetName(std::string const name) { m_name = name; };
	void SetHealth(int const health) { m_health = health; };
	void SetWeapon(Weapon const weapon) { m_weapon = weapon; };
	void SetArmor(Armor armor);

	//	Getters
	std::string GetName() const { return m_name; };
	int GetHealth() const { return m_health; };
	Weapon GetWeapon() const { return m_weapon; };
	Armor GetArmor() const { return m_armor; };

	//	Member functions
	void GetStatus();
	int ChooseWeapon(bool choice);
	int ChooseArmor(bool choice);
};