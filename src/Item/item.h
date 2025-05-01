#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

class Item {
    public:
        string name;    
        string descriptions;
        virtual void use();
};

#endif