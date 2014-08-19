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
  bool initialize = true;
  while (true) {
    if (initialize == true) {
      printf("\x1b[%d;%dH", 2, 4);
      printf("PooSweeper");
      printf("\x1b[%d;%dH", 4, 2);
      printf("Choose Difficulty:");
      printf("\x1b[%d;%dH", 6, 2);
      printf("Beginner");
      printf("\x1b[%d;%dH", 8, 2);
      printf("Advanced");
      printf("\x1b[%d;%dH", 10, 2);
      printf("Professional");
    }
    MEVENT mouseAction;
    mousemask(ALL_MOUSE_EVENTS, NULL);
    keypad(stdscr, TRUE);
    size_t keycode = getch();
    if (getmouse(&mouseAction) == OK) {
      if (mouseAction.bstate & BUTTON1_CLICKED) {
        if (initialize == true) {
          if (mouseAction.y == 5) {
            clear();
            POO->initialize(9, 9, 10);
            initialize = false;
          } else if (mouseAction.y == 7) {
            clear();
            POO->initialize(16, 16, 40);
            initialize = false;
          } else if (mouseAction.y == 9) {
            clear();
            POO->initialize(16, 30, 99);
            initialize = false;
          }
        } else {
          DISPLAY->show(POO);
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
PooSweeper::~PooSweeper() {
  endwin();
}
