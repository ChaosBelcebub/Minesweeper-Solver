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
        } else if (mouseAction.bstate & BUTTON_SHIFT) {
          if (mouseAction.y < POO->numRows() + 1 &&
              mouseAction.x < POO->numCols() + 1) {
            PooSweeperMove move;
            move.col = mouseAction.x;
            move.row = mouseAction.y;
            move.type = PooSweeperMove::TOGGLE_MARK;
            POO->applyMove(move);
          }
        }
      }
    }
    DISPLAY->show(POO);
    endScreen();
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
void PooSweeper::endScreen() {
  while (true) {
    int end = getch();
    mvprintw(_rows / 2, _cols + 2, "You've lost");
    mvprintw((_rows / 2) + 1, _cols + 2, "Do you want to play again? [y/n]");
    if (end == 'y') break;
    if (end == 'n') exit(1);
    refresh();
  }
  clear();
}
// _____________________________________________________________________________
PooSweeper::~PooSweeper() {
  endwin();
}
