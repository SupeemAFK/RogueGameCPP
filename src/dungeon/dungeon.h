#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <string>

struct Room {
    int x, y, width, height;

    int centerX() const;
    int centerY() const;
    bool intersects(const Room& other, int distance) const;
};

struct Edge {
    int roomA, roomB;
    float weight;

    bool operator>(const Edge& other) const;
};

extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;
extern const int ROOM_COUNT;
extern const int MIN_ROOM_SIZE;
extern const int MAX_ROOM_SIZE;
extern const int ROOM_DISTANCE;

extern std::vector<std::string> map;
extern std::vector<Room> rooms;

void drawRoom(const Room& room);
float distance(const Room& a, const Room& b);
void generateRooms();
std::vector<std::pair<int, int>> createMST();
void moveStickedCorridor(int& bendX, int& bendY, const Room& roomA, const Room& roomB);
void drawCorridor(const Room& a, const Room& b);
void generateCorridors(const std::vector<std::pair<int, int>>& edges);
void clearDungeon();
void generateDungeon();
void printMap();

#endif
