// Copyright 2014, University of Freiburg.
// Michael Kotzjan

#include "./PooSweeperSolver.h"
#include "./PooSweeperStateBase.h"
#include "./PooSweeperDisplayBase.h"
#include "./PooSweeperMove.h"

// Main function
int main(int argc, char** argv) {
  POO->initialize(5, 5, 5);
  PooSweeperSolver solver;
  while (POO->status() == 0) {
    DISPLAY->show(POO);
    POO->applyMove(solver.generateMove(POO));
  }
}
