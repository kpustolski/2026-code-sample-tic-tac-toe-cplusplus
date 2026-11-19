#ifndef _GAMEBOARD_H_ //ensuring that this object is only initialized once
#define _GAMEBOARD_H_ 

#include <iostream>
#include <map>
#include <optional>
#include "Cell.h"
#include "Player.h"

using namespace std;

class GameBoard {
    public:
        GameBoard();
        GameBoard(int rows, int columns);

        bool areAllCellsOwned();
        bool checkForWin(Player &player, const Cell &cell);
        Cell* fillCell(Player &player, string cellId);
        void printBoard();      

    private:
        int total_rows {0};
        int total_columns {0};

        // key: row id, value: position (index) of Cells
        // with the same row id in cell_list.
        map<int, vector<size_t>> row_map {};
        // key: column id, value: position (index) of Cells
        // with the same column id in cell_list.
        map<int, vector<size_t>> column_map {};
        // A list of all Cells in the table.
        vector<Cell> cell_list {};

        void createBoard();
        void sortIntoRowMap();
        void sortIntoColumnMap();
        bool checkForVerticalWin(Player &player, int columnId);
        bool checkForHorizontalWin(Player &player, int rowId);
        bool checkForDiagonalWin(Player &player);
        bool ownsMainDiagonal(Player &player);
        bool ownsAntiDiagonal(Player &player);

        Cell* getCellFromCellList(const string& cellId);
};
#endif // end _GAMEBOARD_H_