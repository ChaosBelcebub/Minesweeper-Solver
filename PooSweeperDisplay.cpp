// Copyright 2014, University of Freiburg,
// Author: Michael Kotzjan

#include "./PooSweeperDisplay.h"
#include <ncurses.h>
#include <iostream>
#include <sstream>
#include <string>

PooSweeperDisplay display;
PooSweeperDisplayBase* DISPLAY = &display;

// ___________________________________________________________________________
void PooSweeperDisplay::show(const PooSweeperStateBase* state) const {
  start_color();
  init_pair(0, COLOR_BLACK, COLOR_BLACK);
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_BLACK);
  init_pair(4, COLOR_BLUE, COLOR_BLACK);
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(6, COLOR_CYAN, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);
  init_pair(8, COLOR_YELLOW, COLOR_BLACK);
  for (int i = 0; i < state->numRows(); ++i) {
    for (int j = 0; j < state->numCols(); ++j) {
      switch (state->getCellInfo(i, j)) {
        case PooSweeperStateBase::UNREVEALED:
          mvprintw(i, j, "?");
          // printf("\x1b[7m");
          // printf("?")r
          // printf("\x1b[0m");
          break;
        case PooSweeperStateBase::MARKED:
          mvprintw(i, j, "M");
          // printf("\x1b[7m");
          // printf("\x1b[41m");
          // printf("\u2691");
          // printf("\x1b[0m");
          break;
        case PooSweeperStateBase::REVEALED_POO:
          mvprintw(i, j, "X");
          // printf("\x1b[0;32m");
          // printf("\u2601");
          // printf("\x1b[0m");
          break;
        case PooSweeperStateBase::REVEALED_ZERO:
          attron(COLOR_PAIR(0));
          mvprintw(i, j, " ");
          attroff(COLOR_PAIR(0));
          break;
        case PooSweeperStateBase::REVEALED_ONE:
          attron(COLOR_PAIR(1));
          mvprintw(i, j, "1");
          attroff(COLOR_PAIR(1));
          break;
        case PooSweeperStateBase::REVEALED_TWO:
          mvprintw(i, j, "2");
          break;
        case PooSweeperStateBase::REVEALED_THREE:
          mvprintw(i, j, "3");
          break;
        case PooSweeperStateBase::REVEALED_FOUR:
          mvprintw(i, j, "4");
          break;
        case PooSweeperStateBase::REVEALED_FIVE:
          mvprintw(i, j, "5");
          break;
        case PooSweeperStateBase::REVEALED_SIX:
          mvprintw(i, j, "6");
          break;
        case PooSweeperStateBase::REVEALED_SEVEN:
          mvprintw(i, j, "7");
          break;
        case PooSweeperStateBase::REVEALED_EIGHT:
          mvprintw(i, j, "8");
          break;
      }
    }
  }
  mvprintw(state->numRows() + 2, 2, "Revealed: %u", state->numRevealed());
  mvprintw(state->numRows() + 3, 2, "Marked: %u   ", state->numMarked());
  mvprintw(state->numRows() + 4, 2, "Poos: %u", state->numPoos());
  refresh();
}
