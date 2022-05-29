
#include "Game.h"

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

Game::Game()
{
	playing = true;

	title_win = newwin(10, 100, 2, 10);
	main_menu_win = newwin(5, 16, 18, 52);
	game_menu_win = newwin(10, 20, 5, 20);
	character_win = newwin(10, 20, 15, 20);
	inventory_win = newwin(10, 20, 15, 20);
	shop_win = newwin(10, 20, 15, 20);
	main_game_win = newwin(20, 40, 5, 60);
	map_win = newwin(8, 30, 10, 65);
	info_win = newwin(4, 40, 1, 60);
	combat_win = newwin(7, 30, 15, 65);
	refresh();

	filename = "save.txt";

	active_character = 0;

	active_enemy = 0;
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
	mvprintw(13, 40, "                                                |>>>");
	mvprintw(14, 40, "                                                |");
	mvprintw(15, 40, "                                            _  _|_  _");
	mvprintw(16, 40, "                                           |;|_|;|_|;|");
	mvprintw(17, 42, "                                         \\\\.    .  /");
	mvprintw(18, 42, "                                          \\\\:  .  /");
	mvprintw(19, 40, "                                             ||:   |");
	mvprintw(20, 40, "                                             ||:.  |");
	mvprintw(21, 40, "                                             ||:  .|");
	mvprintw(22, 40, "                                             ||:   |       \\,/");
	mvprintw(23, 40, "                                             ||: , |            /`\\");
	mvprintw(24, 40, "                                             ||:   |");
	mvprintw(25, 40, "                                             ||: . |");
	mvprintw(26, 40, "              __                            _||_   |");
	mvprintw(27, 40, "     ____--`~    '--~~__            __ ----~    ~`---,              ___");
	mvprintw(28, 40, "-~--~                   ~---__ ,--~'                  ~~----_____-~'   `~----~~");
	mvprintw(29, 35, "_~--'");

	refresh();

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
	int counter = 0;
	int i;

	if (outfile.is_open())
	{
		for (Character c : characters)
		{
			for (i = 0; i < enemies[counter].size(); i++) {}
			outfile << c.as_string() << i << ' ' << enemy_as_string(enemies[counter], counter) << c.inventory_as_string() << endl;
			counter++;
		}
	}

	outfile.close();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// PRINT FUNCTIONS

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string Game::enemy_as_string(vector<Enemy> v, int c)
{
	string enemy_string = "";
	for (int i = 0; i < enemies.size(); i++)
	{
		if (i == c)
		{
			for (int j = 0; j < enemies[i].size(); j++)
			{
				enemy_string += (to_string(enemies[i].at(j).get_level()) + to_string(enemies[i].at(j).get_y_pos()) + to_string(enemies[i].at(j).get_x_pos()) + ' ');
			}
		}
	}

	return enemy_string;
}

void Game::print_enemies()
{
	if (enemies[active_character].size() == 0)
	{
		mvwprintw(main_game_win, 9, 3, "> Enemies Cleared!");
		wrefresh(main_game_win);
		sleep_for(seconds(2));
		mvwprintw(main_game_win, 9, 3, "                   ");
		wrefresh(main_game_win);
		Enemy e1(rand() % characters[active_character].get_level() + 1, rand() % 6 + 1, rand() % 20 + 1);
		Enemy e2(rand() % characters[active_character].get_level() + 1, rand() % 6 + 1, rand() % 20 + 1);
		Enemy e3(rand() % characters[active_character].get_level() + 1, rand() % 6 + 1, rand() % 20 + 1);
		enemies.at(active_character).push_back(e1);
		enemies.at(active_character).push_back(e2);
		enemies.at(active_character).push_back(e3);
	}

	if (enemies.size() > 0)
	{
		for (int e = 0; e < enemies.size(); e++)
		{
			if (active_character == e)
			{
				for (int j = 0; j < enemies.at(e).size(); j++)
				{
					mvwprintw(map_win, enemies[e].at(j).get_y_pos(), enemies[e].at(j).get_x_pos(), "!");
				}
			}
		}
	}
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
		vector<Enemy> temp_enemies;

		while (getline(line, token, ' '))
		{
			build_character(counter, token, line, temp_char, temp_enemies);
			counter++;
		}
		characters.push_back(temp_char);
		enemies.push_back(temp_enemies);
	}

	infile.close();
}

void Game::build_character(int& c, string t, stringstream& line, Character& l, vector<Enemy>& e)
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
	case 12: l.set_gold(stoi(t)); break;
	case 13: build_enemy(c, stoi(t), line, l, e); break;
	}
}

void Game::build_enemy(int& c, int count, stringstream& line, Character& l, vector<Enemy>& e)
{
	int counter = 0;

	for (int i = 0; i < line.str().size(); i++)
	{
		string token;
		while (getline(line, token, ' '))
		{
			
			if (counter >= count)
			{
				build_inventory(counter, token, l);
				break;
			}

			Enemy temp_enemy(0, 0, 0);
			for (int i = 0; i < token.size(); i++)
			{
				switch (i)
				{
				case 0: temp_enemy.set_level(stoi(token.substr(0, 1))); break;
				case 1: temp_enemy.set_y_pos(stoi(token.substr(1, 1))); break;
				case 2: temp_enemy.set_x_pos(stoi(token.substr(2))); break;
				}
			}
			e.push_back(temp_enemy);
			counter++;
		}
	}
	
}

void Game::build_inventory(int& c, string token, Character& l)
{
	Item temp_item;
	for (int i = 0; i < token.size(); i++)
	{
		switch (i)
		{
		case 0: temp_item.set_equipped(stoi(token.substr(0, 1))); break;
		case 1: temp_item.initialize(stoi(token.substr(1))); break;
		}
	}
	l.get_inventory().push_back(shared_ptr<Item> (new Item(temp_item.get_equipped_int(), temp_item.get_id_int())));

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

	//characters[active_character].add_item();

	vector<Enemy> char_enemies;
	enemies.push_back(char_enemies);
	Enemy e1(1, rand() % 6 + 1, rand() % 20 + 1);
	Enemy e2(1, rand() % 6 + 1, rand() % 20 + 1);
	Enemy e3(1, rand() % 6 + 1, rand() % 20 + 1);
	enemies.at(active_character).push_back(e1);
	enemies.at(active_character).push_back(e2);
	enemies.at(active_character).push_back(e3);

	wclear(char_win);
	wrefresh(char_win);
	start_game();
}

void Game::load_character()
{
	refresh();
	noecho();

	generate_title_win();
	WINDOW* load_win = newwin(12, 12, 13, 54);
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
	
	print_enemies();
	
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
		print_enemies();

		for (int i = 0; i < enemies.at(active_character).size(); i++)
		{
			if (characters[active_character].get_y_pos() == enemies[active_character].at(i).get_y_pos() && characters[active_character].get_x_pos() == enemies[active_character].at(i).get_x_pos())
			{
				active_enemy = i;
				start_combat();
			}
		}
		
		box(map_win, 0, 0);
		box(info_win, 0, 0);
		box(main_game_win, 0, 0);

		mvwprintw(info_win, 0, 35, "INFO");
		mvwprintw(info_win, 1, 1, "Astre Depths");
		mvwprintw(info_win, 2, 1, "Floor: 1/4");

		mvwprintw(main_game_win, 0, 36, "MAP");
		wrefresh(info_win);
		wrefresh(main_game_win);
		
		if (characters[active_character].get_hp() <= 0)
		{
			return;
		}

		print_enemies();

		mvwprintw(main_game_win, 19, 1, "Press 'X' to Go Back");
		mvwprintw(main_game_win, 13, 5, "@ = You");
		mvwprintw(main_game_win, 13, 26, "! = Enemy");

		characters[active_character].display();

		mvwaddch(map_win, characters[active_character].get_y_pos(), characters[active_character].get_x_pos(), '@');

		wrefresh(main_game_win);
		wrefresh(info_win);
		wrefresh(map_win);
	} while (characters[active_character].get_move() != 'x' && characters[active_character].get_hp() > 0);

	box(main_game_win, 0, 0);
	box(map_win, 0, 0);

	print_enemies();
	mvwprintw(main_game_win, 0, 36, "MAP");
	mvwprintw(main_game_win, 13, 5, "                              ");

	wrefresh(main_game_win);
	wrefresh(map_win);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// COMBAT FUNCTIONS

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::start_combat()
{
	wclear(main_game_win);
	wrefresh(main_game_win);
	wclear(map_win);
	wrefresh(map_win);
	wclear(info_win);
	wrefresh(info_win);

	box(main_game_win, 0, 0);
	box(info_win, 0, 0);
	mvwprintw(info_win, 0, 35, "INFO");
	mvwprintw(info_win, 1, 1, "Level %d %s", enemies[active_character].at(active_enemy).get_level(), enemies[active_character].at(active_enemy).get_name().c_str());
	mvwprintw(info_win, 2, 1, "HP: %d/%d", enemies[active_character].at(active_enemy).get_hp(), enemies[active_character].at(active_enemy).get_hp_max());
	mvwprintw(main_game_win, 0, 33, "COMBAT");
	mvwprintw(main_game_win, 3, 2, "> You encountered a level %d %s!", enemies[active_character].at(active_enemy).get_level(), enemies[active_character].at(active_enemy).get_name().c_str());

	wrefresh(main_game_win);
	wrefresh(info_win);
	build_combat_window();

	wclear(main_game_win);
	wrefresh(main_game_win);
	wclear(info_win);
	wrefresh(info_win);
}

void Game::build_combat_window()
{
	keypad(combat_win, true);
	box(combat_win, 0, 0);
	wrefresh(combat_win);
	noecho();

	vector<string> options = { "Attack", "Block", "Inventory", "Character Sheet", "Flee" };
	int choice;
	int highlight = 0;

	enemies[active_character].at(active_enemy).start_curr_attack();
	mvwprintw(main_game_win, 5, 2, "> %s is attacking for %d damage!", enemies[active_character].at(active_enemy).get_name().c_str(), enemies[active_character].at(active_enemy).get_curr_attack());
	mvwprintw(main_game_win, 7, 2, "> What will you do?");
	wrefresh(main_game_win);

	while (1)
	{
		if (characters[active_character].get_hp() <= 0)
		{
			wclear(combat_win);
			wrefresh(combat_win);
			break;
		}

		if (enemies[active_character].at(active_enemy).get_hp() <= 0)
		{
			enemies[active_character].erase(enemies[active_character].begin() + active_enemy);
			wclear(combat_win);
			wrefresh(map_win);
			wrefresh(combat_win);
			break;
		}

		for (int i = 0; i < options.size(); i++)
		{
			if (highlight == i)
				wattron(combat_win, A_REVERSE);
			mvwprintw(combat_win, 1 + i, 1, options[i].c_str());
			wattroff(combat_win, A_REVERSE);
		}

		choice = wgetch(combat_win);
		switch (choice)
		{
		case KEY_DOWN: if (highlight < options.size() - 1) highlight++; break;
		case KEY_UP: if (highlight > 0) highlight--; break;
		}

		if (choice == 10)
		{
			switch (highlight)
			{
			case 0: player_attack(); break;
			case 1: player_block(); if (characters[active_character].get_hp() <= 0) { return; } break;
			case 2: build_inv_menu(); break;
			case 3: build_char_menu(); break;
			case 4: characters[active_character].set_x_pos(characters[active_character].get_x_pos() - 1); return; break;
			}
			
		}
	}
}

void Game::player_attack()
{
	characters[active_character].set_curr_attack();
	enemies[active_character].at(active_enemy).set_hp(enemies[active_character].at(active_enemy).get_hp() - characters[active_character].get_curr_attack());
	mvwprintw(info_win, 2, 1, "              ");
	wrefresh(info_win);
	mvwprintw(info_win, 2, 1, "HP: %d/%d", enemies[active_character].at(active_enemy).get_hp(), enemies[active_character].at(active_enemy).get_hp_max());
	wrefresh(info_win);
	if (enemies[active_character].at(active_enemy).get_hp() <= 0)
	{
		enemy_death();
	}
	else
	{
		take_damage();
	}
}

void Game::player_block()
{
	enemies[active_character].at(active_enemy).set_curr_attack(enemies[active_character].at(active_enemy).get_curr_attack() - characters[active_character].get_block());
	take_damage();
}

void Game::take_damage()
{
	enemies[active_character].at(active_enemy).set_curr_attack(enemies[active_character].at(active_enemy).get_curr_attack() - characters[active_character].get_defense());
	characters[active_character].set_hp(characters[active_character].get_hp() - enemies[active_character].at(active_enemy).get_curr_attack());
	if (characters[active_character].get_hp() <= 0)
	{
		player_death();
		return;
	}
	build_char_menu();

	enemies[active_character].at(active_enemy).start_curr_attack();
	mvwprintw(main_game_win, 5, 2, "> %s is attacking for %d damage!", enemies[active_character].at(active_enemy).get_name().c_str(), enemies[active_character].at(active_enemy).get_curr_attack());
	mvwprintw(main_game_win, 7, 2, "> What will you do?");
	wrefresh(main_game_win);
}

void Game::player_death()
{
	clear();
	move(15, 52);
	printw("!!!YOU DIED!!!");
	refresh();
	sleep_for(seconds(3));
	move(15, 52);
	printw("                 ");
	refresh();

	wclear(combat_win);
	wrefresh(combat_win);
	wclear(main_game_win);
	wrefresh(main_game_win);
	wclear(map_win);
	wrefresh(map_win);

	build_temp_game_menu();
}


void Game::enemy_death()
{
	wclear(map_win);
	wclear(combat_win);
	wrefresh(map_win);
	wrefresh(combat_win);
	wclear(main_game_win);
	wrefresh(main_game_win);

	int gained_xp = (enemies[active_character].at(active_enemy).get_level() * enemies[active_character].at(active_enemy).get_level()) * 10;
	int gained_gold = rand() % (enemies[active_character].at(active_enemy).get_level() * 10) + 1;
	characters[active_character].gain_xp(gained_xp);
	characters[active_character].gain_gold(gained_gold);

	box(main_game_win, 0, 0);
	mvwprintw(main_game_win, 0, 33, "COMBAT");
	mvwprintw(main_game_win, 7, 3, "> You killed the %s!", enemies[active_character].at(active_enemy).get_name().c_str());
	mvwprintw(main_game_win, 9, 3, "> You gain %d XP.", gained_xp);
	mvwprintw(main_game_win, 11, 3, "> You loot %d gold.", gained_gold);
	build_char_menu();
	wrefresh(main_game_win);
	sleep_for(seconds(2));

	characters[active_character].level_up();
	build_char_menu();

	wclear(main_game_win);
	wrefresh(main_game_win);
	wclear(map_win);
	wclear(combat_win);
	wrefresh(map_win);
	wrefresh(combat_win);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// SHOP FUNCTIONS

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::shop()
{
	if (shop_items.size() < 3)
	{
		for (int i = shop_items.size(); i < 3; i++)
			generate_shop_item();
	}
}

void Game::generate_shop_item()
{
	shared_ptr<Item> item;
	item = shared_ptr<Item>(new Item(rand() % 100));
	if (item.get()->get_level() >= (characters[active_character].get_level() + 1) || item.get()->get_level() == 0)
	{
		generate_shop_item();
		return;
	}
	else
	{
		for (shared_ptr<Item> i : shop_items)
			if (i.get()->get_id() == item.get()->get_id())
			{
				generate_shop_item();
				return;
			}
	}
	shop_items.push_back(item);
}


void Game::buy_item(shared_ptr<Item>& i, int o)
{
	if (characters[active_character].get_gold() >= i.get()->get_buy_value() && characters[active_character].get_inventory().size() < characters[active_character].get_cap())
	{
		mvprintw(26, 21, "%s purchased!", i.get()->get_name().c_str());
		refresh();
		sleep_for(seconds(1));
		mvprintw(26, 21, "                        ");
		refresh();
		characters[active_character].set_gold(characters[active_character].get_gold() - i.get()->get_buy_value());
		characters[active_character].get_inventory().push_back(i);
		shop_items.erase(shop_items.begin() + o);
		shop();
	}
	else if (characters[active_character].get_inventory().size() >= characters[active_character].get_cap())
	{
		mvprintw(26, 21, "Inventory full!");
		refresh();
		sleep_for(milliseconds(600));
		mvprintw(26, 21, "                 ");
		refresh();
		shop();
	}
	else
	{
		mvprintw(26, 21, "Not enough gold!");
		refresh();
		sleep_for(milliseconds(600));
		mvprintw(26, 21, "                 ");
		refresh();
		shop();
	}
	wclear(shop_win);
	box(shop_win, 0, 0);
	mvwprintw(shop_win, 0, 15, "SHOP");
	if (characters[active_character].get_gold() >= 0 && characters[active_character].get_gold() < 10)
		mvwprintw(shop_win, 9, 12, "GOLD: %d", characters[active_character].get_gold());
	else if (characters[active_character].get_gold() >= 10 && characters[active_character].get_gold() < 100)
		mvwprintw(shop_win, 9, 11, "GOLD: %d", characters[active_character].get_gold());
	else if (characters[active_character].get_gold() >= 100 && characters[active_character].get_gold() < 1000)
		mvwprintw(shop_win, 9, 10, "GOLD: %d", characters[active_character].get_gold());
	wrefresh(shop_win);
}

void Game::shop_recycle()
{
	if (characters[active_character].get_gold() >= 15)
	{
		characters[active_character].set_gold(characters[active_character].get_gold() - 15);
		shop_items.clear();
		shop();
		wclear(shop_win);
		box(shop_win, 0, 0);
		mvwprintw(shop_win, 0, 15, "SHOP");
		if (characters[active_character].get_gold() >= 0 && characters[active_character].get_gold() < 10)
			mvwprintw(shop_win, 9, 12, "GOLD: %d", characters[active_character].get_gold());
		else if (characters[active_character].get_gold() >= 10 && characters[active_character].get_gold() < 100)
			mvwprintw(shop_win, 9, 11, "GOLD: %d", characters[active_character].get_gold());
		else if (characters[active_character].get_gold() >= 100 && characters[active_character].get_gold() < 1000)
			mvwprintw(shop_win, 9, 10, "GOLD: %d", characters[active_character].get_gold());
		wrefresh(shop_win);
	}
	else
	{
		mvprintw(26, 21, "Not enough gold!");
		refresh();
		sleep_for(milliseconds(600));
		mvprintw(26, 21, "                 ");
		refresh();
		shop();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// INVENTORY FUNCTIONS

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::use_item(shared_ptr<Item>& i, int n)
{
	if (i.get()->get_item_type() == 0)
	{
		characters[active_character].set_hp(characters[active_character].get_hp() + i.get()->get_defense());
		if (characters[active_character].get_hp() > characters[active_character].get_hp_max()) characters[active_character].set_hp(characters[active_character].get_hp_max());
		mvprintw(26, 21, "Gained %d health!", i.get()->get_defense());
		refresh();
		sleep_for(seconds(1));
		mvprintw(26, 21, "                     ");
		refresh();
		characters[active_character].get_inventory().erase(characters[active_character].get_inventory().begin() + n);
	}
	else
	{
		mvprintw(26, 21, "You can't use that item!", i.get()->get_defense());
		refresh();
		sleep_for(seconds(1));
		mvprintw(26, 21, "                          ");
		refresh();
	}
}

void Game::equip_item(shared_ptr<Item>& i)
{
	switch (i.get()->get_item_type())
	{
	case 0: 
		mvprintw(26, 21, "You can't equip that!");
		refresh();
		sleep_for(seconds(1));
		mvprintw(26, 21, "                      ");
		refresh(); 
		break;
	case 1:
		for (int j = 0; j < characters[active_character].get_inventory().size(); j++)
			if (characters[active_character].get_inventory().at(j).get()->get_item_type() == 1 && characters[active_character].get_inventory().at(j).get()->get_equipped_int() == 1)
				characters[active_character].get_inventory().at(j).get()->set_equipped(0);

		i.get()->set_equipped(1);
		characters[active_character].set_rh_weapon(i);
		mvprintw(26, 21, "Equipped %s!", i.get()->get_name().c_str());
		refresh();
		sleep_for(seconds(1));
		mvprintw(26, 21, "                              ");
		refresh();
		break;
	case 2:
		for (int j = 0; j < characters[active_character].get_inventory().size(); j++)
			if (characters[active_character].get_inventory().at(j).get()->get_item_type() == 2 && characters[active_character].get_inventory().at(j).get()->get_equipped_int() == 1)
				characters[active_character].get_inventory().at(j).get()->set_equipped(0);
		i.get()->set_equipped(1);
		characters[active_character].set_armor(i);
		mvprintw(26, 21, "Equipped %s!", i.get()->get_name().c_str());
		refresh();
		sleep_for(seconds(1));
		mvprintw(26, 21, "                              ");
		refresh();
		break;
	case 3:
		for (int j = 0; j < characters[active_character].get_inventory().size(); j++)
			if (characters[active_character].get_inventory().at(j).get()->get_item_type() == 3 && characters[active_character].get_inventory().at(j).get()->get_equipped_int() == 1)
				characters[active_character].get_inventory().at(j).get()->set_equipped(0);

		i.get()->set_equipped(1);
		characters[active_character].set_lh_weapon(i);
		mvprintw(26, 21, "Equipped %s!", i.get()->get_name().c_str());
		refresh();
		sleep_for(seconds(1));
		mvprintw(26, 21, "                              ");
		refresh();
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// WINDOW FUNCTIONS

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::build_shop_item_menu(shared_ptr<Item>& i, int o)
{
	wclear(shop_win);
	wrefresh(shop_win);
	wclear(inventory_win);
	wrefresh(inventory_win);
	wclear(character_win);
	wrefresh(character_win);
	keypad(shop_win, true);
	noecho();

	shop();

	box(shop_win, 0, 0);
	mvwprintw(shop_win, 0, 15, "SHOP");
	if (characters[active_character].get_gold() >= 0 && characters[active_character].get_gold() < 10)
		mvwprintw(shop_win, 9, 12, "GOLD: %d", characters[active_character].get_gold());
	else if (characters[active_character].get_gold() >= 10 && characters[active_character].get_gold() < 100)
		mvwprintw(shop_win, 9, 11, "GOLD: %d", characters[active_character].get_gold());
	else if (characters[active_character].get_gold() >= 100 && characters[active_character].get_gold() < 1000)
		mvwprintw(shop_win, 9, 10, "GOLD: %d", characters[active_character].get_gold());
	wrefresh(shop_win);

	vector<string> options = { "Buy Item" };
	int choice;
	int highlight = 0;

	while (1)
	{
		mvwprintw(shop_win, 2, 1, "%s", i.get()->get_name().c_str());
		if (i.get()->get_item_type() == 0)
		{
			mvwprintw(shop_win, 3, 1, "COST: %d", i.get()->get_buy_value());
			mvwprintw(shop_win, 4, 1, "LEVEL: %d", i.get()->get_level());
			mvwprintw(shop_win, 5, 1, "HEALS: %d", i.get()->get_defense());
		}
		else if (i.get()->get_item_type() == 1)
		{
			mvwprintw(shop_win, 3, 1, "COST: %d", i.get()->get_buy_value());
			mvwprintw(shop_win, 4, 1, "LEVEL: %d", i.get()->get_level());
			mvwprintw(shop_win, 5, 1, "ATK: %d-%d", i.get()->get_min_dmg(), i.get()->get_max_dmg());
		}
		else if (i.get()->get_item_type() == 2)
		{
			mvwprintw(shop_win, 3, 1, "COST: %d", i.get()->get_buy_value());
			mvwprintw(shop_win, 4, 1, "LEVEL: %d", i.get()->get_level());
			mvwprintw(shop_win, 5, 1, "DEF: %d", i.get()->get_defense());
		}
		else if (i.get()->get_item_type() == 3)
		{
			mvwprintw(shop_win, 3, 1, "COST: %d", i.get()->get_buy_value());
			mvwprintw(shop_win, 4, 1, "LEVEL: %d", i.get()->get_level());
			mvwprintw(shop_win, 5, 1, "BLK: %d", i.get()->get_block());
		}

		for (int i = 0; i < options.size(); i++)
		{
			if (i == highlight)
				wattron(shop_win, A_REVERSE);
			mvwprintw(shop_win, 7, 1, options.at(i).c_str());
			wattroff(shop_win, A_REVERSE);
		}

		if (highlight == options.size())
			wattron(shop_win, A_REVERSE);
		mvwprintw(shop_win, 8, 1, "Go Back");
		wattroff(shop_win, A_REVERSE);

		choice = wgetch(shop_win);
		switch (choice)
		{
		case KEY_DOWN: if (highlight < options.size()) highlight++; break;
		case KEY_UP: if (highlight > 0) highlight--; break;
		}
		if (choice == 10)
		{
			if (highlight == 0)
			{
				buy_item(i, o);
				mvwprintw(shop_win, 2, 1, "              ");
				mvwprintw(shop_win, 3, 1, "              ");
				mvwprintw(shop_win, 4, 1, "              ");
				mvwprintw(shop_win, 5, 1, "              ");
				mvwprintw(shop_win, 7, 1, "              ");
				break;
			}
			if (highlight == options.size())
			{
				mvwprintw(shop_win, 2, 1, "              ");
				mvwprintw(shop_win, 3, 1, "              ");
				mvwprintw(shop_win, 4, 1, "              ");
				mvwprintw(shop_win, 5, 1, "              ");
				mvwprintw(shop_win, 7, 1, "              ");
				return;
			}
		}
	}

}

void Game::build_shop_menu()
{
	wclear(shop_win);
	wrefresh(shop_win);
	wclear(inventory_win);
	wrefresh(inventory_win);
	wclear(character_win);
	wrefresh(character_win);
	keypad(shop_win, true);
	noecho();

	shop();

	box(shop_win, 0, 0);
	mvwprintw(shop_win, 0, 15, "SHOP");
	if (characters[active_character].get_gold() >= 0 && characters[active_character].get_gold() < 10) 
		mvwprintw(shop_win, 9, 12, "GOLD: %d", characters[active_character].get_gold());
	else if (characters[active_character].get_gold() >= 10 && characters[active_character].get_gold() < 100)
		mvwprintw(shop_win, 9, 11, "GOLD: %d", characters[active_character].get_gold());
	else if (characters[active_character].get_gold() >= 100 && characters[active_character].get_gold() < 1000)
		mvwprintw(shop_win, 9, 10, "GOLD: %d", characters[active_character].get_gold());
	wrefresh(shop_win);

	
	int choice;
	int highlight = 0;

	while (1)
	{
		for (int i = 0; i < shop_items.size(); i++)
		{
			if (i == highlight)
				wattron(shop_win, A_REVERSE);
			mvwprintw(shop_win, 1 + i, 1, shop_items.at(i).get()->get_name().c_str());
			wattroff(shop_win, A_REVERSE);
		}

		if (highlight == shop_items.size())
			wattron(shop_win, A_REVERSE);
		mvwprintw(shop_win, 5, 1, "Recycle Cost: 15");
		wattroff(shop_win, A_REVERSE);

		if (highlight == shop_items.size() + 1)
			wattron(shop_win, A_REVERSE);
		mvwprintw(shop_win, 8, 1, "Go Back");
		wattroff(shop_win, A_REVERSE);

		choice = wgetch(shop_win);
		switch (choice)
		{
		case KEY_DOWN: if (highlight < shop_items.size() + 1) highlight++; break;
		case KEY_UP: if (highlight > 0) highlight--; break;
		}
		if (choice == 10)
		{
			if (highlight == shop_items.size())
			{
				shop_recycle();
			}

			else if (highlight == shop_items.size() + 1)
			{
				mvwprintw(shop_win, 5, 1, "                ");
				wrefresh(shop_win);
				mvwprintw(shop_win, 8, 1, "       ");
				wrefresh(shop_win);
				break;
			}

			else
			{
				build_shop_item_menu(shop_items.at(highlight), highlight);
			}
		}
	}
	
}


void Game::build_char_menu()
{
	wclear(shop_win);
	wrefresh(shop_win);
	wclear(inventory_win);
	wrefresh(inventory_win);
	wclear(character_win);
	wrefresh(character_win);
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
	if (characters[active_character].get_gold() >= 0 && characters[active_character].get_gold() < 10)
		mvwprintw(character_win, 9, 12, "GOLD: %d", characters[active_character].get_gold());
	else if (characters[active_character].get_gold() >= 10 && characters[active_character].get_gold() < 100)
		mvwprintw(character_win, 9, 11, "GOLD: %d", characters[active_character].get_gold());
	else if (characters[active_character].get_gold() >= 100 && characters[active_character].get_gold() < 1000)
		mvwprintw(character_win, 9, 10, "GOLD: %d", characters[active_character].get_gold());
	wrefresh(character_win);
}

void Game::build_temp_game_menu()
{
	wclear(map_win);
	wrefresh(map_win);
	mvwaddch(map_win, characters[active_character].get_y_pos(), characters[active_character].get_x_pos(), '@');
	print_enemies();
	box(game_menu_win, 0, 0);
	keypad(game_menu_win, true);

	mvwprintw(game_menu_win, 0, 15, "MENU");
	vector<string> menu_choices = { "Traverse Dungeon", "Inventory", "Character Sheet", "Shop" };

	for (int i = 0; i < menu_choices.size(); i++)
	{
		mvwprintw(game_menu_win, 1 + i, 1, menu_choices[i].c_str());
	}

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
			characters[active_character].get_inventory().clear();
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

		wrefresh(game_menu_win);

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
				build_inv_menu();
				break;
			case 2:
				build_char_menu();
				break;
			case 3:
				build_shop_menu();
				break;
			default: break;
			}
		}
	}
}

void Game::build_inv_item_menu(shared_ptr<Item>& i, int n)
{
	wclear(shop_win);
	wrefresh(shop_win);
	wclear(character_win);
	wrefresh(character_win);
	wclear(inventory_win);
	wrefresh(inventory_win);
	keypad(inventory_win, true);
	noecho();

	box(inventory_win, 0, 0);
	mvwprintw(inventory_win, 0, 10, "INVENTORY");
	if (characters[active_character].get_gold() >= 0 && characters[active_character].get_gold() < 10)
		mvwprintw(inventory_win, 9, 12, "GOLD: %d", characters[active_character].get_gold());
	else if (characters[active_character].get_gold() >= 10 && characters[active_character].get_gold() < 100)
		mvwprintw(inventory_win, 9, 11, "GOLD: %d", characters[active_character].get_gold());
	else if (characters[active_character].get_gold() >= 100 && characters[active_character].get_gold() < 1000)
		mvwprintw(inventory_win, 9, 10, "GOLD: %d", characters[active_character].get_gold());
	wrefresh(inventory_win);

	vector<string> options = { "Use", "Equip", "Drop" };
	int choice;
	int highlight = 0;

	while (1)
	{
		mvwprintw(inventory_win, 1, 1, "%s", i.get()->get_name().c_str());
		if (i.get()->get_item_type() == 0)
		{
			mvwprintw(inventory_win, 2, 1, "LEVEL: %d", i.get()->get_level());
			mvwprintw(inventory_win, 3, 1, "HEALS: %d", i.get()->get_defense());
		}
		else if (i.get()->get_item_type() == 1)
		{
			mvwprintw(inventory_win, 2, 1, "LEVEL: %d", i.get()->get_level());
			mvwprintw(inventory_win, 3, 1, "ATK: %d-%d", i.get()->get_min_dmg(), i.get()->get_max_dmg());
		}
		else if (i.get()->get_item_type() == 2)
		{
			mvwprintw(inventory_win, 2, 1, "LEVEL: %d", i.get()->get_level());
			mvwprintw(inventory_win, 3, 1, "DEF: %d", i.get()->get_defense());
		}
		else if (i.get()->get_item_type() == 3)
		{
			mvwprintw(inventory_win, 2, 1, "LEVEL: %d", i.get()->get_level());
			mvwprintw(inventory_win, 3, 1, "BLK: %d", i.get()->get_block());
		}

		for (int i = 0; i < options.size(); i++)
		{
			if (i == highlight)
				wattron(inventory_win, A_REVERSE);
			mvwprintw(inventory_win, i + 5, 1, options.at(i).c_str());
			wattroff(inventory_win, A_REVERSE);
		}

		if (highlight == options.size())
			wattron(inventory_win, A_REVERSE);
		mvwprintw(inventory_win, 8, 1, "Go Back");
		wattroff(inventory_win, A_REVERSE);

		choice = wgetch(inventory_win);
		switch (choice)
		{
		case KEY_DOWN: if (highlight < options.size()) highlight++; break;
		case KEY_UP: if (highlight > 0) highlight--; break;
		}
		if (choice == 10)
		{
			mvwprintw(inventory_win, 1, 1, "              ");
			mvwprintw(inventory_win, 2, 1, "              ");
			mvwprintw(inventory_win, 3, 1, "              ");
			mvwprintw(inventory_win, 5, 1, "              ");
			mvwprintw(inventory_win, 6, 1, "              ");
			mvwprintw(inventory_win, 7, 1, "              ");
			switch (highlight)
			{
			case 0: use_item(characters[active_character].get_inventory().at(n), n); return; break;
			case 1: equip_item(characters[active_character].get_inventory().at(n)); return; break;
			case 2: break;
			}
			if (highlight == options.size())
			{
				break;
			}
			
		}
	}
}

void Game::build_inv_menu()
{
	wclear(shop_win);
	wrefresh(shop_win);
	wclear(character_win);
	wrefresh(character_win);
	wclear(inventory_win);
	wrefresh(inventory_win);
	keypad(inventory_win, true);
	noecho();

	box(inventory_win, 0, 0);
	mvwprintw(inventory_win, 0, 10, "INVENTORY");
	if (characters[active_character].get_gold() >= 0 && characters[active_character].get_gold() < 10)
		mvwprintw(inventory_win, 9, 12, "GOLD: %d", characters[active_character].get_gold());
	else if (characters[active_character].get_gold() >= 10 && characters[active_character].get_gold() < 100)
		mvwprintw(inventory_win, 9, 11, "GOLD: %d", characters[active_character].get_gold());
	else if (characters[active_character].get_gold() >= 100 && characters[active_character].get_gold() < 1000)
		mvwprintw(inventory_win, 9, 10, "GOLD: %d", characters[active_character].get_gold());
	wrefresh(inventory_win);

	if (characters[active_character].get_inventory().size() == 0)
		mvwprintw(inventory_win, 3, 5, "---EMPTY---");

	int choice;
	int highlight = 0;

	while (1)
	{
		for (int i = 0; i < characters[active_character].get_inventory().size(); i++)
		{
			if (i == highlight)
				wattron(inventory_win, A_REVERSE);
			mvwprintw(inventory_win, 1 + i, 1, characters[active_character].get_inventory().at(i).get()->get_name().c_str());
			int ty, tx;
			getyx(inventory_win, ty, tx);
			if (characters[active_character].get_inventory().at(i).get()->get_equipped_int() == 1)
			{
				mvwprintw(inventory_win, ty, tx, " (E)");
			}
			wattroff(inventory_win, A_REVERSE);
		}

		if (highlight == characters[active_character].get_inventory().size())
			wattron(inventory_win, A_REVERSE);
		mvwprintw(inventory_win, 8, 1, "Go Back");
		wattroff(inventory_win, A_REVERSE);

		choice = wgetch(inventory_win);
		switch (choice)
		{
		case KEY_DOWN: if (highlight < characters[active_character].get_inventory().size()) highlight++; break;
		case KEY_UP: if (highlight > 0) highlight--; break;
		}
		if (choice == 10)
		{
			if (highlight == characters[active_character].get_inventory().size())
			{
				mvwprintw(inventory_win, 8, 1, "       ");
				wrefresh(inventory_win);
				break;
			}
			else
			{
				build_inv_item_menu(characters[active_character].get_inventory().at(highlight), highlight);
			}
		}
	}
}
