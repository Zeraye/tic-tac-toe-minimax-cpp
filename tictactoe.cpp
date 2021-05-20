#include <iostream>
#include <vector>
#include <math.h>
#include <tuple>

using namespace std;

void drawBoard(vector<vector<char>> board);
bool checkFullBoard(vector<vector<char>> board);
vector<vector<char>> makeMove(vector<vector<char>> board, int pos, char player);
int checkWin(vector<vector<char>> board);
vector<vector<char>> makeMoveAI(vector<vector<char>> board, char player);
tuple<bool, vector<vector<char>>> minimax(vector<vector<char>> board, bool isMax);
vector<int> findPossibleMoves(vector<vector<char>> board);
int minimaxTicTacToe(vector<vector<char>> board, bool isMax);

int main() {
    vector<vector<char>> board {
        {'0', '1', '2'},
        {'3', '4', '5'},
        {'6', '7', '9'}
    };

    drawBoard(board);

    int pos;
    while (!checkFullBoard(board)) {
        cin >> pos;
        board = makeMove(board, pos, 'O');
        board = makeMoveAI(board, 'X');
        drawBoard(board);
    }

    return 0;
}

void drawBoard(vector<vector<char>> board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j != 2) { cout << "|"; }
        }
        cout << endl << "-----" << endl;
    }
}

bool checkFullBoard(vector<vector<char>> board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] != 'X' and board[i][j] != 'O') {
                return false;
            }
        }
    }
    return true;
}

vector<vector<char>> makeMove(vector<vector<char>> board, int pos, char player) {
    board[floor(pos/3)][pos%3] = player;
    return board;
}

int checkWin(vector<vector<char>> board) {
    char winPlayer = 'N';
    if (board[0][0] == board[0][1] and board[0][0] == board[0][2]) { winPlayer = board[0][0]; }
    else if (board[1][0] == board[1][1] and board[1][0] == board[1][2]) { winPlayer = board[1][0]; }
    else if (board[2][0] == board[2][1] and board[2][0] == board[2][2]) { winPlayer = board[2][0]; }

    else if (board[0][0] == board[1][0] and board[0][0] == board[2][0]) { winPlayer = board[0][0]; }
    else if (board[0][1] == board[1][1] and board[0][1] == board[2][1]) { winPlayer = board[0][1]; }
    else if (board[0][2] == board[1][2] and board[0][2] == board[2][2]) { winPlayer = board[0][2]; }

    else if (board[0][0] == board[1][1] and board[0][0] == board[2][2]) { winPlayer = board[0][0]; }
    else if (board[2][0] == board[1][1] and board[2][0] == board[0][2]) { winPlayer = board[2][0]; }

    if (winPlayer == 'N') { return 0; }
    if (winPlayer == 'O') { return 1; }
    if (winPlayer == 'X') { return 2; }
}

vector<vector<char>> makeMoveAI(vector<vector<char>> board, char player) {
    int bestEval = -10;
    int bestMove;
    vector<int> possibleMoves = findPossibleMoves(board);

    for (int i = 0; i < possibleMoves.size(); ++i) {
        vector<vector<char>> tempBoard = board;
        board = makeMove(board, possibleMoves[i], 'X');
        int eval = minimaxTicTacToe(board, true);
        board = tempBoard;
        if (eval > bestEval) {
            bestEval = eval;
            bestMove = possibleMoves[i];
        }
    }

    board = makeMove(board, bestMove, 'X');

    return board;
}

int minimaxTicTacToe(vector<vector<char>> board, bool isMax) {
    if (checkFullBoard(board)) {
        return checkWin(board);
    }

    if (isMax) {
        int maxEval = -10;
        vector<int> possibleMoves = findPossibleMoves(board);
        for (int i = 0; i < possibleMoves.size(); ++i) {
            board = makeMove(board, possibleMoves[i], 'O');
            int eval = minimaxTicTacToe(board, false);
            maxEval = max(maxEval, eval);
        }
        return maxEval;  
    }

    else {
        int minEval = 10;
        vector<int> possibleMoves = findPossibleMoves(board);
        for (int i = 0; i < possibleMoves.size(); ++i) {
            board = makeMove(board, possibleMoves[i], 'X');
            int eval = minimaxTicTacToe(board, true);
            minEval = min(minEval, eval);
        }
        return minEval;  
    }
}

vector<int> findPossibleMoves(vector<vector<char>> board) {
    vector<int> possibleMoves;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] != 'X' and board[i][j] != 'O') {
                possibleMoves.push_back(i*3 + j);
            }
        }
    }

    return possibleMoves;
}