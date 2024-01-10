#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"
#include <utility>

class Bishop : public Piece {

  public: 
    Bishop(Colour colour);
    // determines if move made on bishop is valid
    bool isMoveValid(int row, int col, Board &b) override;
    ~Bishop() override;

};




#endif

