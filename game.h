#ifndef GAME_H
#define Game_H
#include <iostream>
#include <conio.h>
#include <ctime>
#include <chrono>
#include <thread>

#include "filehandler.h"
#include "pause.h"
#include "constants.h"

using namespace std;
enemy a1{true, 10, 1};
enemy a2{true, 20, 1};
enemy a3{true, 40, 1};
enemy rA{false, 100, 2};

int firstRow = redAlienHB.y;
int secondRow = redAlienHB.y * 2 + 1;
int thirdRow = redAlienHB.y * 3 + 1;
int firstCol = 8 * 0;
int secondCol = 8 * 1+2;
int thirdCol = 8 * 2+2;
int forthCol = 8 * 3+2;
EnemyGroup enemies[NUM_ALIENS] = {
    // Initialize each enemy with appropriate hitBox and type
    {enemy{true, 10, 1,false,false}, alien1NormalHB, "alien1", firstCol, firstRow},
    {enemy{true, 10, 1,false,false}, alien1NormalHB, "alien1", secondCol, firstRow},
    {enemy{true, 10, 1,false,false}, alien1NormalHB, "alien1", thirdCol, firstRow},
    {enemy{true, 10, 1,false,false}, alien1NormalHB, "alien1", forthCol, firstRow},
    {enemy{true, 20, 1,false,false}, alien2NormalHB, "alien2", firstCol, secondRow},
    {enemy{true, 20, 1,false,false}, alien2NormalHB, "alien2", secondCol, secondRow},
    {enemy{true, 20, 1,false,false}, alien2NormalHB, "alien2", thirdCol, secondRow},
    {enemy{true, 20, 1,false,false}, alien2NormalHB, "alien2", forthCol, secondRow},
    {enemy{true, 30, 1,false,false}, alien3NormalHB, "alien3", firstCol, thirdRow},
    {enemy{true, 30, 1,false,false}, alien3NormalHB, "alien3", secondCol, thirdRow},
    {enemy{true, 30, 1,false,false}, alien3NormalHB, "alien3", thirdCol, thirdRow},
    {enemy{true, 30, 1,false,false}, alien3NormalHB, "alien3", forthCol, thirdRow},
    {enemy{false, 50, 2,false,false}, redAlienHB, "redAlien", firstCol, 0}};
shield covers[NUM_COVERS] = {
    {0, 30, true, false, coverLeftFullHB},
    {50, 30, true, false, coverRightFullHB}};
void insertAliensGrid(string grid[][GRID_COLS]);
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
    // getch(); for debug
        chrono::steady_clock::time_point frame_start = chrono::steady_clock::now();

        // Game logic update
        controllHandler(grid, player, playerBullet);
        nextStep(player,enemies);
        initWave(initiatedWave, enemies, player.player.lastWave);
        hitCheck(player,enemies, covers, playerBullet, enemyBullet);

        // Insert Entities
        // reset grid
        // initGrid(GRID_ROWS, GRID_COLS, grid);

        insertIntoGrid(spaceShip, spaceShipHB.y, grid, player.y, player.x);
        if (playerBullet.isShoot)
        {
            insertIntoGrid(tir, tirHB.y, grid, playerBullet.y, playerBullet.x);
        }
        insertAliensGrid(grid);

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
        saveRecord(RECORDS_FILE, player.player);
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
        enemies[NUM_ALIENS].enemyIns.isAlive=false;
        initiatedWave = true;
    }
}
void insertAliensGrid(string grid[][GRID_COLS])
{
    for (int i = 0; i < NUM_ALIENS; ++i)
    {
        // Check if the enemy is alive
        if (!enemies[i].enemyIns.isAlive)
            continue; // Skip dead enemies

        // Pointer to the alien image array
        const string (*alienImage)[MAX_ALIEN_COLS] = nullptr;
        int alienRows = 0;

        // Select the appropriate alien image based on type and alternative flag
        if (enemies[i].type == "alien1")
        {
            alienImage = enemies[i].enemyIns.isAlternate ? alien1Alternate : alien1Normal;
            alienRows = alien1NormalHB.y; // Number of rows in alien1 images
        }
        else if (enemies[i].type == "alien2")
        {
            alienImage = enemies[i].enemyIns.isAlternate ? alien2Alternate : alien2Normal;
            alienRows = alien2NormalHB.y; // Number of rows in alien2 images
        }
        else if (enemies[i].type == "alien3")
        {
            alienImage = enemies[i].enemyIns.isAlternate ? alien3Alternate : alien3Normal;
            alienRows = alien3NormalHB.y; // Number of rows in alien3 images
        }
        else if (enemies[i].type == "redAlien")
        {
            alienImage = redAlien;
            alienRows = redAlienHB.y; // Number of rows in redAlien images
        }
        // Add more types if necessary

        // Insert the alien into the grid if a valid image was selected
        if (alienImage != nullptr)
        {
            insertIntoGrid(alienImage, alienRows, grid, enemies[i].y, enemies[i].x);
        }
    }
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