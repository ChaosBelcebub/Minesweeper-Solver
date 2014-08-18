// Copyright 2014, University of Freiburg,
// Author: Michael Kotzjan

#include <ncurses.h>
#include "./PooSweeper.h"
#include "./PooSweeperStateBase.h"
#include "./PooSweeperDisplayBase.h"

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
  POO->initialize(5, 5, 5);
  while (POO->status() == 0) {
    DISPLAY->show(POO);
  }
}

// _____________________________________________________________________________
PooSweeper::~PooSweeper() {
  endwin();
}
