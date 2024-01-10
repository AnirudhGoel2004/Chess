#include <vector>
#include "board.h"
#include "king.h"
#include "empty.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "pawn.h"
#include "knight.h"

using namespace std;

// construct a board
Board::Board() : theBoard{vector<vector<Piece*>>(8, vector<Piece*>(8))}, td{nullptr}, gd{nullptr}, win{} {}

// destruct a board
Board::~Board() {
    // delete text and graphics displays
    delete td;
    delete gd;

    // delete pieces
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            delete theBoard[i][j];
        }
    }
}

// make a move and return true if its valid, otherwise don't make the move and return false
bool Board::makeMove(int fromRow, int fromCol, int toRow, int toCol, Colour c) {
    // if you're moving a piece of your own colour, and its a valid move, then make the move
    if (c == theBoard[fromRow][fromCol]->getColour() && theBoard[fromRow][fromCol]->isMoveValid(toRow, toCol, *this)) {
        // if king is in check after move, return false
        if (isKingInCheckAfterMove(c, fromRow, fromCol, toRow, toCol)) return false;

        bool enpassant = false;

        // check for en passant
        if (theBoard[fromRow][fromCol]->getType() == PType::Pawn) {
            int moveDirection = (theBoard[fromRow][fromCol]->getColour() == Colour::White) ? -1 : 1;
            int enPassantRow = (theBoard[fromRow][fromCol]->getColour() == Colour::White) ? 1 : 6;
            if (toRow == fromRow + moveDirection && (toCol == fromCol + 1 || toCol == fromCol - 1) &&
                theBoard[toRow][toCol]->isEmpty() && !theBoard[fromRow][toCol]->isEmpty() && theBoard[fromRow][toCol]->getColour() != theBoard[fromRow][fromCol]->getColour()
                && theBoard[fromRow][toCol]->getType() == PType::Pawn 
                && lastMove[0] == enPassantRow && lastMove[1] == toCol && lastMove[2] == fromRow && lastMove[3] == toCol) {
                    enpassant = true;
            }
        }

        // move the piece to its destination, create a empty piece where the old piece left
        delete theBoard[toRow][toCol];
        theBoard[toRow][toCol] = theBoard[fromRow][fromCol];
        theBoard[fromRow][fromCol] = new Empty(Colour::Empty);
        theBoard[fromRow][fromCol]->attach(td);
        theBoard[fromRow][fromCol]->attach(gd);

        // update locations of moved piece and new empty piece
        theBoard[fromRow][fromCol]->setLocation(fromRow, fromCol);
        theBoard[toRow][toCol]->setLocation(toRow, toCol);
        
        // if the moved piece was a king or rook, the set the hasMoved property to true
        if (theBoard[toRow][toCol]->getType() == PType::King || theBoard[toRow][toCol]->getType() == PType::Rook) {
            theBoard[toRow][toCol]->setHasMoved();
        }

        // if pawn promotion, cin a command and replace pawn with requested piece
        if (theBoard[toRow][toCol]->getType() == PType::Pawn && (toRow == 0 || toRow == 7)) {
            string cmd;
            cin >> cmd;
            delete theBoard[toRow][toCol];

            if (cmd == "Q" || cmd == "q") {
                theBoard[toRow][toCol] = new Queen{c};
            } else if (cmd == "R" || cmd == "r") {
                theBoard[toRow][toCol] = new Rook{c};
            } else if (cmd == "B" || cmd == "b") {
                theBoard[toRow][toCol] = new Bishop{c};
            } else if (cmd == "N" || cmd == "n") {
                theBoard[toRow][toCol] = new Knight{c};
            } else { // if an invalid command is given, just promote to a queen
                theBoard[toRow][toCol] = new Queen{c};
            }

            // atatch observer, setLocation, and notifyobservers for newly promoted pawn
            theBoard[toRow][toCol]->attach(td);
            theBoard[toRow][toCol]->attach(gd);
            theBoard[toRow][toCol]->setLocation(toRow, toCol);
            theBoard[toRow][toCol]->notifyObservers();
        }

        // if en passant delete the captured pawn, and notify observers
        if (enpassant) {
            delete theBoard[fromRow][toCol];
            theBoard[fromRow][toCol] = new Empty(Colour::Empty);
            theBoard[fromRow][toCol]->attach(td);
            theBoard[fromRow][toCol]->attach(gd);
            theBoard[fromRow][toCol]->setLocation(fromRow, toCol);
            theBoard[fromRow][toCol]->notifyObservers();
        }

        // kingside castle
        if (theBoard[toRow][toCol]->getType() == PType::King && (toCol - fromCol == 2)) {
            // move rook
            delete theBoard[toRow][toCol - 1];
            theBoard[toRow][toCol - 1] = theBoard[toRow][toCol + 1];
            theBoard[toRow][toCol + 1] = new Empty(Colour::Empty);
            theBoard[toRow][toCol + 1]->attach(td);
            theBoard[toRow][toCol + 1]->attach(gd);

            theBoard[toRow][toCol - 1]->setLocation(toRow, toCol - 1);
            theBoard[toRow][toCol + 1]->setLocation(toRow, toCol + 1);
            theBoard[toRow][toCol + 1]->notifyObservers();
            theBoard[toRow][toCol - 1]->notifyObservers();
        }

        // queenside castle
        if (theBoard[toRow][toCol]->getType() == PType::King && (toCol - fromCol == -2)) {
            // move rook
            delete theBoard[toRow][toCol + 1];
            theBoard[toRow][toCol + 1] = theBoard[toRow][toCol - 2];
            theBoard[toRow][toCol - 2] = new Empty(Colour::Empty);
            theBoard[toRow][toCol - 2]->attach(td);
            theBoard[toRow][toCol - 2]->attach(gd);

            theBoard[toRow][toCol + 1]->setLocation(toRow, toCol + 1);
            theBoard[toRow][toCol - 2]->setLocation(toRow, toCol - 2);
            theBoard[toRow][toCol + 1]->notifyObservers();
            theBoard[toRow][toCol - 2]->notifyObservers();
        }

        // update last position for en passant
        lastMove[0] = fromRow;
        lastMove[1] = fromCol;
        lastMove[2] = toRow;
        lastMove[3] = toCol;


        // notify observers for the move
        theBoard[fromRow][fromCol]->notifyObservers();
        theBoard[toRow][toCol]->notifyObservers();
        return true;
    }

    return false;
};

// get theBoard
std::vector<std::vector<Piece*>> Board::getBoard() {
    return theBoard;
}

// get the gridSize
int Board::getGridSize() {
    return gridSize;
}

// get the last move played on the board
std::vector<int> Board::getLastMove() {
    return lastMove;
}

// initialize the board
void Board::init() {
    // initialize members
    td = new TextDisplay{};
    gd = new GraphicsDisplay{win};

    // set empty squares
    for (int i = 2; i < gridSize - 2; i++) {
        for (int j = 0; j < gridSize; j++) {
            theBoard[i][j] = new Empty(Colour::Empty);
        }
    }

    // set the black pieces
    theBoard[0][0] = new Rook(Colour::Black);
    theBoard[0][1] = new Knight(Colour::Black);
    theBoard[0][2] = new Bishop(Colour::Black);
    theBoard[0][3] = new Queen(Colour::Black);
    theBoard[0][4] = new King(Colour::Black);
    theBoard[0][5] = new Bishop(Colour::Black);
    theBoard[0][6] = new Knight(Colour::Black);
    theBoard[0][7] = new Rook(Colour::Black);

    for (int i = 0; i < gridSize; i++) {
        theBoard[1][i] = new Pawn(Colour::Black);
    }

    // set the white pieces
    theBoard[7][0] = new Rook(Colour::White);
    theBoard[7][1] = new Knight(Colour::White);
    theBoard[7][2] = new Bishop(Colour::White);
    theBoard[7][3] = new Queen(Colour::White);
    theBoard[7][4] = new King(Colour::White);
    theBoard[7][5] = new Bishop(Colour::White);
    theBoard[7][6] = new Knight(Colour::White);
    theBoard[7][7] = new Rook(Colour::White);

    for (int i = 0; i < gridSize; i++) {
        theBoard[6][i] = new Pawn(Colour::White);
    }

    // attatch observers and set location of pieces
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            theBoard[i][j]->setLocation(i, j);
            theBoard[i][j]->attach(td);
            theBoard[i][j]->attach(gd);
        }
    }
};

// set pieces on the board
void Board::set(int row, int col, PType p, Colour c) {
    // Delete old piece at [row][col]
    delete theBoard[row][col];    
    
    // Create new piece at [row][col]
    switch (p) {
        case PType::King:
            theBoard[row][col] = new King(c);
            break;
        case PType::Queen:
            theBoard[row][col] = new Queen(c);
            break;
        case PType::Rook:
            theBoard[row][col] = new Rook(c);
            break;
        case PType::Bishop:
            theBoard[row][col] = new Bishop(c);
            break;
        case PType::Knight:
            theBoard[row][col] = new Knight(c);
            break;
        case PType::Pawn:
            theBoard[row][col] = new Pawn(c);
            break;
        default:
            theBoard[row][col] = new Empty(c);
            break;
    }

    // Add observer, update location, notify observer
        theBoard[row][col]->attach(td);
        theBoard[row][col]->attach(gd);
        theBoard[row][col]->setLocation(row, col);
        theBoard[row][col]->notifyObservers();
}

// check if board state is valid
bool Board::checkValid() {
    // initialize variable to count number of kings, and boolean to track if pawns are on first or lass rank
    int whiteKingNum = 0;
    int blackKingNum = 0;
    bool pawnEndRows = false;

    // check for 1 white king, 1 black king
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (theBoard[i][j]->getType() == PType::King) {
                if (theBoard[i][j]->getColour() == Colour::White) {
                    whiteKingNum++;
                } else if (theBoard[i][j]->getColour() == Colour::Black) {
                    blackKingNum++;
                }
            }
        }
    }

    // check for pawns on the first and last rank
    for (int i = 0; i < gridSize; ++i) {
        if (theBoard[0][i]->getType() == PType::Pawn) {
            pawnEndRows = true;
        } else if (theBoard[gridSize - 1][i]->getType() == PType::Pawn) {
            pawnEndRows = true;
        }
    }

    // if theres more then 1 black king or white king, or there are pawns on the first or last rank return false
    if (pawnEndRows || whiteKingNum != 1 || blackKingNum != 1) {
        return false;
    }

    // if any of the kings are in check return false
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (theBoard[i][j]->getType() == PType::King && this->isKingInCheck(theBoard[i][j]->getColour())) {
                return false;
            }
        }
    }

    return true; // everything is valid so return true
}

// remove all pieces except the kings
void Board::clear() {
    // set empty squares
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            delete theBoard[i][j];
            theBoard[i][j] = new Empty(Colour::Empty);
        }
    }

    // set kings
    delete theBoard[0][4];
    delete theBoard[7][4];
    theBoard[0][4] = new King(Colour::Black);
    theBoard[7][4] = new King(Colour::White);

    // attach observers and set location of pieces
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            theBoard[i][j]->setLocation(i, j);
            theBoard[i][j]->attach(td);
            theBoard[i][j]->attach(gd);
            theBoard[i][j]->notifyObservers();
        }
    }
}

// return 1 if checkmate, 2 if stalemate, 3 if check
int Board::getGameState(Colour c) {
    // initialize variable to keep track of checkmate, stalemate and check
    bool stalemate = false;
    bool inCheck = false;
    bool blockCheck = false;

    // Generate all possible moves
    std::vector<std::vector<int>> moves;

    for (int i = 0; i < getGridSize(); ++i) {
        for (int j = 0; j < getGridSize(); ++j) {
            for (int k = 0; k < getGridSize(); ++k) {
                for (int l = 0; l < getGridSize(); ++l) {
                    if  (theBoard[i][j]->getColour() == c && theBoard[i][j]->isMoveValid(k, l, *this)) {
                        std::vector<int> m = {i,j,k,l};
                        moves.emplace_back(m);
                    }
                }
            }
        }
    }
    
    // If no moves can be made, stalemate
    if (moves.size() == 0) {
        stalemate = true;
    }

    // If king in current position is in check
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (theBoard[i][j]->getType() == PType::King && theBoard[i][j]->getColour() == c && this->isKingInCheck(c)) {
                inCheck = true;
                break;
            }
        }
    }

    // iterate over all valid moves to check for blocking check
    for (int i = 0; i < moves.size(); ++i) {
        int currentRow = moves[i][0];
        int currentCol = moves[i][1];
        int row = moves[i][2];
        int col = moves[i][3];

        // make sure king does not move into check (including the case that the king captures into a check) excluding opposite king check
        Piece* tmp = theBoard[row][col];
        theBoard[row][col] = theBoard[currentRow][currentCol];
        theBoard[currentRow][currentCol] = new Empty(Colour::Empty);
        theBoard[row][col]->setLocation(row, col);
        theBoard[currentRow][currentCol]->setLocation(currentRow, currentCol);
        for (int j = 0; j < gridSize; j++) {
            for (int k = 0; k < gridSize; k++) {
                if (theBoard[j][k]->getType() == PType::King && theBoard[j][k]->getColour() == c && !this->isKingInCheck(c)) {
                    blockCheck = true;
                }
            }
        }
        delete theBoard[currentRow][currentCol];
        theBoard[currentRow][currentCol] = theBoard[row][col];
        theBoard[row][col] = tmp;
        theBoard[currentRow][currentCol]->setLocation(currentRow, currentCol);
        tmp = nullptr;
        
    }
    if ((inCheck && !blockCheck) || (stalemate && inCheck)) {
        return 1; // checkmate if you are in check and you can't block the check, or if you cant't move (stalemate) and your in check
    } else if (stalemate && !inCheck) {
        return 2; // stalemate if you arent in check and its stalemate
    } else if (inCheck) {
        return 3; // in check
    }
    return 0;
}

// return true if king of colour c is in check, false otherwise
bool Board::isKingInCheck(Colour c) {
    // get the row and coloumn of the king
    int row = -1;
    int col = -1;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (theBoard[i][j]->getType() == PType::King && theBoard[i][j]->getColour() == c) {
                row = i;
                col = j;
            }
        }
    }

    // Check if opposite king is beside king
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int targetRow = row + i;
            int targetCol = col + j;
            if (targetRow >= 0 && targetRow < gridSize && targetCol >= 0 && targetCol < gridSize &&
                theBoard[targetRow][targetCol]->getType() == PType::King &&
                theBoard[targetRow][targetCol]->getColour() != theBoard[row][col]->getColour()) {
                return true;
            }
        }
    }

    // Check if an opposite-color piece (excluding king) can move to where the king is
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (!theBoard[i][j]->isEmpty() && theBoard[i][j]->getType() != PType::King &&
                theBoard[i][j]->getColour() != theBoard[row][col]->getColour() && theBoard[i][j]->isMoveValid(row, col, *this)) {
                return true;
            }
        }
    }

    return false;
}

// returns true if king is in check afer given move, and false otherwise
bool Board::isKingInCheckAfterMove(Colour c, int fromRow, int fromCol, int toRow, int toCol) {
    bool ret = false;

    Piece *tmp = theBoard[toRow][toCol];

    // move piece to where it wants to go 
    theBoard[toRow][toCol] = theBoard[fromRow][fromCol];
    theBoard[fromRow][fromCol] = new Empty(Colour::Empty);
    theBoard[fromRow][fromCol]->attach(td);
    theBoard[fromRow][fromCol]->attach(gd);

    // update locations of moved piece and new empty piece
    theBoard[fromRow][fromCol]->setLocation(fromRow, fromCol);
    theBoard[toRow][toCol]->setLocation(toRow, toCol);

    // if king is in check we want to return true
    if (isKingInCheck(c)) {
        ret = true;
    }

    // undo move before returning; delete empty piece, and move piece back to where it was
    delete theBoard[fromRow][fromCol];
    theBoard[fromRow][fromCol] = theBoard[toRow][toCol];
    theBoard[toRow][toCol] = tmp;
    tmp = nullptr;
    // update locations
    theBoard[fromRow][fromCol]->setLocation(fromRow, fromCol);
    theBoard[toRow][toCol]->setLocation(toRow, toCol);

    return ret;
}

// get all the moves that check the opposing king
std::vector<std::vector<int>> Board::getCheckMoves(std::vector<std::vector<int>> moves, Colour c) {
    std::vector<std::vector<int>> checkMoves;
    // iterate over all valid moves
    for (int i = 0; i < moves.size(); ++i) {
        int currentRow = moves[i][0];
        int currentCol = moves[i][1];
        int row = moves[i][2];
        int col = moves[i][3];
        
        
        // do the move
        Piece* tmp = theBoard[row][col];
        theBoard[row][col] = theBoard[currentRow][currentCol];
        theBoard[currentRow][currentCol] = new Empty(Colour::Empty);
        theBoard[row][col]->setLocation(row, col);
        theBoard[currentRow][currentCol]->setLocation(currentRow, currentCol);
        for (int j = 0; j < gridSize; j++) {
            for (int k = 0; k < gridSize; k++) {
                // if the move checks the king, add it to vector
                if (theBoard[j][k]->getType() == PType::King && theBoard[j][k]->getColour() != c && this->isKingInCheck(theBoard[j][k]->getColour())) {
                    std::vector<int> m = {currentRow, currentCol, row, col};
                    checkMoves.emplace_back(m);
                }
            }
        }
        // undo the move
        delete theBoard[currentRow][currentCol];
        theBoard[currentRow][currentCol] = theBoard[row][col];
        theBoard[row][col] = tmp;
        theBoard[currentRow][currentCol]->setLocation(currentRow, currentCol);
        tmp = nullptr;
        
    }
    return checkMoves;
}

// get all the moves that avoid capturing moves
std::vector<std::vector<int>> Board::getAvoidCaptureMoves(std::vector<std::vector<int>> moves, Colour c) {
    std::vector<std::vector<int>> avoidMoves;
    // iterate over all valid moves
    for (int i = 0; i < moves.size(); ++i) {
        int currentRow = moves[i][0];
        int currentCol = moves[i][1];
        int row = moves[i][2];
        int col = moves[i][3];
        bool canCapture = false;
        
        // do the move
        Piece* tmp = theBoard[row][col];
        theBoard[row][col] = theBoard[currentRow][currentCol];
        theBoard[currentRow][currentCol] = new Empty(Colour::Empty);
        theBoard[row][col]->setLocation(row, col);
        theBoard[currentRow][currentCol]->setLocation(currentRow, currentCol);
        for (int j = 0; j < gridSize; j++) {
            for (int k = 0; k < gridSize; k++) {
                // if the move doesn't avoid capture, set canCapture to true
                if (theBoard[j][k]->getType() != PType::Empty && theBoard[j][k]->getColour() != c && theBoard[j][k]->isMoveValid(row, col, *this)) {
                    canCapture = true;
                }
            }
        }
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                if (theBoard[i][j]->getType() == PType::King && theBoard[i][j]->getColour() == c && this->isKingInCheck(c)) {
                    canCapture = true;
                }
            }
        }
        // undo the move
        delete theBoard[currentRow][currentCol];
        theBoard[currentRow][currentCol] = theBoard[row][col];
        theBoard[row][col] = tmp;
        theBoard[currentRow][currentCol]->setLocation(currentRow, currentCol);
        tmp = nullptr;

        // if no move can capture, then add it to vector
        if (!canCapture) {
            std::vector<int> m = {currentRow, currentCol, row, col};
            avoidMoves.emplace_back(m);
        }
        
    }
    return avoidMoves;
}

// return moves that defend a check
std::vector<std::vector<int>> Board::filterCheck(std::vector<std::vector<int>> moves, Colour c) {
    std::vector<std::vector<int>> defendCheck;

    for (int i = 0; i < moves.size(); ++i) {

        int fromRow = moves[i][0];
        int fromCol = moves[i][1];
        int toRow = moves[i][2];
        int toCol = moves[i][3];

        // make the move
        Piece* tmp = theBoard[toRow][toCol];

        theBoard[toRow][toCol] = theBoard[fromRow][fromCol];
        theBoard[fromRow][fromCol] = new Empty(Colour::Empty);
        theBoard[fromRow][fromCol]->attach(td);
        theBoard[fromRow][fromCol]->attach(gd);

        // update locations
        theBoard[fromRow][fromCol]->setLocation(fromRow, fromCol);
        theBoard[toRow][toCol]->setLocation(toRow, toCol);

        // check if a pinned piece was moved
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                if (theBoard[i][j]->getType() == PType::King && theBoard[i][j]->getColour() == c && !this->isKingInCheck(c)) {
                    vector<int> m = {fromRow, fromCol, toRow, toCol};
                    defendCheck.emplace_back(m);
                }
            }
        }

        // undo the move
        delete theBoard[fromRow][fromCol];
        theBoard[fromRow][fromCol] = theBoard[toRow][toCol];
        theBoard[toRow][toCol] = tmp;
        tmp = nullptr;

        // update locations
        theBoard[fromRow][fromCol]->setLocation(fromRow, fromCol);
        theBoard[toRow][toCol]->setLocation(toRow, toCol);

    }

    return defendCheck;

}

// set the theme of the oard
void Board::setTheme(int o) {
    // set the offset and notify the observers
    gd->setOffest(o);
     for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            theBoard[i][j]->notifyObservers();
        }
    }
}

// print out the board
ostream &operator<<(ostream &out, const Board &b) {
    out << *b.td;
    return out;
}
