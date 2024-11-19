#include "PlayMenuState.h"
#include "MainMenuState.h"
#include "../GameStatesManager.h"
#include "../Gameplay/StandardGame.h"

namespace TicTacToe
{
	int PlayMenuState::m_SelectedMode = 0;
	int PlayMenuState::m_SelectedBoard = 0;
	int PlayMenuState::m_SelectedBot = 0;

	PlayMenuState::PlayMenuState()
		: m_Background()
	{}

	void PlayMenuState::OnEnter()
	{
		Image background = LoadImage("Assets/Background.png");
		ImageResize(&background, GetScreenWidth(), GetScreenHeight());
		m_Background = LoadTextureFromImage(background);
		UnloadImage(background);
	}

	void PlayMenuState::OnExit()
	{
		UnloadTexture(m_Background);
	}

	void PlayMenuState::OnUpdate(float ts)
	{
		if (!m_Animating)
		{
			if (CheckCollisionPointRec(GetMousePosition(), m_StartButton)
				&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				TicTacToe::GameStateManager::ChangeState<Standard>();
			}

			if (CheckCollisionPointRec(GetMousePosition(), m_CancelButton)
				&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				TicTacToe::GameStateManager::ChangeState<MainMenuState>();
			}
		}
	}

	void PlayMenuState::OnRender()
	{
		DrawTexture(m_Background, 0, 0, WHITE);
		DrawText("Play", 40, 25, 75, WHITE);

		ButtonFunctionality();
		DrawButtons();
		DrawTriangles();
	}

	void PlayMenuState::ButtonFunctionality()
	{
		if (!m_Animating)
		{
			if (m_SelectedBoard == 1)
			{
				if (CheckCollisionPointRec(GetMousePosition(), m_ModeButton)
					&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					m_SelectedMode = (m_SelectedMode == 0) ? 1 : 0;
				}
			}

			if (CheckCollisionPointRec(GetMousePosition(), m_BoardButton)
				&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				m_SelectedBoard = (m_SelectedBoard == 0) ? 1 : 0;
			}

			if (CheckCollisionPointRec(GetMousePosition(), m_BotButton)
				&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				if (m_SelectedBoard == 1)
				{
					m_SelectedBot = (m_SelectedBot + 1) % 3;
				}
				else
				{
					m_SelectedBot = (m_SelectedBot == 0) ? 1 : 0;
				}
			}
		}
	}

	void PlayMenuState::DrawButtons()
	{
		static int previousBoardState = m_SelectedBoard;

		auto drawButton = [](const Rectangle& button, Color hoverColor, Color normalColor)
		{
			if (CheckCollisionPointRec(GetMousePosition(), button))
			{
				DrawRectangleLinesEx(button, 2.0f, hoverColor);
			}
			else
			{
				DrawRectangleLinesEx(button, 2.0f, normalColor);
			}
		};

		drawButton(m_StartButton, DARKPURPLE, BLUE);
		drawButton(m_CancelButton, DARKPURPLE, BLUE);

		DrawText("Start", 215, 185, 30, WHITE);
		DrawText("Board", 27, m_BoardButtonY + 10, 30, WHITE);
		DrawText("Bots", 47, m_BotButtonY + 10, 30, WHITE);
		DrawText("Cancel", 210, m_CancelButtonY + 10, 30, WHITE);

		if (m_SelectedBoard == 1)
		{
			previousBoardState = m_SelectedBoard;
			DownAnimation();
		}
		else if (previousBoardState == 1 && m_SelectedBoard == 0)
		{
			SlideOutAnimation();
		}

		if (!m_Animating)
		{
			drawButton(m_ModeButton, DARKPURPLE, BLUE);
			drawButton(m_BoardButton, DARKPURPLE, BLUE);
			drawButton(m_BotButton, DARKPURPLE, BLUE);
		}
		else
		{
			DrawRectangleLinesEx(m_BoardButton, 2.0f, BLUE);
			DrawRectangleLinesEx(m_BotButton, 2.0f, BLUE);
		}
		
		int botOptionX = (m_SelectedBot == 0) ? 195 : (m_SelectedBot == 1) ? 220 : 205;

		DrawText(m_BotOptions[m_SelectedBot], botOptionX, m_BotButtonY + 10, 30, WHITE);
		DrawText(m_SelectedBoard < 1 ? m_BoardOptions[0] : m_BoardOptions[1],
			m_SelectedBoard < 1 ? 185 : 230, m_BoardButtonY + 10, 30, WHITE);
	}

	void PlayMenuState::DrawTriangles()
	{
		// Mode Button
		DrawTriangleLines(Vector2{ m_SlideX + 105, 275 },
			Vector2{ m_SlideX + 120, 265 },
			Vector2{ m_SlideX + 120, 285 }, WHITE);
		DrawTriangleLines(Vector2{ m_SlideX + 325, 275 },
			Vector2{ m_SlideX + 310, 265 },
			Vector2{ m_SlideX + 310, 285 }, WHITE);

		// Board Button
		DrawTriangleLines(Vector2{ 145, m_BoardButtonY + 25 },
			Vector2{ 160, m_BoardButtonY + 15 },
			Vector2{ 160, m_BoardButtonY + 35 }, WHITE);
		DrawTriangleLines(Vector2{ 365, m_BoardButtonY + 25 },
			Vector2{ 350, m_BoardButtonY + 15 },
			Vector2{ 350, m_BoardButtonY + 35 }, WHITE);

		// Bot Button
		DrawTriangleLines(Vector2{ 145, m_BotButtonY + 25 },
			Vector2{ 160, m_BotButtonY + 15 },
			Vector2{ 160, m_BotButtonY + 35 }, WHITE);
		DrawTriangleLines(Vector2{ 365, m_BotButtonY + 25 },
			Vector2{ 350, m_BotButtonY + 15 },
			Vector2{ 350, m_BotButtonY + 35 }, WHITE);
	}

	void PlayMenuState::DownAnimation()
	{
		m_Animating = true;

		static int initialBoardY = m_BoardButtonY;
		static int initialBotY = m_BotButtonY;
		static int initialCancelY = m_CancelButtonY;

		m_BoardButtonY += 2;
		m_BotButtonY += 2;
		m_CancelButtonY += 2;

		m_BoardButton.y = m_BoardButtonY;
		m_BotButton.y = m_BotButtonY;
		m_CancelButton.y = m_CancelButtonY;

		if (m_BoardButtonY > 325)
		{
			m_BoardButtonY = initialBoardY + 75;
			m_BotButtonY = initialBotY + 75;
			m_CancelButtonY = initialCancelY + 75;

			m_BoardButton.y = m_BoardButtonY;
			m_BotButton.y = m_BotButtonY;
			m_CancelButton.y = m_CancelButtonY;

			if (SlideInAnimation())
			{
				m_Animating = false;
			}
		}
	}

	bool PlayMenuState::SlideInAnimation()
	{
		m_SlideX += 6.0f;

		if (m_SlideX > 40) m_SlideX = 40;

		DrawText("Mode", m_SlideX, 260, 30, WHITE);
		m_ModeButton.x = m_SlideX + 90;
		DrawRectangleLinesEx(m_ModeButton, 2.0f, BLUE);

		float modeOptionsX = (m_SelectedMode < 1) ? m_SlideX + 140 : m_SlideX + 180;
		DrawText(m_ModeOptions[m_SelectedMode], modeOptionsX, 260, 30, WHITE);

		if (m_SlideX >= 40) return true;

		return false;
	}

	void PlayMenuState::SlideOutAnimation()
	{
		m_Animating = true;

		m_SlideX -= 4.0f;

		if (m_SlideX < -400.0f) m_SlideX = -400.0f;

		DrawText("Mode", m_SlideX, 260, 30, WHITE);
		m_ModeButton.x = m_SlideX + 90;
		DrawRectangleLinesEx(m_ModeButton, 2.0f, BLUE);

		float modeOptionsX = (m_SelectedMode < 1) ? m_SlideX + 140 : m_SlideX + 180;
		DrawText(m_ModeOptions[m_SelectedMode], modeOptionsX, 260, 30, WHITE);

		if (m_SlideX <= -400.0f)
		{
			if (UpAnimation()) m_Animating = false;
		}
	}

	bool PlayMenuState::UpAnimation()
	{
		static int initialBoardY = m_BoardButtonY;
		static int initialBotY = m_BotButtonY;
		static int initialCancelY = m_CancelButtonY;

		m_BoardButtonY -= 2;
		m_BotButtonY -= 2;
		m_CancelButtonY -= 2;

		m_BoardButton.y = m_BoardButtonY;
		m_BotButton.y = m_BotButtonY;
		m_CancelButton.y = m_CancelButtonY;

		if (m_BoardButtonY <= 250)
		{
			m_BoardButtonY = initialBoardY - 75;
			m_BotButtonY = initialBotY - 75;
			m_CancelButtonY = initialCancelY - 75;

			m_BoardButton.y = m_BoardButtonY;
			m_BotButton.y = m_BotButtonY;
			m_CancelButton.y = m_CancelButtonY;

			return true;
		}

		return false;
	}
}