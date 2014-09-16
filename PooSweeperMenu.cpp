// Copyright 2014, University of Freiburg
// Author: Michael Kotzjan

#include <ncurses.h>
#include <iostream>
#include "./PooSweeperMenu.h"
#include "./PooSweeperStateBase.h"
#include "./PooSweeper.h"

// _____________________________________________________________________________
PooSweeperMenu::PooSweeperMenu() {
  // Initialize screen for ncurses
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  exit = false;
}

// _____________________________________________________________________________
void PooSweeperMenu::startScreen() {
  while (true) {
    // Display all informations from the menu
    mvprintw(1, 2, "PooSweeper");
    mvprintw(3, 1, "Choose Difficulty:");
    mvprintw(5, 2, "Beginner");
    mvprintw(7, 2, "Intermediate");
    mvprintw(9, 2, "Expert");
    mvprintw(11, 2, "Custom");
    refresh();
    // Mouseevent only for the menu
    MEVENT start;
    mousemask(ALL_MOUSE_EVENTS, NULL);
    keypad(stdscr, TRUE);
    size_t ch = getch();
    if (getmouse(&start) == OK) {
      // Check for left click on specific line and set variables for
      // the initialize of the game
      if (start.bstate & BUTTON1_CLICKED) {
        if (start.y == 5) {
          // Beginner
          _rows = 9;
          _cols = 9;
          _poos = 10;
          break;
        } else if (start.y == 7) {
          // Intermediate
          _rows = 16;
          _cols = 16;
          _poos = 40;
          break;
        } else if (start.y == 9) {
          // Expert
          _rows = 16;
          _cols = 30;
          _poos = 99;
          break;
        } else if (start.y == 11) {
          // If user choose custom display another menu for input the variables
          clear();
          refresh();
          mvprintw(5, 2, "Enter x-size:");
          refresh();
          std::cin >> _rows;
          mvprintw(6, 2, "Enter y-size:");
          refresh();
          std::cin >> _cols;
          mvprintw(7, 2, "Enter number of poos:");
          refresh();
          std::cin >> _poos;
          break;
        }
      }
    }
  }
  // Clear Display and start the game with the variables
  clear();
  PooSweeper pooSweeper;
  pooSweeper.play(_rows, _cols, _poos);
}

// _____________________________________________________________________________
void PooSweeperMenu::endScreen() {
  while (true) {
    // Display the Information on the right side of the field, no matter
    // wich size
    if (POO->status() == PooSweeperStateBase::WON) {
      mvprintw(_rows / 2, _cols + 2, "You've won!");
    } else {
      mvprintw(_rows / 2, _cols + 2, "You've lost");
    }
    // Asks for replay
    mvprintw((_rows / 2) + 1, _cols + 2, "Do you want to play again? [y/n]");
    refresh();
    // Get the input
    int end = getch();
    if (end == 'y') break;
    if (end == 'n') {
      exit = true;
      break;
    }
  }
  clear();
}

// _____________________________________________________________________________
PooSweeperMenu::~PooSweeperMenu() {
  // Reset terminal
  endwin();
}
