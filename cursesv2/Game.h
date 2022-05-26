
#ifndef GAME_H
#define GAME_H

#include "Character.h"
#include "Enemy.h"

class Game
{
private:
	bool playing;

	WINDOW* title_win;
	WINDOW* main_menu_win;
	WINDOW* game_menu_win;
	WINDOW* character_win;
	WINDOW* inventory_win;
	WINDOW* main_game_win;
	WINDOW* map_win;
	WINDOW* info_win;
	WINDOW* combat_win;

	std::string filename;

	std::vector<Character> characters;
	int active_character;

	std::vector<std::vector<Enemy>> enemies;
	int active_enemy;

public:
	Game();
	virtual ~Game();

	//Main Menu Functions
	void generate_title_win();
	void main_menu();
	void menu_select(std::string c);

	//Save Functions
	void save_game();

	//Print Functions
	std::string enemy_as_string(std::vector<Enemy> v, int c);
	void print_enemies();

	//Load Functions
	void load_game();
	void build_character(int c, std::string t, Character& l, std::vector<Enemy>& e);
	void build_enemy(std::string t, std::vector<Enemy>& e);
	void new_character();
	void load_character();

	//Game Functions
	void start_game();
	void start_move();

	//Combat Functions
	void start_combat();
	void build_combat_window();

	//Window Functions
	void build_char_menu();
	void build_game_menu();

	//Accessors
	const bool get_playing()& { return playing; }
};

#endif /*GAME_H*/