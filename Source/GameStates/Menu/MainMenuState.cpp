#include "MainMenuState.h"
#include "PlayMenuState.h"
#include "AboutMenuState.h"
#include "ExitMenuState.h"
#include "../GameStatesManager.h"

namespace TicTacToe
{
	MainMenuState::MainMenuState()
		: m_Background()
	{}

	void MainMenuState::OnEnter()
	{
		Image background = LoadImage("Assets/Background.png");
		ImageResize(&background, GetScreenWidth(), GetScreenHeight());
		m_Background = LoadTextureFromImage(background);
		UnloadImage(background);
	}

	void MainMenuState::OnExit()
	{
		UnloadTexture(m_Background);
	}

	void MainMenuState::OnUpdate(float ts)
	{
		if (CheckCollisionPointRec(GetMousePosition(), m_PlayButton) &&
			IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			TicTacToe::GameStateManager::ChangeState<PlayMenuState>();
		}

		if (CheckCollisionPointRec(GetMousePosition(), m_AboutButton) &&
			IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			TicTacToe::GameStateManager::ChangeState<AboutMenuState>();
		}

		if (CheckCollisionPointRec(GetMousePosition(), m_QuitButton) &&
			IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			TicTacToe::GameStateManager::ChangeState<ExitMenuState>();
		}
	}

	void MainMenuState::OnRender()
	{
		DrawTexture(m_Background, 0, 0, WHITE);

		DrawText("TicTacToe", 40, 25, 75, WHITE);

		DrawButtons();
	}

	void MainMenuState::DrawButtons()
	{
		if (CheckCollisionPointRec(GetMousePosition(), m_PlayButton))
		{
			DrawRectangleLinesEx(m_PlayButton, 2.0f, DARKPURPLE);
		}
		else
		{
			DrawRectangleLinesEx(m_PlayButton, 2.0f, BLUE);
		}

		DrawText(m_OIconptions[0], 160, 180, 60, LIGHTGRAY);

		if (CheckCollisionPointRec(GetMousePosition(), m_AboutButton))
		{
			DrawRectangleLinesEx(m_AboutButton, 2.0f, DARKPURPLE);
		}
		else
		{
			DrawRectangleLinesEx(m_AboutButton, 2.0f, BLUE);
		}

		DrawText(m_OIconptions[1], 140, 285, 60, LIGHTGRAY);

		if (CheckCollisionPointRec(GetMousePosition(), m_OIconptionsButton))
		{
			DrawRectangleLinesEx(m_OIconptionsButton, 2.0f, DARKPURPLE);
		}
		else
		{
			DrawRectangleLinesEx(m_OIconptionsButton, 2.0f, BLUE);
		}

		DrawText(m_OIconptions[2], 120, 380, 60, LIGHTGRAY);

		if (CheckCollisionPointRec(GetMousePosition(), m_QuitButton))
		{
			DrawRectangleLinesEx(m_QuitButton, 2.0f, DARKPURPLE);
		}
		else
		{
			DrawRectangleLinesEx(m_QuitButton, 2.0f, BLUE);
		}

		DrawText(m_OIconptions[3], 170, 485, 60, LIGHTGRAY);
	}
}