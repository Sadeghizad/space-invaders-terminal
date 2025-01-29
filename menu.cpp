#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#include "game.h"

using namespace std;

void welcomeScreen();
void howToPlay();

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    PlayerLoc newPlayer;

    welcomeScreen();

    while (true)
    {
        system("cls");

        bool newGame = false;
        bool f = true;
        char operation;

        cout << "\u2554" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2557" << endl;
        cout << "\u2551" << " ~~~~~~~~~~~~~~~~ MENU ~~~~~~~~~~~~~~~~ " << "\u2551" << endl;
        cout << "\u255A" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u255D" << endl
             << endl;

        cout << " 1.NEW GAME         # To play the game enter 1 # " << endl;
        cout << " 2.LOAD GAME        # To load the game enter 2 # " << endl;
        cout << " 3.HOW TO PLAY      # To learn how to play enter 3 # " << endl;
        cout << " 4.LEADERBOARD      # To see the leaderboard enter 4 # " << endl;
        cout << " 5.Show characters             # To select charachter in future # " << endl;
        cout << " 6.Select color             # To select game theme # " << endl;
        cout << " 7.EXIT             # To exit the game enter 7 # " << endl;

        operation = getch();
        bool selectingTheme;

        switch (operation)
        {
        case '1':
            cout << "Enter Your name Guardian: ";
            cin >> newPlayer.player.username;
            newPlayer.player.lastLevel = 1; // Ensure starting level is set to 1
            newPlayer.player.lastWave = 1;
            reset(newPlayer.player);
            do
            {
                // reset player
                run(newPlayer, newGame);
            } while (newGame);

            break;

        case '2':
            cout << "Enter Your name Guardian: ";
            cin >> newPlayer.player.username;
            findPlayer("saves.txt", newPlayer.player.username, newPlayer.player.lastWave, newPlayer.player.lastLevel,newPlayer.player.last_saved_score,newPlayer.player.lives);
            reset(newPlayer.player);
            do
            {
                run(newPlayer, newGame);
            } while (newGame);
            break;

        case '3':
            howToPlay();
            break;

        case '4':
            displayPlayers(RECORDS_FILE);
            break;

        case '5':
            while (f)
            {
                system("cls");
                cout << "cilck 1 to 3 to show charachter and q for exit" << endl;
                char ch = getch();
                switch (ch)
                {
                case '1':
                    cout << " " << " " << "\u256d" << "\u2500" << "\u2500" << "\u2500" << "\u2500" << "\u256e" << endl;
                    cout << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << endl;
                    cout << "\u2503" << "\u2503" << "\u2503" << "\u2503" << "\u2503" << "\u2503" << "\u2503" << "\u2503" << "\u2503" << "\u2503" << endl;
                    cout << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << endl;
                    break;
                case '2':
                    cout << "\u25a0" << " " << " " << "\u25a0" << " " << " " << "\u25a0" << " " << " " << "\u25a0" << endl;
                    cout << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << endl;
                    cout << " " << " " << " " << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << " " << " " << " " << endl;
                    cout << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << endl;
                    break;
                case '3':
                    cout << "\u25a0" << " " << " " << " " << " " << " " << " " << " " << " " << "\u25a0" << endl;
                    cout << "\u25a0" << " " << " " << " " << "\u25a0" << "\u25a0" << " " << " " << " " << "\u25a0" << endl;
                    cout << " " << "\u25a0" << " " << " " << "\u25a0" << "\u25a0" << " " << " " << "\u25a0" << " " << endl;
                    cout << " " << " " << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << "\u25a0" << " " << " " << endl;
                    break;
                case 'q':
                    f = false;
                    break;

                default:
                    break;
                }
            }

            break;
        case '6':
            selectingTheme = true;
            while (selectingTheme)
            {
                system("cls");
                cout << "Select Game Theme:\n";
                cout << "1. Light Theme (White on Black)\n";
                cout << "2. Dark Theme (Bright White on Blue)\n";
                cout << "3. Green Theme (Green on Black)\n";
                cout << "4. Back to Main Menu\n";
                cout << "Enter your choice: ";

                char themeChoice = getch();
                switch (themeChoice)
                {
                case '1':
                    currentTheme = LIGHT_THEME;
                    cout << "\nLight Theme Selected!";
                    break;
                case '2':
                    currentTheme = DARK_THEME;
                    cout << "\nDark Theme Selected!";
                    break;
                case '3':
                    currentTheme = GREEN_THEME;
                    cout << "\nGreen Theme Selected!";
                    break;
                case '4':
                    selectingTheme = false;
                    continue;
                default:
                    cout << "\nInvalid choice. Try again.";
                    break;
                }
                SetColor(currentTheme.textColor,currentTheme.bgColor); // Apply the selected theme
                cout << "\nPress any key to continue...";
                getch();
            }
            break;
        case '7':
            return -1;
            break;

        default:
            break;
        }
        getch();
    }
    return 0;
}

void howToPlay()
{
    system("cls");

    cout << "\u2554" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550";
    cout << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550";
    cout << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550";
    cout << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550";
    cout << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2557" << endl;
    cout << "\u2551" << " ~~~~~~~~~~~~ HOW TO PLAY ~~~~~~~~~~~~~ " << "\u2551" << endl;
    cout << "\u255A" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550";
    cout << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550";
    cout << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550";
    cout << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u255D" << endl
         << endl;

    cout << " BASIC GAMEPLAY : " << endl
         << endl;
    cout << " The player controls the spaceship at the bottom of the screen, which can move only horizontally." << endl;
    cout << " The aliens move both horizontally and vertically (approaching the spaceship)." << endl;
    cout << " The spaceship can be controlled to shoot lasers to destroy the aliens." << endl
         << " The aliens will randomly shoot towards the spaceship." << endl;
    cout << " If an alien is shot by the spaceship, it is destroyed; if the spaceship is shot, it's health will decrease." << endl;
    cout << " You should destroy all the aliens before they destroy you or invade your planet , otherwise YOU WILL LOSE ! " << endl
         << endl;
    cout << " Press any button to go to the menu. " << endl
         << endl
         << endl;

    char operation = getch();
}

void welcomeScreen()
{
    system("cls");

    cout << R"( 
    ███████╗██████╗  █████╗  ██████╗███████╗    ██╗███╗   ██╗██╗   ██╗ █████╗ ██████╗ ███████╗██████╗ ███████╗
    ██╔════╝██╔══██╗██╔══██╗██╔════╝██╔════╝    ██║████╗  ██║██║   ██║██╔══██╗██╔══██╗██╔════╝██╔══██╗██╔════╝
    ███████╗██████╔╝███████║██║     █████╗      ██║██╔██╗ ██║██║   ██║███████║██║  ██║█████╗  ██████╔╝███████╗
    ╚════██║██╔═══╝ ██╔══██║██║     ██╔══╝      ██║██║╚██╗██║╚██╗ ██╔╝██╔══██║██║  ██║██╔══╝  ██╔══██╗╚════██║
    ███████║██║     ██║  ██║╚██████╗███████╗    ██║██║ ╚████║ ╚████╔╝ ██║  ██║██████╔╝███████╗██║  ██║███████║
    ╚══════╝╚═╝     ╚═╝  ╚═╝ ╚═════╝╚══════╝    ╚═╝╚═╝  ╚═══╝  ╚═══╝  ╚═╝  ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝╚══════╝
                                                                                                            
    )";

    cout << endl
         << endl
         << endl;
    cout << "      Welcome to the game !" << endl
         << endl;
    cout << "      Press any button to countinue." << endl;

    char operation = getch();
}