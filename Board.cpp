#include "Board.h"

Board::Board(int nHoles, int nInitialBeansPerHole) : initBeans(nInitialBeansPerHole){
    if (nHoles == 0) {
        nHoles_m = 1;
    } else if (nHoles < 0) {
        nHoles_m = 0;
    } else {
        nHoles_m = nHoles;
    }
    const int const_temp = nHoles_m + 1;
    N_holes.resize(const_temp);
    S_holes.resize(const_temp);
   
    N_holes[0] = 0;
    S_holes[0] = 0;
    for (int i = 1; i < const_temp; i++) {
        N_holes[i] = nInitialBeansPerHole;
        S_holes[i] = nInitialBeansPerHole;
    }
}

Board::~Board() {}

int Board::holes() const {
    return nHoles_m;
}
int Board::beans(Side s, int hole) const {
    if (hole < 0 || hole > nHoles_m) {
        return -1;
    }
    
    if (s == NORTH) {
        return N_holes[hole];
    } else {
        return S_holes[hole];
    }
}

int Board::beansInPlay(Side s) const {
    if (s == NORTH) {
        int count = 0;
        for (int i = 1; i < nHoles_m + 1; i++) {
            count += N_holes[i];
        }
        return count;
    } else {
        int count = 0;
        for (int i = 1; i < nHoles_m + 1; i++) {
            count += S_holes[i];
        }
        return count;
    }
}

int Board::totalBeans() const {
    int count = 0;
    for (int i = 0; i < nHoles_m + 1; i++) {
        count += N_holes[i] + S_holes[i];
    }
    return count;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole) {
    if (hole < 1 || hole > nHoles_m) {
        return false;
    }
    
    int n_beans;
    if (s == NORTH) {
        if (N_holes[hole] == 0) {
            return false;
        } else {
            n_beans = N_holes[hole];
            N_holes[hole] = 0;
        }
    } else {
        if (S_holes[hole] == 0) {
            return false;
        } else {
            n_beans = S_holes[hole];
            S_holes[hole] = 0;
        }
    }
    
    Side temp_s = s;
    Side temp_turn = s;
    int temp_hole = hole;
    while (n_beans != 0) {
        if (temp_hole == 0) {
            if (temp_s == NORTH) {
                temp_hole = 1;
            } else {
                temp_hole = nHoles_m;
            }
            temp_s = opponent(temp_s);
        } else if (temp_s == SOUTH && temp_hole == nHoles_m) {
            temp_hole = 0;
        } else {
            if (temp_s == NORTH) {
                temp_hole--;
            } else {
                temp_hole++;
            }
        }
        
        if (temp_hole == 0 && temp_s != temp_turn) {
            continue;
        }
        
        if (temp_s == NORTH) {
            N_holes[temp_hole]++;
            n_beans--;
        } else {
            S_holes[temp_hole]++;
            n_beans--;
        }
    }
    
    endSide = temp_s;
    endHole = temp_hole;
    
    return true;
}

bool Board::moveToPot(Side s, int hole, Side potOwner) {
    if (hole < 1 || hole > nHoles_m){
        return false;
    }
    
    if (potOwner == NORTH) {
        if (s == NORTH) {
            N_holes[0] += N_holes[hole];
            N_holes[hole] = 0;
        } else {
            N_holes[0] += S_holes[hole];
            S_holes[hole] = 0;
        }
    } else {
        if (s == NORTH) {
            S_holes[0] += N_holes[hole];
            N_holes[hole] = 0;
        } else {
            S_holes[0] += S_holes[hole];
            S_holes[hole] = 0;
        }
    }
    
    return true;
}

bool Board::setBeans(Side s, int hole, int beans) {
    if (hole < 0 || hole > nHoles_m || beans < 0) {
        return false;
    }
    
    if (s == NORTH) {
        N_holes[hole] = beans;
    } else {
        S_holes[hole] = beans;
    }
    
    return true;
}
