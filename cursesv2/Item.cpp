
#include "Item.h"

using namespace std;

Item::Item()
{
	id = 0;
	equipped = 0;
	name = "";

	level = 0;
	item_type = 0;
	buy_value = 0;
	block = 0;
	defense = 0;
	min_dmg = 0;
	max_dmg = 0;
}

Item::Item(int d)
{
	id = 0;
	equipped = 0;
	name = "";

	level = 0;
	item_type = 0;
	buy_value = 0;
	block = 0;
	defense = 0;
	min_dmg = 0;
	max_dmg = 0;
	initialize(d);
}

Item::Item(int e, int d)
{
	equipped = e;
	id = d;
	name = "";

	level = 0;
	item_type = 0;
	buy_value = 0;
	block = 0;
	defense = 0;
	min_dmg = 0;
	max_dmg = 0;
	initialize(id);
}

Item::~Item()
{

}

//Functions

void Item::initialize(int d)
{
	switch (d)
	{
	case 0: id = 0; name = "Fists"; level = 0; item_type = 1; buy_value = 0; block = 0; defense = 0; min_dmg = 3; max_dmg = 6; break;
	case 1: id = 1; name = "No Armor"; level = 0; item_type = 2; buy_value = 0; block = 0; defense = 0; min_dmg = 0; max_dmg = 0; break;
	case 2: id = 2; name = "No Shield"; level = 0; item_type = 3; buy_value = 0; block = 0; defense = 0; min_dmg = 0; max_dmg = 0; break;
	case 10: id = 10; name = "Rusty Sword"; level = 1; item_type = 1; buy_value = 5; block = 0; defense = 0; min_dmg = 0; max_dmg = 0; break;
	case 11: id = 11; name = "Thief Clothes"; level = 1; item_type = 2; buy_value = 20; block = 0; defense = 2; min_dmg = 0; max_dmg = 0; break;
	case 12: id = 12; name = "Plank Shield"; level = 1; item_type = 3; buy_value = 10; block = 3; defense = 0; min_dmg = 0; max_dmg = 0; break;
	default: break;
	}
}

string Item::get_as_string()
{
	if (item_type == 1)
	{
		return " LVL:" + std::to_string(level) +
			" MIN:" + std::to_string(min_dmg) +
			" MAX:" + std::to_string(max_dmg);
	}
	if (item_type == 2)
	{
		return " LVL:" + std::to_string(level) +
			" DEF:" + std::to_string(defense);
	}
	if (item_type == 3)
	{
		return " LVL:" + std::to_string(level) +
			" BLK:" + std::to_string(defense);
	}
}