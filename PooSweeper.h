// Copyright 2014, University of Freiburg,
// Author: Michael Kotzjan

#ifndef PROJEKT_POOSWEEPER_H_
#define PROJEKT_POOSWEEPER_H_

class PooSweeper {
 public:
  // Constructor, used to prepare display etc
  PooSweeper();

  // Play the game!
  void play();

  // Destructor
  ~PooSweeper();

 private:
  size_t _rows;
  size_t _cols;
  size_t _poos;
};

#endif  // PROJEKT_POOSWEEPER_H_
