//
//  main.cpp
//  Muehle
//
//  Created by Phil on 30.05.22.
//

#include <chrono>
#include <iostream>
#include <thread>

#include "board.hpp"

std::pair<Point, Point> UserInput(Board& board);
void clearScreen();
void printBoard(Board& board);
void clearBoardOutput(Board& board);

int main() {
    Board Gameboard("Heinz", "Karl");
    printBoard(Gameboard);
    int ende = 0;
    while (ende != 1) {
        switch (Gameboard.getCurrentPlayer().getCurrentPhase()) {
            case Player::GamePhase::PlacementPhase: {
                clearBoardOutput(Gameboard);
                std::pair<Point, Point> input = UserInput(Gameboard);
                Gameboard.placePiece(input.first);

            } break;
            case Player::GamePhase::TurnPhase: {
                if (!Gameboard.noMovesAvailable()) {
                    clearBoardOutput(Gameboard);
                    std::pair<Point, Point> input = UserInput(Gameboard);
                    Gameboard.movePiece(input.first, input.second);
                }
            } break;
            case Player::GamePhase::JumpPhase: {
                if (!Gameboard.noMovesAvailable()) {
                    clearBoardOutput(Gameboard);
                    std::pair<Point, Point> input = UserInput(Gameboard);
                    Gameboard.jumpPiece(input.first, input.second);
                }
            } break;
            case Player::GamePhase::Morris: {
                clearBoardOutput(Gameboard);
                std::pair<Point, Point> input = UserInput(Gameboard);
                Gameboard.removePiece(input.first);
            } break;
            case Player::GamePhase::GameEnd: {
                Player::EndState end =
                    Gameboard.getCurrentPlayer().getEndState();
                switch (end) {
                    case Player::EndState::Win: {
                        std::cout << "Player: "
                                  << Gameboard.getCurrentPlayer().getName()
                                  << " won!!!!!!!!!" << std::endl;
                        std::cout << "Player: "
                                  << Gameboard.getCurrentPlayer()
                                         .getNextPlayer()
                                         ->getName()
                                  << " lost" << std::endl;
                    } break;
                    case Player::EndState::Loose: {
                        std::cout << "Player: "
                                  << Gameboard.getCurrentPlayer()
                                         .getNextPlayer()
                                         ->getName()
                                  << " won!!!!!!!!!" << std::endl;
                        std::cout << "Player: "
                                  << Gameboard.getCurrentPlayer().getName()
                                  << " lost" << std::endl;
                    } break;
                    case Player::EndState::Draw: {
                        std::cout << "Player: "
                                  << Gameboard.getCurrentPlayer().getName()
                                  << " and "
                                  << Gameboard.getCurrentPlayer()
                                         .getNextPlayer()
                                         ->getName();
                        std::cout << " drew the game!" << std::endl;
                    } break;
                    default: {
                        exit(-121);
                    } break;
                }
                ende = 1;
            } break;
            default: {
                exit(-12321);
            } break;
        }
        // TODO: check if this is the right place for this method
        Gameboard.updateGamePhases();
        // continue the loop and dont change the player to cover the morris
        if (Gameboard.getCurrentPlayer().getCurrentPhase() ==
            Player::GamePhase::Morris)
            continue;
        Gameboard.setNextCurrentPlayer();
    }
}

std::pair<Point, Point> UserInput(Board& board) {
    std::pair<Point, Point> points;
    Point dest, current;
    Point p;

    switch (board.getCurrentPlayer().getCurrentPhase()) {
        case Player::GamePhase::PlacementPhase: {
            do {
                std::cout << "Please type in the position of the Piece u want "
                             "to place: x,y:"
                          << std::endl;
                std::cout << "Position: ";

                std::string Input = "";
                std::cin >> Input;
                p = Point::boardToArrayKoord(Input);
            } while (!board.isValidPlacementPosition(p));

            return std::make_pair(p, Point());
        } break;

        case Player::GamePhase::JumpPhase: {
            do {
                std::cout
                    << "Please type in the position of the Piece u want "
                       "to jump to:\ncurrent position: x,y  destination: x,y:"
                    << std::endl;
                std::cout << "Current position: ";

                std::string currentPosition;
                std::cin >> currentPosition;
                std::cout << "Destination: ";
                std::string destPosition;
                std::cin >> destPosition;

                dest = Point::boardToArrayKoord(destPosition);
                current = Point::boardToArrayKoord(currentPosition);

            } while (!board.isJumpPossible(dest, current));

            return std::make_pair(dest, current);

        } break;

        case Player::GamePhase::TurnPhase: {
            do {
                std::cout
                    << "Please type in the position of the Piece u want "
                       "to move to:\ncurrent position: x,y, destination: x,y:"
                    << std::endl;
                std::cout << "Current position: ";

                std::string currentPosition;
                std::cin >> currentPosition;
                std::cout << "Destination: ";
                std::string destPosition;
                std::cin >> destPosition;

                dest = Point::boardToArrayKoord(destPosition);
                current = Point::boardToArrayKoord(currentPosition);

            } while (!board.isMovePossible(dest, current));

            return std::make_pair(dest, current);
        } break;
        case Player::GamePhase::Morris: {
            do {
                std::string Input;

                std::cout
                    << "Morris! Please remove opponent piece: position: x,y:"
                    << std::endl;
                std::cin >> Input;

                p = Point::boardToArrayKoord(Input);
            } while (!board.isRemoveValid(p));
            return std::make_pair(p, Point());
        } break;
        default:
            break;
    }
    return std::pair<Point, Point>();
}

void clearScreen() {
#if defined(_WIN32) || defined(_WIN64) // Windows
    system("cls");
#else // for unix-based systems
    system("clear");
#endif
}

void clearBoardOutput(Board& board) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    clearScreen();
    printBoard(board);
}

void printBoard(Board& board) {
    std::cout << "Morris Game" << std::endl;
    if (board.getCurrentPlayer().getCurrentPhase() ==
        Player::GamePhase::PlacementPhase) {
        std::cout << "Placement Phase " << std::endl;
    } else if (board.getCurrentPlayer().getCurrentPhase() ==
               Player::GamePhase::JumpPhase) {
        std::cout << "Jumping Phase " << std::endl;
    } else if (board.getCurrentPlayer().getCurrentPhase() ==
               Player::GamePhase::TurnPhase) {
        std::cout << "Turn Phase " << std::endl;
    }

    std::cout << "Player 1: " << board.getPlayer1().getName()
              << " Pieces remaining to place: "
              << board.getPlayer1().getRemainingPieces()
              << " Max Pieces: " << board.getPlayer1().getMaxPieces()
              << std::endl;
    std::cout << "Player 2: " << board.getPlayer2().getName()
              << " Pieces remaining to place: "
              << board.getPlayer2().getRemainingPieces()
              << " Max Pieces: " << board.getPlayer2().getMaxPieces()
              << std::endl;
    std::cout << std::endl;

    std::cout << board.getCurrentPlayer().getName() << " turn" << std::endl
              << std::endl;
    std::cout << "  0 1 2 3 4 5 6" << std::endl;
    for (int i = 0; i < ROW; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < COLUMN; ++j) {
            std::cout << board.getBoardCoord(i, j);
        }

        std::cout << std::endl;
    }
}