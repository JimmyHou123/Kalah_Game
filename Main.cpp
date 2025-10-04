#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

int main()
{
    SmartPlayer hp("Marge");
    SmartPlayer bp("Homer");
    Board b(5, 2);
    Game g(b, &hp, &bp);
    g.play();
}
