// Copyright 2014, University of Freiburg.
// Author: Michael Kotzjan

#include "./PooSweeperMove.h"
#include "./PooSweeperSolver.h"

// _____________________________________________________________________________
PooSweeperMove PooSweeperSolver::generateMove(
    const PooSweeperStateBase* state) {
  PooSweeperMove move;
  if (_startGame < 4) {
  // Reveal the 4 corners
    switch (_startGame) {
      case 0:
        return move;
      case 1:
        return move;
      case 2:
        return move;
      case 3:
        return move;
    }
    ++_startGame;
  }
  for (int i = 0; i < state->numRows(); ++i) {
    for (int j = 0; j < state->numCols(); ++j) {
    // Do something special
    }
  }
  return move;
}

// _____________________________________________________________________________
size_t PooSweeperSolver::numUnrevealed(size_t rowIndex, size_t colIndex) const {
  return rowIndex;
}

// _____________________________________________________________________________
size_t PooSweeperSolver::numMarked(size_t rowIndex, size_t colIndex) const {
  return colIndex;
}

// _____________________________________________________________________________
bool PooSweeperSolver::markAroundField() {
  return true;
}

// _____________________________________________________________________________
bool PooSweeperSolver::revealIfPossible() {
  return true;
}

// _____________________________________________________________________________
bool PooSweeperSolver::specialRevealOperation() {
  return false;
}
