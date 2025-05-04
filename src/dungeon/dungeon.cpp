#include "./dungeon.h"

int Room::centerX() const { return x + width / 2; }
int Room::centerY() const { return y + height / 2; }
bool Room::intersects(const Room& other, int distance) const {
    return !(x + width + distance < other.x ||
             x > other.x + other.width + distance ||
             y + height + distance < other.y ||
             y > other.y + other.height + distance);
}

bool Edge::operator>(const Edge& other) const {
    return weight > other.weight;
}

bool Edge::operator<(const Edge& other) const {
    return weight < other.weight;
}

Dungeon::Dungeon():
    MAP_WIDTH(80),
    MAP_HEIGHT(20),
    ROOM_COUNT(15),
    MIN_ROOM_SIZE(5),
    MAX_ROOM_SIZE(10),
    ROOM_DISTANCE(2),
    map(MAP_HEIGHT, std::string(MAP_WIDTH, ' '))
{}

void Dungeon::clearDungeon() {
    srand(time(NULL));
    rooms.clear();

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            map[y][x] = ' '; //empty space
        }
    }
}

void Dungeon::generateDungeon() {
    clearDungeon();
    generateRooms();
    auto mstEdges = createMST();
    generateCorridors(mstEdges);
}

void Dungeon::drawRoom(const Room& room) {
    //Walls
    for (int i = room.x; i < room.x + room.width; ++i) {
        map[room.y][i] = '-';
        map[room.y + room.height - 1][i] = '-';
    }
    for (int j = room.y; j < room.y + room.height; ++j) {
        map[j][room.x] = '|';
        map[j][room.x + room.width - 1] = '|';
    }

    //Floor
    for (int j = room.y + 1; j < room.y + room.height - 1; ++j) {
        for (int i = room.x + 1; i < room.x + room.width - 1; ++i) {
            map[j][i] = '.';
        }
    }
}

float Dungeon::euclideanDist(const Room& a, const Room& b) {
    float dx = a.centerX() - b.centerX();
    float dy = a.centerY() - b.centerY();
    return std::sqrt(dx * dx + dy * dy);
}

void Dungeon::generateRooms() {
    int attempts = 0;
    while (rooms.size() < ROOM_COUNT && attempts < 5000) {
        int w = MIN_ROOM_SIZE + rand() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE + 1);
        int h = MIN_ROOM_SIZE + rand() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE + 1);
        int x = rand() % (MAP_WIDTH - w - 1);
        int y = rand() % (MAP_HEIGHT - h - 1);

        Room newRoom = {x, y, w, h};

        bool overlaps = false;
        for (const Room& room : rooms) {
            if (newRoom.intersects(room, ROOM_DISTANCE)) {
                overlaps = true;
                break;
            }
        }

        if (!overlaps) {
            rooms.push_back(newRoom);
            drawRoom(newRoom);
        }

        attempts++;
    }
}

std::vector<std::pair<int, int>> Dungeon::createMST() {
    std::vector<std::pair<int, int>> mstEdges;
    PriorityQueue<Edge> pq; // Use custom priority queue
    std::vector<bool> inMST(rooms.size(), false);

    inMST[0] = true;
    for (int i = 1; i < rooms.size(); ++i) {
        pq.push({0, i, euclideanDist(rooms[0], rooms[i])});
    }

    while (!pq.empty()) {
        Edge e = pq.top();
        pq.pop();

        if (inMST[e.roomB]) continue;

        inMST[e.roomB] = true;
        mstEdges.push_back({e.roomA, e.roomB});

        for (int i = 0; i < rooms.size(); ++i) {
            if (!inMST[i]) {
                pq.push({e.roomB, i, euclideanDist(rooms[e.roomB], rooms[i])});
            }
        }
    }

    return mstEdges;
}

void Dungeon::moveStickedCorridor(int& bendX, int& bendY, const Room& roomA, const Room& roomB) {
    int correctionXA = 0, correctionYA = 0;
    int correctionXB = 0, correctionYB = 0;

    //Room A
    if (roomA.x == bendX + 1) correctionXA = 1;
    else if (roomA.x + roomA.width == bendX) correctionXA = -1;
    else if (roomA.x == bendX) correctionXA = 1;
    else if (roomA.x + roomA.width == bendX + 1) correctionXA = -1;

    if (roomA.y == bendY + 1) correctionYA = 1;
    else if (roomA.y + roomA.height == bendY) correctionYA = -1;
    else if (roomA.y == bendY) correctionYA = 1;
    else if (roomA.y + roomA.height == bendY + 1) correctionYA = -1;

    //Room B
    if (roomB.x == bendX + 1) correctionXB = 1;
    else if (roomB.x + roomB.width == bendX) correctionXB = -1;
    else if (roomB.x == bendX) correctionXB = 1;
    else if (roomB.x + roomB.width == bendX + 1) correctionXB = -1;

    if (roomB.y == bendY + 1) correctionYB = 1;
    else if (roomB.y + roomB.height == bendY) correctionYB = -1;
    else if (roomB.y == bendY) correctionYB = 1;
    else if (roomB.y + roomB.height == bendY + 1) correctionYB = -1;

    bendX += correctionXA + correctionXB;
    bendY += correctionYA + correctionYB;
}

void Dungeon::drawCorridor(const Room& a, const Room& b) {
    int x1 = a.centerX();
    int y1 = a.centerY();
    int x2 = b.centerX();
    int y2 = b.centerY();

    int bendX = x2;
    int bendY = y1;

    moveStickedCorridor(bendX, bendY, a, b);

    //Draw starting point
    if (map[y1][x1] == '|' || map[y1][x1] == '-') map[y1][x1] = '+';
    else if (map[y1][x1] == ' ') map[y1][x1] = '#';

    //First leg: horizontal from x1 to bendX at y1
    int dx = (bendX > x1) ? 1 : -1;
    for (int x = x1 + dx; x != bendX + dx; x += dx) {
        if (map[y1][x] == ' ') map[y1][x] = '#';
        else if (map[y1][x] == '|' || map[y1][x] == '-') map[y1][x] = '+';
    }

    //Draw bend point
    if (map[bendY][bendX] == ' ') map[bendY][bendX] = '#';
    else if (map[bendY][bendX] == '|' || map[bendY][bendX] == '-') map[bendY][bendX] = '+';

    //Second leg: vertical from bendY to y2 at bendX
    int dy = (y2 > bendY) ? 1 : -1;
    for (int y = bendY + dy; y != y2 + dy; y += dy) {
        if (map[y][bendX] == ' ') map[y][bendX] = '#';
        else if (map[y][bendX] == '|' || map[y][bendX] == '-') map[y][bendX] = '+';
    }

    //Draw ending point
    if (map[y2][x2] == '|' || map[y2][x2] == '-') map[y2][x2] = '+';
    else if (map[y2][x2] == ' ') map[y2][x2] = '#';
}

void Dungeon::generateCorridors(const std::vector<std::pair<int, int>>& edges) {
    for (auto& edge : edges) {
        drawCorridor(rooms[edge.first], rooms[edge.second]);
    }
}
