// Copyright 2014, University of Freiburg.
// Michael Kotzjan

#include <gtest/gtest.h>
#include "./PooSweeperState.h"

// _____________________________________________________________________________
TEST(PooSweeperStateTest, initialize) {
  PooSweeperState pss;
  pss.initialize(5, 5, 5);
  // Check if the number of poos is correct
  size_t count = 0;
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      if (pss.CellInfoPoo[i][j] == PooSweeperState::POO) { ++count; }
    }
  }
  ASSERT_EQ(5, count);
  ASSERT_EQ(5, pss.numRows());
  ASSERT_EQ(5, pss.numCols());
}

// _____________________________________________________________________________
TEST(PooSweeperStateTest, applyMove) {
  {
    // No poos
    PooSweeperState pss;
    pss.CellInfoStorage.clear();
    pss.CellInfoStorage.resize(5);
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
        pss.CellInfoStorage[i].push_back(PooSweeperStateBase::UNREVEALED);
      }
    }
    PooSweeperMove psm;
    psm.col = 0;
    psm.row = 0;
    psm.type = PooSweeperMove::REVEAL;
    // pss.applyMove(psm);
  }
}
