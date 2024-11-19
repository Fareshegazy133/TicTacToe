#pragma once

#include "raylib.h"
#include "../GameStates.h"
#include <array>
#include <memory>
#include <functional>

namespace TicTacToe
{
	class InitGameState;

	class PlayMenuState : public GameState
	{
	public:
		PlayMenuState();

		void OnEnter() override;
		void OnExit() override;

		void OnUpdate(float ts) override;
		void OnRender() override;

		void ButtonFunctionality();
		void DrawButtons();
		void DrawTriangles();
		
		void DownAnimation();
		bool SlideInAnimation();
		void SlideOutAnimation();
		bool UpAnimation();

	private:
		std::array<const char*, 2> m_ModeOptions = { "Standard", "1v1v1" };
		std::array<const char*, 2> m_BoardOptions = { "Standard", "9x9" };
		std::array<const char*, 3> m_BotOptions = { "No Bots", "1 Bot", "2 Bots" };

		float m_BoardButtonY = 250;
		float m_BotButtonY = 325;
		float m_CancelButtonY = 400;

		bool m_Animating = false;
		float m_SlideX = -400.0f;

		Rectangle m_StartButton = { 130, 175, 250, 50 };
		Rectangle m_ModeButton = { 130, 250, 250, 50 };
		Rectangle m_BoardButton = { 130, m_BoardButtonY, 250, 50 };
		Rectangle m_BotButton = { 130, m_BotButtonY, 250, 50 };
		Rectangle m_CancelButton = { 130, m_CancelButtonY, 250, 50 };

		Texture2D m_Background;

	public:
		static int m_SelectedMode;
		static int m_SelectedBoard;
		static int m_SelectedBot;
	};
}