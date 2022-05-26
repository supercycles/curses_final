
#include "Game.h"

using namespace std;

int main()
{
	initscr();

	Game game;

	while (game.get_playing())
	{
		game.main_menu();
	}

	endwin();
	return 0;
}