// Copyright 2014, University of Freiburg.
// Author: Michael Kotzjan

#include "./PooSweeperStateBase.h"
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
        move.row = 0;
        move.col = 0;
      case 1:
        move.row = state->_numRows();
        move.col = 0;
      case 2:
        move.row = 0;
        move.col = state->_numCols();
      case 3:
        move.row = state->_numRows();
        move.col = state->_numCols();
    }
    move.type = PooSweeperMove::REVEAL;
    ++_startGame;
    return move;
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
