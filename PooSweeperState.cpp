// Copyright 2014, University of Freiburg.
// Author: Michael Kotzjan

#include "./PooSweeperState.h"
#include <stdlib.h>
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
  // Set game to unrevealed and poos to no poos
  CellInfoStorage.resize(_numRows);
  CellInfoPoo.resize(_numRows);
  for (int i = 0; i < _numRows; ++i) {
    for (int j = 0; j < _numCols; ++j) {
      CellInfoStorage[i].push_back(UNREVEALED);
      CellInfoPoo[i].push_back(NO_POO);
    }
  }
  // Set poos
  for (int i = 0; i < _numPoos;) {
    pooRow = random() % _numRows;
    pooCol = random() % _numCols;
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

  if (move.type == PooSweeperMove::REVEAL) {
    if (checkPoo(move.row, move.col) == true) {
      CellInfoStorage[move.row][move.col] = REVEALED_POO;
      _status = LOST;
      ++_numRevealed;
      return;
    }
    for (int x = -1; x < 2; ++x) {
      for (int y = -1; y < 2; ++y) {
        posRow = move.row + x;
        posCol = move.col + y;
        if (CellInfoPoo[posRow][posCol] == POO) {
          ++countPoo;
        }
      }
    }
    CellInfoStorage[move.row][move.col] = CellInfo(countPoo);
    ++_numRevealed;
    return;

  } else if (move.type == PooSweeperMove::TOGGLE_MARK) {
    if (CellInfoStorage[move.row][move.col] == UNREVEALED) {
      CellInfoStorage[move.row][move.col] = MARKED;
      ++_numMarked;
    } else if (CellInfoStorage[move.row][move.col] == MARKED) {
      CellInfoStorage[move.row][move.col] = UNREVEALED;
      --_numMarked;
    }
    if (_numMarked == _numPoos) { _status = WON; }
    return;

  } else if (move.type == PooSweeperMove::LEFT_RIGHT) {
    if (CellInfoStorage[move.row][move.col] >= 1) {
      size_t posX;
      size_t posY;

      for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
          posX = move.row + i;
          posY = move.col + j;
          if (CellInfoPoo[posX][posY] == POO &&
              CellInfoStorage[posX][posY] == UNREVEALED) {
            CellInfoStorage[posX][posY] = REVEALED_POO;
            _status = LOST;
            ++_numRevealed;
            return;
          }
          if (CellInfoStorage[posX][posY] == UNREVEALED) {
            for (int x = -1; x < 2; ++x) {
              for (int y = -1; y < 2; ++y) {
                posRow = posX + x;
                posCol = posY + y;
                if (CellInfoPoo[posRow][posCol] == POO) {
                  ++countPoo;
                }
              }
            }
            CellInfoStorage[posX][posY] = CellInfo(countPoo);
            ++_numRevealed;
            return;
          }
        }
      }
    }
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
void PooSweeperState::autoReveal() {
  while (true) {
    bool tmp = false;
    size_t posRow;
    size_t posCol;
    // Iterate throug the hole field
    for (int i = 0; i < _numRows; ++i) {
      for (int j = 0; j < _numCols; ++j) {
        // Test for cell without poos near by
        if (CellInfoStorage[i][j] == REVEALED_ZERO) {
          tmp = true;
          // Iterate throug all fields around the position
          for (int x = -1; x < 2; ++x) {
            for (int y = -1; y < 2; ++y) {
              posRow = i + x;
              posCol = j + y;
              // Reveal the position
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
    }
    if (tmp != true) { break; }
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
