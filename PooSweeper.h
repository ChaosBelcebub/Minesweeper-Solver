// Copyright 2014, University of Freiburg,
// Author: Michael Kotzjan

#ifndef PROJEKT_POOSWEEPER_H_
#define PROJEKT_POOSWEEPER_H_

#include <stdlib.h>

class PooSweeper {
 public:
  // Constructor, used to prepare display etc
  PooSweeper();

  // Play the game!
  void play(int rows, int cols, int poos);

  // Destructor
  ~PooSweeper();
};

#endif  // PROJEKT_POOSWEEPER_H_
