#include "../include/Game.h"

Game::Game() {}

Game::Game(int rows, int columns)
{
    game_board = {rows, columns};

    player_one = {PLAYER_ONE_ID, PLAYER_ONE_DEFAULT_NAME, SYMBOL_X};
    player_two = {PLAYER_TWO_ID, PLAYER_TWO_DEFAULT_NAME, SYMBOL_O}; 
}

bool Game::startGame()
{
    cout << ART_TITLE << endl;

    while (!is_game_over)
    {
        // Player 1's turn
        bool did_win = playerTurn(player_one);
        bool are_all_cells_owned = game_board.areAllCellsOwned();
        bool did_tie = checkForTie(did_win, are_all_cells_owned);

        if (did_win || did_tie)
        {
            is_game_over = true;
            break;
        }

        // Player 2's turn
        did_win = playerTurn(player_two);
        are_all_cells_owned = game_board.areAllCellsOwned();
        did_tie = checkForTie(did_win, are_all_cells_owned);

        is_game_over = did_win || did_tie;
    }

    return true;
}

bool Game::playerTurn(Player &player)
{
    string raw_player_choice;
    cout << "----------------------" << endl;
    cout << player.Name << "'s Turn " << "(" << player.Symbol << ")" << endl;
    cout << "----------------------" << endl;

    game_board.printBoard();

    cout << endl;
    cout << player.Name << ", please choose a space: ";
    cin >> raw_player_choice;
    cout << endl;

    if (raw_player_choice.empty())
    {
        cout << "Incorrect input. Skipping " << player.Name << "'s turn" << endl;
        return false;
    }

    string trimmed_player_choice = trimWhiteSpace(raw_player_choice);

    Cell* cell = game_board.fillCell(player, trimmed_player_choice);

    if (cell != nullptr)
    {
        bool did_win = game_board.checkForWin(player, *cell);

        if (did_win)
        {
            game_board.printBoard();
            cout << endl;
            cout << player.Name << " won! Good Game!" << endl;
            return did_win;
        }
    }

    return false;
}

bool Game::checkForTie(bool didWin, bool areAllCellsOwned)
{
    if (areAllCellsOwned && !didWin)
    {
        game_board.printBoard();
        cout << endl;
        cout << "It's a draw!" << endl;
        return true;
    }

    return false;
}

// Helper for trimming white space since C++
// doesn't have a '.trim()' option for strings.
string Game::trimWhiteSpace(const string &rawString)
{
    size_t begin = rawString.find_first_not_of(WHITESPACE);
    size_t end = rawString.find_last_not_of(WHITESPACE);
    // Start at the index where the first non-whitespace is found.
    // Extract (end - begin + 1) number of letters and store in 'result'.
    string result = {rawString.substr(begin, end - begin + 1)};
    return result;
}