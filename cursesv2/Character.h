
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Item.h"

class Character
{
private:
	std::string name;
	int level;
	int hp;
	int hp_max;
	int xp;
	int xp_next;
	int block;
	int defense;
	int min_dmg;
	int max_dmg;
	int gold;

	char character;
	std::shared_ptr<Item> rh_weapon;
	std::shared_ptr<Item> armor;
	std::shared_ptr<Item> lh_weapon;

	int curr_attack;

	int y_max, x_max;
	int y_pos;
	int x_pos;

	std::vector<std::shared_ptr<Item>> inventory;

	WINDOW* game_menu_win;
	WINDOW* character_win;
	WINDOW* inventory_win;
	WINDOW* main_game_win;
	WINDOW* map_win;
	WINDOW* info_win;
	WINDOW* combat_win;
public:
	Character(std::string n);
	virtual ~Character();
	void initialize(std::string n);

	void level_up();
	void gain_xp(int x);
	void gain_gold(int g);

	void set_curr_attack();

	void add_item();

	//Move Functions
	void set_move_win(WINDOW* w, WINDOW* mw, WINDOW* iw, WINDOW* chw, WINDOW* invw, WINDOW* menw, int y, int x, char c);
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	int get_move();
	void display();

	//Print Functions
	std::string as_string();
	std::string inventory_as_string();

	//Accessors
	const std::string get_name() const { return name; }
	const int get_level() const { return level; }
	const int get_hp() const { return hp; }
	const int get_hp_max() const { return hp_max; }
	const int get_xp() const { return xp; }
	const int get_xp_next() const { return xp_next; }
	const int get_defense() const { return defense; }
	const int get_block() const { return block; }
	const int get_min_dmg() const { return min_dmg; }
	const int get_max_dmg() const { return max_dmg; }

	const int get_gold() const { return gold; }

	const int get_curr_attack() const { return curr_attack; }

	const int get_y_pos() const { return y_pos; }
	const int get_x_pos() const { return x_pos; }

	std::vector<std::shared_ptr<Item>>& get_inventory() { return inventory; }

	//Mutators
	void set_name(std::string n) { name = n; }
	void set_level(int l) { level = l; }
	void set_hp(int h) { hp = h; }
	void set_hp_max(int hm) { hp_max = hm; }
	void set_xp(int x) { xp = x; }
	void set_xp_next(int xn) { xp_next = xn; }
	void set_defense(int d) { defense = d; }
	void set_block(int b) { block = b; }
	void set_min_dmg(int md) { min_dmg = md; }
	void set_max_dmg(int md) { max_dmg = md; }
	
	void set_y_pos(int y) { y_pos = y; }
	void set_x_pos(int x) { x_pos = x; }
};

#endif /*CHARACTER_H*/

