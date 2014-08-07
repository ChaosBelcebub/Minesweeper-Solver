// Copyright 2014, University of Freiburg.
// Author: Michael Kotzjan

#include "./PooSweeperMove.h"
#include "./PooSweeperSolver.h"

// _____________________________________________________________________________
PooSweeperMove PooSweeperSolver::generateMove(
    const PooSweeperStateBase* state) {
  PooSweeperMove move;
  move.row = 1;
  move.col = 2;
  move.type = PooSweeperMove::REVEAL;
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
