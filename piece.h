#ifndef PIECE_H
#define PIECE_H

#include "move.h"
#include <memory>
#include <string>

class Board; // forward declaration

enum class Color { WHITE, BLACK };
enum class PieceType { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };

class Piece {
protected:
    Color color;
    Position position;
    bool hasMoved;
    char symbol;

public:
    Piece(Color c, Position pos, char sym);
    virtual ~Piece();

    virtual bool isValidMove(const Move& move, const Board& board) const = 0;
    virtual PieceType getType() const = 0;

    Color getColor() const;
    Position getPosition() const;
    void setPosition(Position pos);
    bool getHasMoved() const;
    char getSymbol() const;
    std::string getName() const;
};

class Pawn : public Piece {
public:
    Pawn(Color c, Position pos);
    virtual bool isValidMove(const Move& move, const Board& board) const override;
    virtual PieceType getType() const override;
};

class Knight : public Piece {
public:
    Knight(Color c, Position pos);
    virtual bool isValidMove(const Move& move, const Board& board) const override;
    virtual PieceType getType() const override;
};

class Rook : public Piece {
public:
    Rook(Color c, Position pos);
    virtual bool isValidMove(const Move& move, const Board& board) const override;
    virtual PieceType getType() const override;
};

class Bishop : public Piece {
public:
    Bishop(Color c, Position pos);
    virtual bool isValidMove(const Move& move, const Board& board) const override;
    virtual PieceType getType() const override;
};

class Queen : public Piece {
public:
    Queen(Color c, Position pos);
    virtual bool isValidMove(const Move& move, const Board& board) const override;
    virtual PieceType getType() const override;
};

class King : public Piece {
public:
    King(Color c, Position pos);
    virtual bool isValidMove(const Move& move, const Board& board) const override;
    virtual PieceType getType() const override;
};

#endif // PIECE_H