#include "board.h"
#include <iostream>

Board::Board() {
    initializeBoard();
}

void Board::initializeBoard() {
    // Clear board
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            squares[r][c].reset();
        }
    }

    // Place pawns
    for (int c = 0; c < 8; c++) {
        squares[1][c].reset(new Pawn(Color::BLACK, Position(1, c)));
        squares[6][c].reset(new Pawn(Color::WHITE, Position(6, c)));
    }

    // Place other pieces (back row)
    // Rooks
    squares[0][0].reset(new Rook(Color::BLACK, Position(0, 0)));
    squares[0][7].reset(new Rook(Color::BLACK, Position(0, 7)));
    squares[7][0].reset(new Rook(Color::WHITE, Position(7, 0)));
    squares[7][7].reset(new Rook(Color::WHITE, Position(7, 7)));

    // Knights
    squares[0][1].reset(new Knight(Color::BLACK, Position(0, 1)));
    squares[0][6].reset(new Knight(Color::BLACK, Position(0, 6)));
    squares[7][1].reset(new Knight(Color::WHITE, Position(7, 1)));
    squares[7][6].reset(new Knight(Color::WHITE, Position(7, 6)));

    // Bishops
    squares[0][2].reset(new Bishop(Color::BLACK, Position(0, 2)));
    squares[0][5].reset(new Bishop(Color::BLACK, Position(0, 5)));
    squares[7][2].reset(new Bishop(Color::WHITE, Position(7, 2)));
    squares[7][5].reset(new Bishop(Color::WHITE, Position(7, 5)));

    // Queens
    squares[0][3].reset(new Queen(Color::BLACK, Position(0, 3)));
    squares[7][3].reset(new Queen(Color::WHITE, Position(7, 3)));

    // Kings
    squares[0][4].reset(new King(Color::BLACK, Position(0, 4)));
    squares[7][4].reset(new King(Color::WHITE, Position(7, 4)));
}

Piece* Board::getPieceAt(Position pos) const {
    if (!pos.isValid()) return nullptr;
    return squares[pos.row][pos.col].get();
}

bool Board::isPositionEmpty(Position pos) const {
    if (!pos.isValid()) return false;
    return squares[pos.row][pos.col] == nullptr;
}

bool Board::movePiece(const Move& move) {
    auto piece = getPieceAt(move.from);
    if (!piece) return false;

    // Move the piece
    squares[move.to.row][move.to.col] = std::move(squares[move.from.row][move.from.col]);
    piece->setPosition(move.to);

    moveHistory.push_back(move);
    return true;
}

void Board::display() const {
    std::cout << "\n  a b c d e f g h\n";
    std::cout << "  ----------------\n";

    for (int r = 0; r < 8; r++) {
        std::cout << 8 - r << "|";
        for (int c = 0; c < 8; c++) {
            if (auto piece = squares[r][c].get()) {
                std::cout << piece->getSymbol() << " ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << "|" << 8 - r << "\n";
    }

    std::cout << "  ----------------\n";
    std::cout << "  a b c d e f g h\n";
}

void Board::displayMoveHistory() const {
    if (moveHistory.empty()) {
        std::cout << "No moves made yet.\n";
        return;
    }

    std::cout << "\nMove History:\n";
    for (size_t i = 0; i < moveHistory.size(); i++) {
        std::cout << (i + 1) << ". " << moveHistory[i].toString() << "\n";
    }
}