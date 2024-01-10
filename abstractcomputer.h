#ifndef __ABSTRACTCOMPUTER_H__
#define __ABSTRACTCOMPUTER_H__
#include "piece.h"

// For Computer Bot
class AbstractComputer {

  public:
    // Virtual method for making the next move
    // will call the make move function from board
    virtual void nextMove(Colour c, Board &b, bool inCheck) const = 0;
    virtual ~AbstractComputer() {};


};




#endif

