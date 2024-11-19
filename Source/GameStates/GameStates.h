#pragma once

namespace TicTacToe
{
	class GameState
	{
	public:
		virtual ~GameState() = default;

		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;

		virtual void OnUpdate(float ts) = 0;
		virtual void OnRender() = 0;
	};
}