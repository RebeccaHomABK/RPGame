#pragma once

#include <string>

enum class ItemType
{
	Item,
	Weapon,
	Armor
};

class Item
{
protected:
	std::string m_name;
	ItemType m_type;

public:
	Item();
	Item(std::string name, ItemType type = ItemType::Item);

	virtual ~Item();

	//	Setter
	void SetItemName(std::string const name) { m_name = name; }

	//	Getter
	std::string GetItemName() const { return m_name; }
	ItemType GetItemType() const { return m_type; }
};