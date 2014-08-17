// Copyright 2014, University of Freiburg,
// Author: Michael Kotzjan

#include "./PooSweeperDisplayBase"

#ifndef PROJEKT_POOSWEEPERDISPLAY_H_
#define PROJEKT_POOSWEEPERDISPLAY_H_

class PooSweeperDisplayBase;
extern PooSweeperDisplayBase* DISPLAY;

// Class for showing a state of the game on the screen
class PooSweeperDisplay : public PooSweeperDisplayBase {
 public:
  void show(const PooSweeperStateBase* state);
};
#endif  // PROJEKT_POOSWEEPERDISPLAY_H_
