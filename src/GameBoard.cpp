#include "../include/GameBoard.h"

GameBoard::GameBoard() {}

GameBoard::GameBoard(int rows, int columns)
{
    total_rows = rows;
    total_columns = columns;

    createBoard();
}

bool GameBoard::areAllCellsOwned()
{
    for (auto cell : cell_list)
    {
        if (cell.isCellEmpty())
        {
            return false;
        }
    }

    return true;
}

bool GameBoard::checkForWin(Player &player, const Cell &cell)
{
    bool did_win_horizontal = checkForHorizontalWin(player, cell.row_id);
    if (did_win_horizontal)
    {
        return true;
    }

    bool did_win_vertical = checkForVerticalWin(player, cell.column_id);
    if (did_win_vertical)
    {
        return true;
    }

    bool did_win_diagonal = checkForDiagonalWin(player);
    if (did_win_diagonal)
    {
        return true;
    }

    return false;
}

Cell* GameBoard::fillCell(Player &player, string cellId)
{
    Cell* cell = getCellFromCellList(cellId);

    if (cell == nullptr)
    {
        // Cell was not found. This will return a nullptr.
        return nullptr;
    }

    // If the cell is NOT empty,
    // then it already has an owner.
    if (!cell->isCellEmpty())
    {
        return nullptr;
    }

    // If the cell is empty, fill the cell
    // AKA, assign an owner to it.
    cell->fillCell(player);
    return cell;
}

void GameBoard::createBoard()
{
    // Create the cells
    for (int i {0}; i < total_rows; i++)
    {
        for (int j {0}; j < total_columns; j++)
        {
            Cell new_cell {i, j};
            cell_list.push_back(new_cell);
        }
    }

    sortIntoRowMap();
    sortIntoColumnMap();
}

void GameBoard::sortIntoRowMap()
{
    // Sort the rows into the row map.
    for (int i {0}; i < total_rows; i++)
    {
        vector<size_t> r_list;

        for (size_t cell {0}; cell < cell_list.size(); cell++)
        {
            if (cell_list[cell].row_id == i)
            {
                r_list.push_back(cell);
            }
        }

        row_map.insert({i, r_list});
    }
}

void GameBoard::sortIntoColumnMap()
{
    // Sort the columns into the column map.
    for (int i {0}; i < total_columns; i++)
    {
        vector<size_t> col_list;
        for (size_t cell {0}; cell < cell_list.size(); cell++)
        {
            if (cell_list[cell].column_id == i)
            {
                col_list.push_back(cell);
            }
        }

        column_map.insert({i, col_list});
    }
}

bool GameBoard::checkForVerticalWin(Player &player, int columnId)
{
    for (auto index : column_map[columnId])
    {
        if (!cell_list[index].doesPlayerOwnCell(player))
        {
            return false;
        }
    }

    // If we get to this point, we know that the player owns all of
    // the cells in the column.
    return true;
}

bool GameBoard::checkForHorizontalWin(Player &player, int rowId)
{
    for (auto index : row_map[rowId])
    {
        if (!cell_list[index].doesPlayerOwnCell(player))
        {
            return false;
        }
    }

    // If we get to this point, we know that the player owns all of
    // the cells in the row.
    return true;
}

bool GameBoard::checkForDiagonalWin(Player &player)
{
    // In order to check for this win condition, the number
    // of rows must equal the number of columns.
    // Aka, the board must be balanced.
    if (total_columns != total_rows)
    {
        return false;
    }

    bool wins_diagonal = ownsMainDiagonal(player) || ownsAntiDiagonal(player);
    return wins_diagonal;
}

/// From top left corner to bottom right corner.
bool GameBoard::ownsMainDiagonal(Player&player)
{
    vector<Cell> diagonal_cell_list;
    
    // Find all "main diagonal" cells.
    // These cells have matching row and column ids.
    for (int i {0}; i < cell_list.size(); i++)
    {
        if (cell_list[i].row_id == cell_list[i].column_id)
        {
            diagonal_cell_list.push_back(cell_list[i]);
        }
    }

    // Next we need to check if the player owns all
    // of the cells in the diagonal.
    for (auto cell : diagonal_cell_list)
    {
        if (!cell.doesPlayerOwnCell(player))
        {
            return false;
        }
    }

    // If we get to this point, then the player
    // owns all of the cells in the diagonal_cell_list.
    return true;
}

/// From the bottom left corner to the top right corner.
bool GameBoard::ownsAntiDiagonal(Player &player)
{
    vector<Cell> diagonal_cell_list;
    Cell *ptr_c {nullptr};

    // Starting from the bottom left corner, the row id ~decreases~ by one as
    // the column id ~increases~ by one. For example, on a 3x3 board the 
    // anti-diagonal consists of cells 20, 11, and 02.
    // The player must own all of these cells to win this diagonal.
    for (int i {0}; i < row_map.size(); i++)
    {
        // Determine the column id value.
        int column_id_value = column_map.size() - i - 1;
        // Placing this in its own variable for consistency and readability.
        int row_id_value = i;
        // Reset the Cell pointer variable to null;
        ptr_c = nullptr;
        
        // Find the cell that matches the intended row and column values.
        // i in this loop is the equivalent of the row id here.
        for (auto index : row_map[i])
        {
            if (cell_list[index].row_id == row_id_value && cell_list[index].column_id == column_id_value)
            {
                ptr_c = &cell_list[index];
                break;
            }
        }

        // Only move forward if the cell exists.
        if (ptr_c == nullptr)
        {
            continue;
        }

        // Check if the cell is owned.
        // If the player owns it, add it to the
        // diagonal list.
        if (ptr_c->doesPlayerOwnCell(player))
        {
            diagonal_cell_list.push_back(*ptr_c);
        }
    }

    // The number of owned cells should equal the total number of rows (or columns)
    // on a balanced tic-tac-toe board.
    return total_rows == diagonal_cell_list.size();
}

// Option 1: pointer (nullptr if not found)
Cell* GameBoard::getCellFromCellList(const string& cellId)
{
    for (auto &cell : cell_list)
    {
        if (cell.id == cellId)
        {
            return &cell;
        }
    }

    return nullptr;
}

void GameBoard::printBoard()
{
    string wall = "|";

    for (const auto &row : row_map)
    {
        cout << wall;
        for (size_t index : row.second)
        {
            cout << " " << cell_list[index].current_symbol << " " << wall;
        }
        cout << endl;
    }
}