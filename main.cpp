#include <iostream>
#include <cstdlib>
#include <utility>
#include <vector>

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

vector<pair<int,int> > getPossibilities() {
    vector<pair<int, int> > possibilities;
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
    if (getPossibilities().empty()) { //Check for tie
        return 3;
    }
    return 0;
}

vector<int> checkForBlock(pair<int, int> currentPossibility, int currentGrid[3][3], int turnNum) {
    currentGrid[currentPossibility.first][currentPossibility.second] = turnNum;
    if (checkForWin(currentGrid) == turnNum) {
        return {1,currentPossibility.first, currentPossibility.second};
    }
    return {0};
}

vector<pair<int, int>> search(int depth, vector<pair<int,int>> possibilities,int currentGrid[3][3], int turnNum, vector<pair<int, int>> existingMoves) {
    
    vector<pair<int, int>> moves = existingMoves;

    for (int i = 0; i < possibilities.size(); i++) {
        //Step 1, check for available block/win
        vector<int> block = checkForBlock(possibilities[i],currentGrid, turnNum);
        if (block[0] == 1) { //If block or win possible
            moves.push_back({block[1],block[2]});
            return moves;
        } else {
            moves.push_back(possibilities[i]);
        }
    }
    if (depth > 1){search(depth-1,possibilities,currentGrid,1,moves);} else {return moves;}
}

pair<int, int> initSearch(int depth) {
    vector<pair<int,int>> possibilities = getPossibilities();
    int turnNum = 2; //Used when in depth
    vector<pair<int, int>> bestMoves; //List of all the moves that won't make the bot lose
    
    int temp[3][3] = {{},{},{}};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            temp[i][j] = grid[i][j];
        }
    }
    
    vector<pair<int, int>> moves = search(2,possibilities,temp,2,{});
    srand(time(nullptr));
    return moves[rand()%possibilities.size()]; //Pick random move from acceptable moves
}

void botTurn() {
    //cout << "Num of possibilities: " << botPossibilities.size() << endl;
    //cout << endl << "INDEX : " << index << endl << "COORDINATES: " << botPossibilities[index].first << ", " << botPossibilities[index].second << endl;
    pair<int, int> chosenCoordinates = initSearch(2);
    grid[chosenCoordinates.first][chosenCoordinates.second] = 2;
}

void playerTurn(){ //Handle out of range and already used spaces
    vector<pair<int,int> > playerPossibilities = getPossibilities();
    bool status = false;
    while (not status) {
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