#include "board.h"
#include "validator.h"
#include <iostream>
#include <string>

void displayHelp() {
    std::cout << "\n=== CHESS HELP ===\n";
    std::cout << "To move: Enter source and destination separated by dash\n";
    std::cout << "Examples: e2-e4, g1-f3, a7-a5\n\n";
    std::cout << "Available commands:\n";
    std::cout << "  board   - Show current board\n";
    std::cout << "  moves   - Show move history\n";
    std::cout << "  help    - Show this help\n";
    std::cout << "  quit    - End the game\n\n";
    std::cout << "Piece movement rules implemented:\n";
    std::cout << "  • Pawns: Forward 1 or 2 (first move), capture diagonally\n";
    std::cout << "  • Knights: L-shape (2+1 squares)\n";
    std::cout << "  • Rooks: Horizontal/vertical any distance\n";
    std::cout << "  • Bishops: Diagonal any distance\n";
    std::cout << "  • Queens: Any direction any distance\n";
    std::cout << "  • Kings: One square any direction\n";
}

int main() {
    Board board;
    Color currentPlayer = Color::WHITE;
    BasicMoveValidator moveValidator(currentPlayer);
    bool gameOver = false;

    std::cout << "=== SIMPLE CHESS GAME ===\n";
    std::cout << "Commands:\n";
    std::cout << "  move <from>-<to>  - Move piece (e.g., 'e2-e4')\n";
    std::cout << "  board             - Display board\n";
    std::cout << "  moves             - Show move history\n";
    std::cout << "  help              - Show commands\n";
    std::cout << "  quit              - Quit game\n\n";
    std::cout << "Piece Symbols: Upper=White, Lower=Black\n";
    std::cout << "  K/k=King, Q/q=Queen, R/r=Rook, B/b=Bishop, N/n=Knight, P/p=Pawn\n\n";

    board.display();

    while (!gameOver) {
        std::cout << "\n" << (currentPlayer == Color::WHITE ? "White" : "Black") << "'s turn: ";

        std::string input;
        std::getline(std::cin, input);

        if (input == "quit") {
            std::cout << "Game ended.\n";
            break;
        } else if (input == "board") {
            board.display();
            continue;
        } else if (input == "moves") {
            board.displayMoveHistory();
            continue;
        } else if (input == "help") {
            displayHelp();
            continue;
        } else if (input.find("move ") == 0) {
            std::string moveStr = input.substr(5);
            // Process the move
            Move move = Move::fromString(moveStr);

            // Basic validation
            auto errors = moveValidator.validate(move, board);
            if (!errors.empty()) {
                std::cout << "Invalid move:\n";
                for (const auto& error : errors) {
                    std::cout << "  • " << error << "\n";
                }
                continue;
            }

            // Piece-specific validation
            auto piece = board.getPieceAt(move.from);
            if (!piece->isValidMove(move, board)) {
                std::cout << "Invalid move for " << piece->getName() << "\n";
                continue;
            }

            // Execute move
            if (board.movePiece(move)) {
                std::cout << "Moved " << piece->getName() << " from " 
                          << move.from.toAlgebraic() << " to " 
                          << move.to.toAlgebraic() << "\n";

                // Switch player
                currentPlayer = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;
                moveValidator = BasicMoveValidator(currentPlayer);

                board.display();
            }
        } else {
            // Try to parse as direct move command
            if (input.find('-') != std::string::npos) {
                Move move = Move::fromString(input);
                // Basic validation
                auto errors = moveValidator.validate(move, board);
                if (!errors.empty()) {
                    std::cout << "Invalid move:\n";
                    for (const auto& error : errors) {
                        std::cout << "  • " << error << "\n";
                    }
                    continue;
                }

                // Piece-specific validation
                auto piece = board.getPieceAt(move.from);
                if (!piece->isValidMove(move, board)) {
                    std::cout << "Invalid move for " << piece->getName() << "\n";
                    continue;
                }

                // Execute move
                if (board.movePiece(move)) {
                    std::cout << "Moved " << piece->getName() << " from " 
                              << move.from.toAlgebraic() << " to " 
                              << move.to.toAlgebraic() << "\n";

                    // Switch player
                    currentPlayer = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;
                    moveValidator = BasicMoveValidator(currentPlayer);

                    board.display();
                }
            } else {
                std::cout << "Invalid command. Type 'help' for commands.\n";
            }
        }
    }

    return 0;
}