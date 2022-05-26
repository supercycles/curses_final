
#include "Game.h"

using namespace std;

int main()
{
	initscr();

	Game game;
	game.load_game();

	while (game.get_playing())
	{
		game.main_menu();
	}

	game.save_game();
	endwin();
	return 0;
}