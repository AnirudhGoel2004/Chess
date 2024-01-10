#include "knight.h"
#include "board.h"

using namespace std;

// create a knight piece
Knight::Knight(Colour colour) : Piece{colour, PType::Knight} {};

// detrmines if knight move is valid
bool Knight::isMoveValid(int row, int col, Board &b) {
    vector<std::vector<Piece*>> theBoard = b.getBoard();
    // initalize current row and column
    int currentRow = this->getLocation().first;
    int currentCol = this->getLocation().second;

    // make sure knight is moving
    if (row == currentRow && col == currentCol) {
        return false;
    }

    // make sure move is located within board
    int gridSize = b.getGridSize();
    if (row >= gridSize || col >= gridSize || row < 0 || col < 0) {
        return false;
    }

    // Check if the destination square is occupied by a same colour piece
    if (theBoard[row][col]->getColour() == this->getColour()) {
        return false;
    }

    // Check if the move is an L-shaped jump (2 squares in one direction, 1 square in the other)
    int rowDifference = row - currentRow;
    int colDifference = col - currentCol;
    // 8 different positions
    if ((rowDifference == 1 && (colDifference == 2 || colDifference == -2)) ||
        (rowDifference == 2 && (colDifference == 1 || colDifference == -1)) ||
        (rowDifference == -1 && (colDifference == 2 || colDifference == -2)) ||
        (rowDifference == -2 && (colDifference == 1 || colDifference == -1))) {
            return true;
    } else {
        return false;
    }
}

Knight::~Knight() {}
