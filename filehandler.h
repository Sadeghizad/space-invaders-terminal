#ifndef FILEHANDELER_H
#define FILEHANDELER_H
#include <iostream>
#include <fstream>
#include "constants.h"
#include "logic.h"
using namespace std;

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
void findPlayer(const char *filename, char *username, int& wave, int &level)
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

void displayPlayers(const char *filename)
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
#endif