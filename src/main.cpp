//
//  main.cpp
//  Muehle
//
//  Created by Phil on 30.05.22.
//

#include <iostream>

#include "board.hpp"

int main() {
    Board Gameboard("Heinz", "Karl");
    Gameboard.printBoard();
    int ende = 0;
    while (ende != 1) {
        switch (Gameboard.getCurrentPlayer().getCurrentPhase()) {
            case Player::GamePhase::PlacementPhase: {
                Gameboard.clearBoardOutput();
                std::pair<Point, Point> input = Gameboard.UserInput();
                Gameboard.placePiece(input.first);

            } break;
            case Player::GamePhase::TurnPhase: {
                if (!Gameboard.noMovesAvailable()) {
                    Gameboard.clearBoardOutput();
                    std::pair<Point, Point> input = Gameboard.UserInput();
                    Gameboard.movePiece(input.first, input.second);
                }
            } break;
            case Player::GamePhase::JumpPhase: {
                if (!Gameboard.noMovesAvailable()) {
                    Gameboard.clearBoardOutput();
                    std::pair<Point, Point> input = Gameboard.UserInput();
                    Gameboard.jumpPiece(input.first, input.second);
                }
            } break;
            case Player::GamePhase::Morris: {
                Gameboard.clearBoardOutput();
                std::pair<Point, Point> input = Gameboard.UserInput();
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
