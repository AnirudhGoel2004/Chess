#include <iostream>
#include "graphicsdisplay.h"

using namespace std;

// ctor with refrence to Xwindow
GraphicsDisplay::GraphicsDisplay(Xwindow &w) : win{w} {
    for (int i = 0; i < numCells*cellWidth; i += cellWidth) {
        for (int j = 0; j < numCells*cellWidth; j += cellWidth) {
            if ((i / cellWidth + j / cellWidth) % 2 == 0) {
                win.fillRectangle(j, i, cellWidth, cellWidth, tile1 + offset);
            } else {
                win.fillRectangle(j, i, cellWidth, cellWidth, tile2 + offset);
            }
        }
    }

    // draw white pawns
    for (int i = 0; i < numCells*cellWidth; i += cellWidth) {
        win.drawPawn(i, 420, piece2 + offset);
    }
    // draw black pawns
    for (int i = 0; i < numCells*cellWidth; i += cellWidth) {
        win.drawPawn(i, 70, piece1 + offset);
    }
    // draw white rooks
    win.drawRook(0, 490, piece2 + offset);
    win.drawRook(490, 490, piece2 + offset);

    // draw black rooks
    win.drawRook(0, 0, piece1 + offset);
    win.drawRook(490, 0, piece1 + offset);

    // draw white knights
    win.drawKnight(70, 490, piece2 + offset);
    win.drawKnight(420, 490, piece2 + offset);

    // draw black kights
    win.drawKnight(70, 0, piece1 + offset);
    win.drawKnight(420, 0, piece1 + offset);

    // draw white bishops
    win.drawBishop(140, 490, piece2 + offset);
    win.drawBishop(350, 490, piece2 + offset);
    
    // draw black bishops
    win.drawBishop(140, 0, piece1 + offset);
    win.drawBishop(350, 0, piece1 + offset);

    // draw white queen
    win.drawQueen(210, 490, piece2 + offset);
    
    // draw black queen
    win.drawQueen(210, 0, piece1 + offset);

    // draw white king
    win.drawKing(280, 490, piece2 + offset);
    
    // draw black king
    win.drawKing(280, 0, piece1 + offset);
}

// draw the piece at its new location
void GraphicsDisplay::notify(Piece &p) {
    // get location and type of piece
    pair<int, int> loc = p.getLocation();
    PType t = p.getType();

    // get colour of piece
    int colour = (p.getColour() == Colour::Black) ? 0 : 1;

    // Make square blank first
    if ((loc.first + loc.second) % 2 == 0) {
        // change colour for white tile
        win.fillRectangle(loc.second*cellWidth, loc.first*cellWidth, cellWidth, cellWidth, tile1 + offset);
    } else {
        // change colour for black tile
        win.fillRectangle(loc.second*cellWidth, loc.first*cellWidth, cellWidth, cellWidth, tile2 + offset);
    } 

    // update display based on the new location of the piece
    if (t == PType::Knight) {
        win.drawKnight(loc.second*cellWidth, loc.first*cellWidth, colour + piece1 + offset);
    } else if (t == PType::Bishop) {
        win.drawBishop(loc.second*cellWidth, loc.first*cellWidth, colour + piece1 + offset);
    } else if (t == PType::Rook) {
        win.drawRook(loc.second*cellWidth, loc.first*cellWidth, colour + piece1 + offset);
    } else if (t == PType::King) {
        win.drawKing(loc.second*cellWidth, loc.first*cellWidth, colour + piece1 + offset);
    } else if (t == PType::Queen) {
        win.drawQueen(loc.second*cellWidth, loc.first*cellWidth, colour + piece1 + offset);
    } else if (t == PType::Pawn) {
        win.drawPawn(loc.second*cellWidth, loc.first*cellWidth, colour + piece1 + offset);
    } else {
        if ((loc.first + loc.second) % 2 == 0) {
            // change colour for white tile
            colour = 0;
            win.fillRectangle(loc.second*cellWidth, loc.first*cellWidth, cellWidth, cellWidth, tile1 + offset);
        } else {
            // change colour for black tile
            win.fillRectangle(loc.second*cellWidth, loc.first*cellWidth, cellWidth, cellWidth, tile2 + offset);
        }
    }
};

// set offset for graphicsdisplay
void GraphicsDisplay::setOffest(int o) {
    offset = o;
}

GraphicsDisplay::~GraphicsDisplay() {};

