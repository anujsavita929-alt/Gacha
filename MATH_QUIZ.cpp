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
class MathQuiz {
    int mode; // 1: Easy, 2: Medium, 3: Hard
public:
    MathQuiz(int difficulty) {
        mode = difficulty;
    }

    int play() {
        int questions = 5;
        int correct = 0;

        for (int i = 0; i < questions; i++) {
            int a, b;
            char op;
            int answer;

            if (mode == 1) {
                a = rand() % 10 + 1;
                b = rand() % 10 + 1;
                op = '+';
            } else if (mode == 2) {
                a = rand() % 50 + 1;
                b = rand() % 20 + 1;
                int type = rand() % 2;
                op = type ? '+' : '-';
                if (op == '-' && a < b) swap(a, b);
            } else {
                a = rand() % 20 + 1;
                b = rand() % 10 + 1;
                int type = rand() % 3;
                if (type == 0) op = '+';
                else if (type == 1) op = '-';
                else op = '*';
                
                if (op == '-' && a < b) swap(a, b);
            }

            if (op == '+') answer = a + b;
            else if (op == '-') answer = a - b;
            else answer = a * b;

            cout << "\nQ" << (i + 1) << ": What is " << a << " " << op << " " << b << "?\n";
            cout << "Answer: ";
            int userAns;
            cin >> userAns;

            if (userAns == answer) {
                cout << "Correct!\n";
                correct++;
            } else {
                cout << "Wrong! The correct answer was " << answer << ".\n";
            }
        }

        cout << "\nYou got " << correct << " out of " << questions << " correct.\n";
        
        int base = 0;
        if (correct >= 3) {
            base = (mode == 1) ? 1 : (mode == 2 ? 3 : 5);
            if (correct == questions) base += 2; // Perfect bonus
            cout << "Total Gain: " << base << endl;
        } else {
            cout << "You didn't pass. No score gained.\n";
        }
        
        return base;
    }
};

int main() {
    srand(time(0));

    ScoreManager sm;
    sm.load();

    int mode;
    cout << "\nMATH QUIZ\n";
    cout << "1. Easy (Addition 1-10)\n2. Medium (Add/Sub 1-50)\n3. Hard (Add/Sub/Mul 1-20)\nChoice: ";
    cin >> mode;

    if (mode < 1 || mode > 3) mode = 1;

    MathQuiz game(mode);
    int gained = game.play();

    if (gained == 0) {
        mciSendStringA("play fahhhhh.mp3 wait", NULL, 0, NULL);
    }

    sm.addScore("math_quiz", gained);
    sm.save();
    sm.show();

    return 0;
}
