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
	void SetItemName(std::string const name) { m_name = name; };

	//	Getter
	std::string GetItemName() const { return m_name; };
};