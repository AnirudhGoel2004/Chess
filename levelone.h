#ifndef __LEVELONE_H__
#define __LEVELONE_H__
#include "abstractcomputer.h"
#include "board.h"
#include "piece.h"
#include <vector>

class LevelOne : public AbstractComputer {

  public:
  // generate nextMove for computer
    void nextMove(Colour c, Board &b, bool inCheck) const override;
    ~LevelOne() = default;


};




#endif
