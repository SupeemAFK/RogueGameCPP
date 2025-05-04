#include "./item.h"
#include "../gameManager/gameManager.h"

Item::Item(): 
    name(""), 
    descriptions(""), 
    itemRender(' ')
{}

Item::Item(const std::string& _name, const std::string& _desc, char _render) : 
    name(_name), 
    descriptions(_desc), 
    itemRender(_render) 
{}

void Item::setGameManager(GameManager* _gm) {
    gm = _gm;
}

//Base
bool Item::use() {
    return true;
}

int Item::getX() {
    return itemX;
}

int Item::getY() {
    return itemY;
}

void Item::setX(int x) {
    itemX = x;
}

void Item::setY(int y) {
    itemY = y;
}

std::string Item::getName() const {
    return name;
}

std::string Item::getDescriptions() const {
    return descriptions;
}

char Item::getItemRender() const {
    return itemRender;
}

bool Item::operator==(const Item& other) const {
    return name == other.name;
}

bool Item::operator!=(const Item& other) const {
    return !(*this == other);
}

std::string to_string(const Item& item) {
    return item.getName();
}