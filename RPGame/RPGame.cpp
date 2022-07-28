#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Game.h"

int main()
{
    //	Seed random
    srand((unsigned)time(NULL));

    //PlayGame();
    Game game = Game();
    game.PlayGame();
}