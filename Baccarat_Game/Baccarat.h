// Header file: Baccarat.h
#ifndef BACCARAT_H
#define BACCARAT_H

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// Enum for Bet Choices
enum class BetChoice {
    Banker,
    Player,
    Draw
};

class CardCalculation {
public:
    int card1;
    int card2;
    int extraCard;
    int cardSum;

    CardCalculation();
    void drawInitialCards();
    void drawExtraCard();
};

class BaccaratGame {
private:
    string playerName;
    int money;

    void printCardsWithSum(int card1, int card2, int sum, int card3 = -1) const;
    void printCardsWithNaturalWin(int card1, int card2, int sum) const;
    BetChoice determineWinner(int bankerCardSum, int playerCardSum) const;
    int calculateWinnings(BetChoice winner, BetChoice playerChoice, int bet) const;

public:
    BaccaratGame(const string& name, int initialMoney);
    void play();
};

#endif // BACCARAT_GAME_H
