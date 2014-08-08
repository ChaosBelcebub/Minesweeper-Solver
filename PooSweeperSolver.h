// Copyright 2014, University of Freiburg.
// Author: Michael Kotzjan

#ifndef PROJEKT_POOSWEEPERSOLVER_H_
#define PROJEKT_POOSWEEPERSOLVER_H_

#include "./PooSweeperMove.h"
#include "./PooSweeperSolverBase.h"

// Abstract interface class for a PooSweeper solver.
class PooSweeperSolver : public PooSweeperSolverBase {
 public:
  // Generate a move given the current state. A move is simply the position of a
  // particular cell to be uncovered next.
  PooSweeperMove generateMove(const PooSweeperStateBase* state);

 private:
  // Return the number of unrevealed fields around given position
  size_t numUnrevealed(size_t rowIndex, size_t colIndex) const;

  // Return the number of marked fields around given position
  size_t numMarked(size_t rowIndex, size_t colIndex) const;

  // Mark the fields around the position if the number of unrevealed fields
  // is similar to the poos around the field. Return true if successfull
  bool markAroundField();

  // Reveal all unrevealed fields around the position if the number of marked
  // fields is similar to the poos around. Return true if successfull
  bool revealIfPossible();

  // Special operation for revealing some fields
  bool specialRevealOperation();
};

#endif  // PROJEKT_POOSWEEPERSOLVER_H_
