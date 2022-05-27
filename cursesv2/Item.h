
#ifndef ITEM_H
#define ITEM_H

#include "includes.h"

class Item
{
private:
	int id;
	int equipped;
	std::string name;
public:
	Item();
	Item(int d);
	Item(int e, int d);
	virtual ~Item();

	//Functions
	void initialize(int d);

	//Accessors
	const std::string get_name() const { return name; }
	const std::string get_id() const { return std::to_string(id); }
	const std::string get_equipped() const { return std::to_string(equipped); }
	const int get_equipped_int() const { return equipped; }
	const int get_id_int() const { return id; }

	//Mutators
	void set_equipped(int e) { equipped = e; }
};

#endif /*ITEM_H*/