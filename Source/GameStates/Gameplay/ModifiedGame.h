#pragma once

#include "raylib.h"

#include "../GameStates.h"
#include "../Menu/PlayMenuState.h"
#include <vector>

namespace TicTacToe
{
	class Modified : public GameState
	{
	public:
		Modified();

		void OnEnter() override;
		void OnExit() override;

		void OnUpdate(float ts) override;
		void OnRender() override;

		void DrawBoard();
		void DrawHover();
		void DrawUI();

		void Run();
		void CheckOutcome();

		void BotTurn();
		void ResetAnimation();
		void LineAnimation();

	private:
		std::vector<std::vector<char>> m_Board;

		Texture2D m_XIcon;
		Texture2D m_OIcon;
		Texture2D m_YIcon;

		Texture2D m_XIconSmall;
		Texture2D m_OIconSmall;
		Texture2D m_YIconSmall;

		int m_XScore;
		int m_OScore;
		int m_YScore;

		char m_Turn;

		bool m_GameDone;

		Vector2 m_WinStart = { 0, 0 };
		Vector2 m_WinEnd = { 0, 0 };

		bool m_Reset;
		float m_ElapsedTime = 0.0f;
		float m_DelayTime = 0.0f;

		Texture2D m_Background;
	};
}