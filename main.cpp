#include "messages.h"
#include"Map.h"

int Player::playerCount = 0;
int main() {
    map_grid;
    worldbuilding(); 
    int choose = 9, rounds = 0;
    choose = options();
    while (choose != 7) { 
        action(choose);
        rounds++;
        if (rounds % 200 == 0) supply_the_markets();
        choose = options();
    }
	
    cout << "\n Player count: " << Player::getPlayerCount();
    end();
    return 0;
}
void copyDemo() {
    Player player1("Hero", 1, 100, "Warrior", 100, 50, 50, 10, 5, 5, 100, 0);
    player1.buy(new Weapon("Sword", 10, 1, 5, false));
    player1.buy(new Armor("Shield", 5, 1, 3));
    player1.displayStats();
    Player player2 = player1;
    player2.displayStats();
    player1.setHealthPower(80);
    cout << "After modifying player1's health:\n";
    player1.displayStats();
    player2.displayStats();
}
