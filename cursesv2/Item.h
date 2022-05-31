
#ifndef ITEM_H
#define ITEM_H

#include "includes.h"

class Item
{
private:
	int id;
	int equipped;
	std::string name;

	int level;
	int item_type;
	int buy_value;
	int block;
	int defense;
	int min_dmg;
	int max_dmg;
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

	const int& get_level() const { return level; }
	const int& get_buy_value() const { return buy_value; }
	const int& get_block() const { return block; }

	const int& get_item_type() const { return item_type; }
	const int& get_min_dmg() const { return min_dmg; }
	const int& get_max_dmg() const { return max_dmg; }
	const int& get_defense() const { return defense; }

	//Mutators
	void set_equipped(int e) { equipped = e; }
};

#endif /*ITEM_H*/