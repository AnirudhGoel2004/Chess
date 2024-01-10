#ifndef __PAWN_H__
#define __PAWN_H__
#include "piece.h"
#include <utility>

class Pawn : public Piece {

  public: 
    Pawn(Colour colour);
    // determines if move made on pawn is valid
    bool isMoveValid(int row, int col, Board &b) override;
    ~Pawn() override;


};



#endif

