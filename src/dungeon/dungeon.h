#ifndef DUNGEON_H
#define DUNGEON_H

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

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


class Dungeon {
    public:
        int MAP_WIDTH;
        int MAP_HEIGHT;
        int ROOM_COUNT;
        int MIN_ROOM_SIZE;
        int MAX_ROOM_SIZE;
        int ROOM_DISTANCE;

        std::vector<std::string> map;
        std::vector<Room> rooms;

        Dungeon();

        void clearDungeon();
        void generateDungeon();

    private:
        void drawRoom(const Room& room);
        float euclideanDist(const Room& a, const Room& b);
        void generateRooms();
        std::vector<std::pair<int, int>> createMST();
        void moveStickedCorridor(int& bendX, int& bendY, const Room& roomA, const Room& roomB);
        void drawCorridor(const Room& a, const Room& b);
        void generateCorridors(const std::vector<std::pair<int, int>>& edges);
};

#endif
