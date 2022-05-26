
#include "Character.h"

using namespace std;

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

	character = '@';

	y_max = 0;
	x_max = 0;

	y_pos = 0;
	x_pos = 0;

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
	block = 0;
	defense = 0;
	min_dmg = 3;
	max_dmg = 6;

	y_pos = 3;
	x_pos = 4;
}

void Character::set_curr_attack()
{
	curr_attack = rand() % max_dmg;
	while (curr_attack < min_dmg)
		curr_attack++;
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
		to_string(x_pos) + ' ';
}