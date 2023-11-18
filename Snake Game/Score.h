#pragma once

class Score {
public:
    Score();
    ~Score();

    int GetScore() const;
    void IncrementScore();
    void ResetScore();

private:
    int score;
};
