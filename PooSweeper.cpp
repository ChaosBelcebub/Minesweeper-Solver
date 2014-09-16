// Copyright 2014, University of Freiburg,
// Author: Michael Kotzjan

#include <ncurses.h>
#include "./PooSweeper.h"
#include "./PooSweeperStateBase.h"
#include "./PooSweeperDisplayBase.h"

// _____________________________________________________________________________
void PooSweeper::play(int rows, int cols, int poos) {
  // Initialize the game with the given variables from the menu
  POO->initialize(rows, cols, poos);
  while (POO->status() == PooSweeperStateBase::ONGOING) {
    // First display the field
    DISPLAY->show(POO);
    // All mouseEvents for left and ctrl-left click
    MEVENT mouseAction;
    mousemask(ALL_MOUSE_EVENTS, NULL);
    keypad(stdscr, TRUE);
    size_t keycode = getch();
    if (getmouse(&mouseAction) == OK) {
      if (mouseAction.bstate & BUTTON_CTRL) {
        // Only apply the move if its inside the field
        if (mouseAction.y < POO->numRows() + 1 &&
            mouseAction.x < POO->numCols() + 1) {
          PooSweeperMove move;
          move.col = mouseAction.x;
          move.row = mouseAction.y;
          move.type = PooSweeperMove::TOGGLE_MARK;
          POO->applyMove(move);
        }
      } else if (mouseAction.bstate & BUTTON1_CLICKED) {
        // Only apply the move if its inside the field
        if (mouseAction.y < POO->numRows() &&
            mouseAction.x < POO->numCols() + 1) {
          PooSweeperMove move;
          move.col = mouseAction.x;
          move.row = mouseAction.y;
          move.type = PooSweeperMove::REVEAL;
          POO->applyMove(move);
        }
      }
      // Show the new field
      DISPLAY->show(POO);
    }
  }
}
