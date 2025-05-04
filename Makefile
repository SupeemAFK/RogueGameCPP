CXX = g++
CXXFLAGS = -lncursesw
OUTPUT = game

SRC = \
	src/lib/hashtable/HashTable.cpp \
	src/main.cpp \
	src/lib/priorityqueue/PriorityQueue.cpp \
	src/dungeon/dungeon.cpp \
	src/UI/ui.cpp \
	src/player/player.cpp \
	src/coin/coin.cpp \
	src/nextLevel/nextLevel.cpp \
	src/gameManager/gameManager.cpp \
	src/enemy/enemy.cpp \
	src/inventory/inventory.cpp \
	src/Item/item.cpp \
	src/Item/healingPotion/healingPotion.cpp \
	src/Item/megaPotion/megaPotion.cpp \
	src/Item/weapon/weapon.cpp \
	src/Item/weapon/SteelSword/steelSword.cpp \
	src/Item/weapon/Dagger/dagger.cpp \
	src/Item/weapon/Katana/katana.cpp \
	src/Item/weapon/Axe/axe.cpp \
	src/Item/weapon/Hammer/hammer.cpp

all:
	$(CXX) $(SRC) -o $(OUTPUT) $(CXXFLAGS)

clean:
	rm -f $(OUTPUT)
