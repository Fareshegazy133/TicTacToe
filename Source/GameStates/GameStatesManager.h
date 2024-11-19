#pragma once

#include "GameStates.h"
#include <utility>

namespace TicTacToe
{
	class GameStateManager
	{
	public:
		GameStateManager();
		~GameStateManager();

		template<typename T>
		static void ChangeState()
		{
			if (s_Instance->m_CurrentState)
			{
				s_Instance->m_CurrentState->OnExit();
			}

			delete s_Instance->m_CurrentState;

			GameState* newState = new T();
			s_Instance->m_CurrentState = newState;

			if (s_Instance->m_CurrentState)
			{
				s_Instance->m_CurrentState->OnEnter();
			}
		}

		GameState* GetCurrentState() const;

	private:
		GameState* m_CurrentState;
		static GameStateManager* s_Instance;

		int m_CurrentMode;
		int m_CurrentBoard;
		int m_CurrentBot;
	};
}