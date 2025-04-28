#include "./ui.h"
#include <iostream>
#include <locale.h>
#include <ncursesw/ncurses.h>

GameUI::GameUI(Dungeon& _dungeon, Player& _player) : dungeon(_dungeon), player(_player) {}

void GameUI::initUI() {
    setlocale(LC_ALL, "en_US.UTF-8");
    initscr();
    start_color();
    noecho();
    curs_set(0);
    cbreak();
    keypad(stdscr, TRUE);
    refresh();

    //Init color
    init_pair(1, COLOR_GREEN, COLOR_BLACK); 
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); 
    init_pair(3, COLOR_BLUE, COLOR_BLACK); 

    int screenHeight, screenWidth;
    getmaxyx(stdscr, screenHeight, screenWidth);

    int gameWidth = dungeon.MAP_WIDTH;
    int uiWidth = screenWidth - gameWidth;

    gameWin = newwin(screenHeight, gameWidth, 0, 0);
    uiWin = newwin(screenHeight, uiWidth, 0, gameWidth);

    box(gameWin, 0, 0);
    box(uiWin, 0, 0);

    wrefresh(gameWin);
    wrefresh(uiWin);
}

void GameUI::drawDungeon() {
    for (size_t y = 0; y < dungeon.map.size(); ++y) {
        for (size_t x = 0; x < dungeon.map[y].size(); ++x) {
            char tile = dungeon.map[y][x];
            if (tile == '@') {
                wattron(gameWin, COLOR_PAIR(1));
            }
            else if (tile == '$') {
                wattron(gameWin, COLOR_PAIR(2));
            }
            else if (tile == 'D') {
                wattron(gameWin, COLOR_PAIR(3));
            }

            //Draw tile
            mvwaddch(gameWin, y + 1, x + 1, dungeon.map[y][x]);

            //Turn off color
            wattroff(gameWin, COLOR_PAIR(1));
            wattroff(gameWin, COLOR_PAIR(2));
            wattroff(gameWin, COLOR_PAIR(3));
        }
    }
    wrefresh(gameWin);
}

void GameUI::drawPlayerStatus() {
    int y = 1;

    mvwprintw(uiWin, y++, 2, "Floor: %d", player.playerFloor);
    mvwprintw(uiWin, y++, 2, "Player:");
    mvwprintw(uiWin, y++, 4, "Level: %d", 5);
    mvwprintw(uiWin, y++, 4, "HP: %d/%d", 35, 50);
    mvwprintw(uiWin, y++, 4, "Coins: %d", player.playerCoin);
    mvwprintw(uiWin, y++, 2, "Inventory:");
    mvwprintw(uiWin, y++, 4, "- HealingPotion x3");
    mvwprintw(uiWin, y++, 4, "- Bomb x1");
}

void GameUI::drawDialogue(int startY) {
    const char* asciiArt[] = {
        " (o_o) ",
        "<(   )>",
        "  / \\  "
    };

    int artWidth = 8;
    int artHeight = sizeof(asciiArt) / sizeof(asciiArt[0]);

    // Draw ASCII art
    for (int i = 0; i < artHeight; ++i) {
        mvwprintw(uiWin, startY + i, 2, "%s", asciiArt[i]);
    }

    // Draw dialogue text next to art
    mvwprintw(uiWin, startY, 12, "Hello, adventurer!");
    mvwprintw(uiWin, startY + 1, 12, "Be careful ahead...");
}

void GameUI::drawPlayerControl(int startY) {
    mvwprintw(uiWin, startY, 2, "<-------Control------->");
    mvwprintw(uiWin, startY + 1, 2, "W A S D to walk.");
    mvwprintw(uiWin, startY + 2, 2, "q to exit");
}

void GameUI::updateUI() {
    werase(uiWin);
    box(uiWin, 0, 0);

    drawPlayerStatus();
    drawDialogue(10);
    drawPlayerControl(15);

    wrefresh(uiWin);
}

void GameUI::updateGameScreen() {
    werase(gameWin);
    box(gameWin, 0, 0);
    drawDungeon();
}
