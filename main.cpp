#include <iostream>
#include <cstdlib>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

int grid[3][3] = {
    {0,0,0},
    {0,0,0},
    {0,0,0}
    }; // 0 =  null, 1 = X and 2 = O

string printGrid() { //To get readable string and not memory value
    string printableGrid = "";
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++) {
            printableGrid += to_string(grid[i][j]) + ", ";
        }
        printableGrid += "\n";
    }
    return printableGrid;
}

vector<pair<int,int>> getPossibilities(int grid[3][3]) {
    vector<pair<int, int>> possibilities;
    for (int row = 0; row < 3; row++) {
        for (int i = 0; i < 3; i++) {
            if (grid[row][i] == 0) {
                possibilities.push_back(make_pair(row, i));
            }
        }
    }
    return possibilities;
}

int checkForWin(int grid[3][3]) { //Returns 0 for no one wins, 1 for X wins, 2 for O wins and 3 for tie. Player = 1 and Bot = 2
    for (int i = 0; i < 3; i++){
        if ((grid[i][0] == 1 && grid[i][1] == 1 && grid[i][2] == 1) || (grid[i][0] == 2 && grid[i][1] == 2 && grid[i][2] == 2)){
            //Row win
            return grid[i][0];
        } else if ((grid[0][i] == 1 && grid[1][i] == 1 && grid[2][i] == 1) || (grid[0][i] == 2 && grid[1][i] == 2 && grid[2][i] == 2)) {
            //Column win
            return grid[0][i];
        }
    }
    if ((grid[0][0] == 1 && grid[1][1] == 1 && grid[2][2] == 1) || (grid[0][0] == 2 && grid[1][1] == 2 && grid[2][2] == 2) || (grid[0][2] == 1 && grid[1][1] == 1 && grid[2][0] == 1) || (grid[0][2] == 2 && grid[1][1] == 2 && grid[2][0] == 2)) {
        //Cross win
        return grid[1][1];
    }
    if (getPossibilities(grid).empty()) { //Check for tie
        return 3;
    }
    return 0;
}

bool checkForBlock(pair<int, int> currentPossibility, int currentGrid[3][3], bool maximizingBot) {
    currentGrid[currentPossibility.first][currentPossibility.second] = !maximizingBot+1; //=> 2 - Bot
    if (checkForWin(currentGrid) == !maximizingBot + 1) {
        currentGrid[currentPossibility.first][currentPossibility.second] = 0;
        return true; //{1,currentPossibility.first, currentPossibility.second};
    }
    return false; //{0};
}

bool checkForPossibleWin(int grid[3][3], pair<int,int> currentMove, bool maximizingBot) {
    grid[currentMove.first][currentMove.second] = maximizingBot + 1;
    if (checkForWin(grid) == maximizingBot + 1) {return true;} else {return false;}
}

int evaluateMove(int grid[3][3], pair<int,int> currentMove, bool maximizingBot) {
    int score = 5;
    int playerInFavor = maximizingBot ? 2:1;
    int coeff = maximizingBot? 1:-1;
    cout<< "Player" << playerInFavor << endl;
    if (checkForPossibleWin(grid, currentMove, maximizingBot)) {score = 100;}
    if (checkForBlock(currentMove, grid, maximizingBot)) {score = 50;}
    
    //For later perhaps: 2 in row = 10; 1 in line = 1; else 0 AND HEATMAP
    cout<< "EVALUATING: " << score * coeff << endl;
    return score * coeff;
}

pair<int,pair<int,int>> miniMax(int depth, bool maximizingBot, int currentGrid[3][3], pair<int,int> move = {-1,-1}) { //{Evaluation; (MoveX; MoveY)}
    if (depth == 0) {
        return make_pair(evaluateMove(currentGrid, move, !maximizingBot), move);
    }
    
    if (move.first != -1 && move.second != -1) { //If there was a move passed on
        currentGrid[move.first][move.second] = maximizingBot ? 1:2;
        cout << (maximizingBot ? 1:2) << endl;
    }

    vector<pair<int,int>> possibilities = getPossibilities(currentGrid); //Get possiblities from currentGrid
    
    if  (maximizingBot) { //If bots's turn => take highest value (best move for himself)
        int maxEval = -1000000; //-1 million
        pair<int,pair<int,int>> result;
        pair<int,int> bestMove;
        for (int i = 0; i < possibilities.size(); i++) {
            int newGrid[3][3];
            copy(&currentGrid[0][0], &currentGrid[0][0] + 3 * 3, &newGrid[0][0]);
            
            result = miniMax(depth - 1, false, newGrid, possibilities[i]);
            int eval = result.first;
            //maxEval = max(maxEval, eval);
            if (maxEval < eval) {
                maxEval = eval;
                bestMove = possibilities[i];
            }
        }
        return make_pair(maxEval,bestMove);
    } else { //If player's turn => takes lowest value (best move for opponent)
        int minEval = 1000000; //+1 million
        pair<int,pair<int,int>> result;
        pair<int,int> bestMove;
        for (int i = 0; i < possibilities.size(); i++) {
            int newGrid[3][3];
            copy(&currentGrid[0][0], &currentGrid[0][0] + 3 * 3, &newGrid[0][0]);
            
            result = miniMax(depth - 1, true, newGrid, possibilities[i]);
            int eval = result.first;
            //minEval = min(minEval, eval);
            if (minEval > eval) {
                minEval = eval;
                bestMove = possibilities[i];
            }
        }
        return make_pair(minEval,bestMove); //Instead, we should return the best move instead of value
    }
}

void botTurn() {
    int gridReplica[3][3] = {{},{},{}};
    copy(&grid[0][0], &grid[0][0] + 3 * 3, &gridReplica[0][0]); //So that it doesn't affect the actual game
    
    pair<int,pair<int,int>> bestMoveValue = miniMax(2, true, gridReplica);
    cout << endl << "VALUE RETURNED: " << bestMoveValue.first << endl;
    grid[bestMoveValue.second.first][bestMoveValue.second.second] = 2;
}

void playerTurn(){ //Handle out of range and already used spaces
    vector<pair<int,int> > playerPossibilities = getPossibilities(grid);
    bool status = false;
    while (!status) {
        int xCoord, yCoord;
        cout << "Where would you like to place your mark?\nX = ";
        cin >> xCoord;
        cout << "Y = " ;
        cin >> yCoord;
        if ((xCoord >=0 && xCoord <=2) && (yCoord >=0 && yCoord <=2)) { //Check if index is in range
            for (int p = 0; p < playerPossibilities.size(); p++) {
                if (playerPossibilities[p].first == yCoord && playerPossibilities[p].second == xCoord) { //If in the possibilites vector
                    grid[yCoord][xCoord] = 1;
                    status = true;
                }
            }
        }
    }
}

int main() {
    cout << "Tic-Tac-Toe\n" << endl << printGrid() << endl;
    int win = 0;
    while (win == 0){ //Game loop

        //Player turn
        playerTurn();

        cout << printGrid() << endl;
        
        win = checkForWin(grid);
        if (win == 1) {
            cout << "You won!" << endl;
        } 
        else if (win == 2) {
            cout << "Bot won!" << endl;
        }
        else if (win == 3) {
            cout << "Tie!" << endl;
        }

        //Bot turn
        botTurn();
        
        cout << printGrid() << endl;

        win = checkForWin(grid);
        if (win == 1) {
            cout << "You won!" << endl;
        } 
        else if (win == 2) {
            cout << "Bot won!" << endl;
        }
        else if (win == 3) {
            cout << "Tie!" << endl;
        }
    }
    return 0;
}