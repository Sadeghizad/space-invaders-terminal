#ifndef ALIENS_H
#define ALIENS_H
#include <iostream>
#include <windows.h>
#include "constants.h"

using namespace std;

void SetColor(int textColor, int bgColor);

void SetColor(int textColor, int bgColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

const string spaceShip[4][MAX_ALIEN_COLS] = {
    {" ", " ", "\u256d", "\u2500", "\u2500", "\u2500", "\u2500", "\u256e", " ", " ", "G", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G"},
    {"\u2503", "\u2503", "\u2503", "\u2503", "\u2503", "\u2503", "\u2503", "\u2503", "\u2503", "\u2503", "G", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G"}};

const hitBox spaceShipHB{10, 4};

const string spaceShip1[4][MAX_ALIEN_COLS] = {
    {"\u25a0", " ", " ", "\u25a0", " ", " ", "\u25a0", " ", " ", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G"},
    {" ", " ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", " ", "G", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G"}};

const string spaceShip2[4][MAX_ALIEN_COLS] = {
    {"\u25a0", " ", " ", " ", " ", " ", " ", " ", " ", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", " ", " ", " ", "\u25a0", "\u25a0", " ", " ", " ", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G"},
    {" ", "\u25a0", " ", " ", "\u25a0", "\u25a0", " ", " ", "\u25a0", " ", "G", "G", "G", "G", "G", "G", "G", "G"},
    {" ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", "G", "G", "G", "G", "G", "G", "G", "G"}};

const string alien1Normal[6][MAX_ALIEN_COLS] = {
    {" ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", "G", "G", "G", "G", "G", "G", "G"},
    {" ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", "\u25a0", "(", "O", ")", "\u25a0", "(", "O", ")", "\u25a0", "\u25a0", "G", "G", "G", "G", "G", "G", "G"},
    {" ", " ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", " ", "G", "G", "G", "G", "G", "G", "G"},
    {" ", " ", "\u25a0", " ", " ", " ", " ", " ", "\u25a0", " ", " ", "G", "G", "G", "G", "G", "G", "G"},
    {" ", "\u25a0", " ", " ", " ", " ", " ", " ", " ", "\u25a0", " ", "G", "G", "G", "G", "G", "G", "G"}};

const hitBox alien1NormalHB{11, 6};

const string alien1Alternate[6][MAX_ALIEN_COLS] = {
    {" ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", "G", "G", "G", "G", "G", "G", "G"},
    {" ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", "\u25a0", "(", "O", ")", "\u25a0", "(", "O", ")", "\u25a0", "\u25a0", "G", "G", "G", "G", "G", "G", "G"},
    {" ", " ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", " ", "G", "G", "G", "G", "G", "G", "G"},
    {" ", " ", "\u25a0", " ", " ", " ", " ", " ", "\u25a0", " ", " ", "G", "G", "G", "G", "G", "G", "G"},
    {" ", " ", " ", "\u25a0", " ", " ", " ", "\u25a0", " ", " ", " ", "G", "G", "G", "G", "G", "G", "G"}};

const string alien2Normal[6][MAX_ALIEN_COLS] = {
    {" ", " ", " ", " ", "\u25a0", " ", "\u25a0", " ", " ", " ", " ", "G", "G", "G", "G", "G", "G", "G"},
    {" ", " ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", " ", "G", "G", "G", "G", "G", "G", "G"},
    {" ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", "\u25a0", "[", "O", "]", "\u25a0", "[", "O", "]", "\u25a0", "\u25a0", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", " ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", "\u25a0", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", " ", " ", " ", " ", " ", " ", " ", " ", " ", "\u25a0", "G", "G", "G", "G", "G", "G", "G"}};

const hitBox alien2NormalHB{11, 6};

const string alien2Alternate[6][MAX_ALIEN_COLS] = {
    {" ", " ", " ", " ", "\u25a0", " ", "\u25a0", " ", " ", " ", " ", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", " ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", "\u25a0", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", "\u25a0", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", "\u25a0", "[", "O", "]", "\u25a0", "[", "O", "]", "\u25a0", "\u25a0", "G", "G", "G", "G", "G", "G", "G"},
    {" ", " ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", " ", "G", "G", "G", "G", "G", "G", "G"},
    {" ", " ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", " ", "G", "G", "G", "G", "G", "G", "G"}};

const string alien3Normal[7][MAX_ALIEN_COLS] = {
    {" ", "\u25a0", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
    {"\u25a0", " ", " ", " ", " ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", " ", " ", " ", " ", "G"},
    {" ", "\u25a0", " ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", " ", " ", "G"},
    {" ", " ", "\u25a0", "\u25a0", "\u25a0", "(", "O", ")", "\u25a0", "(", "O", ")", "\u25a0", "\u25a0", "\u25a0", " ", " ", "G"},
    {" ", " ", " ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", "\u25a0", "G", "G"},
    {" ", " ", " ", " ", " ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", " ", " ", " ", "\u25a0", "G"},
    {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "\u25a0", " ", "G"}};

const hitBox alien3NormalHB{MAX_ALIEN_COLS, 7};

const string alien3Alternate[7][MAX_ALIEN_COLS] = {
    {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "\u25a0", " ", " "},
    {" ", " ", " ", " ", " ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", " ", " ", " ", "\u25a0", "G"},
    {" ", " ", " ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", "\u25a0", " ", "G"},
    {" ", " ", "\u25a0", "\u25a0", "\u25a0", "(", "O", ")", "\u25a0", "(", "O", ")", "\u25a0", "\u25a0", "\u25a0", " ", " ", "G"},
    {" ", "\u25a0", " ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", "G", "G", "G"},
    {"\u25a0", " ", " ", " ", " ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", " ", " ", "G", "G", "G"},
    {" ", "\u25a0", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "G"}};

const string redAlien[6][MAX_ALIEN_COLS] = {
    {" ", " ", " ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", " ", "G"},
    {" ", " ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", "G", "G"},
    {"\u25a0", "\u25a0", "(", "O", ")", "\u25a0", "\u25a0", "(", " ", " ", ")", "\u25a0", "\u25a0", "(", "O", ")", "\u25a0", "\u25a0"},
    {"\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0"},
    {" ", " ", "\u25a0", "\u25a0", "\u25a0", " ", " ", " ", "\u25a0", "\u25a0", " ", " ", " ", "\u25a0", "\u25a0", "\u25a0", " ", " "},
    {" ", " ", " ", "\u25a0", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "\u25a0", " ", " ", " "}};

const hitBox redAlienHB{MAX_ALIEN_COLS, 6};

const string coverRightFull[7][MAX_ALIEN_COLS] = {
    {"\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {" ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {" ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {" ", " ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"}};

const hitBox coverRightFullHB{8, 7};

const string coverRightBroken[7][MAX_ALIEN_COLS] = {
    {"\u25a0", " ", "\u25a0", "\u25a0", " ", "\u25a0", " ", " ", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", " ", "\u25a0", " ", "\u25a0", "\u25a0", "\u25a0", " ", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", " ", "\u25a0", "\u25a0", " ", "\u25a0", " ", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {" ", "\u25a0", " ", "\u25a0", "\u25a0", "\u25a0", " ", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {" ", " ", "\u25a0", "\u25a0", " ", " ", " ", " ", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {" ", " ", " ", "\u25a0", "\u25a0", "\u25a0", " ", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {" ", " ", " ", " ", "\u25a0", "\u25a0", " ", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"}};

const string coverLeftFull[7][MAX_ALIEN_COLS] = {
    {" ", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {" ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", " ", " ", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"}};

const hitBox coverLeftFullHB{8, 7};

const string coverLeftBroken[7][MAX_ALIEN_COLS] = {
    {" ", " ", "\u25a0", " ", "\u25a0", " ", "\u25a0", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {" ", "\u25a0", "\u25a0", " ", "\u25a0", " ", "\u25a0", " ", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", " ", "\u25a0", "\u25a0", " ", "\u25a0", " ", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", "\u25a0", "\u25a0", " ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {" ", "\u25a0", "\u25a0", "\u25a0", "\u25a0", " ", "\u25a0", " ", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", "\u25a0", " ", "\u25a0", " ", "\u25a0", " ", " ", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"},
    {"\u25a0", " ", "\u25a0", " ", "\u25a0", " ", " ", " ", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"}};

const string tir[1][MAX_ALIEN_COLS] = {
    {"\u2588", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"}};

const hitBox tirHB{1, 1};

int charachterChoose()
{
    while (true)
    {
        system("cls");
        cout << "cilck 1 to 3 to show charachter and y to select" << endl;
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

        default:
            break;
        }
        char ans = getch();
        if (ans == 'y')
            return int(ch) - 48;
    }
}

#endif