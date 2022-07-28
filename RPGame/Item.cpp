#include "Item.h"

//	Constructor
Item::Item()
	: m_name("Item")
	, m_type(ItemType::Item)
{

}

Item::Item(std::string name, ItemType type)
	: m_name(name)
	, m_type(type)
{

}

//	Destructor
Item::~Item()
{

}