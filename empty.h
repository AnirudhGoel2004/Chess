#ifndef __EMPTY_H__
#define __EMPTY_H__
#include "piece.h"
#include <utility>

class Empty : public Piece {

  public: 
    Empty(Colour colour);
    // determines if move made on empty piece is valid
    bool isMoveValid(int row, int col, Board &b) override;
    ~Empty() override;

};




#endif

