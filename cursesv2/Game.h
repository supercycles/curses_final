
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
	WINDOW* shop_win;
	WINDOW* main_game_win;
	WINDOW* map_win;
	WINDOW* info_win;
	WINDOW* combat_win;

	std::string filename;

	std::vector<std::shared_ptr<Item>> shop_items;

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
	void build_character(int& c, std::string t, std::stringstream& line, Character& l, std::vector<Enemy>& e);
	void build_enemy(int& c, int count, std::stringstream& line, Character& l, std::vector<Enemy>& e);
	void build_inventory(int& c, std::string token, Character& l);
	void new_character();
	void play_intro();
	void load_character();

	//Game Functions
	void start_game();
	void play_random_music();
	void start_move();

	//Combat Functions
	void start_combat();
	void build_combat_window();
	void player_attack();
	void player_block();
	void take_damage();
	void player_death();
	void enemy_death();

	//Shop Functions
	void shop();
	void generate_shop_item();
	void buy_item(std::shared_ptr<Item>& i, int o);
	void shop_recycle();

	//Inventory Functions
	void use_item(std::shared_ptr<Item>& i, int n);
	void equip_item(std::shared_ptr<Item>& i);

	//Window Functions
	void build_shop_item_menu(std::shared_ptr<Item>& i, int o);
	void build_shop_menu();
	void build_char_menu();
	void build_temp_game_menu();
	void build_game_menu();
	void build_inv_item_menu(std::shared_ptr<Item>& i, int n);
	void build_inv_menu();

	//Accessors
	const bool get_playing()& { return playing; }
};

#endif /*GAME_H*/