#ifndef _CELL_H_ //ensuring that this object is only initialized once
#define _CELL_H_ 

#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

class Cell {
    public:
        Cell();
        Cell(int rowId, int columnId);

        string id;
        Player *ptr_owner {nullptr};
        string current_symbol;

        int row_id {0};
        int column_id {0};

        void fillCell(Player &player);
        bool doesPlayerOwnCell(Player &player);
        bool isCellEmpty();
};
#endif // end _CELL_H_