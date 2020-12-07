#include <iostream>
#include <cstdlib>
#include "global.h"
#include "player.h"
#include "city.h"
using namespace std;

Player::Player(City* cp, int r, int c)
{
    if (cp == nullptr)
    {
        cout << "***** The player must be created in some City!" << endl;
        exit(1);
    }
    if (r < 1 || r > cp->rows() || c < 1 || c > cp->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
            << "," << c << ")!" << endl;
        exit(1);
    }
    m_city = cp;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_health = PLAYER_START_HEALTH;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

int Player::age() const
{
    return m_age;
}

int Player::health() const
{
    return m_health;
}

bool Player::isPassedOut() const
{
    return m_health <= 0;
}

void Player::preach()
{
    m_age++;
    m_city->preachToFlatulansAroundPlayer();
}

void Player::move(int dir)
{
    m_age++;

    int newR = m_row;
    int newC = m_col;
    if (m_city->determineNewPosition(newR, newC, dir)) {
        if (m_city->nFlatulansAt(newR, newC) == 0) {
            m_row = newR;
            m_col = newC;
        }
    }
}

void Player::getGassed()
{
    m_health--;
}