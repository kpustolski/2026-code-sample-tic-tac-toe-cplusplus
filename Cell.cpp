#include "Cell.h"

Cell::Cell() {}

Cell::Cell(int rId, int cId)
{
    id = to_string(rId) + to_string(cId);
    row_id = rId;
    column_id = cId;
    current_symbol = id;
}

void Cell::fillCell(Player &player)
{
    ptr_owner = &player;
    current_symbol = player.Symbol;
}

bool Cell::doesPlayerOwnCell(Player &player)
{
    return ptr_owner != nullptr && ptr_owner->Id == player.Id; 
}

bool Cell::isCellEmpty()
{
    return ptr_owner == nullptr;
}