
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
	case 3: id = 3; name = "Bread"; level = 1; item_type = 0; buy_value = 3; block = 0; defense = 3; min_dmg = 0; max_dmg = 0; break;
	case 4: id = 4; name = "Porkchop"; level = 1; item_type = 0; buy_value = 5; block = 0; defense = 5; min_dmg = 0; max_dmg = 0; break;
	case 5: id = 5; name = "Salmon"; level = 3; item_type = 0; buy_value = 15; block = 0; defense = 8; min_dmg = 0; max_dmg = 0; break;
	case 6: id = 6; name = "Turkey Leg"; level = 5; item_type = 0; buy_value = 40; block = 0; defense = 12; min_dmg = 0; max_dmg = 0; break;
	case 7: id = 7; name = "Mutton"; level = 8; item_type = 0; buy_value = 100; block = 0; defense = 18; min_dmg = 0; max_dmg = 0; break;
	case 10: id = 10; name = "Rusty Sword"; level = 1; item_type = 1; buy_value = 5; block = 0; defense = 0; min_dmg = 5; max_dmg = 8; break;
	case 11: id = 11; name = "Cloth Armor"; level = 1; item_type = 2; buy_value = 20; block = 0; defense = 2; min_dmg = 0; max_dmg = 0; break;
	case 12: id = 12; name = "Plank Shield"; level = 1; item_type = 3; buy_value = 10; block = 3; defense = 0; min_dmg = 0; max_dmg = 0; break;
	case 13: id = 13; name = "Flail"; level = 3; item_type = 1; buy_value = 25; block = 0; defense = 0; min_dmg = 9; max_dmg = 13; break;
	case 14: id = 14; name = "Chain Armor"; level = 3; item_type = 2; buy_value = 50; block = 0; defense = 4; min_dmg = 0; max_dmg = 0; break;
	case 15: id = 15; name = "Buckler"; level = 3; item_type = 3; buy_value = 25; block = 5; defense = 0; min_dmg = 0; max_dmg = 0; break;
	case 16: id = 16; name = "Scimitar"; level = 5; item_type = 1; buy_value = 75; block = 0; defense = 0; min_dmg = 15; max_dmg = 20; break;
	case 17: id = 17; name = "Plate Armor"; level = 5; item_type = 2; buy_value = 125; block = 0; defense = 7; min_dmg = 0; max_dmg = 0; break;
	case 18: id = 18; name = "Tower Shield"; level = 5; item_type = 3; buy_value = 100; block = 8; defense = 0; min_dmg = 0; max_dmg = 0; break;
	case 19: id = 19; name = "Sledgehammer"; level = 8; item_type = 1; buy_value = 200; block = 0; defense = 0; min_dmg = 22; max_dmg = 28; break;
	case 20: id = 20; name = "Dragon Armor"; level = 8; item_type = 2; buy_value = 325; block = 0; defense = 12; min_dmg = 0; max_dmg = 0; break;
	case 21: id = 21; name = "Greatshield"; level = 8; item_type = 3; buy_value = 250; block = 15; defense = 0; min_dmg = 0; max_dmg = 0; break;
	case 99: id = 99; name = "Godsword"; level = 10; item_type = 1; buy_value = 1000; block = 0; defense = 0; min_dmg = 50; max_dmg = 80; break;
	default: break;
	}
}
