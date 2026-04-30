#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#pragma comment(lib, "winmm.lib")
using namespace std;

// load score from file
int loadScore() {
    ifstream file("score.txt");

    if (!file) return 0;

    string game, colon;
    int value, total = 0;

    while (file >> game >> colon >> value) {
        total += value;
    }

    return total;
}

// save only math quiz score (simple version)
void saveScore(int score) {
    ofstream file("score.txt", ios::app);
    file << "math_quiz : " << score << endl;
}

// quiz function
int playQuiz(int mode) {
    int correct = 0;

    for (int i = 0; i < 5; i++) {
        int a, b, answer;
        char op;

        // decide difficulty
        if (mode == 1) {
            a = rand() % 10 + 1;
            b = rand() % 10 + 1;
            op = '+';
        }
        else if (mode == 2) {
            a = rand() % 50 + 1;
            b = rand() % 20 + 1;

            if (rand() % 2 == 0)
                op = '+';
            else
                op = '-';

            if (op == '-' && a < b)
                swap(a, b);
        }
        else {
            a = rand() % 20 + 1;
            b = rand() % 10 + 1;

            int r = rand() % 3;
            if (r == 0) op = '+';
            else if (r == 1) op = '-';
            else op = '*';

            if (op == '-' && a < b)
                swap(a, b);
        }

        // calculate answer
        if (op == '+') answer = a + b;
        else if (op == '-') answer = a - b;
        else answer = a * b;

        cout << "\nQ" << i + 1 << ": " << a << " " << op << " " << b << " = ";
        
        int user;
        cin >> user;

        if (user == answer) {
            cout << "Correct\n";
            correct++;
        } else {
            cout << "Wrong! Answer is " << answer << endl;
        }
    }

    cout << "\nYou got " << correct << "/5 correct\n";

    int score = 0;

    if (correct >= 3) {
        if (mode == 1) score = 1;
        else if (mode == 2) score = 3;
        else score = 5;

        if (correct == 5)
            score += 2;

        cout << "Score gained: " << score << endl;
    } else {
        cout << "No score gained\n";
    }

    return score;
}

int main() {
    srand(time(0));

    cout << "MATH QUIZ\n";
    cout << "1. Easy\n2. Medium\n3. Hard\nChoice: ";

    int mode;
    cin >> mode;

    if (mode < 1 || mode > 3)
        mode = 1;

    int gained = playQuiz(mode);

    if (gained == 0) {
        mciSendStringA("play fahhhhh.mp3 wait", NULL, 0, NULL);
    }

    saveScore(gained);

    int total = loadScore();
    cout << "\nTotal Score: " << total << endl;

    return 0;
}