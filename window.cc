#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[16][10]={"white", "black", "purple", "orange", "red", "black", "white", "black", 
  "red", "green", "blue", "yellow", "purple", "white", "blue", "orange"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 16; ++i) {
      XParseColor(d,cmap,color_vals[i],&xcolour);
      XAllocColor(d,cmap,&xcolour);
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawPawn(int x, int y, int colour) {
  XSetForeground(d, gc, colours[colour]);
  // draw the head 
  XFillArc(d, w, gc, x + 22.5, y + 5, 25, 25, 0, 360 * 64);
  // draw the stem
  fillRectangle(x + 28.5, y + 20, 13, 35, colour);
  // draw the base
  fillRectangle(x + 20, y + 50, 30, 10, colour);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawRook(int x, int y, int colour) {
  XSetForeground(d, gc, colours[colour]);
  // draw top portion
  fillRectangle(x + 15, y + 10, 10, 15, colour);
  fillRectangle(x + 30, y + 10, 10, 15, colour);
  fillRectangle(x + 45, y + 10, 10, 15, colour);

  // draw body
  fillRectangle(x + 22.5, y + 20, 25, 40, colour);

  // draw base
  fillRectangle(x + 15, y + 50, 40, 10, colour);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawKnight(int x, int y, int colour) {
  XSetForeground(d, gc, colours[colour]);
  // draw ear
  fillRectangle(x + 45, y + 5, 5, 8, colour);

  // draw head
  fillRectangle(x + 10, y + 10, 40, 10, colour);

  // draw body
  fillRectangle(x + 30, y + 20, 20, 30, colour);

  // draw base
  fillRectangle(x + 15, y + 50, 40, 10, colour);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawBishop(int x, int y, int colour) {
  XSetForeground(d, gc, colours[colour]);
  // draw top
  XFillArc(d, w, gc, x + 29, y + 9, 12, 12, 0, 360 * 64); 

  // draw body
  XFillArc(d, w, gc, x + 25, y + 17, 20, 42, 0, 360 * 64); 

  // draw base
  fillRectangle(x + 15, y + 50, 40, 10, colour);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawKing(int x, int y, int colour) {
  XSetForeground(d, gc, colours[colour]);
  // draw top portion
  fillRectangle(x + 32.5, y + 12, 5, 25, colour);
  fillRectangle(x + 27.5, y + 17, 15, 5, colour);

  // draw body
  fillRectangle(x + 20, y + 25, 30, 30, colour);

  // draw base
  fillRectangle(x + 15, y + 50, 40, 10, colour);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawQueen(int x, int y, int colour) {
  XSetForeground(d, gc, colours[colour]);
  // draw top portion
  XFillArc(d, w, gc, x + 30, y + 15, 10, 10, 0, 360 * 64); 

  // draw body
  fillRectangle(x + 20, y + 25, 30, 30, colour);

  // draw base
  fillRectangle(x + 15, y + 50, 40, 10, colour);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg) {
  XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}

