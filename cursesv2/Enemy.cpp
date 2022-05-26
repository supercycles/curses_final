
#include "Enemy.h"

using namespace std;

Enemy::Enemy(int l, int y, int x)
{
	name = fetch_name();
	level = l;
	hp_max = level * 5;
	hp = hp_max;

	min_dmg = level * 1;
	max_dmg = level * 2;

	curr_attack = 0;

	y_pos = y;
	x_pos = x;
	enemy = '!';
}

Enemy::~Enemy()
{

}

void Enemy::start_curr_attack()
{
	curr_attack = rand() % max_dmg + 1;
	if (curr_attack < min_dmg)
		curr_attack++;
}

string Enemy::fetch_name()
{
	int num = rand() % 100;
	if (num < 40) name = "Slime";
	else if (num >= 40 && num < 70) name = "Imp";
	else if (num >= 70 && num < 80) name = "Golem";
	else if (num >= 80 && num < 90) name = "Gryphon";
	else name = "Dragon";

	return name;
}