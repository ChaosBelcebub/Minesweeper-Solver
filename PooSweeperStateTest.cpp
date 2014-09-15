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
    pss._numRows = 5;
    pss._numCols = 5;
    pss._numPoos = 0;
    pss._numRevealed = 0;
    pss._numMarked = 0;
    pss._status = PooSweeperStateBase::ONGOING;
    pss.CellInfoStorage.clear();
    pss.CellInfoPoo.clear();
    pss.CellInfoStorage.resize(5);
    pss.CellInfoPoo.resize(5);
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
        pss.CellInfoStorage[i].push_back(PooSweeperStateBase::UNREVEALED);
        pss.CellInfoPoo[i].push_back(PooSweeperState::NO_POO);
      }
    }
    PooSweeperMove move;
    move.col = 0;
    move.row = 0;
    move.type = PooSweeperMove::REVEAL;
    pss.applyMove(move);
    // Every field should be unrevealed zero
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
        ASSERT_EQ(0, pss.CellInfoStorage[i][j]);
      }
    }
    ASSERT_EQ(25, pss.numRevealed());
    ASSERT_EQ(0, pss.numMarked());
  }
  {
    // Only poos
    PooSweeperState pss;
    pss._numRows = 5;
    pss._numCols = 5;
    pss._numPoos = 25;
    pss._numRevealed = 0;
    pss._numMarked = 0;
    pss._status = PooSweeperStateBase::ONGOING;
    pss.CellInfoStorage.clear();
    pss.CellInfoPoo.clear();
    pss.CellInfoStorage.resize(5);
    pss.CellInfoPoo.resize(5);
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
        pss.CellInfoStorage[i].push_back(PooSweeperStateBase::UNREVEALED);
        pss.CellInfoPoo[i].push_back(PooSweeperState::POO);
      }
    }
    PooSweeperMove move;
    move.col = 0;
    move.row = 0;
    move.type = PooSweeperMove::REVEAL;
    pss.applyMove(move);
    // Every field should be an unrevealed poo
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
        ASSERT_EQ(-3, pss.CellInfoStorage[i][j]);
      }
    }
  }
  {
  }
}
