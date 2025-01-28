#ifndef LOGIC_H
#define LOGIC_H
#include <iostream>
#include <windows.h>
#include <iomanip>

#include "aliens.h"
#include "render.h"
#include "sound.h"
#include "constants.h"
using namespace std;


enum Direction
{
    LEFT,
    RIGHT
};

struct enemy
{
    bool couldFire;
    int bounsScore;
    int speed;
    bool isAlive = true;
    bool isAlternate =false;
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
    string type; // e.g., "alien1", "alien2", "alien3", "redAlien"
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



void hitCheck(PlayerLoc &player,EnemyGroup enemies[], shield shields[], bullet &playerB, bullet &enemyB)
{
    // Check collision between player's bullet and aliens
    if (playerB.isShoot)
    {
        for (int i = 0; i < NUM_ALIENS; ++i)
        {
            EnemyGroup &alien = enemies[i];
            if (!alien.enemyIns.isAlive)
                continue;

            // Get current hitBox based on alien type or state
            hitBox currentHB = alien.hb; // Adjust if you have alternate states

            // Check if bullet's position intersects with alien's position and hitBox
            if (playerB.x >= alien.x && playerB.x < alien.x + currentHB.x &&
                playerB.y >= alien.y && playerB.y < alien.y + currentHB.y)
            {
                // Collision detected
                playSound("invaderkilled.wav");

                // Update alien state
                alien.enemyIns.isAlive = false;

                // Stop the bullet
                playerB.isShoot = false;

                // Update player's score
                player.player.score += alien.enemyIns.bounsScore;

                // Optionally, you can add more effects here (e.g., explosion animation)
                break; // Assuming one collision per bullet
            }
        }
    }

    // Check collision between aliens and player
    for (int i = 0; i < NUM_ALIENS; ++i)
    {
        EnemyGroup &alien = enemies[i];
        if (!alien.enemyIns.isAlive)
            continue;

        hitBox currentHB = alien.hb; // Adjust if you have alternate states

        // Player's spaceship boundaries
        // int playerLeft = player.x;
        // int playerRight = player.x + spaceShipHB.x;
        int playerTop = player.y;

        // Alien's boundaries
        // int alienLeft = alien.x;
        // int alienRight = alien.x + currentHB.x;
        // int alienTop = alien.y;
        int alienBottom = alien.y + currentHB.y;

        // Check for overlap For now just on y axis
        bool overlap = !(alienBottom <= playerTop);

        if (overlap)
        {
            // Collision detected between alien and player
            playSound("explosion.wav");

            // Handle player damage or game over
            player.player.lives--;
            // You can set a game over flag here
        }
    }

    if (enemyB.isShoot)
    {

        // Get current hitBox based on alien type or state
        hitBox currentHB = spaceShipHB; // Adjust if you have alternate states

        // Check if bullet's position intersects with alien's position and hitBox
        if (enemyB.x >= player.x && enemyB.x < player.x + currentHB.x &&
            enemyB.y >= player.y && enemyB.y < player.y + currentHB.y)
        {
            // Collision detected
            playSound("explosion.wav");

            // Update alien state
            player.player.lives--;

            // Stop the bullet
            enemyB.isShoot = false;

            // Update player's score
            // Optionally, you can add more effects here (e.g., explosion animation)
        }
        for(int i=0;i<NUM_COVERS;i++){
        currentHB = shields[i].hb; // Adjust if you have alternate states
        if (enemyB.x >= shields[i].x && enemyB.x < shields[i].x + currentHB.x &&
            enemyB.y >= shields[i].y && enemyB.y < shields[i].y + currentHB.y)
        {
            // Collision detected
            playSound("explosion.wav");

            // Update alien state
            if (shields[i].exist)
            {
                if (shields[i].isBroken)
                {
                    shields[i].exist = false;
                }
                else
                {
                    shields[i].isBroken = false;
                }
            }

            // Stop the bullet
            enemyB.isShoot = false;

            // Update player's score
            // Optionally, you can add more effects here (e.g., explosion animation)
        }}
    } // This requires tracking alien bullets similarly to player bullets
}

void movePlayer(PlayerLoc &player, bool right)
{
    if (right && player.x < GRID_COLS - MAX_ALIEN_COLS)
    {
        player.x++;
    }
    else if (!right && player.x > 0)
    {
        player.x--;
    }
}
void moveAliens(string grid[][GRID_COLS], Direction &direction, EnemyGroup enemies[])
{
    eraseGroupGrid(grid,enemies);
    // Move based on direction
    if (direction == RIGHT)
    {
        if (enemies[NUM_ALIENS - 1].x + 8 < GRID_COLS)
        {
            for (int i = 0; i < NUM_ALIENS; i++)
            {
                enemies[i].x++;
                enemies[i].enemyIns.isAlternate=!enemies[i].enemyIns.isAlternate;
            }
        }
        else
        {
            // Change direction to left and step down
            direction = Direction::LEFT;
        }
    }
    else if (direction == LEFT)
    {
        if (enemies[0].x >= 0)
        {
            for (int i = 0; i < NUM_ALIENS; i++)
            {
                enemies[i].x--;
                enemies[i].enemyIns.isAlternate=!enemies[i].enemyIns.isAlternate;
            }
        }
        else
        {
            // Change direction to right and step down
            direction = Direction::RIGHT;
            for (int i = 0; i < NUM_ALIENS; i++)
            {
                enemies[i].y++;
            }
        }
    }
}
#endif