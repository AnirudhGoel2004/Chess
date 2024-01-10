#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "piece.h"
#include <utility>

class Knight : public Piece {

  public: 
    Knight(Colour colour);
    // determines if move made on knight is valid
    bool isMoveValid(int row, int col, Board &b) override;
    ~Knight() override;

};



#endif

