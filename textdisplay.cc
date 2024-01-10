#include "textdisplay.h"

using namespace std;

TextDisplay::TextDisplay() : theDisplay{vector<vector<char>>(8, vector<char>(8))} {
    string whitePieces = "rnbqkbnr";
    string blackPieces = "RNBQKBNR";
    
    // initialize theDisplay
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            // set white/black squares
            if ((i + j) % 2 == 0) {
                theDisplay[i][j] = ' ';
            } else {
                theDisplay[i][j] = '_';
            }

            // set white/black pieces
            if (i == 0) {
                theDisplay[i][j] = whitePieces[j];
            } else if (i == 1) {
                theDisplay[i][j] = 'p';
            } else if (i == boardSize - 1) {
                theDisplay[i][j] = blackPieces[j];
            } else if (i == boardSize - 2) {
                theDisplay[i][j] = 'P';
            }
        }
    }
}

void TextDisplay::notify(Piece &p) {
    // get location and type of piece
    pair<int, int> loc = p.getLocation();
    PType t = p.getType();

    // update display based on the new location of the piece
    if (t == PType::Knight) {
        theDisplay[loc.first][loc.second] = 'n';
    } else if (t == PType::Bishop) {
        theDisplay[loc.first][loc.second] = 'b';
    } else if (t == PType::Rook) {
        theDisplay[loc.first][loc.second] = 'r';
    } else if (t == PType::King) {
        theDisplay[loc.first][loc.second] = 'k';
    } else if (t == PType::Queen) {
        theDisplay[loc.first][loc.second] = 'q';
    } else if (t == PType::Pawn) {
        theDisplay[loc.first][loc.second] = 'p';
    } else {
        if ((loc.first + loc.second) % 2 == 0) {
            theDisplay[loc.first][loc.second] = ' ';
        } else {
            theDisplay[loc.first][loc.second] = '_';
        }
    }

    // update display based on the colour of the piece
    if (p.getColour() == Colour::White) {
        theDisplay[loc.first][loc.second] -= 32;
    }
}

TextDisplay::~TextDisplay() {}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  // print out the board, adding a newline at the end of each row
  for (int i = 0; i < td.boardSize; ++i) {
    out << 8-i << " ";
    for (int j = 0; j < td.boardSize; ++j) {
      out << td.theDisplay[i][j];
      if (j == td.boardSize - 1) out << endl;
    }
  }
  char coords;
  out << endl << "  ";
  for (int i = 0; i < td.boardSize; ++i) {
    coords = 'a' + i;
      out << coords;
  }
  out << endl << endl;
  
  return out;
}
