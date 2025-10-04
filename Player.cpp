#include "Player.h"
#include <iostream>

Player::Player(std::string name) : name_m(name) {}

std::string Player::name() const {
    return name_m;
}

bool Player::isInteractive() const {
    return false;
}

Player::~Player() {}

HumanPlayer::HumanPlayer(std::string name) : Player(name) {}

bool HumanPlayer::isInteractive() const {
    return true;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const {
    Timer timer;

    if (b.beansInPlay(s) == 0) {
        return -1;
    }
    
    int temp_hole = 0;
    while (temp_hole < 1 || temp_hole > b.holes() || b.beans(s, temp_hole) == 0) {
        std::cout << "Choose Valid Move: ";
        std::cin >> temp_hole;
    }
    
    return temp_hole;
}

HumanPlayer::~HumanPlayer() {}

BadPlayer::BadPlayer(std::string name) : Player(name) {}

bool BadPlayer::isInteractive() const {
    return false;
}

int BadPlayer::chooseMove(const Board& b, Side s) const {
    if (b.beansInPlay(s) == 0) {
        return -1;
    }
    
    int temp_hole = 1;
    for (int i = 1; i <= b.holes(); i++) {
        if (b.beans(s, i) != 0) {
            temp_hole = i;
            break;
        }
    }
    
    return temp_hole;
}

BadPlayer::~BadPlayer() {}

SmartPlayer::SmartPlayer(std::string name) : Player(name) {}

bool SmartPlayer::isInteractive() const {
    return false;
}

int SmartPlayer::chooseMove(const Board& b, Side s) const {
    if (b.beansInPlay(s) == 0) {
        return -1;
    }
    Board temp_board = b;
    int best_value, best_hole;
    Timer timer;
    explore(temp_board, s, s, best_value, best_hole, 0, 4990, timer);
    return best_hole;
}

SmartPlayer::~SmartPlayer() {}

int SmartPlayer::result(const Board& b, Side smart_s) const {
    if (b.beansInPlay(smart_s) == 0) {
        if (b.beans(smart_s, 0) > b.totalBeans() - b.beans(smart_s, 0)) {
            return 999;
        } else if (b.beans(smart_s, 0) < b.totalBeans() - b.beans(smart_s, 0)) {
            return -999;
        } else {
            return 0;
        }
    } else {
        return b.beans(smart_s, 0) - b.beans(opponent(smart_s), 0);
    }
}

void SmartPlayer::explore(const Board& b, const Side& smart_s, Side s, int& best_value, int& best_hole, int round, double timeLimit, Timer& timer) const {
    Board temp = b;
    if (temp.beansInPlay(s) == 0) {
        best_hole = -1;
        best_value = result(temp, smart_s);
        return;
    }
    
    if (round == 50) {
        best_hole = -1;
        best_value = result(b, smart_s);
        return;
    } else if (timeLimit <= 0) {
        best_hole = -1;
        best_value = result(b, smart_s);
        return;
    } else {
        int best_value_temp;
        int best_hole_temp;

        if(s == smart_s) {
            best_value = -9999;
        } else {
            best_value = 9999;
        }
           
        for (int i = 1; i <= temp.holes(); i++) {
            if (temp.beans(s, i) != 0) {
                Side endSide;
                int startHole = i;
                int endHole;
                int turn = 1;
                double startTime = timer.elapsed();
                
                do {
                    if (temp.beansInPlay(s) == 0) {
                        for (int i = 1; i <= temp.holes(); i++) {
                            temp.moveToPot(opponent(s), i, opponent(s));
                        }
                        break;
                    }
                    
                    if (turn > 1) {
                        round++;
                        explore(temp, smart_s, s, startHole, endHole, round + 1, timeLimit, timer);
                        startHole = startHole;
                    }
                    
                    temp.sow(s, startHole, endSide, endHole);
                    turn++;
                        
                    if (endSide == s && endHole != 0 && temp.beans(opponent(s), endHole) != 0 && temp.beans(s, endHole) == 1) {
                        temp.moveToPot(s, endHole, s);
                        temp.moveToPot(opponent(s), endHole, s);
                    }
                        
                } while (endSide == s && endHole == 0);
                                
                timeLimit -= timer.elapsed();
                if (timeLimit <= 0) {
                    timeLimit = 0;
                }

                explore(temp, smart_s, opponent(s), best_value_temp, best_hole_temp, round + 1, timeLimit, timer);
                
                if(s == smart_s && best_value <= best_value_temp)
                {
                    best_value = best_value_temp;
                    best_hole = i;
                }
                else if(s == opponent(smart_s) && best_value  >= best_value_temp)
                {
                    best_value = best_value_temp;
                    best_hole = i;
                }
            }
        }
        return;
    }
}


