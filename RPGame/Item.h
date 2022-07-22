#pragma once

#include <string>

class Item
{
protected:
	std::string m_name;

public:
	Item();
	Item(std::string name);

	~Item();

	//	Setter
	void SetItemName(std::string name) { m_name = name; };

	//	Getter
	std::string GetItemName() { return m_name; };
};