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
  while (true) {
    startScreen();
    _initialize = false;
    POO->initialize(_rows, _cols, _poos);
    while (POO->status() == PooSweeperStateBase::ONGOING) {
      MEVENT mouseAction;
      mousemask(ALL_MOUSE_EVENTS, NULL);
      keypad(stdscr, TRUE);
      size_t keycode = getch();
      if (getmouse(&mouseAction) == OK) {
        if (mouseAction.bstate & BUTTON1_CLICKED) {
          if (mouseAction.y < POO->numRows() + 1 &&
              mouseAction.x < POO->numCols() + 1) {
            PooSweeperMove move;
            move.col = mouseAction.x;
            move.row = mouseAction.y;
            move.type = PooSweeperMove::REVEAL;
            POO->applyMove(move);
          }
        }
      }
    }
  }
}

// _____________________________________________________________________________
void PooSweeper::startScreen() {
  MEVENT start;
  mousemask(ALL_MOUSE_EVENTS, NULL);
  keypad(stdscr, TRUE);
  while (true) {
    printf("test");
    mvprintw(1, 2, "PooSweeper\n\n");
    mvprintw(3, 1, "Choose Difficulty:\n\n");
    mvprintw(5, 2, "Beginner\n\n");
    mvprintw(7, 2, "Intermediate\n\n");
    mvprintw(9, 2, "Expert");
    printf("test done");
    if (getmouse(&start) == OK) {
      if (start.bstate & BUTTON1_CLICKED) {
        if (start.y == 5) {
          _rows = 9;
          _cols = 9;
          _poos = 10;
          break;
        } else if (start.y == 7) {
          _rows = 16;
          _cols = 16;
          _poos = 40;
          break;
        } else if (start.y == 9) {
          _rows = 16;
          _cols = 30;
          _poos = 99;
          break;
        }
      }
    }
  }
}

// _____________________________________________________________________________
void PooSweeper::endScreen() {}
// _____________________________________________________________________________
PooSweeper::~PooSweeper() {
  endwin();
}
