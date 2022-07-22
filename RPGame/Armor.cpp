#include "Armor.h"

//	Constructor
Armor::Armor()
	: Item("None")
	, m_health_ex(0)
	, m_dodge_rate(0.0f)
{

}

Armor::Armor(std::string name, int health, float dodge_rate)
	: Item(name)
	, m_health_ex(health)
	, m_dodge_rate(dodge_rate)
{

}

//	Destructor
Armor::~Armor()
{

}