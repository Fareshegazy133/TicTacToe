#pragma once

#include "raylib.h"
#include "../GameStates.h"
#include <array>

namespace TicTacToe
{
	class MainMenuState : public GameState
	{
	public:
		MainMenuState();

		void OnEnter() override;
		void OnExit() override;

		void OnUpdate(float ts) override;
		void OnRender() override;

		void DrawButtons();

	private:
		std::array<const char*, 4> m_OIconptions = { "Play", "About", "Options", "Quit" };

		Rectangle m_PlayButton = { 50, 175, 350, 75 };
		Rectangle m_AboutButton = { 50, 275, 350, 75 };
		Rectangle m_OIconptionsButton = { 50, 375, 350, 75 };
		Rectangle m_QuitButton = { 50, 475, 350, 75 };

		Texture2D m_Background;
	};
}