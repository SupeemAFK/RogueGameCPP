#include "./ui.h"
#include "../gameManager/gameManager.h"

GameUI::GameUI(GameManager* _gm) : gm(_gm) {}

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
    init_pair(1, COLOR_CYAN, COLOR_BLACK); 
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); 
    init_pair(3, COLOR_BLUE, COLOR_BLACK); 
    init_pair(4, COLOR_RED, COLOR_BLACK); 
    init_pair(5, COLOR_GREEN, COLOR_BLACK); 

    int screenHeight, screenWidth;
    getmaxyx(stdscr, screenHeight, screenWidth);

    int gameWidth = gm->dungeon.MAP_WIDTH;
    int uiWidth = screenWidth - gameWidth;

    gameWin = newwin(screenHeight, gameWidth, 0, 0);
    uiWin = newwin(screenHeight, uiWidth, 0, gameWidth);

    box(gameWin, 0, 0);
    box(uiWin, 0, 0);

    wrefresh(gameWin);
    wrefresh(uiWin);
}

void GameUI::drawDungeon() {
    for (size_t y = 0; y < gm->dungeon.map.size(); ++y) {
        for (size_t x = 0; x < gm->dungeon.map[y].size(); ++x) {
            char tile = gm->dungeon.map[y][x];
            if (tile == '@') {
                wattron(gameWin, COLOR_PAIR(1));
            }
            else if (tile == '$') {
                wattron(gameWin, COLOR_PAIR(2));
            }
            else if (tile == 'D') {
                wattron(gameWin, COLOR_PAIR(3));
            }
            else if (tile == 'K') {
                wattron(gameWin, COLOR_PAIR(4));
            }
            else if (tile == 'o') {
                wattron(gameWin, COLOR_PAIR(5));
            }

            //Draw tile
            mvwaddch(gameWin, y + 1, x + 1, gm->dungeon.map[y][x]);

            //Turn off color
            wattroff(gameWin, COLOR_PAIR(1));
            wattroff(gameWin, COLOR_PAIR(2));
            wattroff(gameWin, COLOR_PAIR(3));
            wattroff(gameWin, COLOR_PAIR(4));
            wattroff(gameWin, COLOR_PAIR(5));
        }
    }
    wrefresh(gameWin);
}

void GameUI::drawPlayerStatus() {
    int y = 1;

    mvwprintw(uiWin, y++, 2, "Floor: %d", gm->player.playerFloor);

    mvwprintw(uiWin, y++, 2, "Player:");
    mvwprintw(uiWin, y++, 4, "Level: %d", gm->player.level);
    mvwprintw(uiWin, y++, 4, "HP: %d/%d", (int)gm->player.getCurrentHealth(), (int)gm->player.maxHealth);
    mvwprintw(uiWin, y++, 4, "Coins: %d", gm->player.playerCoin);

    string weaponName = "Fist";
    if (gm->player.getPlayerWeapon() != nullptr) {
        weaponName = gm->player.getPlayerWeapon()->getName();
    }
    mvwprintw(uiWin, y++, 4, "Weapon: %s", weaponName.c_str());
    
    mvwprintw(uiWin, y++, 2, "Inventory:");
    for (int i = 0; i < gm->inventory.getInventoryKeys().size(); ++i) {
        Item* item = gm->inventory.getInventoryKeys()[i];
        int* amount = gm->inventory.getHashTable().search(item->getName());
        if (amount) {
            char buffer[256];
            snprintf(buffer, sizeof(buffer), "%d.) %s x%d", i + 1, item->getName().c_str(), *amount);
            mvwprintw(uiWin, y++, 4, "%s", buffer);
            if (i + 1 == gm->getNumItem()) mvwprintw(uiWin, y - 1, 4 + strlen(buffer) + 1, "<-----");
        }
    }
    mvwprintw(uiWin, y++, 4, "Pree E to use item.");
    mvwprintw(uiWin, y++, 4, "Pree C to discrad item.");
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

void GameUI::drawDeathScreen() {
    clear();
    
    int artHeight = sizeof(SKULL) / sizeof(SKULL[0]);
    int artWidth = strlen(SKULL[0]); 

    int y = (LINES - artHeight) / 2;
    int x = (COLS - artWidth) / 2;
    
    for (int i = 0; SKULL[i] != nullptr; ++i) {
        mvprintw(y + i, x, "%s", SKULL[i]);
    }

    std::string message = ">>> YOU DIED <<<";
    int messageLength = message.length();
    int messageX = (COLS - messageLength) / 2; 

    std::string message2 = "---Press R to restart---";
    int messageLength2 = message2.length();
    int messageX2 = (COLS - messageLength2) / 2; 

    mvprintw(y + 9, messageX, "%s", message.c_str());
    mvprintw(y + 10, messageX, "%s", message2.c_str());
    refresh();
}

void GameUI::updateUI() {
    werase(uiWin);
    box(uiWin, 0, 0);

    drawPlayerStatus();
    drawDialogue(20);
    drawPlayerControl(25);

    wrefresh(uiWin);
}

void GameUI::updateGameScreen() {
    werase(gameWin);
    box(gameWin, 0, 0);
    drawDungeon();
}