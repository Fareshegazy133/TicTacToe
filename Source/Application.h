#pragma once

#include "raylib.h"
#include "Game.h"

namespace TicTacToe
{
	struct ApplicationSpecification
	{
		const int Width = 300;
		const int Height = 200;
		const int Scale = 3;
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& spec = ApplicationSpecification());
		~Application();

		void Run();
		void OnUpdate();
		void OnRender();

	private:
		ApplicationSpecification m_Specification;
		Image m_Icon;
		float m_Time = 0.0f;
		Game* m_Game = nullptr;
	};
}