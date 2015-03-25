#include "Entity/Player.h"
#include "CollisionHandler.h"
#include "Turn.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "VectorOfTurn.h"
#include "Game.h"

using namespace std;

int main()
{
	Game game;
	game.init();
	game.mainLoop();
	
	return 0;
}
