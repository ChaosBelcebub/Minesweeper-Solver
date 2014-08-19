// Copyright 2014, University of Freiburg,
// Author: Michael Kotzjan

#include <iostream>
#include "./PooSweeperDisplay.h"

PooSweeperDisplay display;
PooSweeperDisplayBase* DISPLAY = &display;

// ___________________________________________________________________________
void PooSweeperDisplay::show(const PooSweeperStateBase* state) const {
  for (int i = 0; i < state->numRows(); ++i) {
    for (int j = 0; j < state->numCols(); ++j) {
      printf("\x1b[%d;%dH", i + 1, j + 1);
      switch (state->getCellInfo(i, j)) {
        case PooSweeperStateBase::UNREVEALED:
          printf("\x1b[7m");
          printf("?");
          printf("\x1b[0m");
          break;
        case PooSweeperStateBase::MARKED:
          printf("\x1b[7m");
          printf("\x1b[41m");
          printf("\u2691");
          printf("\x1b[0m");
          break;
        case PooSweeperStateBase::REVEALED_POO:
          printf("\x1b[0;32m");
          printf("\u2601");
          printf("\x1b[0m");
          break;
      }
    }
  }
}
