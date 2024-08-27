//
//  Brettlogik.cpp
//  Muehle
//
//  Created by Phil on 30.05.22.
//  Updated on 26th of August 2024

#include "board.hpp"

Board::Board() {
    Sp1.setName("default1");
    Sp2.setName("default2");
    Sp1.setNextPlayer(Sp2);
    Sp2.setNextPlayer(Sp1);
}
Board::Board(std::string name_sp1, std::string name_sp2) {
    Sp1.setName(name_sp1);
    Sp2.setName(name_sp2);
    Sp1.setNextPlayer(Sp2);
    Sp2.setNextPlayer(Sp1);
}

std::pair<Point, Point> Board::UserInput() {
    std::pair<Point, Point> points;
    Point dest, current;
    Point p;

    switch (getCurrentPlayer().getCurrentPhase()) {
        case Player::GamePhase::PlacementPhase: {
            do {
                std::cout << "Please type in the position of the Piece u want "
                             "to place: x,y:"
                          << std::endl;
                std::cout << "Position: ";

                std::string Input = "";
                std::cin >> Input;
                p = Point::boardToArrayKoord(Input);
            } while (!isValidPlacementPosition(p));

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

            } while (!isJumpPossible(dest, current));

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

            } while (!isMovePossible(dest, current));

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
            } while (!isRemoveValid(p));
            return std::make_pair(p, Point());
        } break;
        default:
            break;
    }
}

bool Board::isRemoveValid(Point& p) {
    if (currentPlayer == &Sp1 && GameBoard[p.getY()][p.getX()] == BLACK) {
        return true;
    } else if (currentPlayer == &Sp2 &&
               GameBoard[p.getY()][p.getX()] == WHITE) {
        return true;
    } else {
        return false;
    }
}

void Board::removePiece(Point& p) {
    GameBoard[p.getY()][p.getX()] = 'o';

    getCurrentPlayer().getNextPlayer()->decreaseMaxPieces();

    // reset the morris gamephase back to phase before after removing the piece
    // from the game board
    getCurrentPlayer().setCurrentPhase(getCurrentPlayer().getBeforePhase());
}

void Board::placePiece(Point& p) {
    if (currentPlayer == &Sp1) {
        GameBoard[p.getY()][p.getX()] = WHITE;
    } else {
        GameBoard[p.getY()][p.getX()] = BLACK;
    }

    getCurrentPlayer().decreaseRemainingPieces();

    if (getCurrentPlayer().getRemainingPieces() == 0) {
        getCurrentPlayer().setCurrentPhase(Player::GamePhase::TurnPhase);
        int pieces = getCurrentPlayer().getMaxPieces();
        getCurrentPlayer().setPieces(pieces);
    }

    if (isMorris(p)) {
        getCurrentPlayer().setBeforePhase(getCurrentPlayer().getCurrentPhase());
        getCurrentPlayer().setCurrentPhase(Player::GamePhase::Morris);
    }
}

void Board::updateGamePhases() {
    if (getCurrentPlayer().getNextPlayer()->getMaxPieces() == 3) {
        getCurrentPlayer().getNextPlayer()->setCurrentPhase(
            Player::GamePhase::JumpPhase);
    } else if (getCurrentPlayer().getNextPlayer()->getMaxPieces() == 2) {
        getCurrentPlayer().setCurrentPhase(Player::GamePhase::GameEnd);
        getCurrentPlayer().getNextPlayer()->setCurrentPhase(
            Player::GamePhase::GameEnd);
        getCurrentPlayer().setEndState(Player::EndState::Win);
        getCurrentPlayer().getNextPlayer()->setEndState(
            Player::EndState::Loose);
    } else if (noMovesAvailable()) {
        getCurrentPlayer().setCurrentPhase(Player::GamePhase::GameEnd);
        getCurrentPlayer().getNextPlayer()->setCurrentPhase(
            Player::GamePhase::GameEnd);
        getCurrentPlayer().setEndState(Player::EndState::Loose);
        getCurrentPlayer().getNextPlayer()->setEndState(Player::EndState::Win);
    } else if (checkForDraw()) {
        getCurrentPlayer().setCurrentPhase(Player::GamePhase::GameEnd);
        getCurrentPlayer().getNextPlayer()->setCurrentPhase(
            Player::GamePhase::GameEnd);
    }
}

bool Board::isMovePossible(Point& dest, Point& current) {
    char piece = (currentPlayer == &Sp2) ? BLACK : WHITE;

    if (dest.isPointValid() && current.isPointValid() &&
        (GameBoard[current.getY()][current.getX()] == piece)) {
        if (GameBoard[dest.getY()][dest.getX()] == 'o') {
            if (dest.getY() == current.getY()) {
                int var = dest.getX() - current.getX();
                if (current.getY() == 0 || current.getY() == 6) {
                    if (var == -6 || var == 6)
                        return true;
                } else if (current.getY() == 1 || current.getY() == 5) {
                    if (var == -4 || var == 4)
                        return true;
                } else if (current.getY() == 2 || current.getY() == 4 ||
                           current.getY() == 3) {
                    if (var == -2 || var == 2)
                        return true;
                }
            } else if (dest.getX() == current.getX()) {
                int var = dest.getY() - current.getY();
                if (current.getX() == 0 || current.getX() == 12) {
                    if (var == -3 || var == 3)
                        return true;
                } else if (current.getX() == 2 || current.getX() == 10) {
                    if (var == -2 || var == 2)
                        return true;
                } else if (current.getX() == 4 || current.getX() == 8 ||
                           current.getX() == 6) {
                    if (var == -1 || var == 1)
                        return true;
                }
            } else
                return false;
        } else
            return false;
    }

    return false;
}

bool Board::isJumpPossible(Point& dest, Point& current) {
    if (dest.isPointValid() && current.isPointValid()) {
        if (GameBoard[dest.getY()][dest.getX()] == 'o') {
            return true;
        }
    }
    return false;
}

bool Board::isValidPlacementPosition(Point& p) {
    if (p.isPointValid() && GameBoard[p.getY()][p.getX()] == 'o') {
        return true;
    }
    return false;
}

bool Board::isMorris(Point& newPiece) const {
    char piece = (currentPlayer == &Sp2) ? BLACK : WHITE;

    int y = newPiece.getY();

    if (y == 0 || y == 6) {
        if (GameBoard[y][0] == piece && GameBoard[y][2 * 3] == piece &&
            GameBoard[y][2 * 6] == piece)
            return true;
    } else if (y == 1 || y == 5) {
        if (GameBoard[y][2 * 1] == piece && GameBoard[y][2 * 3] == piece &&
            GameBoard[y][2 * 5] == piece)
            return true;
    } else if (y == 2 || y == 4) {
        if (GameBoard[y][2 * 2] == piece && GameBoard[y][2 * 3] == piece &&
            GameBoard[y][2 * 4] == piece)
            return true;
    } else if (y == 3) {
        if ((GameBoard[y][0] == piece && GameBoard[y][2 * 1] == piece &&
             GameBoard[y][2 * 2] == piece) ||
            (GameBoard[y][2 * 4] == piece && GameBoard[y][2 * 5] == piece &&
             GameBoard[y][2 * 6] == piece))
            return true;
    }

    int x = newPiece.getX();

    if (x == 0 || x == 2 * 6) {
        if (GameBoard[0][x] == piece && GameBoard[3][x] == piece &&
            GameBoard[6][x] == piece)
            return true;
    } else if (x == 2 * 1 || x == 2 * 5) {
        if (GameBoard[1][x] == piece && GameBoard[3][x] == piece &&
            GameBoard[5][x] == piece)
            return true;
    } else if (x == 2 * 2 || x == 2 * 4) {
        if (GameBoard[2][x] == piece && GameBoard[3][x] == piece &&
            GameBoard[4][x] == piece)
            return true;
    } else if (x == 2 * 3) {
        if ((GameBoard[0][x] == piece && GameBoard[1][x] == piece &&
             GameBoard[2][x] == piece) ||
            (GameBoard[4][x] == piece && GameBoard[5][x] == piece &&
             GameBoard[6][x] == piece))
            return true;
    }

    return false;
}

void Board::movePiece(Point& dest, Point& current) {
    char stein = (currentPlayer == &Sp2) ? BLACK : WHITE;

    GameBoard[current.getY()][current.getX()] = 'o';

    GameBoard[dest.getY()][dest.getX()] = stein;

    if (isMorris(dest)) {
        getCurrentPlayer().setBeforePhase(getCurrentPlayer().getCurrentPhase());
        getCurrentPlayer().setCurrentPhase(Player::GamePhase::Morris);
    }
}

void Board::jumpPiece(Point& dest, Point& current) {
    char piece = (currentPlayer == &Sp2) ? BLACK : WHITE;

    if (GameBoard[dest.getY()][dest.getX()] == 'o') {
        GameBoard[current.getY()][current.getX()] = 'o';

        GameBoard[dest.getY()][dest.getX()] = piece;
    }

    if (isMorris(dest)) {
        currentPlayer->setBeforePhase(getCurrentPlayer().getCurrentPhase());
        currentPlayer->setCurrentPhase(Player::GamePhase::Morris);
    }
}

bool Board::checkForDraw() {
    if (Sp1.getCurrentPhase() == Sp2.getCurrentPhase() &&
        Sp1.getCurrentPhase() == Player::GamePhase::JumpPhase) {
        return true;
    }
    return false;
}

bool Board::noMovesAvailable() {
    char stein = (currentPlayer == &Sp2) ? BLACK : WHITE;

    // Check if the player is in the jumping phase
    bool isJumpingPhase =
        (currentPlayer->getCurrentPhase() == Player::GamePhase::JumpPhase);

    if (isJumpingPhase) {
        // In jumping phase, check if there is at least one empty spot
        for (int row = 0; row < ROW; ++row) {
            for (int column = 0; column < COLUMN; column += 2) {
                if (GameBoard[row][column] == 'o') {
                    return false; // Player can jump to this empty spot
                }
            }
        }
        return true; // No empty spots to jump to
    }

    // Lambda function to check if a move is possible in a given direction
    auto isMovePossible = [&](int row,
                              int column,
                              int deltarow,
                              int deltacolumn,
                              char barrier) -> bool {
        int newrow = row + deltarow;
        int newcolumn = column + deltacolumn;

        while (newrow >= 0 && newrow < ROW && newcolumn >= 0 &&
               newcolumn < COLUMN) {
            if (GameBoard[newrow][newcolumn] == 'o') {
                return true;
            }
            if (GameBoard[newrow][newcolumn] == barrier) {
                newrow += deltarow;
                newcolumn += deltacolumn;
                continue;
            }
            break;
        }
        return false;
    };

    for (int row = 0; row < ROW; ++row) {
        for (int column = 0; column < COLUMN; column += 2) {
            if (GameBoard[row][column] == stein) {
                // Check all four directions: North, South, West, East
                if (isMovePossible(row, column, -1, 0, '|') || // North
                    isMovePossible(row, column, 1, 0, '|') ||  // South
                    isMovePossible(row, column, 0, -1, '-') || // West
                    isMovePossible(row, column, 0, 1, '-')) {  // East
                    return false; // A move is possible
                }
            }
        }
    }

    return true; // No moves are possible
}

Player& Board::getCurrentPlayer() {
    return *currentPlayer;
}

void Board::setNextCurrentPlayer() {
    currentPlayer = currentPlayer->getNextPlayer();
}

void Board::printBoard() {
    std::cout << "Morris Game" << std::endl;
    if (getCurrentPlayer().getCurrentPhase() ==
        Player::GamePhase::PlacementPhase) {
        std::cout << "Placement Phase " << std::endl;
    } else if (getCurrentPlayer().getCurrentPhase() ==
               Player::GamePhase::JumpPhase) {
        std::cout << "Jumping Phase " << std::endl;
    } else if (getCurrentPlayer().getCurrentPhase() ==
               Player::GamePhase::TurnPhase) {
        std::cout << "Turn Phase " << std::endl;
    }

    std::cout << "Player 1: " << Sp1.getName()
              << " Pieces Remaining: " << Sp1.getRemainingPieces()
              << " Max Pieces: " << Sp1.getMaxPieces() << std::endl;
    std::cout << "Player 2: " << Sp2.getName()
              << " Pieces Remaining: " << Sp2.getRemainingPieces()
              << " Max Pieces: " << Sp2.getMaxPieces() << std::endl;
    std::cout << std::endl;

    std::cout << getCurrentPlayer().getName() << " turn" << std::endl
              << std::endl;
    std::cout << "  0 1 2 3 4 5 6" << std::endl;
    for (int i = 0; i < ROW; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < COLUMN; ++j) {
            std::cout << GameBoard[i][j];
        }

        std::cout << std::endl;
    }
}

void Board::clearBoardOutput() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    system("clear");
    printBoard();
}

// for unit testing setting up the board how we want
void Board::setBoard(const char newBoard[ROW][COLUMN]) {
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COLUMN; ++j) {
            GameBoard[i][j] = newBoard[i][j];
        }
    }
}
