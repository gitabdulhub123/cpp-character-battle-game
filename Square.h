#pragma once
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "characters.h"
#include "items.h"
#include "monsterlist.h"
using namespace std;
class Square {
protected:
    int type;
    vector<Player*> heroes_here;
    bool isHeroPresent;
public:
    Square(int type = 0);
    int getType() const { return type; }
    void place(Player*);
    bool isHeroesPresent() const;
    int average_level();
    void setHeroesPresent(bool heroesPresent);
    void checkInventory();
    void displayStats();
    int battle_options();
    void shopping_time();
    void battle(monsterList&);
    bool monstersWin();
    bool heroesWin(int, int);
    Player* exit();
    virtual string getMarketName();
    virtual void display_stock(int, Player*);
    virtual int market_options();
    virtual void restock(Weapon* [], Armor* [], Potion* [], Spell* []);
    
};
