#include "Input.h"
#include "SnakeGame.h"

void Input::ProcessInput(HWND hwnd, WPARAM wParam, LPARAM lParam) {
    switch (wParam) {
    case VK_UP:
        SnakeGame::Instance().SetDirection(Direction::UP);
        break;
    case VK_DOWN:
        SnakeGame::Instance().SetDirection(Direction::DOWN);
        break;
    case VK_LEFT:
        SnakeGame::Instance().SetDirection(Direction::LEFT);
        break;
    case VK_RIGHT:
        SnakeGame::Instance().SetDirection(Direction::RIGHT);
        break;
    }
}
