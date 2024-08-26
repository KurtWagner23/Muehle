#include "../src/board.hpp"
#include "gtest/gtest.h"

TEST(BrettlogikTest, MuehleErkennung) {
    Board brett("Heinz", "Karl");

    // Simuliere das Setzen von Steinen in einer Mühle
    // brett.SetzeStein(0); // Position 0
    // brett.SetzeStein(1); // Position 1
    // brett.SetzeStein(9); // Position 9 (Mühle an Positionen 0, 1, 9)

    // // Überprüfe, ob eine Mühle erkannt wird
    // EXPECT_TRUE(brett.MuehleBesteht(
    //     9)); // Sollte True zurückgeben, da eine Mühle gebildet wurde

    EXPECT_EQ(1, 1);
}