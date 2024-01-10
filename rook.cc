#include "rook.h"
#include "board.h"

using namespace std;

// creates a rook piece
Rook::Rook(Colour colour) : Piece{colour, PType::Rook} {};

// determines if rook move is valid
bool Rook::isMoveValid(int row, int col, Board &b) {
    vector<vector<Piece*>> theBoard = b.getBoard();
    // initalize current row and column
    int currentRow = this->getLocation().first;
    int currentCol = this->getLocation().second;

    // make sure rook is moving
    if (row == currentRow && col == currentCol) {
        return false;
    }

    // make sure move is located within board
    int gridSize = b.getGridSize();
    if (row >= gridSize || col >= gridSize || row < 0 || col < 0) {
        return false;
    }

    // Make sure the move is either horizontal or vertical
    if (row != currentRow && col != currentCol) {
        return false;
    }

    // Check if there are any pieces in the path of the rook
    int rowIncrement, colIncrement;

    if (row > currentRow) {
        rowIncrement = 1;
    } else if (row < currentRow) {
        rowIncrement = -1;
    } else {
        rowIncrement = 0;
    }

    if (col > currentCol) {
        colIncrement = 1;
    } else if (col < currentCol) {
        colIncrement = -1;
    } else {
        colIncrement = 0;
    }

    // Traverse the path of the rook
    for (int i = currentRow + rowIncrement, j = currentCol + colIncrement; i != row || j != col; i += rowIncrement, j += colIncrement) {
        if (!theBoard[i][j]->isEmpty()) {
            return false;  // There's a piece in the path
        }
    }

    // Check if the destination square is occupied by a same colour piece
    if (theBoard[row][col]->getColour() == this->getColour()) {
        
        return false;
    }

    return true;
}

// returns hasMoved
bool Rook::getHasMoved() const{
    return hasMoved;
}

// sets hasMoved 
void Rook::setHasMoved(){
    hasMoved = true;
}

Rook::~Rook() {}
