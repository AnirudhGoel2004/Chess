#ifndef __ROOK_H__
#define __ROOK_H__
#include "piece.h"
#include <utility>

class Rook : public Piece {

  public: 
    bool hasMoved = false;
    Rook(Colour colour);
    // determines if move made on rook is valid
    bool isMoveValid(int row, int col, Board &b) override;
    bool getHasMoved() const override;
    void setHasMoved() override;
    
    ~Rook() override;

};



#endif

