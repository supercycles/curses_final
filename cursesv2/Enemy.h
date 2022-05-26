
#ifndef ENEMY_H
#define ENEMY_H

#include "includes.h"

class Enemy
{
private:
	std::string name;
	int level;
	int hp;
	int hp_max;
	int min_dmg;
	int max_dmg;

	int curr_attack;

	int y_pos;
	int x_pos;
	char enemy;
public:
	Enemy(int l, int y, int x);
	virtual ~Enemy();

	//Functions
	void start_curr_attack();
	std::string fetch_name();

	//Accessors
	const std::string get_name() const { return name; }
	const int get_level() const { return level; }
	const int get_hp() const { return hp; }
	const int get_hp_max() const { return hp_max; }
	const int get_curr_attack() const { return curr_attack; }

	const int get_y_pos() const { return y_pos; }
	const int get_x_pos() const { return x_pos; }

	//Mutators
	void set_level(int l) { level = l; hp_max = level * 5; hp = hp_max; min_dmg = level * 1; max_dmg = level * 2; }
	void set_hp(int h) { hp = h; }

	void set_y_pos(int y) { y_pos = y; }
	void set_x_pos(int x) { x_pos = x; }
};

#endif ENEMY_H