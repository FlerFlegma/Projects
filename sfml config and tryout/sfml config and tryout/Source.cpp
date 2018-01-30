#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Game.h"

int main()
{
	srand(time(NULL));
	
	Game game;
	game.main_loop();

	return 0;
}