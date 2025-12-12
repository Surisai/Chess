#ifndef BOARD_H
#define BOARD_H

#include "move.h"
#include "piece.h"
#include <memory>
#include <vector>

class Board {
private:
    std::unique_ptr<Piece> squares[8][8];
    std::vector<Move> moveHistory;

public:
    Board();
    void initializeBoard();
    Piece* getPieceAt(Position pos) const;
    bool isPositionEmpty(Position pos) const;
    bool movePiece(const Move& move);
    void display() const;
    void displayMoveHistory() const;
};

#endif // BOARD_H