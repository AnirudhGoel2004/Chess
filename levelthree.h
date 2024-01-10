#ifndef __LEVELTHREE_H__
#define __LEVELTHREE_H__
#include "abstractcomputer.h"
#include "board.h"
#include "piece.h"
#include <vector>
#include <set>
#include "empty.h"

class LevelThree : public AbstractComputer {

  public:
    // generate nextMove for computer
    void nextMove(Colour c, Board &b, bool inCheck) const override;
    ~LevelThree() = default;


};





#endif
