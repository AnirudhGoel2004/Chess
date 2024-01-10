#include "piece.h"
#include "board.h"

Piece::Piece() : observers{}, location{-1, -1}, colour{Colour::Empty}, type{PType::Empty} {};

Piece::Piece(Colour colour, PType type) : observers{}, location{-1, -1}, colour{colour}, type{type} {};

// notify observers of piece
void Piece::notifyObservers() {
    // call the notify method for every observer
    for (Observer* o : observers) {
        o->notify(*this);
    }
}

// add an observer to piece
void Piece::attach(Observer *o) {
  observers.emplace_back(o);
}

// return true if piece is empty, false otherwise
bool Piece::isEmpty() {
    return (type == PType::Empty) ? true : false;
}

// return location of piece
std::pair<int, int> Piece::getLocation() {
    return location;
}

// return colour fo piece
Colour Piece::getColour() {
    return colour;
}

// return type of piece
PType Piece::getType() {
    return type;
}

// set locatation of piece
void Piece::setLocation(int row, int col) {
    location.first = row;
    location.second = col;
}

// get hasMoved of piece
bool Piece::getHasMoved() const{
    return true;
}

// set hasMoved of piece
void Piece::setHasMoved() {}

Piece::~Piece() { }
