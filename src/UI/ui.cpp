#include "../dungeon/dungeon.h"
#include <iostream>
#include <locale.h>
#include <ncursesw/ncurses.h>

WINDOW* gameWin;
WINDOW* uiWin;

void initUI() {
    setlocale(LC_ALL, "");  // Enable wide chars
    initscr();
    noecho();
    curs_set(0);
    cbreak();
    keypad(stdscr, TRUE);
    refresh();

    int screenHeight, screenWidth;
    getmaxyx(stdscr, screenHeight, screenWidth);

    int gameWidth = MAP_WIDTH; // 80
    int uiWidth = screenWidth - gameWidth; // remaining space

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
            mvwaddch(win, y + 1, x + 1, map[y][x]);
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

void updateUI() {
    werase(uiWin);
    box(uiWin, 0, 0);

    drawPlayerStatus(uiWin);
    drawDialogue(uiWin, 10);

    wrefresh(uiWin);
}