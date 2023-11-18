#include "Score.h"

Score::Score() : score(0) {}

Score::~Score() {}

int Score::GetScore() const {
    return score;
}

void Score::IncrementScore() {
    score++;
}

void Score::ResetScore() {
    score = 0;
}
