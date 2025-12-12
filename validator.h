#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "move.h"
#include "board.h"
#include <vector>
#include <string>

class BasicMoveValidator {
private:
    Color playerColor;

public:
    BasicMoveValidator(Color color);
    std::vector<std::string> validate(const Move& move, const Board& board) const;
};

#endif // VALIDATOR_H