#include "../dungeon/dungeon.h"
#include <iostream>
#include <locale.h>
#include <ncursesw/ncurses.h>

WINDOW* gameWin;
WINDOW* uiWin;

void initUI() {
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    noecho();
    curs_set(0);
    cbreak();
    keypad(stdscr, TRUE);
    refresh();

    //Init color
    init_pair(1, COLOR_GREEN, COLOR_BLACK); 

    int screenHeight, screenWidth;
    getmaxyx(stdscr, screenHeight, screenWidth);

    int gameWidth = MAP_WIDTH;
    int uiWidth = screenWidth - gameWidth;

    gameWin = newwin(screenHeight, gameWidth, 0, 0);
    uiWin = newwin(screenHeight, uiWidth, 0, gameWidth);

    box(gameWin, 0, 0);
    box(uiWin, 0, 0);

    wrefresh(gameWin);
    wrefresh(uiWin);
}

void drawDungeon(WINDOW* win) {
    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {
            char tile = map[y][x];
            if (tile == '@') {
                wattron(win, COLOR_PAIR(1));
            }

            //Draw tile
            mvwaddch(win, y + 1, x + 1, map[y][x]);

            //Turn off color
            wattroff(win, COLOR_PAIR(1));
        }
    }
    wrefresh(win);
}

void drawPlayerStatus(WINDOW* win) {
    int y = 1;

    mvwprintw(win, y++, 2, "Player:");
    mvwprintw(win, y++, 4, "Level: %d", 5);
    mvwprintw(win, y++, 4, "HP: %d/%d", 35, 50);
    mvwprintw(win, y++, 4, "Coins: %d", 123);
    mvwprintw(win, y++, 2, "Inventory:");
    mvwprintw(win, y++, 4, "- HealingPotion x3");
    mvwprintw(win, y++, 4, "- Bomb x1");
}

void drawDialogue(WINDOW* win, int startY) {
    const char* asciiArt[] = {
        " (o_o) ",
        "<(   )>",
        "  / \\  "
    };

    int artWidth = 8;
    int artHeight = sizeof(asciiArt) / sizeof(asciiArt[0]);

    // Draw ASCII art
    for (int i = 0; i < artHeight; ++i) {
        mvwprintw(win, startY + i, 2, "%s", asciiArt[i]);
    }

    // Draw dialogue text next to art
    mvwprintw(win, startY, 12, "Hello, adventurer!");
    mvwprintw(win, startY + 1, 12, "Be careful ahead...");
}

void drawPlayerControl(WINDOW* win, int startY) {
    mvwprintw(win, startY, 2, "<-------Control------->");
    mvwprintw(win, startY + 1, 2, "W A S D to walk.");
    mvwprintw(win, startY + 2, 2, "q to exit");
}

void updateUI() {
    werase(uiWin);
    box(uiWin, 0, 0);

    drawPlayerStatus(uiWin);
    drawDialogue(uiWin, 10);
    drawPlayerControl(uiWin, 15);

    wrefresh(uiWin);
}