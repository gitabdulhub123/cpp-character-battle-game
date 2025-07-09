#include "messages.h"
#include "characters.h"
#include "Map.h"
#include <conio.h>
#include <string>

void worldbuilding() {
    // Start of the game – welcoming the player
    cout << "Welcome to the world of Legends of Valor!" << endl;
    int heroes = 1;
    // Asking user how many heroes they want – sirf 1, 2 ya 3 allowed hain
	cout << "do you want to load saved game? (y/n)" << endl;
	char choice;    
	cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        map_grid.loadGame(); // load the game
    }
    else {
        do {
            cout << "How many heroes would you like on your adventure 1, 2 or 3 ?" << endl;
            heroes = _getch() - '0'; // taking input without enter
            cout << heroes << endl; // display the input
        } while (heroes != 1 && heroes != 2 && heroes != 3); // repeat until valid input
        map_grid.setHeroSize(heroes); // telling the map how many heroes to expect
        // Loop through each hero and get their type and name
        for (int i = 0; i < heroes; i++) {
            if (heroes == 1) {
                cout << "What type of hero do you want to be?" << endl;
            }
            else cout << "Your hero number " << i + 1 << " is a: " << endl;

            // Choose hero class – again sirf 1, 2 ya 3 valid hain
            do {
                cout << "1. Sorcerer" << endl;
                cout << "2. Warrior" << endl;
                cout << "3. Mage" << endl;
                choice = _getch() - '0';
                cout << choice << endl; // display the input
            } while (choice != 1 && choice != 2 && choice != 3);

            string input;
            cout << "What is their name ? " << endl;
            getline(cin, input); // taking name input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Ab jo bhi type choose kiya, uske according hero create kar ke map pe place kar rahe hain
            if (choice == 1)
                map_grid.place_on_the_board(new Sorcerer(input), 18, 9);
            else if (choice == 2)
                map_grid.place_on_the_board(new Warrior(input), 18, 9);
            else if (choice == 3)
                map_grid.place_on_the_board(new Mage(input), 18, 9);
        }

        // Ek hero ho to solo message, warna team assembled ka
        if (heroes == 1)
            cout << "\n Hero Created! Let's begin! " << endl;
        else
            cout << "\n Team Assembled! Let's begin! " << endl;

        map_grid.displayMap(); // game ka map dikha dete hain start mein
    }
}
int options() {
    // User se pooch rahe hain ke ab kya karna hai – like move karna, stats dekhna etc.
    do {
        cout << "\nWhat would you like to do?" << endl << endl;
        map_grid.playerOptions(); // display available actions
        cout << "\n> ";
        choice = _getch() - '0';
		cout << choice << endl; // display the input
    } while (!map_grid.check_option(choice)); // jab tak valid choice na ho, keep looping
    return choice;
}
void action(int choice2) {
    if (choice2 == 1) move(1);
    else if (choice2 == 2) move(2);
    else if (choice2 == 3) move(3);
    else if (choice2 == 4) move(4);
    else if (choice2 == 5) map_grid.checkInventory(); // check inventory
    else if (choice2 == 6) map_grid.displayStats();   // show stats
    /*else if (choice2 == 7) map_grid.displayMap(); */    // show map again
    map_grid.displayMap();
}
void move(int choice2) {
    map_grid.move(choice2); // move in the selected direction
    if (map_grid.inside_a_market()) {
        map_grid.shopping_time();
    }
    else {
        // Random battle check – seeding time
        srand(time(0));
        if (rand() % 5 == 1) {
            map_grid.battle(); // 20% chance of a battle
        }
        else {
            cout << "\n You tread carefully, no monster is in sight.\n"; // safe moment – sukoon
        }
    }
}

void supply_the_markets() {
    // Sab markets ko restock kar rahe hain – yaani nayi cheezein aa rahi hongi
    map_grid.restock();
}

void end() {
    // Ending message – khatam
    cout << "\n Thank you for playing Legends of Valor!" << endl;
    cout << "\n ";
}

