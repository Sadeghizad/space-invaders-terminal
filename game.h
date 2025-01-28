#ifndef GAME_H
#define Game_H
#include <iostream>
#include <conio.h>
#include <ctime>
#include <chrono>
#include <thread>

// #include "sound.h"
#include "logic.h"
#include "pause.h"

using namespace std;
enemy a1{1, 10, 1};
enemy a2{1, 20, 1};
enemy a3{1, 40, 1};
enemy rA{0, 100, 2};

int firstRow = redAlienHB.y;
int secondRow = redAlienHB.y * 2 + 1;
int thirdRow = redAlienHB.y * 3 + 1;
int firstCol = 8 * 0;
int secondCol = 8 * 1;
int thirdCol = 8 * 2;
int forthCol = 8 * 3;
EnemyGroup enemies[NUM_ALIENS] = {
    // Initialize each enemy with appropriate hitBox and type
    {enemy{false, 10, 1}, alien1NormalHB, "alien1", firstCol, firstRow},
    {enemy{false, 10, 1}, alien1NormalHB, "alien1", secondCol, firstRow},
    {enemy{false, 10, 1}, alien1NormalHB, "alien1", thirdCol, firstRow},
    {enemy{false, 10, 1}, alien1NormalHB, "alien1", forthCol, firstRow},
    {enemy{false, 20, 1}, alien2NormalHB, "alien2", firstCol, secondRow},
    {enemy{false, 20, 1}, alien2NormalHB, "alien2", secondCol, secondRow},
    {enemy{false, 20, 1}, alien2NormalHB, "alien2", thirdCol, secondRow},
    {enemy{false, 20, 1}, alien2NormalHB, "alien2", forthCol, secondRow},
    {enemy{false, 30, 1}, alien3NormalHB, "alien3", firstCol, thirdRow},
    {enemy{false, 30, 1}, alien3NormalHB, "alien3", secondCol, thirdRow},
    {enemy{false, 30, 1}, alien3NormalHB, "alien3", thirdCol, thirdRow},
    {enemy{false, 30, 1}, alien3NormalHB, "alien3", forthCol, thirdRow},
    {enemy{false, 50, 2}, redAlienHB, "redAlien", firstCol, 0}};
shield covers[NUM_COVERS] = {
    {0, 30, true, false, coverLeftFullHB},
    {50, 30, true, false, coverRightFullHB}};
void insertAliensGrid(string grid[][GRID_COLS], bool alternative);
void initWave(bool &initiatedWave, EnemyGroup enemies[], int wave);
void displayCalibrationBox();
void initGrid(int rows, int cols, string grid[][GRID_COLS]);
void controllHandler(string grid[][GRID_COLS], PlayerLoc &player, bullet &playerBullet);
// void delGrid(int rows, string grid[][GRID_COLS]); // for dynamic feature

void run(PlayerLoc player, bool &newGame)
{
    string grid[GRID_ROWS][GRID_COLS];
    bullet playerBullet;
    bullet enemyBullet;
    const int target_fps = 4;
    const chrono::duration<double, milli> frame_duration(1000.0 / target_fps);

    displayCalibrationBox();
    initGrid(GRID_ROWS, GRID_COLS, grid);
    Direction direct;
    bool isRunning = true;
    bool save = false;
    bool loose = false;
    bool initiatedWave = false;
    int frame_count = 0;
    // player.player.lastLevel = 1;
    while (isRunning)
    {
        chrono::steady_clock::time_point frame_start = chrono::steady_clock::now();

        // Game logic update
        controllHandler(grid, player, playerBullet);
        initWave(initiatedWave, enemies, player.player.lastWave);
        hitCheck(player, covers, playerBullet, enemyBullet);

        // Insert Entities
        // reset grid
        // initGrid(GRID_ROWS, GRID_COLS, grid);

        insertIntoGrid(spaceShip, spaceShipHB.y, grid, player.y, player.x);
        if (playerBullet.isShoot)
        {
            insertIntoGrid(tir, tirHB.y, grid, playerBullet.y, playerBullet.x);
        }
        insertAliensGrid(grid, frame_count % 2 == 0);

        // Rendering
        render(grid);
        cout << "x: " << player.x << endl;
        cout << "score: " << player.player.score << endl;
        cout << "level: " << player.player.lastLevel << endl;
        cout << "wave: " << player.player.lastWave << endl;
        cout << "playtime: " << player.player.playtime << endl;
        cout << "lives: " << player.player.lives << endl;
        chrono::duration<double, milli> elapsed_time = chrono::steady_clock::now() - frame_start;
        if (elapsed_time < frame_duration)
        {
            std::this_thread::sleep_for(frame_duration - elapsed_time);
        }

        // Exit condition for demonstration
        if (_kbhit() && _getch() == 27) // Press 'q' to exit
        {
            pause(isRunning, newGame, save, player.player); // it is too late to rename player for clean code
        }

        if (playerBullet.isShoot)
        {
            if (frame_count % 2 == 0)
            {

                eraseFromGrid(tir, tirHB.y, grid, playerBullet.y, playerBullet.x);
                if (playerBullet.y > 0)
                    playerBullet.y--;
                else
                    playerBullet.isShoot = false;
            }
        }
        moveAliens(grid, direct, enemies);
        frame_count++;
    }
    if (player.player.lives < 1)
    {
        saveRecord("records.txt", player.player);
    }
    else
    {
        if (save)
        {
            saveAndExit(player.player);
        }
        if (newGame)
        {
            return;
        }
    }
    cout << "Game Over(it always happen XD)" << endl;
    // delGrid(GRID_ROWS, grid); // for dynamic feature
    getch();
}
void displayCalibrationBox()
{
    int opt = 0;
    cout << "Resize or zoom your terminal until the grid that will shown fits comfortably:\nif it doesnt resize then press 'R' to retry\n";
    cin.ignore();
    do
    {
        for (int i = 0; i < GRID_ROWS; i++)
        {
            for (int j = 0; j < GRID_COLS; j++)
            {
                cout << (j == GRID_COLS - 1 ? "|" : "-");
            }
            cout << "\n";
        }
        cout << "Press Enter when ready...\n";
        opt = getch();
        system("cls");
    } while (opt != 13);
    system("cls");
}

void initGrid(int rows, int cols, string grid[][GRID_COLS])
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            grid[i][j] = " "; // Default empty cell
        }
    }
}
void controllHandler(string grid[][GRID_COLS], PlayerLoc &player, bullet &playerBullet)
{
    if (_kbhit()) // Check if a key has been pressed
    {
        int ch = _getch(); // Get the key without waiting for Enter

        if (ch == 'a') // Move left
        {
            eraseFromGrid(spaceShip, spaceShipHB.y, grid, player.y, player.x);
            movePlayer(player, false);
        }
        else if (ch == 'd') // Move right
        {
            eraseFromGrid(spaceShip, spaceShipHB.y, grid, player.y, player.x);
            movePlayer(player, true);
        }

        if (ch == 32) // Spacebar is pressed for shooting
        {
            if (!playerBullet.isShoot) // Only fire if not already fired
            {
                playerBullet.isShoot = true;
                playerBullet.x = player.x + 10 / 2; // Center the bullet
                playerBullet.y = player.y - 1;
            }
        }

        while (_kbhit()) // Clear the input buffer
        {
            _getch();
        }
    }
}
void initWave(bool &initiatedWave, EnemyGroup enemies[], int wave)
{
    if (!initiatedWave)
    {
        for (int i = 0; i < NUM_ALIENS; i++)
        {
            enemies[i].enemyIns.isAlive = true;
        }
        initiatedWave = true;
    }
}
void insertAliensGrid(string grid[][GRID_COLS], bool alternative)
{
    //
}

// for dynamic feature
// void delGrid(int rows, string grid[][GRID_COLS])
// {
//     for (int i = 0; i < rows; ++i)
//     {
//         delete[] grid[i]; // Deallocate each row
//     }
//     delete[] grid; // Deallocate the array of row pointers
// }

#endif