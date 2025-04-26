#ifndef UI_H
#define UI_H

#include <ncursesw/ncurses.h>

extern WINDOW* gameWin;
extern WINDOW* uiWin;

void initUI();
void drawDungeon(WINDOW* win);
void drawPlayerStatus(WINDOW* win);
void drawDialogue(WINDOW* win, int startY);
void updateUI();

#endif
