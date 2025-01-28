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

void hitCheck(PlayerLoc &player, EnemyGroup enemies[], shield shields[], bullet &playerB, bullet *enemyBullets, int enemyBulletCount)
{
    // Check collision between player's bullet and aliens

    if (playerB.isShoot)
    {
        for (int j = 0; j < NUM_COVERS; j++)
        {
            hitBox currentHB = shields[j].hb;
            if (playerB.x >= shields[j].x && playerB.x < shields[j].x + currentHB.x &&
                playerB.y >= shields[j].y && playerB.y < shields[j].y + currentHB.y)
            {
                // Collision detected
                playSound("shield_hit.wav"); // Optional: Add a sound for shield hits

                // Update shield state
                if (shields[j].exist)
                {
                    if (shields[j].isBroken)
                    {
                        shields[j].exist = false; // Destroy the cover
                    }
                    else
                    {
                        shields[j].isBroken = true; // Break the cover
                    }
                }

                // Disable the player bullet
                playerB.isShoot = false;

                break; // Assuming one collision per bullet
            }
        }
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
                if (alien.type == "redAlien")
                    alien.type = "";

                // Stop the bullet
                playerB.isShoot = false;

                // Update player's score
                player.player.score += alien.enemyIns.bounsScore;

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

        hitBox currentHB = alien.hb;

        // Player's spaceship boundaries for feature [move forward]
        // int playerLeft = player.x;
        // int playerRight = player.x + spaceShipHB.x;
        int playerTop = player.y;

        // Alien's boundariesfor feature [move forward]
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

    for (int i = 0; i < enemyBulletCount; i++)
    {
        if (enemyBullets[i].isShoot)
        {
            // Collision with player
            if (enemyBullets[i].x >= player.x && enemyBullets[i].x < player.x + spaceShipHB.x &&
                enemyBullets[i].y >= player.y && enemyBullets[i].y < player.y + spaceShipHB.y)
            {
                playSound("explosion.wav");
                player.player.lives--;
                enemyBullets[i].isShoot = false;
            }

            // Collision with shields
            for (int j = 0; j < NUM_COVERS; j++)
            {
                hitBox currentHB = shields[j].hb;
                if (enemyBullets[i].x >= shields[j].x && enemyBullets[i].x < shields[j].x + currentHB.x &&
                    enemyBullets[i].y >= shields[j].y && enemyBullets[i].y < shields[j].y + currentHB.y)
                {
                    playSound("explosion.wav");

                    // Update shield state
                    if (shields[j].exist)
                    {
                        if (shields[j].isBroken)
                        {
                            shields[j].exist = false; // Destroy the cover
                        }
                        else
                        {
                            shields[j].isBroken = true; // Break the cover
                        }
                    }

                    // Disable the bullet
                    enemyBullets[i].isShoot = false;
                }
            }
        }
    }
}

void movePlayer(PlayerLoc &player, bool right, int speed)
{
    if (right && player.x < GRID_COLS - MAX_ALIEN_COLS)
    {
        player.x += speed;
    }
    else if (!right && player.x > 0)
    {
        player.x -= speed;
    }
}
void moveAliens(string grid[][GRID_COLS], Direction &direction, EnemyGroup enemies[])
{
    eraseGroupGrid(grid, enemies);
    // Move based on direction
    int speed = 1;
    if (enemies[0].y >= 10)
        speed = 2;
    else if (enemies[0].y >= 20)
        speed = 3;
    int firstAliveX = enemies[0].x;
    int lastAliveX = enemies[3].x;
    int enemyCols = (NUM_ALIENS - 1) / 3;
    for (int i = 0; i < enemyCols; i++)
    {
        if ((!enemies[i].enemyIns.isAlive) && (!enemies[i + 4].enemyIns.isAlive) && (!enemies[i + 2 * 4].enemyIns.isAlive))
        {
            if (i + 1 > ((NUM_ALIENS - 1) / 3))
                continue;
            lastAliveX = enemies[i - 1].x;
        }
        if ((!enemies[enemyCols - i].enemyIns.isAlive) && (!enemies[enemyCols - i + 4].enemyIns.isAlive) && (!enemies[enemyCols - i + 2 * 4].enemyIns.isAlive))
        {
            if (!(enemyCols - i - 1 > 0))
                continue;
            firstAliveX = enemies[enemyCols - i + 1].x;
        }
    }
    if (direction == RIGHT)
    {
        if (lastAliveX < GRID_COLS - 20)
        {
            for (int i = 0; i < NUM_ALIENS - 1; i++)
            {
                enemies[i].x += speed;
                enemies[i].enemyIns.isAlternate = !enemies[i].enemyIns.isAlternate;
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
        if (firstAliveX > 0)
        {
            for (int i = 0; i < NUM_ALIENS - 1; i++)
            {
                enemies[i].x -= speed;
                enemies[i].enemyIns.isAlternate = !enemies[i].enemyIns.isAlternate;
            }
        }
        else
        {
            // Change direction to right and step down
            direction = Direction::RIGHT;
            for (int i = 0; i < NUM_ALIENS - 1; i++)
            {
                enemies[i].y++;
            }
        }
    }
    if (enemies[NUM_ALIENS - 1].enemyIns.isAlive)
    {
        if (enemies[NUM_ALIENS - 1].x > GRID_COLS - 1)
            enemies[NUM_ALIENS - 1].enemyIns.isAlive = false;
        enemies[NUM_ALIENS - 1].x += speed * 2;
    }
}

void nextStep(PlayerLoc &player, EnemyGroup *enemies)
{
    bool win = true;
    for (int i = 0; i < NUM_ALIENS; i++)
    {
        if (enemies[i].enemyIns.isAlive)
        {
            win = false;
            break;
        }
    }
    if (win)
    {
        if (++player.player.lastWave)
        {
            player.player.lastLevel++;
            player.player.lastWave = 1;
        }
    }
}

void moveBullets(string grid[][GRID_COLS], bullet &playerBullet, bullet *enemyBullets, int speed, int enemyBulletCount)
{
    if (playerBullet.y > 0)
        playerBullet.y -= speed;
    else
        playerBullet.isShoot = false;
    for (int i = 0; i < enemyBulletCount; i++)
    {
        if (enemyBullets[i].isShoot)
        {
            eraseFromGrid(tir, tirHB.y, grid, enemyBullets[i].y, enemyBullets[i].x);
            enemyBullets[i].y += BulletsSpeed; // Move bullet downwards

            // Disable bullet if it goes out of bounds
            if (enemyBullets[i].y >= GRID_ROWS - 1)
            {
                enemyBullets[i].isShoot = false;
            }
        }
    }
}
#endif