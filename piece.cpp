#include "piece.h"
#include "board.h"
#include <cmath>
#include <cctype>

Piece::Piece(Color c, Position pos, char sym) 
    : color(c), position(pos), hasMoved(false), symbol(sym) {}

Piece::~Piece() {}

Color Piece::getColor() const { return color; }
Position Piece::getPosition() const { return position; }
void Piece::setPosition(Position pos) { position = pos; hasMoved = true; }
bool Piece::getHasMoved() const { return hasMoved; }

char Piece::getSymbol() const {
    return (color == Color::WHITE) ? toupper(symbol) : tolower(symbol);
}

std::string Piece::getName() const {
    switch(getType()) {
        case PieceType::KING: return "King";
        case PieceType::QUEEN: return "Queen";
        case PieceType::ROOK: return "Rook";
        case PieceType::BISHOP: return "Bishop";
        case PieceType::KNIGHT: return "Knight";
        case PieceType::PAWN: return "Pawn";
        default: return "Unknown";
    }
}

// Pawn implementation
Pawn::Pawn(Color c, Position pos) : Piece(c, pos, 'P') {}

PieceType Pawn::getType() const { return PieceType::PAWN; }

bool Pawn::isValidMove(const Move& move, const Board& board) const {
    int direction = (color == Color::WHITE) ? -1 : 1;
    int startRow = (color == Color::WHITE) ? 6 : 1;

    // Basic forward move
    if (move.from.col == move.to.col) {
        // One square forward
        if (move.to.row == move.from.row + direction && 
            board.isPositionEmpty(move.to)) {
            return true;
        }
        // Two squares forward from starting position
        if (!hasMoved && move.from.row == startRow &&
            move.to.row == move.from.row + 2 * direction && 
            board.isPositionEmpty(move.to) &&
            board.isPositionEmpty(Position(move.from.row + direction, move.from.col))) {
            return true;
        }
    }

    // Capture diagonally
    if (abs(move.to.col - move.from.col) == 1 &&
        move.to.row == move.from.row + direction) {
        auto targetPiece = board.getPieceAt(move.to);
        if (targetPiece && targetPiece->getColor() != color) {
            return true;
        }
    }

    return false;
}

// Knight implementation
Knight::Knight(Color c, Position pos) : Piece(c, pos, 'N') {}

PieceType Knight::getType() const { return PieceType::KNIGHT; }

bool Knight::isValidMove(const Move& move, const Board& board) const {
    int rowDiff = abs(move.to.row - move.from.row);
    int colDiff = abs(move.to.col - move.from.col);

    // Knight moves in L-shape: (2,1) or (1,2)
    if (!((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2))) {
        return false;
    }

    // Can move to empty square or capture opponent
    auto targetPiece = board.getPieceAt(move.to);
    return !targetPiece || targetPiece->getColor() != color;
}

// Rook implementation
Rook::Rook(Color c, Position pos) : Piece(c, pos, 'R') {}

PieceType Rook::getType() const { return PieceType::ROOK; }

bool Rook::isValidMove(const Move& move, const Board& board) const {
    // Rook moves horizontally or vertically
    if (move.from.row != move.to.row && move.from.col != move.to.col) {
        return false;
    }

    // Check if path is clear
    int rowStep = (move.to.row > move.from.row) ? 1 : 
                 (move.to.row < move.from.row) ? -1 : 0;
    int colStep = (move.to.col > move.from.col) ? 1 :
                 (move.to.col < move.from.col) ? -1 : 0;

    int currentRow = move.from.row + rowStep;
    int currentCol = move.from.col + colStep;

    while (currentRow != move.to.row || currentCol != move.to.col) {
        if (!board.isPositionEmpty(Position(currentRow, currentCol))) {
            return false;
        }
        currentRow += rowStep;
        currentCol += colStep;
    }

    // Check destination
    auto targetPiece = board.getPieceAt(move.to);
    return !targetPiece || targetPiece->getColor() != color;
}

// Bishop implementation
Bishop::Bishop(Color c, Position pos) : Piece(c, pos, 'B') {}

PieceType Bishop::getType() const { return PieceType::BISHOP; }

bool Bishop::isValidMove(const Move& move, const Board& board) const {
    // Bishop moves diagonally
    if (abs(move.to.row - move.from.row) != abs(move.to.col - move.from.col)) {
        return false;
    }

    // Check if path is clear
    int rowStep = (move.to.row > move.from.row) ? 1 : -1;
    int colStep = (move.to.col > move.from.col) ? 1 : -1;

    int currentRow = move.from.row + rowStep;
    int currentCol = move.from.col + colStep;

    while (currentRow != move.to.row && currentCol != move.to.col) {
        if (!board.isPositionEmpty(Position(currentRow, currentCol))) {
            return false;
        }
        currentRow += rowStep;
        currentCol += colStep;
    }

    // Check destination
    auto targetPiece = board.getPieceAt(move.to);
    return !targetPiece || targetPiece->getColor() != color;
}

// Queen implementation
Queen::Queen(Color c, Position pos) : Piece(c, pos, 'Q') {}

PieceType Queen::getType() const { return PieceType::QUEEN; }

bool Queen::isValidMove(const Move& move, const Board& board) const {
    // Queen moves like rook or bishop
    bool isStraight = (move.from.row == move.to.row || move.from.col == move.to.col);
    bool isDiagonal = (abs(move.to.row - move.from.row) == abs(move.to.col - move.from.col));

    if (!isStraight && !isDiagonal) return false;

    // Check if path is clear
    int rowStep = 0;
    int colStep = 0;
    if (move.to.row > move.from.row) rowStep = 1;
    else if (move.to.row < move.from.row) rowStep = -1;

    if (move.to.col > move.from.col) colStep = 1;
    else if (move.to.col < move.from.col) colStep = -1;

    int currentRow = move.from.row + rowStep;
    int currentCol = move.from.col + colStep;

    while (currentRow != move.to.row || currentCol != move.to.col) {
        if (!board.isPositionEmpty(Position(currentRow, currentCol))) {
            return false;
        }
        currentRow += rowStep;
        currentCol += colStep;
    }

    // Check destination
    auto targetPiece = board.getPieceAt(move.to);
    return !targetPiece || targetPiece->getColor() != color;
}

// King implementation
King::King(Color c, Position pos) : Piece(c, pos, 'K') {}

PieceType King::getType() const { return PieceType::KING; }

bool King::isValidMove(const Move& move, const Board& board) const {
    // King moves one square in any direction
    int rowDiff = abs(move.to.row - move.from.row);
    int colDiff = abs(move.to.col - move.from.col);

    if (rowDiff > 1 || colDiff > 1) return false;

    // Check destination
    auto targetPiece = board.getPieceAt(move.to);
    return !targetPiece || targetPiece->getColor() != color;
}