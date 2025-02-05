#include "player.hpp"

Player::Player(std::string name) {
    Name = name;
    RemainingPieces = 9;
    CurrentPhase = GamePhase::PlacementPhase;
    BeforePhase = GamePhase::PlacementPhase;
}

std::string Player::getName() const {
    return Name;
}
void Player::setName(std::string newName) {
    Name = newName;
}

void Player::setCurrentPhase(GamePhase phase) {
    CurrentPhase = phase;
}
Player::GamePhase Player::getCurrentPhase() {
    return CurrentPhase;
}

void Player::setNextPlayer(Player& nextPlayer_new) {
    NextPlayer = &nextPlayer_new;
}
Player* Player::getNextPlayer() const {
    return NextPlayer;
}

int Player::getRemainingPieces() const {
    return RemainingPieces;
}

void Player::decreaseMaxPieces() {
    MaxPieces -= 1;
}

void Player::decreaseRemainingPieces() {
    RemainingPieces -= 1;
}
int Player::getMaxPieces() const {
    return MaxPieces;
}

Player::EndState Player::getEndState() {
    return Result;
}
void Player::setEndState(Player::EndState result) {
    Result = result;
}

void Player::setBeforePhase(GamePhase phase) {
    BeforePhase = phase;
}
Player::GamePhase Player::getBeforePhase() const {
    return BeforePhase;
}

void Player::setPieces(int i) {
    RemainingPieces = i;
}

void Player::setMaxPieces(int p) {
    MaxPieces = p;
}