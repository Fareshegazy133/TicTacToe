#include "Game.h"

namespace TicTacToe
{
	Game::Game()
	{
		m_StateManager = new GameStateManager();
	}

	Game::~Game()
	{
		delete m_StateManager;
		m_StateManager = nullptr;
	}

	void Game::OnUpdate(float ts)
	{
		if (m_StateManager->GetCurrentState())
		{
			m_StateManager->GetCurrentState()->OnUpdate(ts);
		}
	}

	void Game::OnRender()
	{
		if (m_StateManager->GetCurrentState())
		{
			m_StateManager->GetCurrentState()->OnRender();
		}
	}
}