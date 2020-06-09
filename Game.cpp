#include"head.h"
#include"Mino1.h"
#include"Mino2.h"
#include"Game.h"
void Game::Run()
{
	Mino1 player1;
	player1.Random();
	Mino2 player2;
	player2.Random();
	while (1)
	{
		player1.Down();
		player2.Down();
	}
}