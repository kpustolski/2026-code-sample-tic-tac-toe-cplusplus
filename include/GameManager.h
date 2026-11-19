#ifndef _GAMEMANAGER_H_ //ensuring that this object is only initialized once
#define _GAMEMANAGER_H_

#include <iostream>
#include "Game.h"

using namespace std;

/// Handles overall play session for the tic-tac-toe players.
class GameManager {
    public:
        void startGame();
    private:
        const int TOTAL_ROWS = 3;
        const int TOTAL_COLUMNS = 3;
};
#endif // end _GAMEMANAGER_H_