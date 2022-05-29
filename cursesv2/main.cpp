
#include "Game.h"

using namespace std;

int main()
{
	initscr();

	Game game;
	game.load_game();
	PlaySound(TEXT("C:\\Users\\Ethan\\source\\repos\\windowsmusic\\windowsmusic\\x64\\Debug\\StarWars60.wav"), NULL, SND_ASYNC);

	while (game.get_playing())
	{
		srand(time(NULL));
		game.main_menu();
	}

	game.save_game();
	endwin();
	return 0;
}