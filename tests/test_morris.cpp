#include "board.hpp"
#include "gtest/gtest.h"

class BoardTest : public ::testing::Test {
protected:
    Board board;
    Point dest;
    Point current;

    virtual void SetUp() {
        // Initialize the game board with some setup for testing
        char initialBoard[ROW][COLUMN] = {
            {'W', '-', '-', '-', '-', '-', 'o', '-', '-', '-', '-', '-', 'B'},
            {'|', ' ', 'W', '-', '-', '-', 'B', '-', '-', '-', 'B', ' ', '|'},
            {'|', ' ', '|', ' ', 'B', '-', 'W', '-', 'o', ' ', '|', ' ', '|'},
            {'o', '-', 'B', '-', 'o', ' ', ' ', ' ', 'B', '-', 'W', '-', 'B'},
            {'|', ' ', '|', ' ', 'o', '-', 'W', '-', 'o', ' ', '|', ' ', '|'},
            {'|', ' ', 'B', '-', '-', '-', 'B', '-', '-', '-', 'B', ' ', '|'},
            {'B', '-', '-', '-', '-', '-', 'o', '-', '-', '-', '-', '-', 'W'}};
        board.setBoard(initialBoard);
    }
};

TEST_F(BoardTest, TestMovesAvailableForWhite) {
    // test for player 1

    EXPECT_FALSE(board.noMovesAvailable());
}

TEST_F(BoardTest, TestMovesAvailableForBlack) {
    // test for player 2

    board.setNextCurrentPlayer();

    EXPECT_FALSE(board.noMovesAvailable());
}

TEST_F(BoardTest, TestNoMovesAvailableForWhite) {
    // test for player 1

    char initialBoard[ROW][COLUMN] = {
        {'B', '-', '-', '-', '-', '-', 'o', '-', '-', '-', '-', '-', 'B'},
        {'|', ' ', 'W', '-', '-', '-', 'B', '-', '-', '-', 'B', ' ', '|'},
        {'|', ' ', '|', ' ', 'B', '-', 'W', '-', 'W', ' ', '|', ' ', '|'},
        {'W', '-', 'B', '-', 'o', ' ', ' ', ' ', 'B', '-', 'W', '-', 'B'},
        {'|', ' ', '|', ' ', 'B', '-', 'W', '-', 'B', ' ', '|', ' ', '|'},
        {'|', ' ', 'B', '-', '-', '-', 'B', '-', '-', '-', 'B', ' ', '|'},
        {'B', '-', '-', '-', '-', '-', 'W', '-', '-', '-', '-', '-', 'W'}};
    board.setBoard(initialBoard);

    EXPECT_TRUE(board.noMovesAvailable());
}

TEST_F(BoardTest, TestNoMovesAvailableForBlack) {
    // test for player 2

    board.setNextCurrentPlayer();

    char initialBoard[ROW][COLUMN] = {
        {'W', '-', '-', '-', '-', '-', 'o', '-', '-', '-', '-', '-', 'W'},
        {'|', ' ', 'W', '-', '-', '-', 'W', '-', '-', '-', 'B', ' ', '|'},
        {'|', ' ', '|', ' ', 'B', '-', 'W', '-', 'o', ' ', '|', ' ', '|'},
        {'W', '-', 'B', '-', 'W', ' ', ' ', ' ', 'W', '-', 'W', '-', 'B'},
        {'|', ' ', '|', ' ', 'o', '-', 'W', '-', 'o', ' ', '|', ' ', '|'},
        {'|', ' ', 'B', '-', '-', '-', 'B', '-', '-', '-', 'B', ' ', '|'},
        {'B', '-', '-', '-', '-', '-', 'B', '-', '-', '-', '-', '-', 'W'}};
    board.setBoard(initialBoard);

    EXPECT_TRUE(board.noMovesAvailable());
}

TEST_F(BoardTest, TestValidHorizontalMove) {
    current = Point(0, 0); // Position of a White piece
    dest = Point(6, 0);    // Valid destination
    EXPECT_TRUE(board.isMovePossible(dest, current));
}

TEST_F(BoardTest, TestInvalidHorizontalMove) {
    current = Point(0, 0); // Position of a White piece
    dest = Point(4, 0);    // Invalid destination
    EXPECT_FALSE(board.isMovePossible(dest, current));
}

TEST_F(BoardTest, TestValidVerticalMove) {
    current = Point(0, 0); // Position of a White piece
    dest = Point(0, 3);    // Valid destination
    EXPECT_TRUE(board.isMovePossible(dest, current));
}

TEST_F(BoardTest, TestInvalidVerticalMove) {
    current = Point(0, 0); // Position of a White piece
    dest = Point(0, 2);    // Invalid destination
    EXPECT_FALSE(board.isMovePossible(dest, current));
}

TEST_F(BoardTest, TestInvalidMoveToOccupied) {
    current = Point(6, 2); // Position of a White piece
    dest = Point(6, 1);    // Position occupied by a Black piece
    EXPECT_FALSE(board.isMovePossible(dest, current));
}

TEST_F(BoardTest, TestMoveWithInvalidPoints) {
    current = Point(15, 0); // Invalid position
    dest = Point(6, 0);     // Valid destination
    EXPECT_FALSE(board.isMovePossible(dest, current));
}

TEST_F(BoardTest, TestValidJump) {
    current = Point(6, 6); // Position of a White piece
    dest = Point(0, 3);    // Valid destination (empty spot)
    EXPECT_TRUE(board.isJumpPossible(dest, current));
}

TEST_F(BoardTest, TestInvalidJumpOccupied) {
    current = Point(12, 6); // Position of a White piece
    dest = Point(12, 0);    // Occupied destination by Black
    EXPECT_FALSE(board.isJumpPossible(dest, current));
}

TEST_F(BoardTest, TestJumpWithInvalidPoints) {
    current = Point(15, 6); // Invalid position
    dest = Point(0, 0);     // Valid destination
    EXPECT_FALSE(board.isJumpPossible(dest, current));
}

TEST_F(BoardTest, TestValidPlacementPosition) {
    Point p(6, 0); // Empty spot
    EXPECT_TRUE(board.isValidPlacementPosition(p));
}

TEST_F(BoardTest, TestInvalidPlacementOccupied) {
    Point p(12, 0); // Occupied by a Black piece
    EXPECT_FALSE(board.isValidPlacementPosition(p));
}

TEST_F(BoardTest, TestPlacementWithInvalidPoint) {
    Point p(15, 0); // Invalid position
    EXPECT_FALSE(board.isValidPlacementPosition(p));
}

TEST_F(BoardTest, TestValidPieceRemove) {
    Point p(12, 0); // Black Piece Position
    EXPECT_TRUE(board.isRemoveValid(p));
}

TEST_F(BoardTest, TestInvalidPieceRemove) {
    Point p(6, 0); // Empty position
    EXPECT_FALSE(board.isRemoveValid(p));
}

TEST_F(BoardTest, TestNewMorris) {
    char initialBoard[ROW][COLUMN] = {
        {'W', '-', '-', '-', '-', '-', 'o', '-', '-', '-', '-', '-', 'W'},
        {'|', ' ', 'W', '-', '-', '-', 'B', '-', '-', '-', 'B', ' ', '|'},
        {'|', ' ', '|', ' ', 'B', '-', 'o', '-', 'o', ' ', '|', ' ', '|'},
        {'o', '-', 'B', '-', 'o', ' ', ' ', ' ', 'B', '-', 'o', '-', 'o'},
        {'|', ' ', '|', ' ', 'o', '-', 'o', '-', 'o', ' ', '|', ' ', '|'},
        {'|', ' ', 'B', '-', '-', '-', 'o', '-', '-', '-', 'B', ' ', '|'},
        {'W', '-', '-', '-', '-', '-', 'o', '-', '-', '-', '-', '-', 'W'}};
    board.setBoard(initialBoard);

    // setting Piece to Point(0,3) to make a morris
    Point p(0, 3);
    board.placePiece(p);
    EXPECT_TRUE(board.isMorris(p));
}

TEST_F(BoardTest, TestOldMorris) {
    char initialBoard[ROW][COLUMN] = {
        {'W', '-', '-', '-', '-', '-', 'o', '-', '-', '-', '-', '-', 'W'},
        {'|', ' ', 'W', '-', '-', '-', 'B', '-', '-', '-', 'B', ' ', '|'},
        {'|', ' ', '|', ' ', 'B', '-', 'o', '-', 'o', ' ', '|', ' ', '|'},
        {'W', '-', 'B', '-', 'o', ' ', ' ', ' ', 'B', '-', 'o', '-', 'o'},
        {'|', ' ', '|', ' ', 'o', '-', 'o', '-', 'o', ' ', '|', ' ', '|'},
        {'|', ' ', 'B', '-', '-', '-', 'o', '-', '-', '-', 'B', ' ', '|'},
        {'W', '-', '-', '-', '-', '-', 'o', '-', '-', '-', '-', '-', 'W'}};
    board.setBoard(initialBoard);

    // Check that an old Morris is not seen (on x(0) is already a Morris) when
    // inserting a new piece to another place
    Point p(4, 4);
    board.placePiece(p);
    EXPECT_FALSE(board.isMorris(p));
}

TEST_F(BoardTest, TestGameDrawWithBothPlayersInJumpPhase) {
    board.getCurrentPlayer().setCurrentPhase(Player::GamePhase::JumpPhase);
    board.getCurrentPlayer().getNextPlayer()->setCurrentPhase(
        Player::GamePhase::JumpPhase);

    EXPECT_TRUE(board.checkForDraw());
}

TEST_F(BoardTest, TestGameDrawWithBothPlayersInDifferentPhases) {
    board.getCurrentPlayer().setCurrentPhase(Player::GamePhase::TurnPhase);
    board.getCurrentPlayer().getNextPlayer()->setCurrentPhase(
        Player::GamePhase::JumpPhase);

    EXPECT_FALSE(board.checkForDraw());
}

TEST_F(BoardTest, TestGameWin) {
    char initialBoard[ROW][COLUMN] = {
        {'W', '-', '-', '-', '-', '-', 'o', '-', '-', '-', '-', '-', 'W'},
        {'|', ' ', 'W', '-', '-', '-', 'o', '-', '-', '-', 'o', ' ', '|'},
        {'|', ' ', '|', ' ', 'o', '-', 'o', '-', 'o', ' ', '|', ' ', '|'},
        {'W', '-', 'B', '-', 'o', ' ', ' ', ' ', 'o', '-', 'o', '-', 'o'},
        {'|', ' ', '|', ' ', 'o', '-', 'o', '-', 'o', ' ', '|', ' ', '|'},
        {'|', ' ', 'B', '-', '-', '-', 'o', '-', '-', '-', 'o', ' ', '|'},
        {'W', '-', '-', '-', '-', '-', 'o', '-', '-', '-', '-', '-', 'W'}};
    board.setBoard(initialBoard);

    // opponent has only two pieces left. See GameBoard
    board.getCurrentPlayer().getNextPlayer()->setMaxPieces(2);

    board.updateGamePhases();

    auto phase = board.getCurrentPlayer().getCurrentPhase();

    EXPECT_EQ(phase, Player::GamePhase::GameEnd);
}
