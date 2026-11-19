#include "../include/GameManager.h"

using namespace std;

void GameManager :: startGame()
{
    bool stop_playing = false;

    // Keep looping through tic tac toe games
    // until the player decides they don't want to play
    // another game anymore.
    while (!stop_playing)
    {
        Game current_game {TOTAL_ROWS, TOTAL_COLUMNS};
        bool is_game_finished = current_game.startGame();

        if (is_game_finished)
        {
            char raw_answer {};
            cout << "Would you like to play again? Y or N: ";
            cin >> raw_answer;
            cout << endl;
            
            char modified_answer = (char)tolower(raw_answer);

            if (modified_answer == 'n')
            {
                cout << "Goodbye!" << endl;
                stop_playing = true;
            }
            else if (modified_answer == 'y')
            {
                continue;
            }
            else
            {
                cout << "Incorrect input. Goodbye!" << endl;
            }
        }
    }
}