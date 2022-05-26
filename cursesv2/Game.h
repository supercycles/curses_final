
#ifndef GAME_H
#define GAME_H

#include "Character.h"

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

	std::string filename;

	std::vector<Character> characters;
	int active_character;

	/*
	std::vector<Enemy> enemies;
	int active_enemy;
	*/
public:
	Game();
	virtual ~Game();

	//Main Menu Functions
	void generate_title_win();
	void main_menu();
	void menu_select(std::string c);

	//Save Functions
	void save_game();

	//Load Functions
	void load_game();
	void build_character(int c, std::string t, Character& l);
	void new_character();
	void load_character();

	//Game Functions
	void start_game();
	void start_move();

	//Window Functions
	void build_char_menu();
	void build_game_menu();

	//Accessors
	const bool get_playing()& { return playing; }
};

#endif /*GAME_H*/