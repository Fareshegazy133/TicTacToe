#include "AboutMenuState.h"

namespace TicTacToe
{
	AboutMenuState::AboutMenuState()
		: m_Background()
	{}

	void AboutMenuState::OnEnter()
	{
		Image background = LoadImage("Assets/Background.png");
		ImageResize(&background, GetScreenWidth(), GetScreenHeight());
		m_Background = LoadTextureFromImage(background);
		UnloadImage(background);
	}

	void AboutMenuState::OnExit()
	{
		UnloadTexture(m_Background);
	}

	void AboutMenuState::OnUpdate(float ts)
	{

	}

	void AboutMenuState::OnRender()
	{
		DrawTexture(m_Background, 0, 0, WHITE);
	}
}