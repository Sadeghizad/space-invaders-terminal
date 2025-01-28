
#ifndef RENDER_H
#define RENDER_H
#include <iostream>
#include <windows.h>

#include "aliens.h"

using namespace std;

const int GRID_ROWS = 35;
const int GRID_COLS = 130;


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
void eraseGroupGrid(string grid[][GRID_COLS])
{
    //
}

void render(string grid[][GRID_COLS])
{
    system("cls");
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