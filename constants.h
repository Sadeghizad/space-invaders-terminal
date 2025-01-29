// constants.h
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string> // Add this line to include the string library

using namespace std; // Ensure that 'string' is recognized without 'std::'

const int GRID_ROWS = 70;
const int GRID_COLS = 130;
const int MAX_PLAYERS = 100;
const int NUM_COVERS = 2;
const int NUM_ALIENS = 13;
const int MAX_ENEMY_BULLETS = 5;
const char *RECORDS_FILE = "records.txt";
const int MAX_ALIEN_COLS = 18;
const int playerSpeed = 2;
const int BulletsSpeed = 2;
enum Direction
{
    LEFT,
    RIGHT
};

struct Theme
{
    int textColor;
    int bgColor;
};

// Predefined themes
const Theme LIGHT_THEME = {7, 0};  // White text on Black background
const Theme DARK_THEME = {15, 1};  // Bright White text on Blue background
const Theme GREEN_THEME = {10, 0}; // Green text on Black background
const Theme BLUE_THEME = {15, 16}; // White text on Blue background
// Add more themes as desired
extern Theme currentTheme = LIGHT_THEME;

struct hitBox
{
    int x;
    int y;
};

struct enemy
{
    bool couldFire = false;
    int bounsScore = 0;
    bool isAlive = false;
    bool isAlternate = false;
};

struct Player
{
    char username[50] = "Unknown";
    int lastWave = 1;
    int score = 0;
    int playtime = 0;
    int lastLevel = 1;
    int lives = 3;
    int last_saved_score = 0;
};

struct PlayerLoc
{
    const int y = GRID_ROWS - 5;
    int x = GRID_COLS / 2;
    Player player;
};

struct EnemyGroup
{
    enemy enemyIns;
    hitBox hb;
    string type; // Now recognized as 'std::string' due to inclusion
    int x;
    int y;
};

struct bullet
{
    int x;
    int y;
    int dmg;
    bool isShoot;
};

struct shield
{
    int x;
    int y;
    bool exist;
    bool isBroken;
    hitBox hb;
};
void setCursor(int x, int y)
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = x;
    Position.Y = y;
    SetConsoleCursorPosition(hOut, Position);
}
#endif // CONSTANTS_H
