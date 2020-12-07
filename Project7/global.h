#pragma once
///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

inline const int MAXROWS = 20;               // max number of rows in a city
inline const int MAXCOLS = 30;               // max number of columns in a city
inline const int MAXFLATULANS = 120;         // max number of Flatulans allowed
inline const int PLAYER_START_HEALTH = 12;

inline const int UP = 0;
inline const int DOWN = 1;
inline const int LEFT = 2;
inline const int RIGHT = 3;
inline const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
int randInt(int min, int max);
void clearScreen();