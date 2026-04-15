#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#pragma comment(lib, "winmm.lib")
using namespace std;

// ================= SCORE MANAGER =================
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
class GuessNumber {
    int mode;
    int maxNum;
    int maxTries;
    int target;

public:
    GuessNumber(int difficulty) {
        mode = difficulty;
        setup();
    }

    void setup() {
        if(mode == 1) {
            maxNum = 50;
            maxTries = 10;
        }
        else if(mode == 2) {
            maxNum = 100;
            maxTries = 7;
        }
        else {
            maxNum = 200;
            maxTries = 5;
        }

        target = rand() % maxNum + 1;
    }

    int play() {
        int guess, attempts = 0;

        cout << "\nGuess number between 1 and " << maxNum << endl;

        while(attempts < maxTries) {
            cout << "Attempt " << attempts + 1 << "/" << maxTries << ": ";
            cin >> guess;

            attempts++;

            if(guess == target) {
                cout << "🎉 Correct!\n";
                return calculateScore(attempts);
            }
            else if(guess < target) {
                cout << "Too low!\n";
            }
            else {
                cout << "Too high!\n";
            }
        }

        cout << "❌ You lost! Number was: " << target << endl;
        return 0;
    }

    int calculateScore(int attempts) {
        // Base score (difficulty)
        int base = (mode==1)?10:(mode==2)?20:30;

        // Bonus (performance)
        int bonus = (maxTries - attempts) * 5;
        if(bonus < 0) bonus = 0;

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
    cout << "GUESS NUMBER GAME\n";
    cout << "1. Easy (1-50)\n2. Medium (1-100)\n3. Hard (1-200)\nChoice: ";
    cin >> mode;

    GuessNumber game(mode);
    int gained = game.play();

    if (gained == 0) {
        mciSendStringA("play fahhhhh.mp3 wait", NULL, 0, NULL);
    }

    sm.addScore("guess_number", gained);
    sm.save();

    sm.show();

    return 0;
}