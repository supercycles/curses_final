
#include "Character.h"

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

Character::Character(string n)
{
	name = "";
	level = 0;
	hp = 0;
	hp_max = 0;
	xp = 0;
	xp_next = 0;
	block = 0;
	defense = 0;
	min_dmg = 0;
	max_dmg = 0;

	gold = 0;

	character = '@';

	y_max = 0;
	x_max = 0;

	y_pos = 0;
	x_pos = 0;
	cap = 6;

	rh_weapon = shared_ptr<Item>(new Item(0));
	armor = shared_ptr<Item>(new Item(1));
	lh_weapon = shared_ptr<Item>(new Item(2));

	initialize(n);
}

Character::~Character()
{

}

void Character::initialize(string n)
{
	name = n;
	level = 1;
	hp_max = 10;
	hp = hp_max;
	xp = 0;
	xp_next =
		((50 / 3) * (pow(level, 3)) -
			(6 * pow(level, 3)) +
			(17 * level) - 11);

	rh_weapon = shared_ptr<Item>(new Item(0));
	armor = shared_ptr<Item>(new Item(1));
	lh_weapon = shared_ptr<Item>(new Item(2));

	gold = 0;

	block = lh_weapon.get()->get_block();
	defense = armor.get()->get_defense();
	min_dmg = rh_weapon.get()->get_min_dmg();
	max_dmg = rh_weapon.get()->get_max_dmg();

	y_pos = 3;
	x_pos = 4;
}

void Character::level_up()
{
	while (xp >= xp_next)
	{
		PlaySound(TEXT("C:\\Users\\Ethan\\source\\repos\\cursesv2\\cursesv2\\x64\\Debug\\Music\\level_up"), NULL, SND_ASYNC);
		wclear(main_game_win);
		wrefresh(main_game_win);
		box(main_game_win, 0, 0);
		mvwprintw(main_game_win, 0, 31, "LEVEL UP");
		level++;
		hp_max += 5;
		hp = hp_max;
		xp_next =
			((50 / 3) * (pow(level, 3)) -
				(6 * pow(level, 3)) +
				(17 * level) - 11);
		mvwprintw(main_game_win, 8, 3, "> You leveled up!");
		mvwprintw(main_game_win, 10, 3, "> You are now level %d.", level);
		wrefresh(main_game_win);
		sleep_for(seconds(3));
		wclear(main_game_win);
		wrefresh(main_game_win);
	}
}

void Character::gain_xp(int x)
{
	xp += x;
}

void Character::gain_gold(int g)
{
	gold += g;
}

void Character::set_curr_attack()
{
	curr_attack = rand() % max_dmg;
	while (curr_attack < min_dmg)
		curr_attack++;
}

void Character::set_rh_weapon(shared_ptr<Item>& i)
{
	rh_weapon = i;
	min_dmg = rh_weapon.get()->get_min_dmg();
	max_dmg = rh_weapon.get()->get_max_dmg();
}

void Character::set_lh_weapon(shared_ptr<Item>& i)
{
	lh_weapon = i;
	block = lh_weapon.get()->get_block();
}

void Character::set_armor(shared_ptr<Item>& i)
{
	armor = i;
	defense = armor.get()->get_defense();
}


void Character::add_item()
{
	inventory.push_back(shared_ptr<Item>(new Item(0)));
	inventory.push_back(shared_ptr<Item>(new Item(2)));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// MOVE FUNCTIONS

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Character::set_move_win(WINDOW* w, WINDOW* mw, WINDOW* iw, WINDOW* chw, WINDOW* invw, WINDOW* menw, int y, int x, char c)
{
	map_win = w;
	main_game_win = mw,
		info_win = iw;
	character_win = chw;
	inventory_win = invw;
	game_menu_win = menw;
	combat_win = newwin(7, 30, 15, 65);
	y_pos = y;
	x_pos = x;
	character = c;
	keypad(map_win, true);
	getmaxyx(map_win, y_max, x_max);
}

void Character::move_up()
{
	mvwaddch(map_win, y_pos, x_pos, ' ');
	y_pos--;
	if (y_pos < 1)
		y_pos = 1;
}

void Character::move_down()
{
	mvwaddch(map_win, y_pos, x_pos, ' ');
	y_pos++;
	if (y_pos > y_max - 2)
		y_pos = y_max - 2;
}

void Character::move_left()
{
	mvwaddch(map_win, y_pos, x_pos, ' ');
	x_pos--;
	if (x_pos < 1)
		x_pos = 1;
}

void Character::move_right()
{
	mvwaddch(map_win, y_pos, x_pos, ' ');
	x_pos++;
	if (x_pos > x_max - 2)
		x_pos = x_max - 2;
}

int Character::get_move()
{
	noecho();
	int choice = wgetch(map_win);
	switch (choice)
	{
	case KEY_UP: move_up(); break;
	case KEY_DOWN: move_down(); break;
	case KEY_LEFT: move_left(); break;
	case KEY_RIGHT: move_right(); break;
	default: break;
	}
	box(main_game_win, 0, 0);
	mvwprintw(main_game_win, 0, 36, "MAP");
	mvwprintw(main_game_win, 19, 1, "Press 'X' to Go Back");
	mvwprintw(main_game_win, 13, 5, "@ = You");
	mvwprintw(main_game_win, 13, 26, "! = Enemy");
	box(map_win, 0, 0);
	box(info_win, 0, 0);
	mvwprintw(info_win, 0, 35, "INFO");
	mvwprintw(info_win, 1, 1, "Astre Depths");
	mvwprintw(info_win, 2, 1, "Floor: 1/4");
	wclear(combat_win);
	wrefresh(combat_win);
	wrefresh(info_win);
	wrefresh(main_game_win);
	wrefresh(map_win);
	return choice;
}

void Character::display()
{
	mvwaddch(map_win, y_pos, x_pos, character);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// PRINT FUNCTIONS

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string Character::as_string()
{
	return name + ' ' +
		to_string(level) + ' ' +
		to_string(hp) + ' ' +
		to_string(hp_max) + ' ' +
		to_string(xp) + ' ' +
		to_string(xp_next) + ' ' +
		to_string(block) + ' ' +
		to_string(defense) + ' ' +
		to_string(min_dmg) + ' ' +
		to_string(max_dmg) + ' ' +
		to_string(y_pos) + ' ' +
		to_string(x_pos) + ' ' +
		to_string(gold) + ' ';
}

string Character::inventory_as_string()
{
	string items = "";
	for (shared_ptr<Item> i : inventory)
	{
		items += (i.get()->get_equipped() + i.get()->get_id() + ' ');
	}
	return items;
}