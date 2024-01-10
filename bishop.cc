#include "bishop.h"
#include "board.h"

using namespace std;

// bishop ctor
Bishop::Bishop(Colour colour) : Piece{colour, PType::Bishop} {};

// checks if a bishop move is valid
bool Bishop::isMoveValid(int row, int col, Board &b) {
    vector<std::vector<Piece*>> theBoard = b.getBoard();
    // initalize current row and column
    int currentRow = this->getLocation().first;
    int currentCol = this->getLocation().second;

    // make sure bishop is moving
    if (row == currentRow && col == currentCol) {
        return false;
    }

    // make sure move is located within board
    int gridSize = b.getGridSize();
    if (row >= gridSize || col >= gridSize || row < 0 || col < 0) {
        return false;
    }

    // check if the move is diagonal
    int rowDifference = row - currentRow;
    int colDifference = col - currentCol;
    if (rowDifference != colDifference && rowDifference != -colDifference) {
        return false;
    }

    // check if there are any pieces in the path of the bishop
    int rowIncrement, colIncrement;

    if (rowDifference > 0) {
        rowIncrement = 1;
    } else {
        rowIncrement = -1;
    }

    if (colDifference > 0) {
        colIncrement = 1;
    } else {
        colIncrement = -1;
    }
    
    // traverse the path of the bishop
    for (int i = currentRow + rowIncrement, j = currentCol + colIncrement; i != row; i += rowIncrement, j += colIncrement) {
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

Bishop::~Bishop() {}
