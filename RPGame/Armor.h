#pragma once
#include "Item.h"

class Armor : public Item
{
	int m_health_ex;
	float m_dodge_rate;

public:
	Armor();
	Armor(std::string name, int health, float dodge_rate);

	~Armor();

	//	Setter
	void SetHealthEx(int health) { m_health_ex = health; };
	void SetDodgeRate(float dodge) { m_dodge_rate = dodge; };

	//	Getter
	int GetHealthEx() { return m_health_ex; };
	float GetDodgeRate() { return m_dodge_rate; };
};