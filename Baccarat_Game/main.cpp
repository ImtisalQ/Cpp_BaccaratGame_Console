/*=========================================================
BACCARAT Game
-------------
Player chooses between two sides either
'banker' or 'player'. After drawing two cards the one
who has the sum of cards nearest to 9 wins.

For further explanation regarding the game please refer to
README.txt

===========================================================*/

#include <iostream>
#include <ctime>
#include <string>

#define INIT_DUMMY_VALUE 999

using namespace std;

struct sCardCalculation{

    int card1 = INIT_DUMMY_VALUE;
    int card2 = INIT_DUMMY_VALUE;
    int cardSum = INIT_DUMMY_VALUE;
    int extraCard = INIT_DUMMY_VALUE;
};
enum eBetChoice {
    Banker = 1,
    Player,
    Draw
};

//function prototype
void printCardswithSum(int card1,int card2, int cardSum , int card3 = -1);
void printCardsWithNaturalWin(int card1,int card2, int cardSum);
bool playAgain(char x,int money);
eBetChoice winnerFunction(int bankerCard, int playerCard); //compares two cards
int declareWinner(int winner, eBetChoice decision, int bet, std::string gamblerName); //checks if user win or lose


int main(){

    system ("Color 3F"); //CLI color changer
    srand(time(NULL)); //random number initialization

    //variable declaration
    std::string name;
    int bet, winner, prize, gamblerBet;
    eBetChoice gamblerChoice = Banker; //Just initialization
    char play;
    bool logic = true;
    int money = 10000;

    std::cout << "==============================" << std::endl;
    std::cout << "To Start, please enter your card" << std::endl;

    //name input
    std::cout << "Enter your name: ";
    getline(std::cin, name);

    system("CLS");
    std::cout << "\nGood evening, " << name << std::endl;
    std::cout << "==============================\n\n";
    std::cout << "WELCOME TO VIRTUAL BACCARAT TABLE" << std::endl;
    std::cout << "=================================" << std::endl;

    do{ //main do-while loop

        std::cout << "Current balance= " << money << "$" << std::endl;
        std::cout << "1 - BANKER \n2 - PLAYER \n3 - TIE\n";
        std::cout << "Press 1 to bet on BANKER, 2 to bet on PLAYER or 3 to bet on TIE: ";

        //Checks if input is 1,2 or 3
        while(!(std::cin >> gamblerBet)|| (gamblerBet < 1 || gamblerBet > 3)){
            std::cin.clear();
            std::cout << "\n" << "Invalid choice, Please choose again ";
            std::cout<< "\n" << "1 - BANKER \n 2 - PLAYER \n 3 - TIE";
        }

       do{
        //checks if bet is below balance money
        std::cout << "Place your amount to bet, USD ($): ";
        std::cin >> bet;
       }while(bet > money);

       //translating gambler bet into enum of possible choices
       gamblerChoice = (eBetChoice)gamblerBet;

       //PLAYER CARDS
       std::cout << "\n";
       std::cout << "==============================\n";
       std::cout << "      =" << " PLAYER'S CARD" << "  =\n";
       std::cout << "==============================\n";

       sCardCalculation player;
       //random number generator for 2 cards
       player.card1 = rand() % 10 + 1;
       player.card2 = rand() % 10 + 1;
       player.cardSum = (player.card1 + player.card2)%10;

       //checks if 2 cards are natural win 8 or 9
       if (player.cardSum == 9 || player.cardSum == 8) {
           //natural win 8 or 9, print card of player
           printCardsWithNaturalWin(player.card1, player.card2, player.cardSum);
       }
       else {
           if (player.cardSum <= 5) {
               player.extraCard = rand() % 10 + 1; //Third and extra card
               player.cardSum = (player.cardSum + player.extraCard) % 10;
               printCardswithSum(player.card1, player.card2, player.cardSum, player.extraCard );
           }
           else {
               printCardswithSum(player.card1, player.card2, player.cardSum);
           }
       }

        //BANKER CARDS
        std::cout << "\n==============================\n";
        std::cout << "      =" << " BANKER'S CARD  " << "=\n";
        std::cout << "==============================\n";

        sCardCalculation banker;
        //Random card generator
        banker.card1 = rand() % 10 + 1;
        banker.card2 = rand() % 10 + 1;
        banker.cardSum = (banker.card1 + banker.card2)%10;

        //checks if card is natural win 8 or 9
        if (banker.cardSum == 9 || banker.cardSum == 8) {
            //natural win 8 or 9, print card of player
            printCardsWithNaturalWin(banker.card1, banker.card2, banker.cardSum);
        }
        else {
            if ((player.extraCard != INIT_DUMMY_VALUE &&
                  (
                    (banker.cardSum <= 2) || 
                    ((3 <= banker.cardSum <=5) && player.extraCard != 8)
                  )
                ) ||
                (player.extraCard == INIT_DUMMY_VALUE && banker.cardSum <= 5)
                )
            {
                banker.extraCard = rand() % 10 + 1; //Third and extra card
                banker.cardSum = (banker.cardSum + banker.extraCard) % 10;
                printCardswithSum(banker.card1, banker.card2, banker.cardSum, banker.extraCard);
            }
            else {
                printCardswithSum(banker.card1, banker.card2, banker.cardSum);
            }
        }

    //declaration of winner
    winner = winnerFunction(banker.cardSum, player.cardSum);

    //awards prize for winner, 1:1 for winner;
    prize = declareWinner(winner, gamblerChoice, bet, name);
    std::cout<< "USD " << prize << "$"<<std::endl;
    money += prize;
    std::cout << "Current Money, USD: " << money << "$"<<"\n\n";

    //Asks the user if he wants to play again
    std::cout << "PLAY AGAIN? Y/N ";
    std::cin >> play;
    logic = playAgain(play,money);

    }while(logic != false);

}

void printCardswithSum(int card1,int card2, int sum, int card3)
{

    std::cout << "=======" <<               "\t" << "=======" <<                "\t\t" << "==SUM==\n";
    std::cout << "|     |" <<               "\t" << "|     |" <<                "\t\t" << "|     |\n";
    std::cout << "|  " << card1 << "  |" << "\t" << "|  " << card2 << "  |" <<  "\t\t" << "|  " << sum << "  |\n";
    std::cout << "|     |" <<               "\t" << "|     |"                   "\t\t" << "|     |\n";
    std::cout << "=======" <<               "\t" << "======="                   "\t\t" << "=======\n";

    std::cout << "First Card  => " << card1 << "\n";
    std::cout << "Second Card => " << card2 << "\n";
    if (card3 != -1) {
        std::cout << "Extra Card  => " << card3;
    }
    //std::cout << "CARD "<< sum << "\n";
}
void printCardsWithNaturalWin(int card1,int card2, int sum)
{

    std::cout << "=======" << "\t" << "=======" <<                               "\t\t" << "==SUM==\n";
    std::cout << "|     |" << "\t" << "|     |" <<                               "\t\t" << "|     |\n";
    std::cout << "|  " << card1 << "  |" << "\t" << "|  " << card2 << "  |" <<   "\t\t" << "|  " << sum << "  |\n";
    std::cout << "|     |" << "\t" << "|     |"                                  "\t\t" << "|     |\n";
    std::cout << "=======" << "\t" << "======="                                  "\t\t" << "=======\n";

    std::cout << "This is a natural win 8/9 \n";
    std::cout << "First Card  => " << card1 << "\n";
    std::cout << "Second Card => " << card2;
    //std::cout << "CARD " << sum << "\n";
}

bool playAgain(char choice,int money)
{

    if(money > 0){

        if(choice == 'Y' || choice == 'y'){

            return true;
        }else if(choice == 'N' || choice == 'n'){

            std::cout << "THANK YOU FOR PLAYING!";
            return false;
        }
    }else{

        std::cout << "Insufficient funds!";
        return false;
    }

}

eBetChoice winnerFunction(int bankerCard, int playerCard)
{
    //function to determine nearest number to 9
    //returns 1,2,3 depending on conditon met

    std::cout << "\n==================================\n";
    if(bankerCard > playerCard){

        std::cout << "\nBANKER WINS the round, ";
        return Banker;
    }else if( bankerCard < playerCard){

        std::cout << "\nPLAYER WINS the round, ";
        return Player;

    }else if(bankerCard == playerCard){

        std::cout << "\n Its a DRAW, ";
        return Draw;
    }
}
int declareWinner(int winner, eBetChoice decision, int bet, std::string gamblerName){

    if((eBetChoice)winner == decision){

        //win pays the bet
        std::cout << gamblerName <<" WINS!\n";
        return bet;
    }
    else{

        std::cout << gamblerName << " LOSES!\n";
        bet *= -1;
        return bet;
    }

}




