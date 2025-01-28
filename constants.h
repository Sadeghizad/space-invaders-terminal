// constants.h
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string> // Add this line to include the string library

using namespace std; // Ensure that 'string' is recognized without 'std::'

const int GRID_ROWS = 100;
const int GRID_COLS = 130;
const int MAX_PLAYERS = 100;
const int NUM_COVERS = 2;
const int NUM_ALIENS = 13;
const char* RECORDS_FILE = "records.txt";
const int MAX_ALIEN_COLS = 18;

enum Direction
{
    LEFT,
    RIGHT
};

struct txtCol
{
    int text;
    int bg;
};

struct hitBox
{
    int x;
    int y;
};

struct enemy
{
    bool couldFire;
    int bounsScore;
    int speed;
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

#endif // CONSTANTS_H
