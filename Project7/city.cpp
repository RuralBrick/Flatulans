#include <iostream>
#include <cstdlib>
#include "global.h"
#include "city.h"
using namespace std;

City::City(int nRows, int nCols)
{
    if (nRows <= 0 || nCols <= 0 || nRows > MAXROWS || nCols > MAXCOLS)
    {
        cout << "***** City created with invalid size " << nRows << " by "
            << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nFlatulans = 0;
}

City::~City()
{
    delete m_player;
    for (int i = 0; i < m_nFlatulans; ++i) {
        delete m_flatulans[i];
    }
}

int City::rows() const
{
    return m_rows;
}

int City::cols() const
{
    return m_cols;
}

Player* City::player() const
{
    return m_player;
}

bool City::isPlayerAt(int r, int c) const
{
    return (m_player->row() == r) && (m_player->col() == c);
}

int City::flatulanCount() const
{
    return m_nFlatulans;
}

int City::nFlatulansAt(int r, int c) const
{
    int nFlatulans = 0;
    for (int i = 0; i < m_nFlatulans; ++i) {
        if ((m_flatulans[i]->row() == r) && (m_flatulans[i]->col() == c)) {
            nFlatulans++;
        }
    }
    return nFlatulans;
}

bool City::determineNewPosition(int& r, int& c, int dir) const
{
    bool changed = false;
    switch (dir)
    {
    case UP:
        if (r - 1 >= 1) {
            r--;
            changed = true;
        }
        break;
    case DOWN:
        if (r + 1 <= m_rows) {
            r++;
            changed = true;
        }
        break;
    case LEFT:
        if (c - 1 >= 1) {
            c--;
            changed = true;
        }
        break;
    case RIGHT:
        if (c + 1 <= m_cols) {
            c++;
            changed = true;
        }
        break;
    default:
        return false;
    }
    return changed;
}

void City::display() const
{
    // Position (row,col) in the city coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;

    // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';

    // Indicate each Flatulan's position
    for (int i = 0; i < m_nFlatulans; ++i) {
        char& gridChar = grid[m_flatulans[i]->row() - 1][m_flatulans[i]->col() - 1];
        if (gridChar == '.') {
            gridChar = 'F';
        }
        else if (gridChar == 'F') {
            gridChar = '2';
        }
        else if (gridChar >= '2' && gridChar <= '8') {
            gridChar++;
        }
    }

    // Indicate player's position
    if (m_player != nullptr)
    {
        // Set the char to '@', unless there's also a Flatulan there
        // (which should never happen), in which case set it to '*'.
        char& gridChar = grid[m_player->row() - 1][m_player->col() - 1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }

    // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

    // Write message, Flatulan, and player info
    cout << "There are " << m_nFlatulans << " unconverted Flatulans remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isPassedOut())
            cout << "The player has passed out." << endl;
        else
            cout << "The player's health level is " << m_player->health() << endl;
    }
}

bool City::addFlatulan(int r, int c)
{
    if (!isInBounds(r, c))
        return false;

    // Don't add a Flatulan on a spot with a player
    if (m_player != nullptr && m_player->row() == r && m_player->col() == c)
        return false;

    // If there are MAXFLATULANS unconverted Flatulans, return false.
    // Otherwise, dynamically allocate a new Flatulan at coordinates (r,c).
    // Save the pointer to the newly allocated Flatulan and return true.

    // Your function must work as specified in the preceding paragraph even
    // in this scenario (which won't occur in this game):  MAXFLATULANS
    // Flatulans are added, then some are converted, then more are added.

    if (m_nFlatulans >= MAXFLATULANS) {
        return false;
    }

    m_flatulans[m_nFlatulans] = new Flatulan(this, r, c);
    m_nFlatulans++;

    return true;
}

bool City::addPlayer(int r, int c)
{
    if (!isInBounds(r, c))
        return false;

    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

    // Don't add a player on a spot with a Flatulan
    if (nFlatulansAt(r, c) > 0)
        return false;

    // Dynamically allocate a new Player and add it to the city
    m_player = new Player(this, r, c);
    return true;
}

void City::preachToFlatulansAroundPlayer()
{
    // Preach to Flatulans orthogonally or diagonally adjacent to player.
    // If a Flatulan is converted, destroy it and remove it from the city,
    // since we have no further need to display it or have it interact with
    // the player.

    int nNonconverted = 0;
    for (int i = 0; i < m_nFlatulans; ++i) {
        if (m_flatulans[i]->row() >= m_player->row() - 1 &&
            m_flatulans[i]->row() <= m_player->row() + 1 &&
            m_flatulans[i]->col() >= m_player->col() - 1 &&
            m_flatulans[i]->col() <= m_player->col() + 1 &&
            m_flatulans[i]->possiblyGetConverted()) {
            delete m_flatulans[i];
        }
        else {
            m_flatulans[nNonconverted] = m_flatulans[i];
            nNonconverted++;
        }
    }
    m_nFlatulans = nNonconverted;
}

void City::moveFlatulans()
{
    for (int k = 0; k < m_nFlatulans; k++)
    {
        m_flatulans[k]->move();
        int r = m_flatulans[k]->row();
        int c = m_flatulans[k]->col();
        if (isPlayerAt(r, c - 1) || isPlayerAt(r, c + 1) ||
            isPlayerAt(r - 1, c) || isPlayerAt(r + 1, c)) {
            m_player->getGassed();
        }
    }
}

bool City::isInBounds(int r, int c) const
{
    return (r >= 1 && r <= m_rows && c >= 1 && c <= m_cols);
}