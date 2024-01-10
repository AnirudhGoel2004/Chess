#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];

 public:
  Xwindow(int width=560, int height=560);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  enum {White=0, Black, Red, Green, Blue}; // Available colours.

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a King piece
  void drawPawn(int x, int y, int colour);

  // Draws a Rook piece
  void drawRook(int x, int y, int colour);

  // Draws a Knight piece
  void drawKnight(int x, int y, int colour);

  // Draws a Knight piece
  void drawBishop(int x, int y, int colour);

  // Draws a King piece
  void drawKing(int x, int y, int colour);

  // Draws a Queen piece
  void drawQueen(int x, int y, int colour);

  // Draws a string
  void drawString(int x, int y, std::string msg);

};

#endif
