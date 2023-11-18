#pragma once
#include <windows.h>
#include <vector>

class Renderer {
public:
    static void DrawBoard(HDC hdc, int width, int height);
    static void DrawSnake(HDC hdc, const std::vector<POINT>& snake);
    static void DrawFood(HDC hdc, const POINT& food);
    static void DrawScore(HDC hdc, int score);
};