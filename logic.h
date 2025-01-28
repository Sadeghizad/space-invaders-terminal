#include <iostream>
#include <windows.h>
#include <iomanip>

#include "aliens.h"
#include "render.h"
#include "sound.h"
using namespace std;
const int MAX_PLAYERS = 100;
const int NUM_COVERS=2;
const int NUM_ALIENS = 13; // a1_1 to a3_4 and rA0

enum Direction
{
    LEFT,
    RIGHT
};

struct enemy
{
    bool couldFire;
    bool bounsScore;
    int speed;
    bool isAlive = true;
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
    eraseGroupGrid(grid);
    // Move based on direction
    if (direction == RIGHT)
    {
        if (enemies[NUM_ALIENS - 1].x + 8 < GRID_COLS)
        {
            for (int i = 0; i < NUM_ALIENS; i++)
            {
                enemies[i].x++;
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

int readSavesFromFile(const char *filename, Player players[], int maxPlayers)
{

    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Failed to open saveing file." << endl;
        return 0;
    }

    int count = 0;
    while (count < maxPlayers && file >> players[count].username >> players[count].lastLevel >> players[count].lastWave)
    {
        count++;
    }

    file.close();

    return count;
}
int readPlayersFromFile(const char *filename, Player players[], int maxPlayers)
{

    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Failed to open leaderboard file." << endl;
        return 0;
    }

    int count = 0;
    while (count < maxPlayers && file >> players[count].username >> players[count].score >> players[count].lastLevel >> players[count].lastWave >> players[count].playtime)
    {
        count++;
    }

    file.close();

    return count;
}
void writeSavesToFile(const char *filename, Player players[], int count)
{
    ofstream file(filename);
    for (int i = 0; i < count; ++i)
    {
        file << players[i].username << " "
             << players[i].lastLevel << " "
             << players[i].lastWave << "\n";
    }
    file.close();
    cout << "Error: Unable to save the game.\n";
}

void updatefile(const char *filename, Player player)
{
    Player players[MAX_PLAYERS];

    int playerCount = readSavesFromFile(filename, players, MAX_PLAYERS);

    bool found = false;
    for (int i = 0; i < playerCount; ++i)
    {
        if (strcmp(players[i].username, player.username) == 0)
        {
            // Update player stats based on win and score/playtime
            if (player.lastLevel > players[i].lastLevel)
            {
                players[i].lastLevel = max(players[i].lastLevel, player.lastLevel);
                players[i].lastWave = player.lastWave;
            }
            found = true;
            break;
        }
    }
    if (!found && playerCount < MAX_PLAYERS)
    {
        strcpy(players[playerCount].username, player.username);
        players[playerCount].lastLevel = player.lastLevel;
        players[playerCount].lastWave = player.lastWave;
        ++playerCount;
    }

    writeSavesToFile(filename, players, playerCount);
}
void findPlayer(const char *filename, char *username, int wave, int level)
{
    Player players[MAX_PLAYERS];

    int playerCount = readSavesFromFile(filename, players, MAX_PLAYERS);

    bool found = false;
    for (int i = 0; i < playerCount; ++i)
    {
        if (strcmp(players[i].username, username) == 0)
        {
            found = true;
            wave = players[i].lastWave;
            level = players[i].lastLevel;
            break;
        }
    }
    if (!found && playerCount < MAX_PLAYERS)
    {
        cout << "Record not found" << endl;
    }
}

void sortPlayers(Player players[], int count)
{
    for (int i = 0; i < count - 1; ++i)
    {
        for (int j = 0; j < count - i - 1; ++j)
        {
            bool swap = false;

            if (players[j].score < players[j + 1].score)
            {
                swap = true;
            }
            // If playtime is the same, prioritize by score
            else if (players[j].score == players[j + 1].score)
            {
                if (players[j].playtime > players[j + 1].playtime)
                {
                    swap = true;
                }
                // If everything else is equal, prioritize alphabetically by username
                else if (players[j].playtime == players[j + 1].playtime)
                    if (strcmp(players[j].username, players[j + 1].username) > 0)
                    {
                        swap = true;
                    }
            }

            // Swap the players if needed
            if (swap)
            {
                Player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
}
void writePlayersToFile(const char *filename, Player players[], int count)
{
    ofstream file(filename);
    for (int i = 0; i < count; ++i)
    {
        file << players[i].username << " "
             << players[i].score << " "
             << players[i].lastLevel << " "
             << players[i].lastWave << " "
             << players[i].playtime << "\n";
    }
    file.close();
}

void saveRecord(const char *filename, Player player)
{
    Player players[MAX_PLAYERS];

    int playerCount = readPlayersFromFile(filename, players, MAX_PLAYERS);

    bool found = false;
    for (int i = 0; i < playerCount; ++i)
    {
        if (strcmp(players[i].username, player.username) == 0)
        {
            // Update player stats based on win and score/playtime
            if (player.score > players[i].score)
            {
                players[i].score = max(players[i].score, player.score);
                players[i].playtime = min(players[i].playtime, player.playtime);
                players[i].lastLevel = max(players[i].lastLevel, player.lastLevel);
                players[i].lastWave = players[i].lastWave;
            }
            found = true;
            break;
        }
    }

    // Add a new player if not found
    if (!found && playerCount < MAX_PLAYERS)
    {
        strcpy(players[playerCount].username, player.username);
        players[playerCount].score = player.score;
        players[playerCount].playtime = player.playtime;
        players[playerCount].lastLevel = player.lastLevel;
        players[playerCount].lastWave = player.lastWave;
        ++playerCount;
    }

    sortPlayers(players, playerCount);
    writePlayersToFile(filename, players, playerCount);
}

void displayPlayers(char *filename)
{
    Player players[MAX_PLAYERS];

    int count = readPlayersFromFile(filename, players, MAX_PLAYERS);
    cout << setw(5) << "Rank"
         << setw(20) << "Username"
         << setw(10) << "Score"
         << setw(10) << "Last Level"
         << setw(10) << "Last Wave"
         << setw(12) << "Playtime\n";
    cout << string(60, '-') << "\n";

    for (int i = 0; i < count; ++i)
    {
        cout << setw(5) << (i + 1)
             << setw(20) << players[i].username
             << setw(10) << players[i].score
             << setw(12) << players[i].lastLevel
             << setw(12) << players[i].lastWave
             << setw(12) << players[i].playtime << "\n";
    }
}
