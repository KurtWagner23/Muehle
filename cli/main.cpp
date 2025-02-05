#include "board.hpp"
#include <chrono>
#include <iostream>
#include <thread>

struct Input {
    Point p1;
    Point p2;
};

Input getUserInput(Board& board);
void clearScreen();
void printBoard(Board& board);
void clearBoardOutput(Board& board);
void printGameEndMessage(Board& board);
bool handlePlacementPhase(Board& board);
bool handleMovePhase(Board& board);
bool handleJumpPhase(Board& board);
bool handleMorrisPhase(Board& board);
void printPlayerInfo(Board& board);

int main() {
    Board gameboard("Heinz", "Karl");
    printBoard(gameboard);

    bool gameOver = false;

    while (!gameOver) {
        switch (gameboard.getCurrentPlayer().getCurrentPhase()) {
            case Player::GamePhase::PlacementPhase:
                gameOver = handlePlacementPhase(gameboard);
                break;
            case Player::GamePhase::TurnPhase:
                gameOver = handleMovePhase(gameboard);
                break;
            case Player::GamePhase::JumpPhase:
                gameOver = handleJumpPhase(gameboard);
                break;
            case Player::GamePhase::Morris:
                gameOver = handleMorrisPhase(gameboard);
                break;
            case Player::GamePhase::GameEnd:
                printGameEndMessage(gameboard);
                gameOver = true;
                break;
            default:
                exit(-12321); // Unexpected game phase
        }

        if (!gameOver) {
            gameboard.updateGamePhases();
            if (gameboard.getCurrentPlayer().getCurrentPhase() !=
                Player::GamePhase::Morris) {
                gameboard.setNextCurrentPlayer();
            }
        }
    }
}

bool handlePlacementPhase(Board& board) {
    clearBoardOutput(board);
    Input input = getUserInput(board);
    board.placePiece(input.p1);
    return board.getCurrentPlayer().getCurrentPhase() ==
           Player::GamePhase::GameEnd;
}

bool handleMovePhase(Board& board) {
    if (board.noMovesAvailable())
        return false;
    clearBoardOutput(board);
    Input input = getUserInput(board);
    board.movePiece(input.p1, input.p2);
    return board.getCurrentPlayer().getCurrentPhase() ==
           Player::GamePhase::GameEnd;
}

bool handleJumpPhase(Board& board) {
    if (board.noMovesAvailable())
        return false;
    clearBoardOutput(board);
    Input input = getUserInput(board);
    board.jumpPiece(input.p1, input.p2);
    return board.getCurrentPlayer().getCurrentPhase() ==
           Player::GamePhase::GameEnd;
}

bool handleMorrisPhase(Board& board) {
    clearBoardOutput(board);
    Input input = getUserInput(board);
    board.removePiece(input.p1);
    return board.getCurrentPlayer().getCurrentPhase() ==
           Player::GamePhase::GameEnd;
}

Input getUserInput(Board& board) {
    Input points;
    Point dest, current, p;

    switch (board.getCurrentPlayer().getCurrentPhase()) {
        case Player::GamePhase::PlacementPhase:
            do {
                std::cout << "Placement Phase!\nEnter the position to place "
                             "your piece (x,y): ";
                std::string input;
                std::cin >> input;
                p = Point::boardToArrayKoord(input);
            } while (!board.isValidPlacementPosition(p));
            return points = {.p1 = p, .p2 = Point()};

        case Player::GamePhase::JumpPhase:
            do {
                std::cout << "Jumping Phase!\nEnter current position (x,y) and "
                             "destination (x,y): ";
                std::string currentPos, destPos;
                std::cin >> currentPos >> destPos;
                current = Point::boardToArrayKoord(currentPos);
                dest = Point::boardToArrayKoord(destPos);
            } while (!board.isJumpPossible(dest, current));
            return points = {.p1 = dest, .p2 = current};
        case Player::GamePhase::TurnPhase:
            do {
                std::cout << "Turn Phase!\nEnter current position (x,y) and "
                             "destination (x,y): ";
                std::string currentPos, destPos;
                std::cin >> currentPos >> destPos;
                current = Point::boardToArrayKoord(currentPos);
                dest = Point::boardToArrayKoord(destPos);
            } while (!board.isMovePossible(dest, current));
            return points = {.p1 = dest, .p2 = current};

        case Player::GamePhase::Morris:
            do {
                std::cout << "Morris!\nRemove opponent's piece (x,y): ";
                std::string input;
                std::cin >> input;
                p = Point::boardToArrayKoord(input);
            } while (!board.isRemoveValid(p));
            return points = {.p1 = p, .p2 = Point()};

        default:
            return points = {Point(), Point()};
    }
}

void printGameEndMessage(Board& board) {
    Player::EndState end = board.getCurrentPlayer().getEndState();
    std::string currentPlayer = board.getCurrentPlayer().getName();
    std::string nextPlayer =
        board.getCurrentPlayer().getNextPlayer()->getName();

    switch (end) {
        case Player::EndState::Win:
            std::cout << "Player " << currentPlayer << " won!!!\n";
            std::cout << "Player " << nextPlayer << " lost.\n";
            break;
        case Player::EndState::Loose:
            std::cout << "Player " << nextPlayer << " won!!!\n";
            std::cout << "Player " << currentPlayer << " lost.\n";
            break;
        case Player::EndState::Draw:
            std::cout << "Players " << currentPlayer << " and " << nextPlayer
                      << " drew the game.\n";
            break;
        default:
            exit(-121); // Unexpected end state
    }
}

void clearScreen() {
#if defined(_WIN32) || defined(_WIN64) // Windows
    system("cls");
#else
    system("clear");
#endif
}

void clearBoardOutput(Board& board) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    clearScreen();
    printBoard(board);
}

void printBoard(Board& board) {
    std::cout << "Morris Game\n";
    printPlayerInfo(board);
    std::cout << "\n  0 1 2 3 4 5 6\n";
    for (int i = 0; i < ROW; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < COLUMN; ++j) {
            std::cout << board.getBoardCoord(i, j);
        }
        std::cout << std::endl;
    }
}

void printPlayerInfo(Board& board) {
    std::cout << "Player 1: " << board.getPlayer1().getName()
              << " Pieces remaining: "
              << board.getPlayer1().getRemainingPieces()
              << " Max Pieces: " << board.getPlayer1().getMaxPieces() << "\n";
    std::cout << "Player 2: " << board.getPlayer2().getName()
              << " Pieces remaining: "
              << board.getPlayer2().getRemainingPieces()
              << " Max Pieces: " << board.getPlayer2().getMaxPieces() << "\n";
    std::cout << board.getCurrentPlayer().getName() << "'s turn\n";
}
