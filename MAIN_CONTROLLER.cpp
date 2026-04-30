#include <iostream>

#include <fstream>

#include <cstdlib>

#include <ctime>

#include <string>

#include <memory>

#include <windows.h>

#pragma comment(lib, "winmm.lib")

using namespace std;


// Probability Class

class Probability {

public:

int trash, common, rare, epic, legendary;



Probability(int t=0, int c=0, int r=0, int e=0, int l=0) 

    : trash(t), common(c), rare(r), epic(e), legendary(l) {}

};



class ScoreManager {

private:

string filename;

public:

ScoreManager(const string& file) : filename(file) {}



int getTotalScore() const {

    ifstream file(filename);

    if(!file) {

        cout << "Error opening score file!\n";

        return 0;

    }



    int total = 0;

    string game, colon;

    int value;



    while(file >> game >> colon >> value) {

        total += value;

    }



    file.close();

    return total;

}

};

//////////////////////////////////////////////////

// Game Runner Class

//////////////////////////////////////////////////

class GameRunner {

public:

void runGames() const {

    cout << "Running Tic Tac Toe...\n";

    system("TIC_TAC_TOE.exe");



    cout << "Running Number Guess...\n";

    system("NUMBER_GUESS.exe");



    cout << "Running Rock Paper Scissors...\n";

    system("ROCK_PAPER_SCISSORS.exe");



    cout << "Running Math Quiz...\n";

    system("MATH_QUIZ.exe");

}

};

//////////////////////////////////////////////////

// Strategy Base Class (Polymorphism)

//////////////////////////////////////////////////

class ProbabilityStrategy {

public:

virtual ~ProbabilityStrategy() = default;

virtual Probability getProbability(int score) const = 0;

};

//////////////////////////////////////////////////

// Derived Strategies

//////////////////////////////////////////////////

class BeginnerStrategy : public ProbabilityStrategy {

public:

Probability getProbability(int score) const override {

    return Probability(70, 20, 10, 0, 0);

}

};

class IntermediateStrategy : public ProbabilityStrategy {

public:

Probability getProbability(int score) const override {

    return Probability(60, 25, 14, 1, 0);

}

};

class AdvancedStrategy : public ProbabilityStrategy {

public:

Probability getProbability(int score) const override {

    return Probability(50, 30, 17, 2, 1);

}

};

class ProStrategy : public ProbabilityStrategy {

public:

Probability getProbability(int score) const override {

    return Probability(40, 30, 20, 7, 3);

}

};

//////////////////////////////////////////////////

// Gacha System Class

//////////////////////////////////////////////////

class GachaSystem {

private:

Probability prob;

public:

GachaSystem(const Probability& p) : prob(p) {}



string rollReward() const {

    int roll = rand() % 100;



    if(roll < prob.trash) return "Trash";

    else if(roll < prob.trash + prob.common) return "Common";

    else if(roll < prob.trash + prob.common + prob.rare) return "Rare";

    else if(roll < prob.trash + prob.common + prob.rare + prob.epic) return "Epic";

    else return "Legendary";

}



void displayProbabilities() const {

    cout << "\n--- Probability Distribution ---\n";

    cout << "Trash: " << prob.trash << "%\n";

    cout << "Common: " << prob.common << "%\n";

    cout << "Rare: " << prob.rare << "%\n";

    cout << "Epic: " << prob.epic << "%\n";

    cout << "Legendary: " << prob.legendary << "%\n";

}

};

//////////////////////////////////////////////////

// MAIN FUNCTION

//////////////////////////////////////////////////

int main() {

srand(time(0));

GameRunner runner;

runner.runGames();

ScoreManager sm("score.txt");

int totalScore = sm.getTotalScore();



cout << "\nTotal Score: " << totalScore << endl;



if (totalScore == 0) {

    mciSendStringA("play fahhhhh.mp3 wait", NULL, 0, NULL);

}



//////////////////////////////////////////////////

// Select Strategy (Polymorphism)

//////////////////////////////////////////////////

ProbabilityStrategy* strategy;



if(totalScore < 50)

    strategy = new BeginnerStrategy();

else if(totalScore >= 50 && totalScore < 90)

    strategy = new IntermediateStrategy();

else if(totalScore >= 90 && totalScore < 110)

    strategy = new AdvancedStrategy();

else

    strategy = new ProStrategy();



Probability prob = strategy->getProbability(totalScore);


GachaSystem gacha(prob);



gacha.displayProbabilities();



string reward = gacha.rollReward();



cout << "\n🎁 You Got: " << reward << endl;



if (reward == "Trash") {

    mciSendStringA("play fahhhhh.mp3 wait", NULL, 0, NULL);

}


delete strategy;



return 0;

}