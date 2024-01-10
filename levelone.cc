#include "levelone.h"

// Idea:
//   Generate array of all valid moves 
void LevelOne::nextMove(Colour c, Board &b, bool inCheck) const {
    // Calculate best move to make
    std::vector<std::vector<int>> moves;

    for (int i = 0; i < b.getGridSize(); ++i) {
        for (int j = 0; j < b.getGridSize(); ++j) {
            for (int k = 0; k < b.getGridSize(); ++k) {
                for (int l = 0; l < b.getGridSize(); ++l) {
                    if  (b.getBoard()[i][j]->getColour() == c && b.getBoard()[i][j]->isMoveValid(k, l, b)) {
                        std::vector<int> m = {i,j,k,l};
                        moves.emplace_back(m);
                    }
                }
            }
        }
    }

    if (inCheck) {
        moves = b.filterCheck(moves, c);
    }

    int random = std::rand() % moves.size();

    b.makeMove(moves[random][0], moves[random][1], moves[random][2], moves[random][3], c);

    // Call Board's make move
}


