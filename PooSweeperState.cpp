// Copyright 2014, University of Freiburg.
// Author: Michael Kotzjan

#include "./PooSweeperState.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "./PooSweeperMove.h"

PooSweeperState poo;
PooSweeperStateBase* POO = &poo;

// _____________________________________________________________________________
PooSweeperState::CellInfo PooSweeperState::getCellInfo(
    size_t rowIndex, size_t colIndex) const {
  return CellInfoStorage[rowIndex][colIndex];
}

// _____________________________________________________________________________
void PooSweeperState::initialize(
    size_t numRows, size_t numCols, size_t numPoos) {
  _numRows = numRows;
  _numCols = numCols;
  _numPoos = numPoos;

  // Set other variable to default
  _numRevealed = 0;
  _numMarked = 0;
  _status = ONGOING;

  size_t pooRow;
  size_t pooCol;
  // Clear vector in case of last game
  CellInfoStorage.clear();
  CellInfoPoo.clear();
  // Set game to unrevealed and poos to no poos
  CellInfoStorage.resize(_numRows);
  CellInfoPoo.resize(_numRows);
  for (int i = 0; i < _numRows; ++i) {
    for (int j = 0; j < _numCols; ++j) {
      CellInfoStorage[i].push_back(UNREVEALED);
      CellInfoPoo[i].push_back(NO_POO);
    }
  }
  // Initialize random seed
  unsigned int seed = time(NULL);

  // Set poos
  for (int i = 0; i < _numPoos;) {
    pooRow = rand_r(&seed) % _numRows;
    pooCol = rand_r(&seed) % _numCols;
    if (CellInfoPoo[pooRow][pooCol] == NO_POO) {
      CellInfoPoo[pooRow][pooCol] = POO;
      ++i;
    }
  }
}

// _____________________________________________________________________________
void PooSweeperState::applyMove(const PooSweeperMove& move) {
  size_t posRow;
  size_t posCol;
  size_t countPoo = 0;
  // Switch for different move types
  switch (move.type) {
    case PooSweeperMove::REVEAL:
      // Return if field is not unrevealed
      if (CellInfoStorage[move.row][move.col] != UNREVEALED) return;
      // Check for poo and end game if needed
      if (checkPoo(move.row, move.col) == true) {
        CellInfoStorage[move.row][move.col] = REVEALED_POO;
        // Reveal all poos at end
        revealPoos();
        _status = LOST;
        return;
      }
      // Count the amount of poos around a field
      for (int x = -1; x < 2; ++x) {
        for (int y = -1; y < 2; ++y) {
          posRow = move.row + x;
          posCol = move.col + y;
          // But only if the cells are inside the field
          if (posRow >= 0 && posCol >= 0 && posRow < _numRows &&
            posCol < _numCols) {
            if (CellInfoPoo[posRow][posCol] == POO) {
              ++countPoo;
            }
          }
        }
      }
      // Set the storage on this position to the amount of poos around
      CellInfoStorage[move.row][move.col] = CellInfo(countPoo);
      ++_numRevealed;
      // Autoreveal if needed
      if (countPoo == 0) { autoReveal(move.row, move.col); }
      // Check for change of gamestatus
      wonGame();
      return;

    case PooSweeperMove::TOGGLE_MARK:
      // Simply toggle the marked cells
      if (CellInfoStorage[move.row][move.col] == UNREVEALED) {
        CellInfoStorage[move.row][move.col] = MARKED;
        ++_numMarked;
      } else if (CellInfoStorage[move.row][move.col] == MARKED) {
        CellInfoStorage[move.row][move.col] = UNREVEALED;
        --_numMarked;
      }
      // Check for change of gamestatus
      wonGame();
      return;
  }
}

// _____________________________________________________________________________
PooSweeperState::GameStatus PooSweeperState::status() const {
  return _status;
}

// _____________________________________________________________________________
size_t PooSweeperState::numRows() const { return _numRows; }

// _____________________________________________________________________________
size_t PooSweeperState::numCols() const { return _numCols; }

// _____________________________________________________________________________
size_t PooSweeperState::numPoos() const { return _numPoos; }

// _____________________________________________________________________________
size_t PooSweeperState::numRevealed() const { return _numRevealed; }

// _____________________________________________________________________________
size_t PooSweeperState::numMarked() const { return _numMarked; }

// _____________________________________________________________________________
void PooSweeperState::autoReveal(size_t rowIndex, size_t colIndex) {
  size_t posRow;
  size_t posCol;
  if (CellInfoStorage[rowIndex][colIndex] == REVEALED_ZERO) {
  // Iterate throug all fields around the position
    for (int x = -1; x < 2; ++x) {
      for (int y = -1; y < 2; ++y) {
        posRow = rowIndex + x;
        posCol = colIndex + y;
        // Reveal the position, only if its inside the field
        if (posRow >= 0 && posCol >= 0 && posRow < _numRows &&
         posCol < _numCols) {
          if (CellInfoStorage[posRow][posCol] == UNREVEALED) {
            PooSweeperMove autoReveal;
            autoReveal.row = posRow;
            autoReveal.col = posCol;
            autoReveal.type = PooSweeperMove::REVEAL;
            applyMove(autoReveal);
          }
        }
      }
    }
  }
}

// _____________________________________________________________________________
bool PooSweeperState::checkPoo(size_t rowIndex, size_t colIndex) const {
  if (CellInfoPoo[rowIndex][colIndex] == POO) {
    return true;
  } else {
    return false;
  }
}

// _____________________________________________________________________________
void PooSweeperState::wonGame() {
  // Calculate if game is won
  size_t numCells = _numRows * _numCols;
  size_t numRevealed = _numRevealed + _numMarked;
  size_t numUnrevealed = numCells - numRevealed;
  if (_numMarked + numUnrevealed == _numPoos) _status = WON;
}

// _____________________________________________________________________________
void PooSweeperState::revealPoos() {
  for (int i = 0; i < _numRows; ++i) {
    for (int j = 0; j < _numCols; ++j) {
      if (checkPoo(i, j)) {
        CellInfoStorage[i][j] = REVEALED_POO;
      }
    }
  }
}
