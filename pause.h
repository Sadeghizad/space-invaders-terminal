#ifndef PAUSE_H
#define PAUSE_H
#include <iostream>
#include <conio.h>
#include <fstream>
#include "logic.h"

using namespace std;

void saveAndExit(Player player)
{
    system("cls");

    cout << " Saving game...\n";
    updatefile("saves.txt", player);
    cout << "Game saved successfully.\n";
    cout << "Game saved at strat of this wave.\n";
}

void pause(bool &isRunning, bool &newGame, bool &save, Player player)
{
    while (true)
    {
    system("cls");
        cout << R"(
        ██████   █████  ██    ██ ███████ ███████     ███    ███ ███████ ███    ██ ██    ██ 
        ██   ██ ██   ██ ██    ██ ██      ██          ████  ████ ██      ████   ██ ██    ██ 
        ██████  ███████ ██    ██ ███████ █████       ██ ████ ██ █████   ██ ██  ██ ██    ██ 
        ██      ██   ██ ██    ██      ██ ██          ██  ██  ██ ██      ██  ██ ██ ██    ██ 
        ██      ██   ██  ██████  ███████ ███████     ██      ██ ███████ ██   ████  ██████  
                                                                                        
                                                                                        
        )";

        cout << endl
             << endl;

        cout << " 1. RESUME          ~ Press 1 to resume. ~ " << endl;
        cout << " 2. RESET        ~ Press 2 to start a new game. ~ " << endl;
        cout << " 3. SAVE AND EXIT          ~ Press 3 to save and exit the game. ~ " << endl;

        char operation = getch();

        switch (operation)
        {
        case '1':
            return;
        case 27:
            return;

        case '2':
            isRunning = false;
            newGame = true;
            return;

        case '3':
            isRunning = false;
            save=true;
            return;

        default:
            break;
        }
    }
}

#endif