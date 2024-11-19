#pragma once

#include "raylib.h"
#include "../GameStates.h"
#include <array>

namespace TicTacToe
{
	class ExitMenuState : public GameState
	{
	public:
		ExitMenuState();

		void OnEnter() override;
		void OnExit() override;

		void OnUpdate(float ts) override;
		void OnRender() override;

		void DrawMainMenu();

	private:
		std::array<const char*, 2> m_OIconptions = { "Yes", "No" };

		Rectangle m_YesButton = { 235, 335, 200, 50 };
		Rectangle m_NoButton = { 465, 335, 200, 50 };

		Texture2D m_Background;
	};
}