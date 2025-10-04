#ifndef Game_h
#define Game_h

#include "Board.h"
#include "Player.h"
#include "Side.h"

class Game {
public:
    Game(const Board& b, Player* south, Player* north);
    void display() const;
    void status(bool& over, bool& hasWinner, Side& winner) const;
    bool move(Side s);
    void play();
    int beans(Side s, int hole) const;
    
private:
    Board board_m;
    Player* south_m;
    Player* north_m;
    bool move_result;
};

#endif /* Game_h */
