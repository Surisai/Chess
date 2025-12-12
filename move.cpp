#include "move.h"
#include <cctype>
#include <sstream>

Position::Position(int r, int c) : row(r), col(c) {}

bool Position::operator==(const Position& other) const {
    return row == other.row && col == other.col;
}

bool Position::isValid() const {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}

std::string Position::toAlgebraic() const {
    return std::string(1, 'a' + col) + std::to_string(8 - row);
}

Position Position::fromAlgebraic(const std::string& alg) {
    if (alg.length() < 2) return Position(-1, -1);
    int col = tolower(alg[0]) - 'a';
    int row = 8 - (alg[1] - '0');
    return Position(row, col);
}

Move::Move(Position f, Position t) : from(f), to(t) {}

std::string Move::toString() const {
    return from.toAlgebraic() + "-" + to.toAlgebraic();
}

Move Move::fromString(const std::string& str) {
    if (str.length() < 5) return Move(Position(-1, -1), Position(-1, -1));
    std::string fromStr = str.substr(0, 2);
    std::string toStr = str.substr(3, 2);
    return Move(Position::fromAlgebraic(fromStr), 
                Position::fromAlgebraic(toStr));
}