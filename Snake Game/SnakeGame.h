#pragma once
#include <vector>
#include <windows.h>
#include "Score.h"
#include "Renderer.h"
#include <chrono>


// Define the size of the game board
const int BOARD_WIDTH = 20;
const int BOARD_HEIGHT = 20;

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class SnakeGame {
public:
    static SnakeGame& Instance();  // Singleton pattern

    void Initialize(HWND hwnd); // Initialize the game
    void Cleanup(); // Clean up resources
    void Update(); // Update game logic
    void Render(HDC hdc); // Render the game
    void SetDirection(Direction newDirection); // Set the direction of the snake
    bool IsGameRunning() const; // Check if the game is running
    bool IsWaitingForMessageBox() const; // Check if waiting for a message box response

private:
    SnakeGame(); // Private constructor to enforce Singleton pattern
    ~SnakeGame(); // Destructor

    void MoveSnake(); // Move the snake based on the current direction
    void GenerateFood(); // Generate food at a random position
    bool IsFoodOnSnake() const; // check is food spawned on snake
    void CheckCollision(); // Check for collisions (self or walls)
    void GameOver(); // Handle game over condition

    HWND hwnd;
    Direction direction;
    POINT food;
    std::vector<POINT> snake;
    bool gameRunning;
    bool waitingForMessageBox;
    Score* score; // Encapsulation of Game Logic (Score)
    std::chrono::high_resolution_clock::time_point lastDirectionChangeTime;
    const std::chrono::milliseconds directionChangeCooldown{ 100 }; // Adjust the cooldown time as needed
};
