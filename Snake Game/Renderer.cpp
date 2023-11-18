#include "Renderer.h"

void Renderer::DrawBoard(HDC hdc, int width, int height) {
    Rectangle(hdc, 0, 0, width * 20, height * 20);
}

void Renderer::DrawSnake(HDC hdc, const std::vector<POINT>& snake) {
    // Draw the snake
    for (size_t i = 0; i < snake.size(); ++i) {
        int color = RGB(0, 255 - i * 10, 0); // Varying shades of green
        HBRUSH hBrush = CreateSolidBrush(color);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        Rectangle(hdc, snake[i].x * 20, snake[i].y * 20, (snake[i].x + 1) * 20, (snake[i].y + 1) * 20);
        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
    }
}

void Renderer::DrawFood(HDC hdc, const POINT& food) {
    // Draw the food
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // Red color for food
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    Rectangle(hdc, food.x * 20, food.y * 20, (food.x + 1) * 20, (food.y + 1) * 20);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hBrush);
}

void Renderer::DrawScore(HDC hdc, int score) {
    wchar_t scoreText[50];
    swprintf_s(scoreText, L"Score: %d", score);
    TextOut(hdc, 10, 10, scoreText, wcslen(scoreText));
}
