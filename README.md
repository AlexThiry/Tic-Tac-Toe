# Tic-Tac-Toe Game

Welcome to the Tic-Tac-Toe game implemented in C++! This console-based game features an AI opponent that uses the minimax algorithm to provide a challenging gameplay experience.

## How to Play

1. The game board is a 3x3 grid, and each cell can be empty (represented by '_'), contain an 'X' (player's mark), or an 'O' (AI's mark).
2. Players take turns making moves.
3. To make a move, enter the coordinates (X, Y) where you want to place your mark when prompted.
4. The game continues until there is a winner, a tie, or you decide to exit.

## Getting Started

1. Clone the repository to your local machine.
   ```bash
   git clone https://github.com/AlexThiry/tic-tac-toe.git
   cd tic-tac-toe
   ```

2. Compile the source code using a C++ compiler.
   ```bash
   g++ main.cpp
   ```

3. Run the executable.
   ```bash
   ./a.out
   ```

## Gameplay Instructions

1. Upon starting the game, you will be prompted to choose whether you want to play first (y) or let the AI play first (n).

2. Enter your moves by providing the X and Y coordinates when prompted.

3. The game will display the current state of the board after each move.

4. The game ends when there is a winner, a tie, or you decide to exit.

**PLEASE NOTE** The coordinate system is different => top left corner is (0,0) and bottom right corner is (2,2)

## Game Features

- **Minimax Algorithm:** The AI opponent uses the minimax algorithm to make strategic moves.

- **Game Loop:** The main game loop ensures a seamless and engaging experience until the game concludes.

- **Winning and Tie Detection:** The game checks for a winner or a tie after each move.

- **Readability:** The code is structured and includes comments for better understanding.

Feel free to explore, modify, and enhance the game! If you encounter any issues or have suggestions for improvement, please create an issue or submit a pull request.

Have fun!
