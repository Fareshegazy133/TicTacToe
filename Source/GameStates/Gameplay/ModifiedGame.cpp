#include "ModifiedGame.h"
#include <string>
#include <climits>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace TicTacToe
{
	Modified::Modified()
		: m_Board(9, std::vector<char>(9, ' ')), m_GameDone(false), m_Background(),
		m_XIcon(), m_OIcon(), m_YIcon(), m_XIconSmall(), m_OIconSmall(), m_YIconSmall(),
		m_XScore(0), m_OScore(0), m_YScore(), m_Turn('X'), m_Reset(false)
	{}

	void Modified::OnEnter()
	{
		Image background = LoadImage("Assets/Background.png");
		ImageResize(&background, GetScreenWidth(), GetScreenHeight());
		m_Background = LoadTextureFromImage(background);
		UnloadImage(background);

		Image X = LoadImage("Assets/X.png");
		ImageResize(&X, 120, 120);
		m_XIcon = LoadTextureFromImage(X);

		Image O = LoadImage("Assets/O.png");
		ImageResize(&O, 120, 120);
		m_OIcon = LoadTextureFromImage(O);

		if (PlayMenuState::m_SelectedBoard == 1)
		{
			ImageResize(&X, 40, 40);
			ImageResize(&O, 40, 40);

			m_XIconSmall = LoadTextureFromImage(X);
			m_OIconSmall = LoadTextureFromImage(O);
		}

		UnloadImage(X);
		UnloadImage(O);

		if (PlayMenuState::m_SelectedMode == 1)
		{
			Image Y = LoadImage("Assets/Y.png");
			ImageResize(&Y, 120, 120);
			m_YIcon = LoadTextureFromImage(Y);

			if (PlayMenuState::m_SelectedBoard == 1)
			{
				ImageResize(&Y, 40, 40);

				m_YIconSmall = LoadTextureFromImage(Y);
			}

			UnloadImage(Y);
		}
	}

	void Modified::OnExit()
	{
		UnloadTexture(m_Background);
		UnloadTexture(m_XIcon);
		UnloadTexture(m_OIcon);
		UnloadTexture(m_YIcon);
	}

	void Modified::OnUpdate(float ts)
	{

	}

	void Modified::OnRender()
	{
		DrawTexture(m_Background, 0, 0, WHITE);
		DrawUI();

		if (m_XScore == 1)
		{
			DrawText("Player X  Won!", 175, 200, 75, WHITE);
			DrawText(":", 440, 260, 150, WHITE);
			DrawTexture(m_XIcon, 300, 275, WHITE);
			DrawTexture(m_OIcon, 475, 275, WHITE);
		}
		else if (m_OScore == 1)
		{
			DrawText("Player O  Won!", 175, 200, 75, WHITE);
			DrawText(":", 440, 260, 150, WHITE);
			DrawTexture(m_OIcon, 300, 275, WHITE);
			DrawTexture(m_XIcon, 475, 275, WHITE);
		}
		else
		{
			DrawBoard();
			Run();
		}
	}

	void Modified::DrawBoard()
	{
		DrawHover();

		DrawRectangleRounded(Rectangle{ 370, 140, 10, 420 }, 1.0f, 140, DARKBLUE);
		DrawRectangleRounded(Rectangle{ 520, 140, 10, 420 }, 1.0f, 140, DARKBLUE);
		DrawRectangleRounded(Rectangle{ 240, 270, 420, 10 }, 1.0f, 140, DARKBLUE);
		DrawRectangleRounded(Rectangle{ 240, 420, 420, 10 }, 1.0f, 140, DARKBLUE);

		if (PlayMenuState::m_SelectedBoard == 1)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					DrawRectangleRounded(Rectangle{ 270.0f + (j * 150),
						140.0f + (i * 150), 10, 120 }, 1.0f, 120, PURPLE);
					DrawRectangleRounded(Rectangle{ 320.0f + (j * 150),
						140.0f + (i * 150), 10, 120 }, 1.0f, 120, PURPLE);
					DrawRectangleRounded(Rectangle{ 240.0f + (j * 150),
						170.0f + (i * 150), 120, 10 }, 1.0f, 120, PURPLE);
					DrawRectangleRounded(Rectangle{ 240.0f + (j * 150),
						220.0f + (i * 150), 120, 10 }, 1.0f, 120, PURPLE);
				}
			}
		}
	}

	void Modified::DrawHover()
	{
		if (PlayMenuState::m_SelectedBoard == 0 && !m_GameDone)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (CheckCollisionPointRec(GetMousePosition(),
						Rectangle{ 240.0f + (j * 140),
							140.0f + (i * 140), 140, 140 }) && m_Board[i][j] == ' ')
					{
						DrawRectangleRounded(Rectangle{ 240.0f + (j * 140),
							140.0f + (i * 140), 140, 140 }, 0.1f, 1, BLUE);
					}
				}
			}
		}
		else if (PlayMenuState::m_SelectedBoard == 1 && !m_GameDone)
		{
			for (int largeRow = 0; largeRow < 3; largeRow++)
			{
				for (int largeCol = 0; largeCol < 3; largeCol++)
				{
					int boardX = 240 + largeCol * 140;
					int boardY = 140 + largeRow * 140;

					for (int smallRow = 0; smallRow < 3; smallRow++)
					{
						for (int smallCol = 0; smallCol < 3; smallCol++)
						{
							int cellX = boardX + (smallCol * 40) + (largeCol * 10);
							int cellY = boardY + (smallRow * 40) + (largeRow * 10);

							Rectangle cell = { (float)cellX, (float)cellY, 40, 40 };

							if (CheckCollisionPointRec(GetMousePosition(), cell))
							{
								DrawRectangleRounded(cell, 0.1f, 1, BLUE);
							}
						}
					}
				}
			}
		}
	}

	void Modified::DrawUI()
	{
		DrawRectangleRounded(Rectangle{ 150, -200, 600, 300 }, 0.3f, 120, DARKPURPLE);
		DrawTexture(m_XIcon, 200, -10, WHITE);
		DrawTexture(m_OIcon, 580, -10, WHITE);

		std::string XScoreStr = std::to_string(m_XScore);
		std::string OScoreStr = std::to_string(m_OScore);

		const char* XScore = XScoreStr.c_str();
		const char* OScore = OScoreStr.c_str();

		DrawText(XScore, 315, 70, 30, WHITE);
		DrawText(OScore, 695, 70, 30, WHITE);

		if (PlayMenuState::m_SelectedMode == 1)
		{
			std::string YScoreStr = std::to_string(m_YScore);
			const char* YScore = YScoreStr.c_str();
			DrawText(YScore, 505, 70, 30, WHITE);
		}

		if (!m_GameDone)
		{
			DrawText("Player Turn:", 25, 250, 25, WHITE);

			if (m_Turn == 'X')
			{
				DrawTexture(m_XIcon, 50, 270, WHITE);
			}
			else if (m_Turn == 'O')
			{
				DrawTexture(m_OIcon, 50, 270, WHITE);
			}
			else
			{
				DrawTexture(m_YIcon, 50, 270, WHITE);
			}
		}
	}

	void Modified::Run()
	{
		static int waitTime = -1;
		waitTime++;

		static bool scoreUpdated = false;

		bool validMove = false;

		if (waitTime >= 1)
		{
			waitTime = 1;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					Rectangle cell =
						Rectangle{ 240.0f + (j * 140), 140.0f + (i * 140), 140, 140 };

					if (CheckCollisionPointRec(GetMousePosition(), cell) &&
						IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !m_GameDone)
					{
						if (m_Turn == 'X' && m_Board[i][j] == ' ')
						{
							m_Board[i][j] = 'X';
							validMove = true;
						}
						else if (m_Turn == 'O' && m_Board[i][j] == ' ')
						{
							m_Board[i][j] = 'O';
							validMove = true;
						}
					}
				}
			}

			if (validMove)
			{
				CheckOutcome();

				m_Turn = (m_Turn == 'X') ? 'O' : 'X';

				if (PlayMenuState::m_SelectedBot == 1)
				{
					BotTurn();
				}
			}

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (m_Board[i][j] == 'X' && !m_GameDone)
					{
						DrawTexture(m_XIcon, 250.0f + (j * 140), 150.0f + (i * 140), WHITE);
					}
					else if (m_Board[i][j] == 'O' && !m_GameDone)
					{
						DrawTexture(m_OIcon, 250.0f + (j * 140), 150.0f + (i * 140), WHITE);
					}
				}
			}

			if (m_GameDone)
			{
				if (!scoreUpdated)
				{
					if (m_Turn == 'X')
					{
						m_OScore++;
					}
					else
					{
						m_XScore++;
					}

					scoreUpdated = true;
				}

				ResetAnimation();
			}
			else
			{
				scoreUpdated = false;
			}
		}
	}

	void Modified::CheckOutcome()
	{
		for (int row = 0; row < 3; row++)
		{
			if (m_Board[row][0] == m_Turn && m_Board[row][1] == m_Turn &&
				m_Board[row][2] == m_Turn)
			{
				m_WinStart = { 240.0f, 210.0f + (row * 140) };
				m_WinEnd = { 660.0f, 210.0f + (row * 140) };
				m_GameDone = true;
			}
		}

		for (int col = 0; col < 3; col++)
		{
			if (m_Board[0][col] == m_Turn && m_Board[1][col] == m_Turn &&
				m_Board[2][col] == m_Turn)
			{
				m_WinStart = { 310.0f + (col * 140), 140.0f };
				m_WinEnd = { 310.0f + (col * 140), 560.0f };
				m_GameDone = true;
			}
		}

		if (m_Board[0][0] == m_Turn && m_Board[1][1] == m_Turn && m_Board[2][2] == m_Turn)
		{
			m_WinStart = { 240.0f, 140.0f };
			m_WinEnd = { 660.0f, 560.0f };
			m_GameDone = true;
		}

		if (m_Board[0][2] == m_Turn && m_Board[1][1] == m_Turn && m_Board[2][0] == m_Turn)
		{
			m_WinStart = { 660.0f, 140.0f };
			m_WinEnd = { 240.0f, 560.0f };
			m_GameDone = true;
		}
	}

	void Modified::BotTurn()
	{

	}

	void Modified::ResetAnimation()
	{
		if (m_Turn == 'X')
		{
			if (m_Reset)
			{
				m_DelayTime = 0.0f;
				m_ElapsedTime = 0.0f;
				LineAnimation();
			}
			else
			{
				DrawLineEx(m_WinStart, m_WinEnd, 10, BLUE);
			}
		}
		else if (m_Turn == 'O')
		{
			if (m_Reset)
			{
				m_DelayTime = 0.0f;
				m_ElapsedTime = 0.0f;
				LineAnimation();
			}
			else
			{
				DrawLineEx(m_WinStart, m_WinEnd, 10, Color{ 255, 0, 0, 255 });
			}
		}

		const float animationDelay = 0.5f;
		const float animationDuration = 2.0f;
		const float startY = 150.0f;
		const float endY = 1100.0f;

		m_DelayTime += 0.008f;

		if (m_DelayTime < animationDelay)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (m_Board[i][j] == 'X')
					{
						DrawTexture(m_XIcon, 250.0f + (j * 140), startY + (i * 140), WHITE);
					}
					else if (m_Board[i][j] == 'O')
					{
						DrawTexture(m_OIcon, 250.0f + (j * 140), startY + (i * 140), WHITE);
					}
				}
			}
		}

		if (m_DelayTime >= animationDelay)
		{
			m_ElapsedTime += 0.008f;

			if (m_ElapsedTime > animationDuration)
			{
				m_ElapsedTime = animationDuration;
			}

			float t = m_ElapsedTime / animationDuration;
			float bounce = sin(2 * M_PI * t) * (0.5f - t);
			float textureY = startY + (endY - startY) * (t - bounce);

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (m_Board[i][j] == 'X')
					{
						DrawTexture(m_XIcon, 250.0f + (j * 140), textureY + (i * 140), WHITE);
					}
					else if (m_Board[i][j] == 'O')
					{
						DrawTexture(m_OIcon, 250.0f + (j * 140), textureY + (i * 140), WHITE);
					}
				}
			}
		}

		if (m_ElapsedTime >= animationDuration)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					m_Board[i][j] = ' ';
				}
			}

			m_Reset = true;
		}
	}

	void Modified::LineAnimation()
	{
		static float alpha = 255.0f;
		const float fadeSpeed = 2.0f;

		Color lineColor;

		if (m_Turn == 'X')
		{
			lineColor = { 0, 121, 241, static_cast<unsigned char>(alpha) };
		}
		else
		{
			lineColor = { 255, 0, 0, static_cast<unsigned char>(alpha) };
		}

		DrawLineEx(m_WinStart, m_WinEnd, 10, lineColor);

		if (alpha > 0.0f)
		{
			alpha -= fadeSpeed;

			if (alpha < 0.0f)
			{
				alpha = 255.0f;
				m_GameDone = false;
				m_Reset = false;
			}
		}
	}
}