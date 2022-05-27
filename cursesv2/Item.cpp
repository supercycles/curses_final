
#include "Item.h"

using namespace std;

Item::Item()
{
	id = 0;
	equipped = 0;
	name = "";
}

Item::Item(int d)
{
	id = 0;
	equipped = 0;
	name = "";
	initialize(d);
}

Item::Item(int e, int d)
{
	equipped = e;
	id = d;
	name = "";
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
	case 0: id = 0; name = "Rusty Sword"; break;
	case 1: id = 1; name = "Broadsword"; break;
	case 2: id = 2; name = "Greatsword"; break;
	}
}