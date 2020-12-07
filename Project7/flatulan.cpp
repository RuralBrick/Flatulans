#include <iostream>
#include <cstdlib>
#include "global.h"
#include "flatulan.h"
#include "city.h"
using namespace std;

Flatulan::Flatulan(City* cp, int r, int c)
{
    if (cp == nullptr)
    {
        cout << "***** A Flatulan must be created in some City!" << endl;
        exit(1);
    }
    if (r < 1 || r > cp->rows() || c < 1 || c > cp->cols())
    {
        cout << "***** Flatulan created with invalid coordinates (" << r << ","
            << c << ")!" << endl;
        exit(1);
    }
    m_city = cp;
    m_row = r;
    m_col = c;
}

int Flatulan::row() const
{
    return m_row;
}

int Flatulan::col() const
{
    return m_col;
}

void Flatulan::move()
{
    // Attempt to move in a random direction; if it can't move, don't move.
    // If the player is there, don't move.
    int dir = randInt(0, NUMDIRS - 1);  // dir is now UP, DOWN, LEFT, or RIGHT
    int newR = m_row;
    int newC = m_col;
    if (m_city->determineNewPosition(newR, newC, dir)) {
        if (!(m_city->isPlayerAt(newR, newC))) {
            m_row = newR;
            m_col = newC;
        }
    }
}

bool Flatulan::possiblyGetConverted()  // return true if converted
{
    return randInt(1, 3) != 3;
}