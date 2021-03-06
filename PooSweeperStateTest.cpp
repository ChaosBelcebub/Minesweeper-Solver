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
    ASSERT_EQ(PooSweeperStateBase::LOST, pss._status);
    ASSERT_EQ(0, pss.numRevealed());
    ASSERT_EQ(0, pss.numMarked());
  }
  // Now i'm going to test the counting of the mines
  {
    // One poo
    PooSweeperState pss;
    pss._numRows = 3;
    pss._numCols = 3;
    pss._numPoos = 1;
    pss._numRevealed = 0;
    pss._numMarked = 0;
    pss._status = PooSweeperStateBase::ONGOING;
    pss.CellInfoStorage.clear();
    pss.CellInfoPoo.clear();
    pss.CellInfoStorage.resize(3);
    pss.CellInfoPoo.resize(3);
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        pss.CellInfoStorage[i].push_back(PooSweeperStateBase::UNREVEALED);
        pss.CellInfoPoo[i].push_back(PooSweeperState::NO_POO);
      }
    }
    pss.CellInfoPoo[0][0] = PooSweeperState::POO;
    PooSweeperMove move;
    move.row = 1;
    move.col = 1;
    move.type = PooSweeperMove::REVEAL;
    pss.applyMove(move);
    ASSERT_EQ(1, pss.CellInfoStorage[1][1]);
  }
  {
    // Two poos
    PooSweeperState pss;
    pss._numRows = 3;
    pss._numCols = 3;
    pss._numPoos = 1;
    pss._numRevealed = 0;
    pss._numMarked = 0;
    pss._status = PooSweeperStateBase::ONGOING;
    pss.CellInfoStorage.clear();
    pss.CellInfoPoo.clear();
    pss.CellInfoStorage.resize(3);
    pss.CellInfoPoo.resize(3);
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        pss.CellInfoStorage[i].push_back(PooSweeperStateBase::UNREVEALED);
        pss.CellInfoPoo[i].push_back(PooSweeperState::NO_POO);
      }
    }
    pss.CellInfoPoo[0][0] = PooSweeperState::POO;
    pss.CellInfoPoo[1][0] = PooSweeperState::POO;
    PooSweeperMove move;
    move.row = 1;
    move.col = 1;
    move.type = PooSweeperMove::REVEAL;
    pss.applyMove(move);
    ASSERT_EQ(2, pss.CellInfoStorage[1][1]);
  }
  {
    // Three poos
    PooSweeperState pss;
    pss._numRows = 3;
    pss._numCols = 3;
    pss._numPoos = 1;
    pss._numRevealed = 0;
    pss._numMarked = 0;
    pss._status = PooSweeperStateBase::ONGOING;
    pss.CellInfoStorage.clear();
    pss.CellInfoPoo.clear();
    pss.CellInfoStorage.resize(3);
    pss.CellInfoPoo.resize(3);
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        pss.CellInfoStorage[i].push_back(PooSweeperStateBase::UNREVEALED);
        pss.CellInfoPoo[i].push_back(PooSweeperState::NO_POO);
      }
    }
    pss.CellInfoPoo[0][0] = PooSweeperState::POO;
    pss.CellInfoPoo[1][0] = PooSweeperState::POO;
    pss.CellInfoPoo[2][0] = PooSweeperState::POO;
    PooSweeperMove move;
    move.row = 1;
    move.col = 1;
    move.type = PooSweeperMove::REVEAL;
    pss.applyMove(move);
    ASSERT_EQ(3, pss.CellInfoStorage[1][1]);
  }
  {
    // Four poos
    PooSweeperState pss;
    pss._numRows = 3;
    pss._numCols = 3;
    pss._numPoos = 1;
    pss._numRevealed = 0;
    pss._numMarked = 0;
    pss._status = PooSweeperStateBase::ONGOING;
    pss.CellInfoStorage.clear();
    pss.CellInfoPoo.clear();
    pss.CellInfoStorage.resize(3);
    pss.CellInfoPoo.resize(3);
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        pss.CellInfoStorage[i].push_back(PooSweeperStateBase::UNREVEALED);
        pss.CellInfoPoo[i].push_back(PooSweeperState::NO_POO);
      }
    }
    pss.CellInfoPoo[0][0] = PooSweeperState::POO;
    pss.CellInfoPoo[1][0] = PooSweeperState::POO;
    pss.CellInfoPoo[2][0] = PooSweeperState::POO;
    pss.CellInfoPoo[0][1] = PooSweeperState::POO;
    PooSweeperMove move;
    move.row = 1;
    move.col = 1;
    move.type = PooSweeperMove::REVEAL;
    pss.applyMove(move);
    ASSERT_EQ(4, pss.CellInfoStorage[1][1]);
  }
  {
    // Five poos
    PooSweeperState pss;
    pss._numRows = 3;
    pss._numCols = 3;
    pss._numPoos = 1;
    pss._numRevealed = 0;
    pss._numMarked = 0;
    pss._status = PooSweeperStateBase::ONGOING;
    pss.CellInfoStorage.clear();
    pss.CellInfoPoo.clear();
    pss.CellInfoStorage.resize(3);
    pss.CellInfoPoo.resize(3);
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        pss.CellInfoStorage[i].push_back(PooSweeperStateBase::UNREVEALED);
        pss.CellInfoPoo[i].push_back(PooSweeperState::NO_POO);
      }
    }
    pss.CellInfoPoo[0][0] = PooSweeperState::POO;
    pss.CellInfoPoo[1][0] = PooSweeperState::POO;
    pss.CellInfoPoo[2][0] = PooSweeperState::POO;
    pss.CellInfoPoo[0][1] = PooSweeperState::POO;
    pss.CellInfoPoo[0][2] = PooSweeperState::POO;
    PooSweeperMove move;
    move.row = 1;
    move.col = 1;
    move.type = PooSweeperMove::REVEAL;
    pss.applyMove(move);
    ASSERT_EQ(5, pss.CellInfoStorage[1][1]);
  }
  {
    // Six poos
    PooSweeperState pss;
    pss._numRows = 3;
    pss._numCols = 3;
    pss._numPoos = 1;
    pss._numRevealed = 0;
    pss._numMarked = 0;
    pss._status = PooSweeperStateBase::ONGOING;
    pss.CellInfoStorage.clear();
    pss.CellInfoPoo.clear();
    pss.CellInfoStorage.resize(3);
    pss.CellInfoPoo.resize(3);
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        pss.CellInfoStorage[i].push_back(PooSweeperStateBase::UNREVEALED);
        pss.CellInfoPoo[i].push_back(PooSweeperState::NO_POO);
      }
    }
    pss.CellInfoPoo[0][0] = PooSweeperState::POO;
    pss.CellInfoPoo[1][0] = PooSweeperState::POO;
    pss.CellInfoPoo[2][0] = PooSweeperState::POO;
    pss.CellInfoPoo[0][1] = PooSweeperState::POO;
    pss.CellInfoPoo[0][2] = PooSweeperState::POO;
    pss.CellInfoPoo[1][2] = PooSweeperState::POO;
    PooSweeperMove move;
    move.row = 1;
    move.col = 1;
    move.type = PooSweeperMove::REVEAL;
    pss.applyMove(move);
    ASSERT_EQ(6, pss.CellInfoStorage[1][1]);
  }
  {
    // Seven poos
    PooSweeperState pss;
    pss._numRows = 3;
    pss._numCols = 3;
    pss._numPoos = 1;
    pss._numRevealed = 0;
    pss._numMarked = 0;
    pss._status = PooSweeperStateBase::ONGOING;
    pss.CellInfoStorage.clear();
    pss.CellInfoPoo.clear();
    pss.CellInfoStorage.resize(3);
    pss.CellInfoPoo.resize(3);
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        pss.CellInfoStorage[i].push_back(PooSweeperStateBase::UNREVEALED);
        pss.CellInfoPoo[i].push_back(PooSweeperState::NO_POO);
      }
    }
    pss.CellInfoPoo[0][0] = PooSweeperState::POO;
    pss.CellInfoPoo[1][0] = PooSweeperState::POO;
    pss.CellInfoPoo[2][0] = PooSweeperState::POO;
    pss.CellInfoPoo[0][1] = PooSweeperState::POO;
    pss.CellInfoPoo[0][2] = PooSweeperState::POO;
    pss.CellInfoPoo[1][2] = PooSweeperState::POO;
    pss.CellInfoPoo[2][1] = PooSweeperState::POO;
    PooSweeperMove move;
    move.row = 1;
    move.col = 1;
    move.type = PooSweeperMove::REVEAL;
    pss.applyMove(move);
    ASSERT_EQ(7, pss.CellInfoStorage[1][1]);
  }
  {
    // Eight poos
    PooSweeperState pss;
    pss._numRows = 3;
    pss._numCols = 3;
    pss._numPoos = 1;
    pss._numRevealed = 0;
    pss._numMarked = 0;
    pss._status = PooSweeperStateBase::ONGOING;
    pss.CellInfoStorage.clear();
    pss.CellInfoPoo.clear();
    pss.CellInfoStorage.resize(3);
    pss.CellInfoPoo.resize(3);
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        pss.CellInfoStorage[i].push_back(PooSweeperStateBase::UNREVEALED);
        pss.CellInfoPoo[i].push_back(PooSweeperState::NO_POO);
      }
    }
    pss.CellInfoPoo[0][0] = PooSweeperState::POO;
    pss.CellInfoPoo[1][0] = PooSweeperState::POO;
    pss.CellInfoPoo[2][0] = PooSweeperState::POO;
    pss.CellInfoPoo[0][1] = PooSweeperState::POO;
    pss.CellInfoPoo[0][2] = PooSweeperState::POO;
    pss.CellInfoPoo[1][2] = PooSweeperState::POO;
    pss.CellInfoPoo[2][1] = PooSweeperState::POO;
    pss.CellInfoPoo[2][2] = PooSweeperState::POO;
    PooSweeperMove move;
    move.row = 1;
    move.col = 1;
    move.type = PooSweeperMove::REVEAL;
    pss.applyMove(move);
    ASSERT_EQ(8, pss.CellInfoStorage[1][1]);
  }
  {
    // Check if a field change when its not unrevealed
    PooSweeperState pss;
    pss._numRows = 3;
    pss._numCols = 3;
    pss._numPoos = 1;
    pss._numRevealed = 0;
    pss._numMarked = 0;
    pss._status = PooSweeperStateBase::ONGOING;
    pss.CellInfoStorage.clear();
    pss.CellInfoPoo.clear();
    pss.CellInfoStorage.resize(3);
    pss.CellInfoPoo.resize(3);
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        pss.CellInfoStorage[i].push_back(PooSweeperStateBase::REVEALED_ONE);
        pss.CellInfoPoo[i].push_back(PooSweeperState::NO_POO);
      }
    }
    PooSweeperMove move;
    move.row = 1;
    move.col = 1;
    move.type = PooSweeperMove::REVEAL;
    pss.applyMove(move);
    // Nothing should change
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        ASSERT_EQ(1, pss.CellInfoStorage[i][j]);
      }
    }
  }
  {
    // Check togglemark
    PooSweeperState pss;
    pss._numRows = 3;
    pss._numCols = 3;
    pss._numPoos = 1;
    pss._numRevealed = 0;
    pss._numMarked = 0;
    pss._status = PooSweeperStateBase::ONGOING;
    pss.CellInfoStorage.clear();
    pss.CellInfoPoo.clear();
    pss.CellInfoStorage.resize(3);
    pss.CellInfoPoo.resize(3);
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        pss.CellInfoStorage[i].push_back(PooSweeperStateBase::UNREVEALED);
        pss.CellInfoPoo[i].push_back(PooSweeperState::NO_POO);
      }
    }
    PooSweeperMove move;
    move.row = 1;
    move.col = 1;
    move.type = PooSweeperMove::TOGGLE_MARK;
    pss.applyMove(move);
    // Now the cell should be marked
    ASSERT_EQ(-2, pss.CellInfoStorage[1][1]);
    ASSERT_EQ(0, pss.numRevealed());
    ASSERT_EQ(1, pss.numMarked());
    PooSweeperMove moveback;
    moveback.row = 1;
    moveback.col = 1;
    moveback.type = PooSweeperMove::TOGGLE_MARK;
    pss.applyMove(moveback);
    // Now the cell should be unrevealed
    ASSERT_EQ(-1, pss.CellInfoStorage[1][1]);
    ASSERT_EQ(0, pss.numRevealed());
    ASSERT_EQ(0, pss.numMarked());
  }
}

TEST(PooSweeperStateTest, autoReveal) {
  // Simple autoreveal test
  PooSweeperState pss;
  pss._numRows = 5;
  pss._numCols = 5;
  pss._numPoos = 4;
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
  // Set poos
  pss.CellInfoPoo[0][0] = PooSweeperState::POO;
  pss.CellInfoPoo[0][4] = PooSweeperState::POO;
  pss.CellInfoPoo[4][0] = PooSweeperState::POO;
  pss.CellInfoPoo[4][4] = PooSweeperState::POO;
  PooSweeperMove move;
  move.col = 2;
  move.row = 2;
  move.type = PooSweeperMove::REVEAL;
  pss.applyMove(move);
  // Check variables
  ASSERT_EQ(21, pss.numRevealed());
  ASSERT_EQ(0, pss.numMarked());
  // Check field. Should be:
  // ?1 1?
  // 11 11
  //
  // 11 11
  // ?1 1?
  ASSERT_EQ(-1, pss.CellInfoStorage[0][0]);
  ASSERT_EQ(1, pss.CellInfoStorage[0][1]);
  ASSERT_EQ(0, pss.CellInfoStorage[0][2]);
  ASSERT_EQ(1, pss.CellInfoStorage[0][3]);
  ASSERT_EQ(-1, pss.CellInfoStorage[0][4]);
  ASSERT_EQ(1, pss.CellInfoStorage[1][0]);
  ASSERT_EQ(1, pss.CellInfoStorage[1][1]);
  ASSERT_EQ(0, pss.CellInfoStorage[1][2]);
  ASSERT_EQ(1, pss.CellInfoStorage[1][3]);
  ASSERT_EQ(1, pss.CellInfoStorage[1][4]);
  ASSERT_EQ(0, pss.CellInfoStorage[2][0]);
  ASSERT_EQ(0, pss.CellInfoStorage[2][1]);
  ASSERT_EQ(0, pss.CellInfoStorage[2][2]);
  ASSERT_EQ(0, pss.CellInfoStorage[2][3]);
  ASSERT_EQ(0, pss.CellInfoStorage[2][4]);
  ASSERT_EQ(1, pss.CellInfoStorage[3][0]);
  ASSERT_EQ(1, pss.CellInfoStorage[3][1]);
  ASSERT_EQ(0, pss.CellInfoStorage[3][2]);
  ASSERT_EQ(1, pss.CellInfoStorage[3][3]);
  ASSERT_EQ(1, pss.CellInfoStorage[3][4]);
  ASSERT_EQ(-1, pss.CellInfoStorage[4][0]);
  ASSERT_EQ(1, pss.CellInfoStorage[4][1]);
  ASSERT_EQ(0, pss.CellInfoStorage[4][2]);
  ASSERT_EQ(1, pss.CellInfoStorage[4][3]);
  ASSERT_EQ(-1, pss.CellInfoStorage[4][4]);
}

TEST(PooSweeperStateTest, checkPoo) {
  // initialize a field with four poos
  PooSweeperState pss;
  pss._numRows = 3;
  pss._numCols = 3;
  pss._numPoos = 1;
  pss._numRevealed = 0;
  pss._numMarked = 0;
  pss._status = PooSweeperStateBase::ONGOING;
  pss.CellInfoStorage.clear();
  pss.CellInfoPoo.clear();
  pss.CellInfoStorage.resize(3);
  pss.CellInfoPoo.resize(3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      pss.CellInfoStorage[i].push_back(PooSweeperStateBase::UNREVEALED);
      pss.CellInfoPoo[i].push_back(PooSweeperState::NO_POO);
    }
  }
  pss.CellInfoPoo[0][0] = PooSweeperState::POO;
  pss.CellInfoPoo[1][0] = PooSweeperState::POO;
  pss.CellInfoPoo[2][0] = PooSweeperState::POO;
  pss.CellInfoPoo[0][1] = PooSweeperState::POO;
  // Check every field for poos
  ASSERT_EQ(true, pss.checkPoo(0, 0));
  ASSERT_EQ(true, pss.checkPoo(0, 1));
  ASSERT_EQ(false, pss.checkPoo(0, 2));
  ASSERT_EQ(true, pss.checkPoo(1, 0));
  ASSERT_EQ(false, pss.checkPoo(1, 1));
  ASSERT_EQ(false, pss.checkPoo(1, 2));
  ASSERT_EQ(true, pss.checkPoo(2, 0));
  ASSERT_EQ(false, pss.checkPoo(2, 1));
  ASSERT_EQ(false, pss.checkPoo(2, 2));
}

TEST(PooSweeperStateTest, wonGame) {
// Simple test with only the variables
  {
    // Test for zero marked fields but no more fields without poos left
    PooSweeperState pss;
    pss._numRows = 5;
    pss._numCols = 5;
    pss._numRevealed = 0;
    pss._numPoos = 5;
    pss._numMarked = 0;
    pss._status = PooSweeperStateBase::ONGOING;
    pss.wonGame();
    // Game should be still ongoing
    ASSERT_EQ(PooSweeperStateBase::ONGOING, pss._status);
    // Reveal all fields without poo
    pss._numRevealed = 20;
    pss.wonGame();
    // The Game should now be won
    ASSERT_EQ(PooSweeperStateBase::WON, pss._status);
  }
  {
    // Test for a mix of the tests above and below
    PooSweeperState pss;
    pss._numRows = 5;
    pss._numCols = 5;
    pss._numRevealed = 0;
    pss._numPoos = 5;
    pss._numMarked = 0;
    pss._status = PooSweeperStateBase::ONGOING;
    pss.wonGame();
    // Game should be still ongoing
    ASSERT_EQ(PooSweeperStateBase::ONGOING, pss._status);
    // Mark two fields, reveal all without poo
    pss._numRevealed = 20;
    pss._numMarked = 2;
    pss.wonGame();
    // The Game should now be won
    ASSERT_EQ(PooSweeperStateBase::WON, pss._status);
  }
  {
    // Test for all poos marked and all other fields revealed
    PooSweeperState pss;
    pss._numRows = 5;
    pss._numCols = 5;
    pss._numRevealed = 0;
    pss._numPoos = 5;
    pss._numMarked = 0;
    pss._status = PooSweeperStateBase::ONGOING;
    pss.wonGame();
    // Game should be still ongoing
    ASSERT_EQ(PooSweeperStateBase::ONGOING, pss._status);
    // Mark all poos, reveal all fields without poo
    pss._numRevealed = 20;
    pss._numMarked = 5;
    pss.wonGame();
    // The Game should now be won
    ASSERT_EQ(PooSweeperStateBase::WON, pss._status);
  }
}

TEST(PooSweeperStateTest, revealPoos) {
  // Set a field with 5 poos
  PooSweeperState pss;
  pss._numRows = 3;
  pss._numCols = 3;
  pss._numPoos = 1;
  pss._numRevealed = 0;
  pss._numMarked = 0;
  pss._status = PooSweeperStateBase::ONGOING;
  pss.CellInfoStorage.clear();
  pss.CellInfoPoo.clear();
  pss.CellInfoStorage.resize(3);
  pss.CellInfoPoo.resize(3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      pss.CellInfoStorage[i].push_back(PooSweeperStateBase::UNREVEALED);
      pss.CellInfoPoo[i].push_back(PooSweeperState::NO_POO);
    }
  }
  pss.CellInfoPoo[0][0] = PooSweeperState::POO;
  pss.CellInfoPoo[1][0] = PooSweeperState::POO;
  pss.CellInfoPoo[2][0] = PooSweeperState::POO;
  pss.CellInfoPoo[0][1] = PooSweeperState::POO;
  pss.CellInfoPoo[0][2] = PooSweeperState::POO;
  // Reveal all poos, normaly at end of game
  pss.revealPoos();
  // All other fields should be unrevealed
  ASSERT_EQ(-3, pss.CellInfoStorage[0][0]);
  ASSERT_EQ(-3, pss.CellInfoStorage[0][1]);
  ASSERT_EQ(-3, pss.CellInfoStorage[0][2]);
  ASSERT_EQ(-3, pss.CellInfoStorage[1][0]);
  ASSERT_EQ(-1, pss.CellInfoStorage[1][1]);
  ASSERT_EQ(-1, pss.CellInfoStorage[1][2]);
  ASSERT_EQ(-3, pss.CellInfoStorage[2][0]);
  ASSERT_EQ(-1, pss.CellInfoStorage[2][1]);
  ASSERT_EQ(-1, pss.CellInfoStorage[2][2]);
}
