#include "ExitMenuState.h"
#include "MainMenuState.h"
#include "../GameStatesManager.h"

namespace TicTacToe
{
    ExitMenuState::ExitMenuState()
        : m_Background()
    {}

    void ExitMenuState::OnEnter()
    {
        Image background = LoadImage("Assets/Background.png");
        ImageResize(&background, GetScreenWidth(), GetScreenHeight());
        m_Background = LoadTextureFromImage(background);
        UnloadImage(background);
    }

    void ExitMenuState::OnExit()
    {
        UnloadTexture(m_Background);
    }

    void ExitMenuState::OnUpdate(float ts)
    {
        if (CheckCollisionPointRec(GetMousePosition(), m_YesButton) &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {

        }

        if (CheckCollisionPointRec(GetMousePosition(), m_NoButton) &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            TicTacToe::GameStateManager::ChangeState<MainMenuState>();
        }
    }

    void ExitMenuState::OnRender()
    {
        DrawMainMenu();

        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{ 0, 0, 0, 150 });

        DrawRectangleGradientV(200, 200, 500, 200, DARKBLUE, Color{ 0, 0, 30, 255 });
        DrawText("Are you sure you\n\n\n\n   want to quit?", 225, 215, 50, LIGHTGRAY);

        if (CheckCollisionPointRec(GetMousePosition(), m_YesButton))
        {
            DrawRectangleGradientEx(m_YesButton, DARKBLUE, DARKBLUE, BLUE, BLUE);
            DrawRectangleLinesEx(m_YesButton, 1.0f, BLACK);
        }
        else
        {
            DrawRectangleGradientEx(m_YesButton, DARKPURPLE, DARKPURPLE, PURPLE, PURPLE);
            DrawRectangleLinesEx(m_YesButton, 1.0f, BLACK);
        }

        DrawText("Yes", 310, 345, 30, LIGHTGRAY);

        if (CheckCollisionPointRec(GetMousePosition(), m_NoButton))
        {
            DrawRectangleGradientEx(m_NoButton, BLUE, BLUE, DARKBLUE, DARKBLUE);
            DrawRectangleLinesEx(m_NoButton, 1.0f, BLACK);
        }
        else
        {
            DrawRectangleGradientEx(m_NoButton, PURPLE, PURPLE, DARKPURPLE, DARKPURPLE);
            DrawRectangleLinesEx(m_NoButton, 1.0f, BLACK);
        }

        DrawText("No", 545, 345, 30, LIGHTGRAY);
    }

    void ExitMenuState::DrawMainMenu()
    {
        DrawTexture(m_Background, 0, 0, WHITE);

        DrawText("TicTacToe", 40, 25, 75, WHITE);

        DrawRectangleLinesEx(Rectangle{ 50, 175, 350, 75 }, 2.0f, BLUE);
        DrawText("Play", 160, 180, 60, LIGHTGRAY);

        DrawRectangleLinesEx(Rectangle{ 50, 275, 350, 75 }, 2.0f, BLUE);
        DrawText("About", 140, 285, 60, LIGHTGRAY);

        DrawRectangleLinesEx(Rectangle{ 50, 375, 350, 75 }, 2.0f, BLUE);
        DrawText("Options", 120, 380, 60, LIGHTGRAY);

        DrawRectangleLinesEx(Rectangle{ 50, 475, 350, 75 }, 2.0f, BLUE);
        DrawText("Quit", 170, 485, 60, LIGHTGRAY);
    }
}