#ifndef Board_h
#define Board_h

#include "Side.h"
#include <vector>

class Board {
public:
    Board(int nHoles, int nInitialBeansPerHole);
    ~Board();
    int holes() const;
    int beans(Side s, int hole) const;
    int beansInPlay(Side s) const;
    int totalBeans() const;
    bool sow(Side s, int hole, Side& endSide, int& endHole);
    bool moveToPot(Side s, int hole, Side potOwner);
    bool setBeans(Side s, int hole, int beans);
    
private:
    int nHoles_m;
    int initBeans;
    std::vector<int> N_holes;
    std::vector<int> S_holes;
};

#endif /* Board_h */
