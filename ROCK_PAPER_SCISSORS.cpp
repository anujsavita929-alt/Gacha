#include <iostream>
#include <fstream>
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
class RockPaperScissors {
    int mode;
    int scoreGained;

public:
    RockPaperScissors(int difficulty) {
        mode = difficulty; // 1: Easy (1 round), 2: Best of 3, 3: Best of 5
        scoreGained = 0;
    }

    int play() {
        int roundsToWin = (mode == 1) ? 1 : (mode == 2 ? 2 : 3);
        int playerWins = 0, aiWins = 0;
        string options[3] = {"Rock", "Paper", "Scissors"};

        while (playerWins < roundsToWin && aiWins < roundsToWin) {
            cout << "\n1. Rock\n2. Paper\n3. Scissors\nChoice: ";
            int choice;
            cin >> choice;

            if (choice < 1 || choice > 3) {
                cout << "Invalid choice!\n";
                continue;
            }

            int playerMove = choice - 1;
            int aiMove = rand() % 3;

            cout << "You chose: " << options[playerMove] << endl;
            cout << "AI chose: " << options[aiMove] << endl;

            if (playerMove == aiMove) {
                cout << "It's a draw!\n";
            } else if ((playerMove == 0 && aiMove == 2) ||
                       (playerMove == 1 && aiMove == 0) ||
                       (playerMove == 2 && aiMove == 1)) {
                cout << "You win this round!\n";
                playerWins++;
            } else {
                cout << "AI wins this round!\n";
                aiWins++;
            }
            cout << "Score -> You: " << playerWins << " | AI: " << aiWins << endl;
        }

        if (playerWins > aiWins) {
            cout << "\nCongratulations! You won the game!\n";
            int base = (mode == 1) ? 1 : (mode == 2 ? 3 : 5);
            cout << "Total Gain: " << base << endl;
            return base;
        } else {
            cout << "\nYou lost the game!\n";
            return 0;
        }
    }
};

int main() {
    srand(time(0));

    ScoreManager sm;
    sm.load();

    int mode;
    cout << "\nROCK PAPER SCISSORS\n";
    cout << "1. Single Round (Easy)\n2. Best of 3 (Medium)\n3. Best of 5 (Hard)\nChoice: ";
    cin >> mode;

    if (mode < 1 || mode > 3) mode = 1;

    RockPaperScissors game(mode);
    int gained = game.play();

    if (gained == 0) {
        mciSendStringA("play fahhhhh.mp3 wait", NULL, 0, NULL);
    }

    sm.addScore("rps", gained);
    sm.save();
    sm.show();

    return 0;
}
