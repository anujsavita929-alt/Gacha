# C++ Gacha System & Mini-Games

A terminal-based C++ suite containing a collection of mini-games. The system accumulates your scores across these games and uses them to determine your probability odds in a pseudo-roulette "Gacha" system! 

## Included Games
1. **Rock Paper Scissors**: Classic RPS against an AI (Single, Best of 3, or Best of 5).
2. **Tic Tac Toe**: Noughts and Crosses against an AI with varying difficulties (Random, Medium, Minimax AI).
3. **Math Quiz**: Quick-fire math equations.
4. **Number Guess**: Guess the randomly generated number within a set amount of attempts.

## Core Features
*   **Persistent Scores**: Scores are saved across executions in `score.txt`. 
*   **Polymorphic Probabilities**: 
    The probability for different Gacha drops (Trash, Common, Rare, Epic, Legendary) adjusts dynamically based on your total accumulated score across all the mini-games.
*   **Dynamic Audio Feedback**: Plays a custom sound (`fahhhhh.mp3`) via the `mciSendStringA` multimedia library if a game yields 0 points, or if the user's gacha roll results in the "Trash" tier.

## How To Run

**Requirements**: 
* Windows OS
* GNU C++ Compiler (MinGW GCC) or equivalent MSVC environment.

This project uses the native `<windows.h>` media libraries.

### Quick Setup (using VS Code)
If you are using the **Code Runner** extension in VS Code, we've bundled a `.vscode/settings.json` that sets up the correct build flags for MinGW. You can simply press the *Play* button on `MAIN_CONTROLLER.cpp`!

### Manual Compilation
Open up your terminal or PowerShell and run the individual build commands:
```powershell
g++ MATH_QUIZ.cpp -o MATH_QUIZ.exe -lwinmm
g++ TIC_TAC_TOE.cpp -o TIC_TAC_TOE.exe -lwinmm
g++ ROCK_PAPER_SCISSORS.cpp -o ROCK_PAPER_SCISSORS.exe -lwinmm
g++ NUMBER_GUESS.cpp -o NUMBER_GUESS.exe -lwinmm
g++ MAIN_CONTROLLER.cpp -o MAIN_CONTROLLER.exe -lwinmm
```

Then, run the main controller file:
```powershell
.\MAIN_CONTROLLER.exe
```
