#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include <vector>
#include <iostream>
#include "observer.h"
#include "piece.h"

class TextDisplay: public Observer {
    std::vector<std::vector<char>> theDisplay;
    const int boardSize = 8;

    public:
        TextDisplay();
        // update state based on new state of the piece
        void notify(Piece &p) override;
        ~TextDisplay();
    // friend class so that it can have acess to private memeber theDisplay
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
