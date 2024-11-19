#include "raylib.h"
#include "Application.h"

using namespace TicTacToe;

int main()
{
	Application* game = new Application();

	game->Run();

	delete game;
	game = nullptr;
}