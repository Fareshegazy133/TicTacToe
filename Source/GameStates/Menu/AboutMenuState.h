#pragma once

#include "raylib.h"
#include "../GameStates.h"

namespace TicTacToe
{
	class AboutMenuState : public GameState
	{
	public:
		AboutMenuState();

		void OnEnter() override;
		void OnExit() override;

		void OnUpdate(float ts) override;
		void OnRender() override;

	private:
		Texture2D m_Background;
	};
}