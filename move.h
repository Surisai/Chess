#ifndef MOVE_H
#define MOVE_H

#include <string>

struct Position {
    int row; // 0-7 (1-8 in chess notation)
    int col; // 0-7 (a-h in chess notation)

    Position(int r = -1, int c = -1);
    bool operator==(const Position& other) const;
    bool isValid() const;
    std::string toAlgebraic() const;
    static Position fromAlgebraic(const std::string& alg);
};

struct Move {
    Position from;
    Position to;

    Move(Position f = Position(), Position t = Position());
    std::string toString() const;
    static Move fromString(const std::string& str);
};

#endif // MOVE_H