// Copyright 2014, University of Freiburg.
// Michael Kotzjan

#include "./PooSweeperMenu.h"

// Main function
int main(int argc, char** argv) {
  // Object of PooSweeperMenu
  PooSweeperMenu menu;
  while (true) {
    // Initialize the screen for the Menu
    menu.startScreen();
    menu.endScreen();
    if (menu.exit == true) break;
  }
}
