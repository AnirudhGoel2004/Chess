#ifndef __LEVELFOUR_H__
#define __LEVELFOUR_H__
#include "abstractcomputer.h"
#include "board.h"
#include "piece.h"
#include <vector>
#include <set>
#include "empty.h"

class LevelFour : public AbstractComputer {

  public:
    // generate nextMove for computer
    void nextMove(Colour c, Board &b, bool inCheck) const override;
    ~LevelFour() = default;


};





#endif
