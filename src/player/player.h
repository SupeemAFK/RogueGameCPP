#ifndef Player_H
#define Player_H

#include <vector>

extern int playerX, playerY;

void clearPlayer();
void randomSpawnPlayer();
void movePlayer(std::vector<int> direction);

#endif