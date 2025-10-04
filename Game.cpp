#include "Game.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

Game::Game(const Board& b, Player* south, Player* north) : board_m(b), south_m(south), north_m(north), move_result(true) {}

void Game::display() const {
    std::cout << "--------------" << std::endl;
    std::cout << "North's Player: " << north_m->name() << std::endl;
    std::cout << "South's Player: " << south_m->name() << std:: endl;
    
    int size = board_m.holes();
    int lineLength = size + (size - 1) * 5; // Total length of the output line
    int middleIndex = lineLength / 2 + 3 + 20;
    
    std::cout << std::setw(middleIndex) << "North" << std::endl << std::endl;
    
    std::cout << "                    "; // 19 spaces for the starting index
    for (int i = 1; i <= size; i++)
    {
        std::cout << beans(NORTH, i);
        if (i != size)  // Skip the gap after the last element
        {
            std::cout << "     ";  // Five spaces for the gap
        }
    }
    std::cout << std::endl << std::endl;
    std::cout << "North's pot" << "   " << board_m.beans(NORTH, 0) << std::setw(lineLength + 11) << board_m.beans(SOUTH, 0) << "   " << "South's pot" << std::endl << std::endl;

    std::cout << "                    ";
    for (int i = 1; i <= size; i++)
    {
        std::cout << beans(SOUTH, i);
        if (i != size)  // Skip the gap after the last element
        {
            std::cout << "     ";  // Five spaces for the gap
        }
    }
    std::cout << std::endl << std::endl;
    std::cout << std::setw(middleIndex) << "South" << std::endl;
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const {
    if (move_result) {
        // Game is not over
        display();
        over = false;
        hasWinner = false;
        return;
    }

    // Game is over
    display();
    over = true;

    int southBeans = board_m.beans(SOUTH, 0);
    int northBeans = board_m.beans(NORTH, 0);

    if (southBeans == northBeans) {
        // Tie game
        hasWinner = false;
    } else {
        // Determine the winning side
        hasWinner = true;
        winner = (southBeans > northBeans) ? SOUTH : NORTH;
    }
}

bool Game::move(Side s) {
    Side endSide;
    int startHole;
    int endHole;
    int turn = 1;
    
    do {
        if (board_m.beansInPlay(s) == 0) {
            for (int i = 1; i <= board_m.holes(); i++) {
                board_m.moveToPot(opponent(s), i, opponent(s));
            }
            move_result = false;
            return false;
        }

        if (turn > 1) {
            display();
        }
        
        if (s == NORTH) {
            std::cout << "North's turn" << std::endl;
            startHole = north_m->chooseMove(board_m, s);
            if (north_m->isInteractive()) {
                std::cout << std::endl;
            } else {
                std::cout << "Hole Chosen: " << startHole << std::endl << std::endl;
            }
        } else {
            std::cout << "South's turn" << std::endl;
            startHole = south_m->chooseMove(board_m, s);
            if (north_m->isInteractive()) {
                std::cout << std::endl;
            } else {
                std::cout << "Hole Chosen: " << startHole << std::endl << std::endl;
            }
        }
        board_m.sow(s, startHole, endSide, endHole);
        turn++;
            
        if (endSide == s && endHole != 0 && board_m.beans(opponent(s), endHole) != 0 && board_m.beans(s, endHole) == 1) {
            board_m.moveToPot(s, endHole, s);
            board_m.moveToPot(opponent(s), endHole, s);
            display();
            std::cout << "Capture!" << std::endl << std::endl;
        }
            
    } while (endSide == s && endHole == 0);

    // check the opponent can move for the next turn
    if (board_m.beansInPlay(opponent(s)) == 0) {
        for (int i = 1; i <= board_m.holes(); i++) {
                board_m.moveToPot(s, i, s);
            }
        move_result = false;
        return false;
    }
    
    return true;
}

void Game::play() {
    bool over = false;
    bool hasWinner = false;
    Side winner;
    if (south_m->isInteractive() || north_m->isInteractive()) {
        bool isNorth = true;
        display();
        do {
            if (isNorth) {
                move(NORTH);
            } else {
                move(SOUTH);
            }
            isNorth = !isNorth;
            status(over, hasWinner, winner);
        } while (!over);
    } else {
        bool isNorth = true;
        display();
        do {
            if (isNorth) {
                move(NORTH);
                isNorth = !isNorth;
            } else {
                move(SOUTH);
                isNorth = !isNorth;
            }
            status(over, hasWinner, winner);
            if (over) {
                break;
            }
            std::cout << "Press Enter to continue..." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } while (!over);
    }
    
    if (hasWinner) {
        std::string winnerName;
        if (winner == NORTH) {
            winnerName = north_m->name();
        } else {
            winnerName = south_m->name();
        }
        std::cout << "The is winner is: " << winnerName << std::endl;
    } else {
        std::cout << "It's a tie game." << std::endl;
    }
    std::cout << "Game over!" << std::endl;
}

int Game::beans(Side s, int hole) const {
    return board_m.beans(s, hole);
}


