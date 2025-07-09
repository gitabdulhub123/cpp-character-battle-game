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
#include"Square.h"
#include "market.h"
#include <fstream>
class Map {
private:
    int heroes;
    static const int gridRows = 19;
    static const int gridColumns = 19;
    Square* board[gridRows][gridColumns];
    Enemy* monsters[25];
    Weapon* weapons[6];
    Armor* armours[4];
    Potion* potions[12];
    Spell* spells[9];
public:
    int positionX;
    int positionY;
    Map();
    void displayMap();
    void setHeroSize(int);
    void place_on_the_board(Player*, int , int);
    void playerOptions();
    bool check_option(int);
    void checkInventory();
    void shopping_time();
    void displayStats();
    void restock();
    void battle();
    bool inside_a_market();
    void move(int);
	void loadGame() {
		ifstream saveFile("savegame.dat");
        int x, y;
		if (saveFile.is_open()) {
			saveFile >> x >> y;
            place_on_the_board(new Sorcerer("umr"), x, y);
			positionX = x;
			positionY = y;
			displayMap();
			saveFile.close();
		}
        else {
			cout << "No saved game found." << endl;
        }
	}
    ~Map() {}
};

