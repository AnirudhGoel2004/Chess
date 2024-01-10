#include "leveltwo.h"
  
// generate nextMove for computer
void LevelTwo::nextMove(Colour c, Board &b, bool inCheck) const {
    
    // Generate all random moves
    std::vector<std::vector<int>> randMoves;
    std::vector<std::vector<int>> captureMoves;
    std::vector<std::vector<int>> checkMoves;

    for (int i = 0; i < b.getGridSize(); ++i) {
        for (int j = 0; j < b.getGridSize(); ++j) {
            for (int k = 0; k < b.getGridSize(); ++k) {
                for (int l = 0; l < b.getGridSize(); ++l) {
                    if  (b.getBoard()[i][j]->getColour() == c && b.getBoard()[i][j]->isMoveValid(k, l, b)) {
                        std::vector<int> m = {i,j,k,l};
                        randMoves.emplace_back(m);
                    }
                }
            }
        }
    }
    // Can Check logic
    checkMoves = b.getCheckMoves(randMoves, c);
    // Can capture Logic
    for (int i = 0; i < b.getGridSize(); ++i) {
        for (int j = 0; j < b.getGridSize(); ++j) {
            for (int k = 0; k < b.getGridSize(); ++k) {
                for (int l = 0; l < b.getGridSize(); ++l) {
                    if  (b.getBoard()[i][j]->getColour() == c && b.getBoard()[i][j]->isMoveValid(k, l, b)
                      && b.getBoard()[k][l]->getColour() != Colour::Empty && b.getBoard()[k][l]->getColour() != c) {
                        std::vector<int> m = {i,j,k,l};
                        captureMoves.emplace_back(m);
                    }
                }
            }
        }
    }

    if (inCheck) {
        checkMoves = b.filterCheck(checkMoves, c);
        captureMoves = b.filterCheck(captureMoves, c);
        randMoves = b.filterCheck(randMoves, c);
    }

    if (checkMoves.size() > 0) {
        int random = std::rand() % checkMoves.size();

        b.makeMove(checkMoves[random][0], checkMoves[random][1], checkMoves[random][2], checkMoves[random][3], c);
    } else if (captureMoves.size() > 0) {
        int random = std::rand() % captureMoves.size();

        b.makeMove(captureMoves[random][0], captureMoves[random][1], captureMoves[random][2], captureMoves[random][3], c);
    } else {
        // Random logic
        int random = std::rand() % randMoves.size();

        b.makeMove(randMoves[random][0], randMoves[random][1], randMoves[random][2], randMoves[random][3], c);
    }
}

