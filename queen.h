#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "piece.h"
#include <utility>

class Queen : public Piece {

  public: 
    Queen(Colour colour);
    // determines if move made on queen is valid
    bool isMoveValid(int row, int col, Board &b) override;
    ~Queen() override;

};



#endif

