#ifndef _GAME_H_ //ensuring that this object is only initialized once
#define _GAME_H_ 

#include <iostream>
#include <string>
#include <optional>
#include "GameBoard.h"
#include "Player.h"

using namespace std;

class Game {
    public:
        Game();
        Game(int rows, int columns);

        bool startGame();
        bool playerTurn(Player &player);

        string trimWhiteSpace(const string &rawString);

    private:
        const char* WHITESPACE = " ";
        const string PLAYER_ONE_ID = "P1";
        const string PLAYER_TWO_ID = "P2";
        const string PLAYER_ONE_DEFAULT_NAME = "Player 1";
        const string PLAYER_TWO_DEFAULT_NAME = "Player 2";
        const string SYMBOL_X = "xx";
        const string SYMBOL_O = "oo";
        const string ART_TITLE = R"(
_   _      _             _             
| | (_)    | |           | |            
| |_ _  ___| |_ __ _  ___| |_ ___   ___ 
| __| |/ __| __/ _` |/ __| __/ _ \ / _ \
| |_| | (__| || (_| | (__| || (_) |  __/
\__|_|\___|\__\__,_|\___|\__\___/ \___|        
)";

        GameBoard game_board;
        Player player_one;
        Player player_two;

        bool is_game_over {false};
        bool checkForTie(bool didWin, bool areAllCellsOwned); 
};
#endif // end _GAME_H_