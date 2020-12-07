#include "global.h"
#include "flatulan.h"
#include "player.h"
#include "city.h"
#include "game.h"
using namespace std;

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(MAXROWS, MAXCOLS, MAXFLATULANS);

    // Play the game
    g.play();
}