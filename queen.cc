#include "queen.h"
#include "board.h"

using namespace std;

// creates a queen piece
Queen::Queen(Colour colour) : Piece{colour, PType::Queen} {};

// determines if queen move is valid
bool Queen::isMoveValid(int row, int col, Board &b) {
    vector<std::vector<Piece*>> theBoard = b.getBoard();
    // initalize current row and column
    int currentRow = this->getLocation().first;
    int currentCol = this->getLocation().second;

    // make sure queen is moving
    if (row == currentRow && col == currentCol) {
        return false;
    }

    // make sure move is located within board
    int gridSize = b.getGridSize();
    if (row >= gridSize || col >= gridSize || row < 0 || col < 0) {
        return false;
    }

    // Check if the move is horizontal, vertical, or diagonal
    int rowDifference = row - currentRow;
    int colDifference = col - currentCol;

    if ((rowDifference != colDifference && rowDifference != -colDifference) && (row != currentRow && col != currentCol)) {
        return false;
    }

    // Check if there are any pieces in the path
    int rowIncrement, colIncrement;

    if (rowDifference > 0) {
        rowIncrement = 1;
    } else if (rowDifference < 0) {
        rowIncrement = -1;
    } else {
        rowIncrement = 0;
    }

    if (colDifference > 0) {
        colIncrement = 1;
    } else if (colDifference < 0) {
        colIncrement = -1;
    } else {
        colIncrement = 0;
    }

    for (int i = currentRow + rowIncrement, j = currentCol + colIncrement; i != row || j != col; i += rowIncrement, j += colIncrement) {
        if (!theBoard[i][j]->isEmpty()) {
            return false;  // There's a piece in the path
        }
    }

    // Check if the destination square is occupied by a same colour piece
    if (theBoard[row][col]->getColour() == this->getColour()) {
        return false;
    }

    return true;  // everything is valid
}

Queen::~Queen() {}
