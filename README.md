# ♟️ Chess Game – Object-Oriented Programming in C++

A fully functional console-based **Chess Game implemented in C++**, demonstrating strong Object-Oriented Programming (OOP) design including inheritance, polymorphism, encapsulation, and composition.

## 📑 Table of Contents
- [Project Overview](#-project-overview)
- [Features](#-features)
- [Project Structure](#-project-structure)
- [Class Architecture](#-class-architecture)
- [How to Compile & Run](#-how-to-compile--run)
- [Game Commands](#-game-commands)
- [Piece Movement Rules](#-piece-movement-rules)
- [Object-Oriented Design Principles](#-object-oriented-design-principles)
- [Implementation Details](#-implementation-details)
- [Example Game Session](#-example-game-session)
- [Testing](#-testing)
- [Future Enhancements](#-future-enhancements)
- [Known Limitations](#-known-limitations)
- [License](#-license)

## 🎯 Project Overview
This project is a **C++ console-based chess game** created to demonstrate real-world object modeling, class architecture, input validation, polymorphism, and memory-safe design.

## ⭐ Features
### ✔️ Fully Working Chess Engine
- Algebraic notation (`e2-e4`)
- Illegal move detection
- Turn-by-turn gameplay
- Move history
- ASCII board UI

### ✔️ Strong C++ OOP Concepts
- Inheritance & polymorphism
- Encapsulation
- Composition

## 🏗️ Project Structure
```
chess_game/
├── chess.h
├── chess.cpp
├── main.cpp
└── README.md
```

## 🧱 Class Architecture
### Piece Hierarchy
```
Piece
├── Pawn
├── Knight
├── Bishop
├── Rook
├── Queen
└── King
```

### Supporting Classes
```
Position
Move
Board
MoveValidator
ChessGame
```

## 🚀 How to Compile & Run
### Compile
```bash
g++ -std=c++11 -o chess main.cpp chess.cpp
```
### Run
```bash
./chess
```

## 🎮 Game Commands
| Command | Description |
|--------|-------------|
| move e2-e4 | Move a piece |
| board | Show board |
| moves | Show move history |
| help | Show commands |
| quit | Exit game |

## ♟️ Piece Movement Rules
| Piece | Movement | Notes |
|-------|----------|-------|
| Pawn | Forward | Diagonal capture |
| Knight | L‑shape | Jumps pieces |
| Bishop | Diagonal | Needs clear path |
| Rook | Straight | Needs clear path |
| Queen | Any direction | Needs clear path |
| King | One square | — |

## 🧩 Object-Oriented Design Principles
- Encapsulation  
- Inheritance  
- Polymorphism  
- Composition  
- Single Responsibility  

## 🔧 Implementation Details
- Path validation  
- Smart pointers (`unique_ptr`)  
- RAII  

## 📝 Example Game Session
```
White: e2-e4
Black: e7-e5
White: g1-f3
```

## 🧪 Testing
### Try these:
```
e2-e4
e7-e5
g1-f3
b8-c6
```

### Error Cases
- Invalid format  
- Illegal movement  
- Moving opponent’s piece  

## 🔮 Future Enhancements
- Check/checkmate  
- Castling, en passant  
- Save/load  
- Undo/redo  
- AI  

## 🐛 Known Limitations
- No checkmate detection  
- No special moves  
- No stalemate logic  

## 📄 License
Educational use only.
