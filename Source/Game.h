#pragma once

#include "GameStates/GameStatesManager.h"

namespace TicTacToe
{
	class Game
	{
	public:
		Game();
		~Game();

		void OnUpdate(float ts);
		void OnRender();

	private:
		GameStateManager* m_StateManager = nullptr;
	};
}