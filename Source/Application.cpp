#include "Application.h"

namespace TicTacToe
{
	Application::Application(const ApplicationSpecification& spec)
		: m_Specification(spec), m_Icon(LoadImage("Assets/Icon.png"))
	{
		InitWindow(m_Specification.Width * m_Specification.Scale,
			m_Specification.Height * m_Specification.Scale, "TicTacToe");

		SetWindowIcon(m_Icon);
		SetTargetFPS(60);

		m_Game = new Game();
	}

	Application::~Application()
	{
		UnloadImage(m_Icon);
		delete m_Game;
		m_Game = nullptr;
		CloseWindow();
	}

	void Application::Run()
	{
		while (!WindowShouldClose())
		{
			m_Time = GetFrameTime();
			OnUpdate();
			OnRender();
		}
	}

	void Application::OnUpdate()
	{
		m_Game->OnUpdate(m_Time);
	}

	void Application::OnRender()
	{
		BeginDrawing();

		ClearBackground(SKYBLUE);

		m_Game->OnRender();

		EndDrawing();
	}
}