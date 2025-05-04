# Rogue Game built with C++ 🗡️

## What is Rogue Game? 🕹️👾
 A rogue game is a challenging dungeon crawler with randomized levels and permadeath, designed for replayability. It originated from the game Rogue which was created using the C programming language.


## Example Gameplay :
![Gameplay footage](/images/roguegameimage.png)


  ## Objectives 🗒 ˎˊ˗ 
  
   This project is a Rogue dungeon crawler game but we built with C++ and designed to enhance the classic Rogue gameplay by applying advanced data structures.<br>


 ## Goal ⛳ 
to procedurally generate dungeons using Prim's algorithm to create a graph-based layout with rooms connected by corridors for a more dynamic and immersive experience.

## Key Features 🌟
- **Procedural Dungeon Generaion** using MST with Prim's algorithm.
- **RPG Elements** with level, strength, weapon selection and player progression.
- **Inventory System** Inventory management using Hash Table (open adressing).
- **Turn-based combat** Introduce turned-base combat making game fun and challenging.
- **Text-based user interface(TUI)** with ncurses library to create engaging and beautiful TUI.

## Installation 
### Required Dependencies
To build and run the project, you will need the following:
- **C++ Compiler**: g++ (or any other C++11 compliant compiler)
- **ncurses Library**: Required for handling the text-based UI

For **Linux-based systems (including WSL)**, you can install these dependencies with:

```bash
sudo apt-get install build-essential libncursesw5-dev
```

For **MSYS2**, you can install these dependencies with:
```
pacman -Syu      # Update MSYS2 base system
pacman -S make   # Install make
pacman -S gcc    # Install g++
pacman -S ncurses-devel  #
```

Or **Compile Manually** using
```
g++ src/lib/hashtable/HashTable.cpp src/main.cpp src/lib/priorityqueue/PriorityQueue.cpp src/dungeon/dungeon.cpp src/UI/ui.cpp src/player/player.cpp src/coin/coin.cpp src/nextLevel/nextLevel.cpp src/gameManager/gameManager.cpp src/enemy/enemy.cpp src/inventory/inventory.cpp src/Item/item.cpp src/Item/healingPotion/healingPotion.cpp src/Item/megaPotion/megaPotion.cpp src/Item/weapon/weapon.cpp src/Item/weapon/SteelSword/steelSword.cpp src/Item/weapon/Dagger/dagger.cpp src/Item/weapon/Katana/katana.cpp src/Item/weapon/Axe/axe.cpp src/Item/weapon/Hammer/hammer.cpp -o game -lncursesw
```