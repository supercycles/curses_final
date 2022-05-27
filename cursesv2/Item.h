
#ifndef ITEM_H
#define ITEM_H

#include "includes.h"

class Item
{
private:
	int id;
	std::string name;
public:
	Item(int d);
	virtual ~Item();

	//Functions
	void initialize(int d);

	//Accessors
	const std::string get_name() const { return name; }
};

#endif /*ITEM_H*/