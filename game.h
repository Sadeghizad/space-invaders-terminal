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

int charachter = 1;
int firstRow = redAlienHB.x;
int secondRow = firstRow + alien1NormalHB.x;
int thirdRow = secondRow + alien1NormalHB.x;
int firstCol = 0;
int secondCol = 20 * 1;
int thirdCol = 20 * 2;
int forthCol = 20 * 3;
EnemyGroup enemies[NUM_ALIENS] = {
    // Initialize each enemy with appropriate hitBox and type
    {enemy{true, 10, false, false}, alien1NormalHB, "alien1", firstCol, firstRow},
    {enemy{true, 10, false, false}, alien1NormalHB, "alien1", secondCol, firstRow},
    {enemy{true, 10, false, false}, alien1NormalHB, "alien1", thirdCol, firstRow},
    {enemy{true, 10, false, false}, alien1NormalHB, "alien1", forthCol, firstRow},
    {enemy{true, 20, false, false}, alien2NormalHB, "alien2", firstCol, secondRow},
    {enemy{true, 20, false, false}, alien2NormalHB, "alien2", secondCol, secondRow},
    {enemy{true, 20, false, false}, alien2NormalHB, "alien2", thirdCol, secondRow},
    {enemy{true, 20, false, false}, alien2NormalHB, "alien2", forthCol, secondRow},
    {enemy{true, 30, false, false}, alien3NormalHB, "alien3", firstCol, thirdRow},
    {enemy{true, 30, false, false}, alien3NormalHB, "alien3", secondCol, thirdRow},
    {enemy{true, 30, false, false}, alien3NormalHB, "alien3", thirdCol, thirdRow},
    {enemy{true, 30, false, false}, alien3NormalHB, "alien3", forthCol, thirdRow},
    {enemy{false, 50, false, false}, redAlienHB, "", firstCol, 0}};
shield covers[NUM_COVERS] = {
    {0, GRID_ROWS - 15, true, false, coverLeftFullHB},
    {50, GRID_ROWS - 15, true, false, coverRightFullHB}};
void insertAliensGrid(string grid[][GRID_COLS]);
void initWave(bool &initiatedWave, EnemyGroup enemies[], int &fireChance,Player &player);
void displayCalibrationBox();
void initGrid(int rows, int cols, string grid[][GRID_COLS]);
void controllHandler(string grid[][GRID_COLS], PlayerLoc &player, bullet &playerBullet);

void run(PlayerLoc &player, bool &newGame)
{
    string grid[GRID_ROWS][GRID_COLS];
    bullet playerBullet;
    bullet enemyBullets[MAX_ENEMY_BULLETS] = {};
    int enemyBulletCount = 0;
    const int target_fps = 4;
    const chrono::duration<double, milli> frame_duration(1000.0 / target_fps);
    charachter = charachterChoose();
    displayCalibrationBox();

    initGrid(GRID_ROWS, GRID_COLS, grid);
    Direction direct;
    bool isRunning = true;
    bool save = false;
    bool loose = false;
    bool initiatedWave = false;
    int frame_count = 0;
    int fireChance=1;
    while (isRunning)
    {
        chrono::steady_clock::time_point frame_start = chrono::steady_clock::now();

        // Game logic
        controllHandler(grid, player, playerBullet);
        initWave(initiatedWave, enemies, fireChance,player.player);
        nextStep(player, enemies, initiatedWave);
        // Enemy shooting logic
        for (int i = 0; i < NUM_ALIENS - 1; i++)
        {
            if (enemies[i].enemyIns.isAlive)
            {
                if (rand() % 100 < fireChance)
                { // 1% chance to shoot each frame
                    if (enemyBulletCount < MAX_ENEMY_BULLETS)
                    {
                        enemyBullets[enemyBulletCount].isShoot = true;
                        enemyBullets[enemyBulletCount].x = enemies[i].x + (enemies[i].hb.x / 2); // Center the bullet
                        enemyBullets[enemyBulletCount].y = enemies[i].y + enemies[i].hb.y;       // Position below the enemy
                        enemyBullets[enemyBulletCount].dmg = 1;                                  // Set damage value
                        enemyBulletCount++;
                    }
                }
            }
        }

        hitCheck(player, enemies, covers, playerBullet, enemyBullets, enemyBulletCount);

        // Insert Entities
        setCursor(0, 0);
        for (int i = 0; i < NUM_COVERS; ++i)
        {
            if (covers[i].exist)
            {
                if (covers[i].isBroken)
                {
                    insertIntoGrid(
                        (i == 0) ? coverLeftBroken : coverRightBroken,
                        covers[i].hb.y,
                        grid,
                        covers[i].y,
                        covers[i].x);
                }
                else
                {
                    insertIntoGrid(
                        (i == 0) ? coverLeftFull : coverRightFull,
                        covers[i].hb.y,
                        grid,
                        covers[i].y,
                        covers[i].x);
                }
            }
            else
            {
                eraseFromGrid(coverLeftFull, coverLeftFullHB.y, grid, covers[i].y, covers[i].x);
            }
        }
        switch (charachter)
        {
        case 1:
            insertIntoGrid(spaceShip, spaceShipHB.y, grid, player.y, player.x);
            break;
        case 2:
            insertIntoGrid(spaceShip1, spaceShipHB.y, grid, player.y, player.x);
            break;
        case 3:
            insertIntoGrid(spaceShip2, spaceShipHB.y, grid, player.y, player.x);
            break;

        default:
            break;
        }
        if (playerBullet.isShoot)
        {
            insertIntoGrid(tir, tirHB.y, grid, playerBullet.y, playerBullet.x);
        }
        for (int i = 0; i < enemyBulletCount; i++)
        {
            if (enemyBullets[i].isShoot)
            {
                insertIntoGrid(tir, tirHB.y, grid, enemyBullets[i].y, enemyBullets[i].x);
            }
        }

        insertAliensGrid(grid);

        // Insert Covers into the Grid

        // Rendering
        render(grid);
        cout << "x: " << player.x << endl;
        cout << "score: " << player.player.score << endl;
        cout << "level: " << player.player.lastLevel << endl;
        cout << "wave: " << player.player.lastWave << endl;
        cout << "playtime: " << player.player.playtime << endl;
        cout << "lives: " << player.player.lives << endl;
        // Sleep with thread to not use windows h to work on linux too
        chrono::duration<double, milli> elapsed_time = chrono::steady_clock::now() - frame_start;
        if (elapsed_time < frame_duration)
        {
            std::this_thread::sleep_for(frame_duration - elapsed_time);
        }

        // Pause
        if (_kbhit() && _getch() == 27) // Press "esc"
        {
            pause(isRunning, newGame, save, player.player);
        }

        if (playerBullet.isShoot)
        {
            if (frame_count % 2 == 0)
            {
                if (!enemies[NUM_ALIENS - 1].enemyIns.isAlive)
                {
                    if (rand() % 40 == 38)
                    {
                        enemies[NUM_ALIENS - 1].enemyIns.isAlive = true;
                        enemies[NUM_ALIENS - 1].type = "redAlien";
                    }
                }
            }
        }

        eraseFromGrid(tir, tirHB.y, grid, playerBullet.y, playerBullet.x);
        moveBullets(grid, playerBullet, enemyBullets, BulletsSpeed, enemyBulletCount);
        moveAliens(grid, direct, enemies);
        if (player.player.lives < 1)
        {
            system("cls");
            gameOverScreen();
            getch();
            system("cls");
            saveRecord(RECORDS_FILE, player.player);
            cout << "Your record saved Champion(looser version)!" << endl;
            getch();
            displayPlayers(RECORDS_FILE);
            getch();
            return;
        }
        else
        {
            if (save)
            {
                saveAndExit(player.player);
                return;
            }
            if (newGame)
            {
                return;
            }
        }
        frame_count++;
    }
    cout << "Game Over(it always happen XD)" << endl;
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
            movePlayer(player, false, playerSpeed);
        }
        else if (ch == 'd') // Move right
        {
            eraseFromGrid(spaceShip, spaceShipHB.y, grid, player.y, player.x);
            movePlayer(player, true, playerSpeed);
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
void initWave(bool &initiatedWave, EnemyGroup enemies[], int &fireChance,Player &player)
{
    int wave=player.lastWave;
    int level=player.lastLevel;
    if (!initiatedWave)
    {
        if(level>3) level=3;
        switch (wave)
        {
        case 3:
            for (int i = 0; i < level; i++)
            {
                enemies[i * 4 + 2].enemyIns.isAlive = true;
            }
        case 2:
            for (int i = 0; i < level; i++)
            {
                enemies[i * 4 + 1].enemyIns.isAlive = true;
            }
        case 1:
            for (int i = 0; i < level; i++)
            {
                enemies[i * 4].enemyIns.isAlive = true;
            }

        default:
            break;
        }
        player.last_saved_score=player.score;
        fireChance+=10;
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
        const string(*alienImage)[MAX_ALIEN_COLS] = nullptr;
        int alienRows = 0;

        // Select the appropriate alien image based on type and alternative flag
        if (enemies[i].type == "alien1")
        {
            alienImage = enemies[i].enemyIns.isAlternate ? alien1Alternate : alien1Normal;
            alienRows = alien1NormalHB.y;
        }
        else if (enemies[i].type == "alien2")
        {
            alienImage = enemies[i].enemyIns.isAlternate ? alien2Alternate : alien2Normal;
            alienRows = alien2NormalHB.y;
        }
        else if (enemies[i].type == "alien3")
        {
            alienImage = enemies[i].enemyIns.isAlternate ? alien3Alternate : alien3Normal;
            alienRows = alien3NormalHB.y;
        }
        else if (enemies[i].type == "redAlien")
        {
            alienImage = redAlien;
            alienRows = redAlienHB.y;
        }
        // Insert the alien into the grid if a valid image was selected
        if (alienImage != nullptr)
        {
            insertIntoGrid(alienImage, alienRows, grid, enemies[i].y, enemies[i].x);
        }
    }
}
void reset(Player player)
{
    player.score = 0;
    for (int i = 0; i < NUM_COVERS; i++)
    {
        covers[i].exist = true;
        covers[i].isBroken = false;
    }
}
#endif