// Object-Oriented Refactored BACCARAT Game

// Main header file inclusion
#include "Baccarat.h"

int main() {
    system("Color 3F"); //CLI color changer
    string name;
    cout << "Enter your name: ";
    getline(cin, name);
    BaccaratGame game(name, 10000);
    game.play();

    return 0;
}
