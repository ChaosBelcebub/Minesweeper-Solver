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
    clear();
    POO->initialize(_rows, _cols, _poos);
    while (POO->status() == PooSweeperStateBase::ONGOING) {
      DISPLAY->show(POO);
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
  while (true) {
    mvprintw(1, 2, "PooSweeper");
    mvprintw(3, 1, "Choose Difficulty:");
    mvprintw(5, 2, "Beginner");
    mvprintw(7, 2, "Intermediate");
    mvprintw(9, 2, "Expert");
    refresh();
    MEVENT start;
    mousemask(ALL_MOUSE_EVENTS, NULL);
    keypad(stdscr, TRUE);
    size_t ch = getch();
    if (getmouse(&start) == OK) {
      mvprintw(11, 2, "success");
      refresh();
      if (start.bstate & BUTTON1_CLICKED) {
        mvprintw(12, 2, "success2");
        refresh();
        if (start.y == 5) {
          mvprintw(13, 2, "beginner success");
          refresh();
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
