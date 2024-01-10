#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include <iostream>
#include "piece.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "window.h"

class Board {
    std::vector<std::vector<Piece*>> theBoard;
    const int gridSize = 8;
    TextDisplay *td;
    GraphicsDisplay *gd;
    Xwindow win;
    std::vector<int> lastMove = {-1, -1, -1, -1};

    public:
        Board();
        ~Board();
        // makes a move to the piece at given row and coloumn; makes sure piece is of given colour
        bool makeMove(int fromRow, int fromCol, int toRow, int toCol, Colour c);
        // initializes board to a standard chess board
        void init();
        // sets piece at given row and coloumn to given piece type
        void set(int row, int col, PType p, Colour c);
        // Checks if board is in a valid state or not for set
        bool checkValid();
        // determines if a player has won = 1, stalemate = 2, nothing = 0
        int getGameState(Colour c);
        // checks if king with given colour is in check
        bool isKingInCheck(Colour c);
        // checks if king with given colour is in check after the given move is performed
        bool isKingInCheckAfterMove(Colour c, int fromRow, int fromCol, int toRow, int toCol);
        // returns the 2D vector of Piece pointers
        std::vector<std::vector<Piece*>> getBoard();
        // returns gridsize
        int getGridSize();
        // get lastMove
        std::vector<int> getLastMove();
        // Clears board (leaves 2 kings)
        void clear();
        // sets the theme of the board
        void setTheme(int o);
        // Get Possible Check moves
        std::vector<std::vector<int>> getCheckMoves(std::vector<std::vector<int>> moves, Colour c);
        // Get Avoid Capture moves
        std::vector<std::vector<int>> getAvoidCaptureMoves(std::vector<std::vector<int>> moves, Colour c);
        // Defend Check filter for computer
        std::vector<std::vector<int>> filterCheck(std::vector<std::vector<int>> moves, Colour c);

        // friend class so it can acess private members
        friend std::ostream &operator<<(std::ostream &out, const Board &b);

};

#endif
