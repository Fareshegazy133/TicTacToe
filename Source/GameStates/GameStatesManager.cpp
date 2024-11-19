#include "GameStatesManager.h"
#include "Menu/MainMenuState.h"

namespace TicTacToe
{
	GameStateManager* GameStateManager::s_Instance = nullptr;

	GameStateManager::GameStateManager()
		: m_CurrentState(nullptr), m_CurrentMode(0), m_CurrentBoard(0), m_CurrentBot(0)
	{
		if (s_Instance == nullptr)
		{
			s_Instance = this;
		}

		s_Instance->m_CurrentState = new MainMenuState();
		s_Instance->m_CurrentState->OnEnter();
	}

	GameStateManager::~GameStateManager()
	{
		delete s_Instance->m_CurrentState;
		s_Instance->m_CurrentState = nullptr;
	}

	GameState* GameStateManager::GetCurrentState() const
	{
		return s_Instance->m_CurrentState;
	}
}