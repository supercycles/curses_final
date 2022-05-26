
#include "Game.h"

using namespace std;

Game::Game()
{
	playing = true;

	title_win = newwin(10, 100, 2, 10);
	main_menu_win = newwin(5, 16, 18, 51);
	game_menu_win = newwin(10, 20, 5, 20);
	character_win = newwin(10, 20, 15, 20);
	inventory_win = newwin(10, 20, 15, 20);
	main_game_win = newwin(20, 40, 5, 60);
	map_win = newwin(8, 30, 10, 65);
	info_win = newwin(4, 40, 1, 60);
	refresh();

	filename = "save.txt";

	active_character = 0;
}

Game::~Game()
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// MAIN MENU FUNCTIONS

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::generate_title_win()
{
	box(title_win, 0, 0);

	mvwprintw(title_win, 4, 25, "C        U        R        S        E        S (v2)");
	mvwprintw(title_win, 8, 29, "A Rogue-like Game Made By Ethan Ordorica");

	wrefresh(title_win);
}

void Game::main_menu()
{
	noecho();
	keypad(main_menu_win, true);

	generate_title_win();
	box(main_menu_win, 0, 0);

	vector<string> menu_choices = { "Load Character", "New Character", "Save & Quit" };
	int choice;
	int highlight = 0;

	mvwprintw(main_menu_win, 0, 3, "MAIN  MENU");

	while (1)
	{
		for (int i = 0; i < menu_choices.size(); i++)
		{
			if (i == highlight)
				wattron(main_menu_win, A_REVERSE);
			mvwprintw(main_menu_win, 1 + i, 1, menu_choices[i].c_str());
			wattroff(main_menu_win, A_REVERSE);
		}
		choice = wgetch(main_menu_win);
		switch (choice)
		{
		case KEY_DOWN: if (highlight < menu_choices.size() - 1) highlight++; break;
		case KEY_UP: if (highlight > 0) highlight--; break;
		}
		if (choice == 10)
		{
			wclear(main_menu_win);
			wrefresh(main_menu_win);
			menu_select(menu_choices[highlight]);
			break;
		}
	}
}

void Game::menu_select(string c)
{
	if (c == "Save & Quit") { playing = false; }
	else if (c == "Load Character") { if (characters.size() > 0) load_character(); }
	else if (c == "New Character") { if (characters.size() < 8) new_character(); }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// SAVE FUNCTIONS

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::save_game()
{
	ofstream outfile(filename);

	if (outfile.is_open())
	{
		for (Character& c : characters)
		{
			outfile << c.as_string() << endl;
		}
	}

	outfile.close();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// LOAD FUNCTIONS

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::load_game()
{
	ifstream infile(filename);
	string temp;

	while (getline(infile, temp))
	{
		int counter = 0;
		stringstream line(temp);
		string token;
		Character temp_char("");

		while (getline(line, token, ' '))
		{
			build_character(counter, token, temp_char);
			counter++;
		}
		characters.push_back(temp_char);
	}

	infile.close();
}

void Game::build_character(int c, string t, Character& l)
{
	switch (c)
	{
	case 0: l.set_name(t); break;
	case 1: l.set_level(stoi(t)); break;
	case 2: l.set_hp(stoi(t)); break;
	case 3: l.set_hp_max(stoi(t)); break;
	case 4: l.set_xp(stoi(t)); break;
	case 5: l.set_xp_next(stoi(t)); break;
	case 6: l.set_block(stoi(t)); break;
	case 7: l.set_defense(stoi(t)); break;
	case 8: l.set_min_dmg(stoi(t)); break;
	case 9: l.set_max_dmg(stoi(t)); break;
	case 10: l.set_y_pos(stoi(t)); break;
	case 11: l.set_x_pos(stoi(t)); break;
	default: break;
	}
}

void Game::new_character()
{
	echo();

	char char_name[10];
	WINDOW* char_win = newwin(3, 75, 18, 22);
	refresh();

	box(char_win, 0, 0);

	mvwprintw(char_win, 1, 1, "Enter your new character's name: ");
	generate_title_win();
	wrefresh(char_win);
	wgetnstr(char_win, char_name, 9);

	Character new_char(char_name);
	characters.push_back(new_char);
	active_character = characters.size() - 1;

	wclear(char_win);
	wrefresh(char_win);
	start_game();
}

void Game::load_character()
{
	refresh();
	noecho();

	generate_title_win();
	WINDOW* load_win = newwin(12, 12, 13, 52);
	refresh();

	if (characters.size() == 0)
	{
		wclear(load_win);
		wrefresh(load_win);
		return;
	}

	keypad(load_win, true);
	box(load_win, 0, 0);

	mvwprintw(load_win, 0, 4, "LOAD");
	int choice;
	int highlight = 0;

	while (1)
	{
		for (int i = 0; i < characters.size(); i++)
		{
			if (i == highlight)
				wattron(load_win, A_REVERSE);
			mvwprintw(load_win, 1 + i, 1, characters[i].get_name().c_str());
			wattroff(load_win, A_REVERSE);
		}

		if (highlight == characters.size())
			wattron(load_win, A_REVERSE);
		mvwprintw(load_win, 10, 1, "Go Back");
		wattroff(load_win, A_REVERSE);

		choice = wgetch(load_win);
		switch (choice)
		{
		case KEY_DOWN: if (highlight < characters.size()) highlight++; break;
		case KEY_UP: if (highlight > 0) highlight--; break;
		default: break;
		}

		if (choice == 10)
		{
			wclear(load_win);
			wrefresh(load_win);
			if (highlight == characters.size())
			{
				return;
			}
			else
			{
				active_character = highlight;
				break;
			}
		}
	}
	start_game();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// GAME FUNCTIONS

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::start_game()
{
	clear();
	refresh();

	build_char_menu();
	box(map_win, 0, 0);
	box(info_win, 0, 0);
	box(main_game_win, 0, 0);

	wrefresh(main_game_win);
	wrefresh(map_win);
	wrefresh(info_win);

	/*
	if (enemies.size() > 0)
	{
		for (int e = 0; e < enemies.size(); e++)
		{
			mvwaddch(map_win, enemies.at(e).get_y_pos(), enemies.at(e).get_x_pos(), '!');
		}
	}
	*/

	mvwprintw(info_win, 0, 35, "INFO");
	mvwprintw(info_win, 1, 1, "Astre Depths");
	mvwprintw(info_win, 2, 1, "Floor: 1/4");

	mvwaddch(map_win, characters[active_character].get_y_pos(), characters[active_character].get_x_pos(), '@');
	mvwprintw(main_game_win, 0, 36, "MAP");

	wrefresh(main_game_win);
	wrefresh(info_win);
	wrefresh(map_win);

	build_game_menu();

	wclear(game_menu_win);
	wrefresh(game_menu_win);
	wclear(character_win);
	wrefresh(character_win);
	wclear(inventory_win);
	wrefresh(inventory_win);
	wclear(main_game_win);
	wrefresh(main_game_win);
	wclear(map_win);
	wrefresh(map_win);
	wclear(info_win);
	wrefresh(info_win);
	clear();
	refresh();
}

void Game::start_move()
{
	characters[active_character].set_move_win(map_win, main_game_win, info_win, character_win, inventory_win, main_menu_win, characters[active_character].get_y_pos(), characters[active_character].get_x_pos(), '@');

	mvwprintw(main_game_win, 19, 1, "Press 'X' to Go Back");
	mvwprintw(main_game_win, 13, 5, "@ = You");
	mvwprintw(main_game_win, 13, 26, "! = Enemy");
	wrefresh(main_game_win);

	do
	{
		if (characters[active_character].get_hp() <= 0)
		{
			break;
		}
		characters[active_character].display();
		wrefresh(map_win);
	} while (characters[active_character].get_move() != 'x');

	box(main_game_win, 0, 0);
	box(map_win, 0, 0);
	mvwprintw(main_game_win, 0, 36, "MAP");
	mvwprintw(main_game_win, 13, 5, "                                 ");

	wrefresh(main_game_win);
	wrefresh(map_win);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// WINDOW FUNCTIONS

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::build_char_menu()
{
	wclear(inventory_win);
	wrefresh(inventory_win);
	box(character_win, 0, 0);
	mvwprintw(character_win, 0, 10, "CHARACTER");
	mvwprintw(character_win, 1, 1, "NAME: %s", characters[active_character].get_name().c_str());
	mvwprintw(character_win, 2, 1, "HP: %d/%d", characters[active_character].get_hp(), characters[active_character].get_hp_max());
	mvwprintw(character_win, 3, 1, "LEVEL: %d", characters[active_character].get_level());
	mvwprintw(character_win, 4, 1, "CURR XP: %d", characters[active_character].get_xp());
	mvwprintw(character_win, 5, 1, "REQ. XP: %d", characters[active_character].get_xp_next());
	mvwprintw(character_win, 6, 1, "DEF: %d", characters[active_character].get_defense());
	mvwprintw(character_win, 7, 1, "BLK: %d", characters[active_character].get_block());
	mvwprintw(character_win, 8, 1, "ATK: %d-%d", characters[active_character].get_min_dmg(), characters[active_character].get_max_dmg());
	wrefresh(character_win);
}

void Game::build_game_menu()
{
	noecho();
	box(game_menu_win, 0, 0);
	keypad(game_menu_win, true);

	mvwprintw(game_menu_win, 0, 15, "MENU");
	vector<string> menu_choices = { "Traverse Dungeon", "Inventory", "Character Sheet", "Shop" };
	int choice;
	int highlight = 0;

	while (1)
	{
		if (characters[active_character].get_hp() <= 0)
		{
			characters[active_character].initialize(characters.at(active_character).get_name());
			mvwaddch(map_win, characters[active_character].get_y_pos(), characters[active_character].get_x_pos(), '@');
			wrefresh(map_win);
			build_char_menu();
		}

		for (int i = 0; i < menu_choices.size(); i++)
		{
			if (i == highlight)
				wattron(game_menu_win, A_REVERSE);
			mvwprintw(game_menu_win, 1 + i, 1, menu_choices[i].c_str());
			wattroff(game_menu_win, A_REVERSE);
		}

		if (highlight == menu_choices.size())
			wattron(game_menu_win, A_REVERSE);
		mvwprintw(game_menu_win, 8, 1, "Back to Main Menu");
		wattroff(game_menu_win, A_REVERSE);

		choice = wgetch(game_menu_win);
		switch (choice)
		{
		case KEY_DOWN: if (highlight < menu_choices.size()) highlight++; break;
		case KEY_UP: if (highlight > 0) highlight--; break;
		default: break;
		}
		if (choice == 10)
		{
			if (highlight == menu_choices.size())
			{
				wclear(game_menu_win);
				wrefresh(game_menu_win);
				wclear(map_win);
				wrefresh(map_win);
				return;
			}
			switch (highlight)
			{
			case 0:
				start_move();
				break;
			case 1:
				//build_inv_menu();
				break;
			case 2:
				build_char_menu();
				break;
			default: break;
			}
		}
	}
}
