#include "global.h"
#include "game.h"

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(MAXROWS, MAXCOLS, MAXFLATULANS);

    // Play the game
    g.play();
}