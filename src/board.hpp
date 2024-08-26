//
//  Brettlogik.hpp
//  Muehle
//
//  Created by Phil on 30.05.22.
//

#pragma once

#include "player.hpp"
#include "point.hpp"

#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#define SPACE ' '
#define ROW 7
#define COLUMN 13
#define BLACK 'B'
#define WHITE 'W'

class Board {
private:
    Player Sp1;
    Player Sp2;
    Player* currentPlayer = &Sp1;

    char GameBoard[ROW][COLUMN] = {
        {'o', '-', '-', '-', '-', '-', 'o', '-', '-', '-', '-', '-', 'o'},
        {'|', SPACE, 'o', '-', '-', '-', 'o', '-', '-', '-', 'o', SPACE, '|'},
        {'|',
         SPACE,
         '|',
         SPACE,
         'o',
         '-',
         'o',
         '-',
         'o',
         SPACE,
         '|',
         SPACE,
         '|'},
        {'o', '-', 'o', '-', 'o', SPACE, SPACE, SPACE, 'o', '-', 'o', '-', 'o'},
        {'|',
         SPACE,
         '|',
         SPACE,
         'o',
         '-',
         'o',
         '-',
         'o',
         SPACE,
         '|',
         SPACE,
         '|'},
        {'|', SPACE, 'o', '-', '-', '-', 'o', '-', '-', '-', 'o', SPACE, '|'},
        {'o', '-', '-', '-', '-', '-', 'o', '-', '-', '-', '-', '-', 'o'}};

public:
    Board(std::string, std::string);

    void updateGamePhases(void);

    void removePiece(Point&);

    bool isRemoveValid(Point& p);

    void placePiece(Point&);

    bool isMovePossible(Point&, Point&);

    bool isJumpPossible(Point&, Point&);

    bool isValidPlacementPosition(Point&);

    bool isMorris(Point&) const;

    void movePiece(Point&, Point&);

    void jumpPiece(Point&, Point&);

    bool checkForDraw(void);

    bool noMovesAvailable(void);

    Player& getCurrentPlayer(void);
    void setNextCurrentPlayer(void);

    void printBoard(void);
    void clearBoardOutput(void);

    std::pair<Point, Point> UserInput(void);
};
