#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Game.h"

int main()
{
    //	Seed random
    srand((unsigned)time(NULL));

    //  Play game
    Game game = Game();
    game.PlayGame();
}