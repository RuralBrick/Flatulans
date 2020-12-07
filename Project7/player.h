#ifndef PLAYER_H
#define PLAYER_H

#include "city.h"

class Player
{
public:
    // Constructor
    Player(City* cp, int r, int c);

    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    int  health() const;
    bool isPassedOut() const;

    // Mutators
    void  preach();
    void  move(int dir);
    void  getGassed();

private:
    City* m_city;
    int   m_row;
    int   m_col;
    int   m_age;
    int   m_health;
};
#endif
