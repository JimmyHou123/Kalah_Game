# 🎮 Mancala Game Simulation (Board, Game, and Player Classes)

## 📘 Overview
This project implements a digital version of the **Mancala board game**, including the core game logic, AI decision-making strategies, and various player types. It demonstrates object-oriented programming principles in C++, recursion for AI exploration, and game-state management.

---

## ⚙️ Core Components

### 🧩 Board Class
The `Board` class represents the Mancala game board, tracking the number of holes, beans per hole, and player pots.

**Key Functions:**
- **`Board(int nHoles, int nInitialBeansPerHole)`** – Initializes the board.
- **`int holes() const`** – Returns the number of holes per side.
- **`int beans(Side s, int hole) const`** – Returns beans in a specific hole.
- **`int beansInPlay(Side s) const`** – Counts beans currently in play.
- **`int totalBeans() const`** – Returns total beans on the board.
- **`bool sow(Side s, int hole, Side& endSide, int& endHole)`** – Simulates sowing beans.
- **`bool moveToPot(Side s, int hole, Side potOwner)`** – Moves beans to a pot.
- **`bool setBeans(Side s, int hole, int beans)`** – Manually sets bean count.

---

### 🧠 Player Hierarchy
All player types inherit from the abstract `Player` class.

#### 👤 Player
- Base class for all player types.  
- Stores player name and defines virtual functions such as `isInteractive()` and `chooseMove()`.

#### 🕹️ HumanPlayer
- Interactive player controlled by user input.
- Prompts the player to choose a valid move.

#### 🤖 BadPlayer
- Simple AI that always chooses the **first available valid move**.
- Non-interactive and deterministic.

#### 🧩 SmartPlayer
- Advanced AI that uses recursive exploration and a **heuristic evaluation** function to determine the best move.
- Uses the following key functions:
  - **`chooseMove()`** – Starts recursive search to pick optimal move.
  - **`explore()`** – Depth-first search through possible moves.
  - **`result()`** – Evaluates the heuristic value of a board state.

**Heuristic Logic:**
- Returns high values (+999) for winning boards, low values (−999) for losses, and 0 for ties.
- Considers the difference between each player’s pot beans.

---

### 🕹️ Game Class
The `Game` class orchestrates the play loop and manages turns, captures, and game status.

**Key Functions:**
- **`Game(const Board& b, Player* south, Player* north)`** – Initializes a game.
- **`void display() const`** – Prints the board and player pots.
- **`void status(bool& over, bool& hasWinner, Side& winner) const`** – Reports game state.
- **`bool move(Side s)`** – Executes a move for the specified side.
- **`void play()`** – Runs the full game until completion.

---

## ▶️ How to Run

### 🧩 1. Folder Structure
Ensure all source files are in the same directory:
Mancala/
├── Board.cpp
├── Board.h
├── Game.cpp
├── Game.h
├── Player.cpp
├── Player.h
├── Side.h
└── Main.cpp

---

### ⚙️ 2. Compile

#### **On macOS / Linux**
```bash
g++ -std=c++17 Main.cpp Board.cpp Game.cpp Player.cpp -o mancala
#### **Windows**
```bash
g++ -std=c++17 Main.cpp Board.cpp Game.cpp Player.cpp -o mancala.exe

---

### 🕹️ 3. Run

#### **On macOS / Linux**
```bash
./mancala
#### **Windows**
```bash
mancala.exe

---

## 🧠 4. What Happens When You Run It

Your `Main.cpp` creates two **SmartPlayer** objects (`Marge` and `Homer`) and runs them against each other automatically:

```cpp
int main() {
    SmartPlayer hp("Marge");
    SmartPlayer bp("Homer");
    Board b(5, 2);
    Game g(b, &hp, &bp);
    g.play();
}

---

## 🧩 Optional: Play as a Human

If you want to play interactively instead of watching two AIs play against each other,  
you can modify your `Main.cpp` like this:

```cpp
int main() {
    HumanPlayer south("You");
    SmartPlayer north("AI");
    Board b(5, 2);
    Game g(b, &south, &north);
    g.play();
}


