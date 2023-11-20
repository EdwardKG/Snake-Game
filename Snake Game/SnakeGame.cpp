#include "SnakeGame.h"
#include <wchar.h>
#include <chrono>

SnakeGame::SnakeGame() : score(nullptr) {}

SnakeGame::~SnakeGame() {
    Cleanup();
}

SnakeGame& SnakeGame::Instance() {
    // Singleton pattern: Ensure only one instance of SnakeGame is created
    static SnakeGame instance;
    return instance;
}

void SnakeGame::Initialize(HWND hwnd) {
    this->hwnd = hwnd;
    direction = Direction::RIGHT;

    // Clear the existing snake vector
    snake.clear();

    // Add a new initial segment to the snake
    snake.push_back({ BOARD_WIDTH / 2, BOARD_HEIGHT / 2 });

    GenerateFood();
    SetTimer(hwnd, 1, 100, nullptr);
    gameRunning = true;
    waitingForMessageBox = false;
    score = new Score();
}

void SnakeGame::Cleanup() {
    KillTimer(hwnd, 1);
    delete score;
}

void SnakeGame::Update() {
    if (gameRunning) {
        MoveSnake();
        CheckCollision();
        InvalidateRect(hwnd, nullptr, TRUE);
    }
}

void SnakeGame::Render(HDC hdc) {
    if (gameRunning) {
        Renderer::DrawBoard(hdc, BOARD_WIDTH, BOARD_HEIGHT);
        Renderer::DrawSnake(hdc, snake);
        Renderer::DrawFood(hdc, food);
        Renderer::DrawScore(hdc, score->GetScore());
    }
}

void SnakeGame::SetDirection(Direction newDirection) {
    // Check if enough time has passed since the last direction change
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto timeSinceLastChange = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastDirectionChangeTime);

    if (timeSinceLastChange >= directionChangeCooldown) {
        // Ensure the snake cannot reverse its direction
        if ((direction == Direction::UP && newDirection != Direction::DOWN) ||
            (direction == Direction::DOWN && newDirection != Direction::UP) ||
            (direction == Direction::LEFT && newDirection != Direction::RIGHT) ||
            (direction == Direction::RIGHT && newDirection != Direction::LEFT)) {
            direction = newDirection;
            lastDirectionChangeTime = currentTime; // Update the last direction change time
        }
    }
}

bool SnakeGame::IsGameRunning() const {
    return gameRunning;
}

bool SnakeGame::IsWaitingForMessageBox() const {
    return waitingForMessageBox;
}

void SnakeGame::MoveSnake() {
    // Move the snake in the current direction
    POINT head = snake.front();
    switch (direction) {
    case Direction::UP:
        head.y = (head.y - 1 + BOARD_HEIGHT) % BOARD_HEIGHT;
        break;
    case Direction::DOWN:
        head.y = (head.y + 1) % BOARD_HEIGHT;
        break;
    case Direction::LEFT:
        head.x = (head.x - 1 + BOARD_WIDTH) % BOARD_WIDTH;
        break;
    case Direction::RIGHT:
        head.x = (head.x + 1) % BOARD_WIDTH;
        break;
    }

    // Insert the new head at the front of the snake
    snake.insert(snake.begin(), head);

    // Check if the snake has eaten the food
    if (head.x == food.x && head.y == food.y) {
        score->IncrementScore();
        GenerateFood();
    }
    else {
        // If not, remove the tail of the snake
        snake.pop_back();
    }
}

void SnakeGame::GenerateFood() {
    // Keep generating random positions until a valid one is found
    do {
        food.x = rand() % BOARD_WIDTH;
        food.y = rand() % BOARD_HEIGHT;
    } while (IsFoodOnSnake());
}

bool SnakeGame::IsFoodOnSnake() const {
    // Check if the food position is occupied by the snake
    for (const auto& segment : snake) {
        if (food.x == segment.x && food.y == segment.y) {
            return true;
        }
    }
    return false;
}

void SnakeGame::CheckCollision() {
    // Check if the snake has collided with the walls or itself
    POINT head = snake.front();

    // Check for self-collision
    for (size_t i = 1; i < snake.size(); ++i) {
        if (head.x == snake[i].x && head.y == snake[i].y) {
            GameOver();
        }
    }
}

void SnakeGame::GameOver() {
    waitingForMessageBox = true;
    gameRunning = false;
    int result = MessageBox(hwnd, L"Game Over! Do you want to play again?", L"Snake Game", MB_YESNO);
    if (result == IDYES) {
        Cleanup();
        waitingForMessageBox = false;
        score->ResetScore();
        Initialize(hwnd);
    }
    else {
        PostQuitMessage(0);
    }
}
