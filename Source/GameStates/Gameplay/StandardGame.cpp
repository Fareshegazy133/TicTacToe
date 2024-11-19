#include "StandardGame.h"
#include <string>
#include <climits>
#include <cstdlib>
#include <ctime>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace TicTacToe
{
	Standard::Standard()
		: m_Board(3, std::vector<char>(3, ' ')), m_GameDone(false), m_Background(),
		m_XIcon(), m_OIcon(), m_XScore(0), m_OScore(0), m_Turn('X'), m_Reset(false),
		m_FullBoard(false)
	{}

	void Standard::OnEnter()
	{
		Image background = LoadImage("Assets/Background.png");
		ImageResize(&background, GetScreenWidth(), GetScreenHeight());
		m_Background = LoadTextureFromImage(background);
		UnloadImage(background);

		Image X = LoadImage("Assets/X.png");
		ImageResize(&X, 120, 120);
		m_XIcon = LoadTextureFromImage(X);
		UnloadImage(X);

		Image O = LoadImage("Assets/O.png");
		ImageResize(&O, 120, 120);
		m_OIcon = LoadTextureFromImage(O);
		UnloadImage(O);
	}

	void Standard::OnExit()
	{
		UnloadTexture(m_Background);
		UnloadTexture(m_XIcon);
		UnloadTexture(m_OIcon);
	}

	void Standard::OnUpdate(float ts)
	{}

	void Standard::OnRender()
	{
		DrawTexture(m_Background, 0, 0, WHITE);
		DrawUI();

		if (m_XScore == 10 && m_GameDone)
		{
			DrawText("Player X  Won!", 175, 200, 75, WHITE);
			DrawText(":", 440, 260, 150, WHITE);
			DrawTexture(m_XIcon, 300, 275, WHITE);
			DrawTexture(m_OIcon, 475, 275, WHITE);
		}
		else if (m_OScore == 10 && m_GameDone)
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

	void Standard::DrawBoard()
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
						140.0f + (i * 150), 10, 120}, 1.0f, 120, PURPLE);
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

	void Standard::DrawHover()
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

	void Standard::DrawUI()
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

		if (!m_GameDone)
		{
			DrawText("Player Turn:", 25, 250, 25, WHITE);

			if (m_Turn == 'X') DrawTexture(m_XIcon, 50, 270, WHITE);
			else DrawTexture(m_OIcon, 50, 270, WHITE);
		}
	}

	void Standard::Run()
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

				if (PlayMenuState::m_SelectedBot == 0 && !m_GameDone)
				{
					m_Turn = (m_Turn == 'X') ? 'O' : 'X';
				}

				if (PlayMenuState::m_SelectedBot == 1 && !m_GameDone)
				{
					BotTurn();
					m_Turn = (CheckOutcome() == 'X') ? 'O' : 'X';
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
					if (m_Turn == 'X' && m_WinStart.x != 0.0f) m_XScore++;
					else if (m_Turn == 'O' && m_WinStart.x != 0.0f) m_OScore++;

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

	void Standard::BotTurn()
	{
		static bool seedInitialized = false;
		
		if (!seedInitialized)
		{
			srand(static_cast<unsigned>(time(nullptr)));
			seedInitialized = true;
		}

		auto checkAndMove = [&](char target, int r1, int c1, int r2, int c2, int r3, int c3)
		{
			if (m_Board[r1][c1] == ' ' && m_Board[r2][c2] == target &&
				m_Board[r3][c3] == target)
			{
				m_Board[r1][c1] = 'O';
				return true;
			}
			if (m_Board[r2][c2] == ' ' && m_Board[r1][c1] == target &&
				m_Board[r3][c3] == target)
			{
				m_Board[r2][c2] = 'O';
				return true;
			}
			if (m_Board[r3][c3] == ' ' && m_Board[r1][c1] == target &&
				m_Board[r2][c2] == target)
			{
				m_Board[r3][c3] = 'O';
				return true;
			}

			return false;
		};

		for (int i = 0; i < 3; i++)
		{
			if (checkAndMove('O', i, 0, i, 1, i, 2)) return;
			if (checkAndMove('O', 0, i, 1, i, 2, i)) return;
		}

		if (checkAndMove('O', 0, 0, 1, 1, 2, 2)) return;
		if (checkAndMove('O', 0, 2, 1, 1, 2, 0)) return;

		for (int i = 0; i < 3; i++)
		{
			if (checkAndMove('X', i, 0, i, 1, i, 2)) return;
			if (checkAndMove('X', 0, i, 1, i, 2, i)) return;
		}

		if (checkAndMove('X', 0, 0, 1, 1, 2, 2)) return;
		if (checkAndMove('X', 0, 2, 1, 1, 2, 0)) return;

		std::vector<std::pair<int, int>> freeSlots;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (m_Board[i][j] == ' ') freeSlots.push_back({ i, j });
			}
		}

		if (!freeSlots.empty())
		{
			int randomIndex = rand() % freeSlots.size();

			int row = freeSlots[randomIndex].first;
			int col = freeSlots[randomIndex].second;

			m_Board[row][col] = 'O';
		}
	}

	char Standard::CheckOutcome()
	{
		for (int row = 0; row < 3; row++)
		{
			if ((m_Board[row][0] == 'X' && m_Board[row][1] == 'X' &&
				m_Board[row][2] == 'X') || (m_Board[row][0] == 'O' &&
					m_Board[row][1] == 'O' && m_Board[row][2] == 'O'))
			{
				m_WinStart = { 240.0f, 210.0f + (row * 140) };
				m_WinEnd = { 660.0f, 210.0f + (row * 140) };
				m_GameDone = true;

				if (m_Board[row][0] == 'X') return 'O';
				else return 'X';
			}
		}

		for (int col = 0; col < 3; col++)
		{
			if ((m_Board[0][col] == 'X' && m_Board[1][col] == 'X' &&
				m_Board[2][col] == 'X') || (m_Board[0][col] == 'O' &&
					m_Board[1][col] == 'O' && m_Board[2][col] == 'O'))
			{
				m_WinStart = { 310.0f + (col * 140), 140.0f };
				m_WinEnd = { 310.0f + (col * 140), 560.0f };
				m_GameDone = true;

				if (m_Board[0][col] == 'X') return 'O';
				else return 'X';
			}
		}

		if ((m_Board[0][0] == 'X' && m_Board[1][1] == 'X' && m_Board[2][2] == 'X') ||
			(m_Board[0][0] == 'O' && m_Board[1][1] == 'O' && m_Board[2][2] == 'O'))
		{
			m_WinStart = { 240.0f, 140.0f };
			m_WinEnd = { 660.0f, 560.0f };
			m_GameDone = true;

			if (m_Board[0][0] == 'X') return 'O';
			else return 'X';
		}

		if ((m_Board[0][2] == 'X' && m_Board[1][1] == 'X' && m_Board[2][0] == 'X') ||
			(m_Board[0][2] == 'O' && m_Board[1][1] == 'O' && m_Board[2][0] == 'O'))
		{
			m_WinStart = { 660.0f, 140.0f };
			m_WinEnd = { 240.0f, 560.0f };
			m_GameDone = true;

			if (m_Board[0][2] == 'X') return 'O';
			else return 'X';
		}

		if (!m_GameDone)
		{
			m_FullBoard = true;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (m_Board[i][j] == ' ') m_FullBoard = false;
				}
			}

			if (m_FullBoard)
			{
				m_WinStart = { 0, 0 };
				m_WinEnd = { 0, 0 };
				m_GameDone = true;
			}
		}
	}

	void Standard::ResetAnimation()
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
				DrawLineEx(m_WinStart, m_WinEnd, 10, RED);
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
				DrawLineEx(m_WinStart, m_WinEnd, 10, BLUE);
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
			double bounce = sin(2 * M_PI * t) * (0.5f - t);
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

	void Standard::LineAnimation()
	{
		static float alpha = 255.0f;
		const float fadeSpeed = 3.0f;

		Color lineColor{}; 

		if (m_Turn == 'X')
		{
			lineColor = { 255, 0, 0, static_cast<unsigned char>(alpha) };
		}
		else
		{
			lineColor = { 0, 121, 241, static_cast<unsigned char>(alpha) };
		}

		DrawLineEx(m_WinStart, m_WinEnd, 10, lineColor);

		if (alpha > 0.0f)
		{
			alpha -= fadeSpeed;

			if (alpha <= 0.0f)
			{
				alpha = 255.0f;
				m_GameDone = false;
				m_Reset = false;
				
				if (m_XScore > m_OScore)
				{
					m_Turn = 'O';
				}
				else if (m_XScore <= m_OScore)
				{
					m_Turn = 'X';
				}
			}
		}
	}
}