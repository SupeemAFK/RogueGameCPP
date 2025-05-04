#ifndef ITEM_H
#define ITEM_H

#include <string>

class GameManager;

class Item {
    public:
        Item(); //Default constructor
        void setGameManager(GameManager* _gm);

        friend std::ostream& operator<<(std::ostream& os, const Item& item) {
            os << item.name;
            return os;
        }

        int getX();
        int getY();
        void setX(int x);
        void setY(int y);

        virtual std::string getName() const;
        virtual std::string getDescriptions() const;
        virtual char getItemRender() const;

        virtual bool use();
        virtual ~Item() {}

        bool operator==(const Item& other) const;
        bool operator!=(const Item& other) const;

    protected:
        Item(const std::string& _name, const std::string& _desc, char _render);
        GameManager* gm;

    private:
        int itemX;
        int itemY;
        std::string name;    
        std::string descriptions;
        char itemRender;
};

std::string to_string(const Item& item);

#endif