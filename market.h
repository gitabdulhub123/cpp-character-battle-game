#pragma once
#include"Square.h"
using namespace std;
class common : public Square {
public:
    explicit common(int type = 1) : Square(type) {}
};

class nonAccessible : public Square {
public:
    explicit nonAccessible(int type = 2) : Square(type) {}
};

class market : public Square {
private:
    string market_name;
    Weapon* weapons_storage[6][7];
    Armor* armours_storage[4][4];
    Potion* potions_storage[12][20];
    Spell* spells_storage[9][16];
public:
    explicit market(Weapon* [], Armor* [], Potion* [], Spell* [], int type = 3, const string& name = "Market Inn");
    string getMarketName();
    void restock(Weapon* [], Armor* [], Potion* [], Spell* []);
    int market_options();
    void display_stock(int, Player*);
};

