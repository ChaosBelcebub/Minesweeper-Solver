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
  // Initialize the colors for ncurses
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
  init_pair(9, COLOR_RED, COLOR_BLACK);
  // Draw the field
  for (int i = 0; i < state->numRows(); ++i) {
    for (int j = 0; j < state->numCols(); ++j) {
      switch (state->getCellInfo(i, j)) {
        case PooSweeperStateBase::UNREVEALED:
          // Put some attributes on the cells with ncurses
          attron(COLOR_PAIR(0));
          attron(A_REVERSE);
          // Ncurses way to draw on specific position
          mvprintw(i, j, "?");
          // Turn off attributes
          attroff(A_REVERSE);
          attroff(COLOR_PAIR(0));
          break;
        case PooSweeperStateBase::MARKED:
          attron(COLOR_PAIR(9));
          attron(A_REVERSE);
          mvprintw(i, j, "M");
          attroff(COLOR_PAIR(9));
          attroff(A_REVERSE);
          break;
        case PooSweeperStateBase::REVEALED_POO:
          attron(COLOR_PAIR(3));
          mvprintw(i, j, "X");
          attroff(COLOR_PAIR(3));
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
          attron(COLOR_PAIR(2));
          mvprintw(i, j, "2");
          attroff(COLOR_PAIR(2));
          break;
        case PooSweeperStateBase::REVEALED_THREE:
          attron(COLOR_PAIR(3));
          mvprintw(i, j, "3");
          attroff(COLOR_PAIR(3));
          break;
        case PooSweeperStateBase::REVEALED_FOUR:
          attron(COLOR_PAIR(4));
          mvprintw(i, j, "4");
          attroff(COLOR_PAIR(4));
          break;
        case PooSweeperStateBase::REVEALED_FIVE:
          attron(COLOR_PAIR(5));
          mvprintw(i, j, "5");
          attroff(COLOR_PAIR(5));
          break;
        case PooSweeperStateBase::REVEALED_SIX:
          attron(COLOR_PAIR(6));
          mvprintw(i, j, "6");
          attroff(COLOR_PAIR(6));
          break;
        case PooSweeperStateBase::REVEALED_SEVEN:
          attron(COLOR_PAIR(7));
          mvprintw(i, j, "7");
          attroff(COLOR_PAIR(7));
          break;
        case PooSweeperStateBase::REVEALED_EIGHT:
          attron(COLOR_PAIR(8));
          mvprintw(i, j, "8");
          attroff(COLOR_PAIR(8));
          break;
      }
    }
  }
  // Display additional informations on the screen
  // Display them everytime under the field no matter the size
  mvprintw(state->numRows() + 2, 2, "Revealed: %u", state->numRevealed());
  mvprintw(state->numRows() + 3, 2, "Marked: %u   ", state->numMarked());
  mvprintw(state->numRows() + 4, 2, "Poos: %u", state->numPoos());
  refresh();
}
