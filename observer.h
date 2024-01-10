#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "piece.h"

// Forward declaration of Piece class
class Piece;

class Observer {
  public:
    // p is the Piece that called the notify method
    virtual void notify(Piece &p) = 0;
    virtual ~Observer() = default;
};

#endif
