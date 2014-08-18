// Copyright 2014, University of Freiburg,
// Author: Michael Kotzjan

#include <ncurses.h>
#include "./PooSweeper.h"

// _____________________________________________________________________________
PooSweeper::PooSweeper() {
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
}

// _____________________________________________________________________________
void PooSweeper::play() {
}

// _____________________________________________________________________________
PooSweeper::~PooSweeper() {
  endwin();
}
