#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#pragma comment(lib, "winmm.lib")
using namespace std;

// ================= SCORE SYSTEM =================
class ScoreManager {
    map<string, int> scores;

public:
    void load() {
        ifstream file("score.txt");
        if(!file) return;

        string game, colon;
        int value;

        while(file >> game >> colon >> value) {
            scores[game] = value;
        }
        file.close();
    }

    void save() {
        ofstream file("score.txt");
        for(auto &s : scores) {
            file << s.first << " : " << s.second << endl;
        }
        file.close();
    }

    void addScore(string game, int value) {
        scores[game] += value;
    }

    void show() {
        cout << "\n--- Scores ---\n";
        for(auto &s : scores) {
            cout << s.first << " : " << s.second << endl;
        }
    }
};

// ================= GAME CLASS =================
class TicTacToe {
    char board[3][3];
    int playerMoves;
    int mode;

public:
    TicTacToe(int difficulty) {
        mode = difficulty;
        playerMoves = 0;
        initBoard();
    }

    void initBoard() {
        char ch = '1';
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                board[i][j] = ch++;
    }

    void printBoard() {
        cout << "\n";
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                cout << " " << board[i][j] << " ";
                if(j<2) cout << "|";
            }
            cout << "\n";
            if(i<2) cout << "---+---+---\n";
        }
    }

    bool isMovesLeft() {
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(board[i][j] != 'X' && board[i][j] != 'O')
                    return true;
        return false;
    }

    bool checkWin(char p) {
        for(int i=0;i<3;i++) {
            if(board[i][0]==p && board[i][1]==p && board[i][2]==p) return true;
            if(board[0][i]==p && board[1][i]==p && board[2][i]==p) return true;
        }
        if(board[0][0]==p && board[1][1]==p && board[2][2]==p) return true;
        if(board[0][2]==p && board[1][1]==p && board[2][0]==p) return true;
        return false;
    }

    // ================= AI =================

    // EASY
    void randomMove() {
        vector<pair<int,int>> moves;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(board[i][j] != 'X' && board[i][j] != 'O')
                    moves.push_back({i,j});

        int r = rand() % moves.size();
        board[moves[r].first][moves[r].second] = 'O';
    }

    // MEDIUM
    bool tryMove(char p) {
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                if(board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    board[i][j] = p;

                    if(checkWin(p)) return true;

                    board[i][j] = temp;
                }
            }
        }
        return false;
    }

    // HARD (Minimax)
    int evaluate() {
        if(checkWin('O')) return 10;
        if(checkWin('X')) return -10;
        return 0;
    }

    int minimax(bool isMax) {
        int val = evaluate();
        if(val == 10 || val == -10) return val;
        if(!isMovesLeft()) return 0;

        if(isMax) {
            int best = -1000;
            for(int i=0;i<3;i++) {
                for(int j=0;j<3;j++) {
                    if(board[i][j] != 'X' && board[i][j] != 'O') {
                        char temp = board[i][j];
                        board[i][j] = 'O';
                        best = max(best, minimax(false));
                        board[i][j] = temp;
                    }
                }
            }
            return best;
        } else {
            int best = 1000;
            for(int i=0;i<3;i++) {
                for(int j=0;j<3;j++) {
                    if(board[i][j] != 'X' && board[i][j] != 'O') {
                        char temp = board[i][j];
                        board[i][j] = 'X';
                        best = min(best, minimax(true));
                        board[i][j] = temp;
                    }
                }
            }
            return best;
        }
    }

    pair<int,int> bestMove() {
        int bestVal = -1000;
        pair<int,int> move = {-1,-1};

        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                if(board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    board[i][j] = 'O';

                    int val = minimax(false);

                    board[i][j] = temp;

                    if(val > bestVal) {
                        move = {i,j};
                        bestVal = val;
                    }
                }
            }
        }
        return move;
    }

    void aiMove() {
        if(mode == 1) randomMove();
        else if(mode == 2) {
            if(!tryMove('O'))
                if(!tryMove('X'))
                    randomMove();
        }
        else {
            auto m = bestMove();
            board[m.first][m.second] = 'O';
        }
    }

    // ================= GAME LOOP =================
    int play() {
        while(true) {
            printBoard();

            int move;
            cout << "\nEnter move (1-9): ";
            cin >> move;

            int r = (move-1)/3;
            int c = (move-1)%3;

            if(board[r][c]=='X' || board[r][c]=='O') {
                cout << "Invalid!\n";
                continue;
            }

            board[r][c] = 'X';
            playerMoves++;

            if(checkWin('X')) {
                printBoard();
                cout << "You Win!\n";
                return calculateScore();
            }

            if(!isMovesLeft()) break;

            aiMove();

            if(checkWin('O')) {
                printBoard();
                cout << "AI Wins!\n";
                return 0;
            }

            if(!isMovesLeft()) break;
        }

        cout << "Draw!\n";
        return 0;
    }

    int calculateScore() {
        int base = (mode==1)?1:(mode==2)?3:5;
        int bonus = max(0, 5 - playerMoves);
        int total = base + bonus;

        cout << "\nBase: " << base
             << "\nBonus: " << bonus
             << "\nTotal Gain: " << total << endl;

        return total;
    }
};

// ================= MAIN =================
int main() {
    srand(time(0));

    ScoreManager sm;
    sm.load();

    int mode;
    cout << "TIC TAC TOE\n";
    cout << "1. Easy\n2. Medium\n3. Hard\nChoice: ";
    cin >> mode;

    TicTacToe game(mode);
    int gained = game.play();

    if (gained == 0) {
        mciSendStringA("play fahhhhh.mp3 wait", NULL, 0, NULL);
    }

    sm.addScore("tic_tac_toe", gained);
    sm.save();

    sm.show();

    return 0;
}