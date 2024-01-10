#include "king.h"
#include "board.h"
#include "empty.h"

using namespace std;

King::King(Colour colour) : Piece{colour, PType::King} {};

bool King::isMoveValid(int row, int col, Board &b) {
    vector<std::vector<Piece*>> theBoard = b.getBoard();
    // initalize current row and column
    int currentRow = this->getLocation().first;
    int currentCol = this->getLocation().second;

    // make sure king is moving
    if (row == currentRow && col == currentCol) {
        return false;
    }

    // make sure move is located within board
    int gridSize = b.getGridSize();
    if (row >= gridSize || col >= gridSize || row < 0 || col < 0) {
        return false;
    }

    // Check if the destination square is beside the opposite-color king
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int targetRow = row + i;
            int targetCol = col + j;
            if (targetRow >= 0 && targetRow < gridSize && targetCol >= 0 && targetCol < gridSize &&
                theBoard[targetRow][targetCol]->getType() == PType::King &&
                theBoard[targetRow][targetCol]->getColour() != this->getColour()) {
                return false;
            }
        }
    }

    // if its a castling move, check if it is valid or not
    if (!hasMoved && row == currentRow && (col - currentCol == 2 || col - currentCol == -2) && (row == 0 || row == 7)){ // attempt to castle
        const int kingsideRookCol = 7;
        const int queensideRookCol = 0;
        
        // Check if there are pieces in the way
        if (col == currentCol + 2) {
            for (int i = currentCol + 1; i <= currentCol + 2; i++) {
                if (!theBoard[currentRow][i]->isEmpty()) {
                    return false;  // There's a piece in the way
                }
            }
        } else if (col == currentCol - 2) {
            for (int i = currentCol - 1; i >= currentCol - 3; i--) {
                if (!theBoard[currentRow][i]->isEmpty()) {
                    return false;  // There's a piece in the way
                }
            }
        }
        // Check if the rook in the corner has moved
        int rookCol;
        if (col == currentCol + 2) {
            rookCol = kingsideRookCol;  // Kingside castling
        } else {
            rookCol = queensideRookCol;  // Queenside castling
        }

        if (theBoard[currentRow][rookCol]->getType() != PType::Rook || theBoard[currentRow][rookCol]->getHasMoved()) {
            return false;  // Rook has moved
        }

        // Check if the squares the king would move through are under attack
        int middleCol;
        if (col == currentCol + 2) {
            middleCol = currentCol + 1;
        } else {
            middleCol = currentCol - 1;
        }
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                if (!theBoard[i][j]->isEmpty() && theBoard[i][j]->getColour() != this->getColour() && theBoard[i][j]->isMoveValid(currentRow, middleCol, b)) {
                    return false;  // The squares are under attack
                }
            }
        }
        // Check if the square king moves to is under attack
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                if (!theBoard[i][j]->isEmpty() && theBoard[i][j]->getColour() != this->getColour() && theBoard[i][j]->isMoveValid(currentRow, col, b)) {
                    return false;  // The square is under attack
                }
            }
        }
        // The move is a valid castling move
        return true;
    }

    // make sure new location is one square away from current location
    if (row - currentRow > 1 || row - currentRow < -1 || col - currentCol > 1 || col - currentCol < -1){
        return false;
    }

    // make sure king does not move into piece of same colour
    if (theBoard[row][col]->getColour() == this->getColour()) {
        return false;
    }

    // make sure king is not under check after move
    if (b.isKingInCheckAfterMove(this->getColour(), currentRow, currentCol, row, col)) {
        return false;
    }   

    // the move is valid if none of the above conditions are true
    return true;
}

// returns getHasMoved
bool King::getHasMoved() const{
    return hasMoved;
}

// sets getHasMoved
void King::setHasMoved(){
    hasMoved = true;
}

King::~King() {}
