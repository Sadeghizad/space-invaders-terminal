
#ifndef RENDER_H
#define RENDER_H
#include <iostream>
#include <windows.h>
#include <string>

#include "aliens.h"
#include "constants.h"

using namespace std;

void insertIntoGrid(const string alien[][MAX_ALIEN_COLS], int alienRows,
                    string grid[][GRID_COLS], int startRow, int startCol)
{
    for (int i = 0; i < alienRows; ++i)
    {
        for (int j = 0; j < MAX_ALIEN_COLS; ++j)
        {
            int row = startRow + i;
            int col = startCol + j;
            if (row >= GRID_ROWS || col >= GRID_COLS || row < 0 || col < 0)
            {
                continue; // Skip invalid indices
            }
            if (alien[i][j] == "G")
            {
                continue; // Skip invalid alien cells
            }
            if (row < GRID_ROWS && col < GRID_COLS)
            {
                grid[row][col] = alien[i][j];
            }
        }
    }
}
// render.h (continued)


void eraseFromGrid(const string alien[][MAX_ALIEN_COLS], int alienRows,
                   string grid[][GRID_COLS], int startRow, int startCol)
{
    for (int i = 0; i < alienRows; ++i)
    {
        for (int j = 0; j < MAX_ALIEN_COLS; ++j)
        {
            int row = startRow + i;
            int col = startCol + j;
            if (row >= GRID_ROWS || col >= GRID_COLS || row < 0 || col < 0)
            {
                continue; // Skip invalid indices
            }
            if (alien[i][j] == "G")
            {
                continue; // Skip invalid alien cells
            }

            if (row < GRID_ROWS && col < GRID_COLS)
            {
                grid[row][col] = " ";
            }
        }
    }
}
void eraseGroupGrid(string grid[][GRID_COLS],EnemyGroup* enemies)
{
    for (int i = 0; i < NUM_ALIENS; ++i)
    {
        // Check if the enemy is alive
         // Skip dead enemies

        // Determine which image to use based on type and current state
        const string (*alienImage)[MAX_ALIEN_COLS] = nullptr;
        int alienRows = 0;

        if (enemies[i].type == "alien1")
        {
            alienImage = enemies[i].enemyIns.isAlternate ? alien1Alternate : alien1Normal;
            alienRows = 6;
        }
        else if (enemies[i].type == "alien2")
        {
            alienImage = enemies[i].enemyIns.isAlternate ? alien2Alternate : alien2Normal;
            alienRows = 6;
        }
        else if (enemies[i].type == "alien3")
        {
            alienImage = enemies[i].enemyIns.isAlternate ? alien3Alternate : alien3Normal;
            alienRows = 7;
        }
        else if (enemies[i].type == "redAlien")
        {
            alienImage = redAlien;
            alienRows = 6;
        }

        // Erase the alien from the grid if a valid image was selected
        if (alienImage != nullptr)
        {
            eraseFromGrid(alienImage, alienRows, grid, enemies[i].y, enemies[i].x);
        }
    }
}
void setCursor(int x, int y)
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = x;
    Position.Y = y;
    SetConsoleCursorPosition(hOut, Position);
}
void render(string grid[][GRID_COLS])
{
    // system("cls");
    setCursor(0,0);

    for (int i = 0; i < GRID_ROWS; ++i)
    {
        for (int j = 0; j < GRID_COLS; ++j)
        {
            cout << grid[i][j];
        }
        cout << '\n';
    }
}

#endif // RENDER_H