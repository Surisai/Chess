#include "validator.h"

BasicMoveValidator::BasicMoveValidator(Color color) : playerColor(color) {}

std::vector<std::string> BasicMoveValidator::validate(const Move& move, const Board& board) const {
    std::vector<std::string> errors;

    // Check if positions are valid
    if (!move.from.isValid() || !move.to.isValid()) {
        errors.push_back("Move is outside board boundaries");
    }

    // Check if moving to same square
    if (move.from == move.to) {
        errors.push_back("Cannot move to the same square");
    }

    // Check if there's a piece at source
    auto piece = board.getPieceAt(move.from);
    if (!piece) {
        errors.push_back("No piece at source position");
    } else {
        // Check if moving own piece
        if (piece->getColor() != playerColor) {
            errors.push_back("Cannot move opponent's piece");
        }
    }

    return errors;
}