#pragma once

#include <string>

class Player {
public:
    enum class GamePhase {
        PlacementPhase,
        TurnPhase,
        JumpPhase,
        GameEnd,
        Morris
    };
    enum class EndState { Win, Loose, Draw };

private:
    int RemainingPieces = 9;
    int MaxPieces = 9;
    GamePhase BeforePhase;
    GamePhase CurrentPhase;
    EndState Result = EndState::Draw;
    std::string Name;
    Player* NextPlayer;

public:
    Player(std::string neuerName = "defaultName");

    std::string getName(void) const;
    void setName(std::string);

    void setCurrentPhase(GamePhase);
    GamePhase getCurrentPhase(void);

    void setNextPlayer(Player&);
    Player* getNextPlayer(void) const;

    void decreaseMaxPieces(void);
    int getMaxPieces(void) const;

    void setPieces(int);

    EndState getEndState(void);
    void setEndState(Player::EndState);

    int getRemainingPieces(void) const;
    void decreaseRemainingPieces(void);

    void setBeforePhase(GamePhase);
    GamePhase getBeforePhase(void) const;
};
