// Implementation file: Baccarat.cpp
#include "Baccarat.h"

CardCalculation::CardCalculation() : card1(999), card2(999), extraCard(999), cardSum(999) {}

void CardCalculation::drawInitialCards() {
    card1 = rand() % 10 + 1;
    card2 = rand() % 10 + 1;
    cardSum = (card1 + card2) % 10;
}

void CardCalculation::drawExtraCard() {
    extraCard = rand() % 10 + 1;
    cardSum = (cardSum + extraCard) % 10;
}

BaccaratGame::BaccaratGame(const string& name, int initialMoney) : playerName(name), money(initialMoney) {}

void BaccaratGame::printCardsWithSum(int card1, int card2, int sum, int card3) const {
    cout << "=======" << "\t" << "=======" << "\t\t" << "==SUM==\n";
    cout << "|     |" << "\t" << "|     |" << "\t\t" << "|     |\n";
    cout << "|  " << card1 << "  |" << "\t" << "|  " << card2 << "  |" << "\t\t" << "|  " << sum << "  |\n";
    cout << "|     |" << "\t" << "|     |" << "\t\t" << "|     |\n";
    cout << "=======" << "\t" << "=======" << "\t\t" << "=======\n";

    cout << "First Card  => " << card1 << "\n";
    cout << "Second Card => " << card2 << "\n";
    if (card3 != -1) {
        cout << "Extra Card  => " << card3 << "\n";
    }
}

void BaccaratGame::printCardsWithNaturalWin(int card1, int card2, int sum) const {
    cout << "=======" << "\t" << "=======" << "\t\t" << "==SUM==\n";
    cout << "|     |" << "\t" << "|     |" << "\t\t" << "|     |\n";
    cout << "|  " << card1 << "  |" << "\t" << "|  " << card2 << "  |" << "\t\t" << "|  " << sum << "  |\n";
    cout << "|     |" << "\t" << "|     |" << "\t\t" << "|     |\n";
    cout << "=======" << "\t" << "=======" << "\t\t" << "=======\n";
    cout << "This is a natural win 8/9 \n";
}

BetChoice BaccaratGame::determineWinner(int bankerCardSum, int playerCardSum) const {
    if (bankerCardSum > playerCardSum) {
        cout << "BANKER WINS the round!\n";
        return BetChoice::Banker;
    }
    else if (bankerCardSum < playerCardSum) {
        cout << "PLAYER WINS the round!\n";
        return BetChoice::Player;
    }
    else {
        cout << "It's a DRAW!\n";
        return BetChoice::Draw;
    }
}

int BaccaratGame::calculateWinnings(BetChoice winner, BetChoice playerChoice, int bet) const {
    if (winner == playerChoice) {
        cout << playerName << " WINS!\n";
        return bet;
    }
    else {
        cout << playerName << " LOSES!\n";
        return -bet;
    }
}

void BaccaratGame::play() {
    char playAgain = 'Y';
    srand(static_cast<unsigned>(time(nullptr)));

    while (playAgain == 'Y' || playAgain == 'y') {
        cout << "Current balance: " << money << "$\n";
        cout << "1 - BANKER\n2 - PLAYER\n3 - TIE\n";
        cout << "Choose your bet (1, 2, or 3): ";

        int choice;
        while (!(cin >> choice) || choice < 1 || choice > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Try again: ";
        }

        BetChoice playerChoice = static_cast<BetChoice>(choice - 1);

        int bet;
        do {
            cout << "Enter your bet amount: ";
            cin >> bet;
        } while (bet > money);

        // Player cards
        CardCalculation player;
        player.drawInitialCards();

        cout << "\nPLAYER'S CARDS:\n";
        if (player.cardSum == 8 || player.cardSum == 9) {
            printCardsWithNaturalWin(player.card1, player.card2, player.cardSum);
        }
        else if (player.cardSum <= 5) {
            player.drawExtraCard();
            printCardsWithSum(player.card1, player.card2, player.cardSum, player.extraCard);
        }
        else {
            printCardsWithSum(player.card1, player.card2, player.cardSum);
        }

        // Banker cards
        CardCalculation banker;
        banker.drawInitialCards();

        cout << "\nBANKER'S CARDS:\n";
        if (banker.cardSum == 8 || banker.cardSum == 9) {
            printCardsWithNaturalWin(banker.card1, banker.card2, banker.cardSum);
        }
        else if (banker.cardSum <= 5 || (player.extraCard != 999 && banker.cardSum <= 2)) {
            banker.drawExtraCard();
            printCardsWithSum(banker.card1, banker.card2, banker.cardSum, banker.extraCard);
        }
        else {
            printCardsWithSum(banker.card1, banker.card2, banker.cardSum);
        }

        // Determine winner
        BetChoice winner = determineWinner(banker.cardSum, player.cardSum);
        int winnings = calculateWinnings(winner, playerChoice, bet);
        money += winnings;

        cout << "New balance: " << money << "$\n";

        if (money <= 0) {
            cout << "Insufficient funds. Game over!\n";
            break;
        }

        cout << "Play again? (Y/N): ";
        cin >> playAgain;
    }

    cout << "Thank you for playing, " << playerName << "!\n";
}
