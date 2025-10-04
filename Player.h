#ifndef Player_h
#define Player_h

#include <string>
#include "Board.h"
#include "Side.h"

class Player {
public:
    Player(std::string name);
    std::string name() const;
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const = 0;
    virtual ~Player();
    
private:
    std::string name_m;
};

class HumanPlayer : public Player {
public:
    HumanPlayer(std::string name);
    bool isInteractive() const;
    int chooseMove(const Board& b, Side s) const;
    ~HumanPlayer();
};

class BadPlayer : public Player {
public:
    BadPlayer(std::string name);
    bool isInteractive() const;
    int chooseMove(const Board& b, Side s) const;
    ~BadPlayer();
};

class SmartPlayer : public Player {
public:
    SmartPlayer(std::string name);
    bool isInteractive() const;
    int chooseMove(const Board& b, Side s) const;
    ~SmartPlayer();
private:
    void explore(const Board& b, const Side& smart_s, Side s, int& best_value, int& best_hole, int round, double timeLimit, Timer& timer) const;
    int result(const Board& b, Side smart_s) const;
};

#endif /* Player_h */
