#pragma once
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <limits>
#include <iomanip>
#include <fstream>
#include <string>
#include "items.h"
using namespace std;
struct GameState {
    string playerName;
    unsigned int playerLevel;
    double playerHealth;
    double playerMoney;
    vector<string> playerWeapons; // Store names of weapons
    vector<string> playerArmors;   // Store names of armors
    vector<string> playerPotions;   // Store names of potions
    vector<string> playerSpells;    // Store names of spells
    void saveData() {
        ofstream outFile("game_state.txt");
        if (outFile.is_open()) {
            outFile << playerName << endl;
            outFile << playerLevel << endl;
            outFile << playerHealth << endl;
            outFile << playerMoney << endl;
            outFile << playerWeapons.size() << endl;
            for (const auto& weapon : playerWeapons) {
                outFile << weapon << endl;
            }
            outFile << playerArmors.size() << endl;
            for (const auto& armor : playerArmors) {
                outFile << armor << endl;
            }
            outFile << playerPotions.size() << endl;
            for (const auto& potion : playerPotions) {
                outFile << potion << endl;
            }
            outFile << playerSpells.size() << endl;
            for (const auto& spell : playerSpells) {
                outFile << spell << endl;
            }
            outFile.close();
        }
        else {
            cout << "Unable to open file for saving game state." << endl;
        }
    }
    void loadData() {
		ifstream inFile("game_state.txt");
		if (inFile.is_open()) {
			getline(inFile, playerName);
			inFile >> playerLevel;
			inFile >> playerHealth;
			inFile >> playerMoney;
			size_t size;
			inFile >> size;
			playerWeapons.resize(size);
			for (size_t i = 0; i < size; ++i) {
				inFile >> playerWeapons[i];
			}
			inFile >> size;
			playerArmors.resize(size);
			for (size_t i = 0; i < size; ++i) {
				inFile >> playerArmors[i];
			}
			inFile >> size;
			playerPotions.resize(size);
			for (size_t i = 0; i < size; ++i) {
				inFile >> playerPotions[i];
			}
			inFile >> size;
			playerSpells.resize(size);
			for (size_t i = 0; i < size; ++i) {
				inFile >> playerSpells[i];
			}
			inFile.close();
		}
		else {
			cout << "Unable to open file for loading game state." << endl;
		}
    }
};
class Living{
    protected:
        string name;
        string type;
        unsigned int level;
        double healthPower;
        double maxPower;
    public:
        Living(const string &name="default", unsigned int level=1, double healthPower=10, const string &type="default", double maxPower=10) : name(name), level(level), healthPower(healthPower), type(type), maxPower(maxPower) {}
        const string &getType() const;
        unsigned int getLevel() const;
        const string &getName() const;
        double getHealthPower() const;
        void setHealthPower(double);
        void setMaxPower(double);
        virtual ~Living(){}
};
class Player : public Living {
public:
    double magicPower;
    double magicMaxPower;
    double strength;
    double dexterity;
    double agility;
    double money;
    double experience;
    vector<Weapon*> my_weapons;
    vector<Armor*> my_armours;
    vector<Potion*> my_potions;
    vector<Spell*> my_spells;
    vector<DefensiveSkill*> my_defensiveSkills;
    static int playerCount;
public:
    Player(const string& name = "default", unsigned int level = 1, double healthPower = 1, const string& type = "default", double maxPower = 1, double magicPower = 1, double magicMaxPower = 1, double strength = 1, double dexterity = 1, double agility = 1, double money = 1, double experience = 0)
        : Living(name, level, healthPower, type, maxPower), magicPower(magicPower), magicMaxPower(magicMaxPower), strength(strength), dexterity(dexterity), agility(agility), money(money), experience(experience) {
        playerCount++;
    }
    Player(const Player& other) : Living(other.name, other.level, other.healthPower, other.type, other.maxPower) {
        this->magicPower = other.magicPower;
        this->magicMaxPower = other.magicMaxPower;
        this->strength = other.strength;
        this->dexterity = other.dexterity;
        this->agility = other.agility;
        this->money = other.money;
        this->experience = other.experience;
        for (const auto& weapon : other.my_weapons) {
            this->my_weapons.push_back(new Weapon(*weapon));
        }
        for (const auto& armour : other.my_armours) {
            this->my_armours.push_back(new Armor(*armour));
        }
        for (const auto& potion : other.my_potions) {
            this->my_potions.push_back(new Potion(*potion));
        }
        for (const auto& spell : other.my_spells) {
            this->my_spells.push_back(new Spell(*spell));
        }
    }
    void acquireDefensiveSkill(DefensiveSkill* skill) {
        my_defensiveSkills.push_back(skill);
    }
    void useDefensiveSkill(int index) {
        if (index >= 0 && index < my_defensiveSkills.size()) {
            my_defensiveSkills[index]->activate();
        }
    }
    void checkDefensiveSkills() {
        for (auto skill : my_defensiveSkills) {
            if (skill->checkActive()) {
                // Logic to handle the duration of the active skill
                // Decrease duration or deactivate if necessary
            }
        }
    }
    static int getPlayerCount() {
        return playerCount;
    }
    void buy(Weapon*);
    void buy(Armor*);
    void buy(Potion*);
    void buy(Spell*);
    Spell* castSpell(int);
    bool has_something_to_sell();
    void acquire(Weapon*);
    void acquire(Armor*);
    void acquire(Potion*);
    void acquire(Spell*);
    bool checkInventory();
    int healthPotionAvail();
    void selling_options();
    void reward(int);
    void LEVEL_UP();
    int spell_check();
    void setMoney(double);
    void setMagicPower(double mP) {
        Player::magicPower = mP;
    }
    void setMagicMaxPower(double mP) {
        Player::magicMaxPower = mP;
    }
    void setStrength(int str) {
        Player::strength = str;
    }
    void setDexterity(double dxtr) {
        Player::dexterity = dxtr;
    }
    void setAgility(double ag) {
        Player::agility = ag;
    }
    double getExperience() const;
    void setExperience(double);
    void inventory();
    double getMoney() const;
    void displayStats();
    int attack();
    //bool defend(int);
    void resurrect();
    void recover();
    bool defend(int damage) {
        cout << name << "!\n";
        double cur_agility = agility;

        // Check for active defensive skills
        for (auto skill : my_defensiveSkills) {
            if (skill->checkActive()) {
                damage *= (1 - skill->getEffectiveness()); // Reduce damage based on skill effectiveness
                skill->deactivate(); // Deactivate the skill after use
                break; // Only apply one defensive skill for this turn
            }
        }

        // Existing agility check logic...
        int probability = int(cur_agility * 100);
        srand(time(NULL));
        if (rand() % 100 < probability) {
            cout << endl << name << " avoided the monster's attack!\n\n";
        }
        else {
            int defensive = 0;
            for (int i = 0; i < my_armours.size(); i++) {
                if (my_armours.at(i)->isInUse()) {
                    defensive = my_armours.at(i)->getProtection();
                }
            }
            int force = damage * damage / (damage + defensive);
            if (force > 0) {
                healthPower -= force;
                cout << endl << name << " received " << force << " damage!" << endl << endl;
            }
            else cout << endl << name << " managed to block the monster's attack!\n\n";
        }
        if (healthPower < 0) {
            healthPower = 0;
            return false; // is defeated
        }
        return true; // still lives
    }
    virtual ~Player() {
        for (auto weapon : my_weapons) delete weapon;
        for (auto armour : my_armours) delete armour;
        for (auto potion : my_potions) delete potion;
        for (auto spell : my_spells) delete spell;
        playerCount--;
    }
};
class Warrior : public Player{
    public:
        Warrior(const string &name="Warrior", unsigned int level=1, double healthPower=10, const string &type="Warrior", double maxPower=10, double magicPower=10, double magicMaxPower=10, double strength=6, double dexterity=0.5, double agility=0.15, double money=7, double experience=0): Player(name, level, healthPower, type, maxPower, magicPower, magicMaxPower, strength, dexterity, agility, money, experience) {
			acquireDefensiveSkill(new Shield()); 
			acquireDefensiveSkill(new Dodge());
        }
        ~Warrior(){}
};
class Sorcerer : public Player{
    public:
        Sorcerer(const string &name="Sorcerer", unsigned int level=1, double healthPower=10, const string &type="Sorcerer", double maxPower=10,
                     double magicPower=16, double magicMaxPower=16, double strength=4, double dexterity=1, double agility=0.16, double money=11,
                     double experience=0): Player(name, level, healthPower, type, maxPower, magicPower, magicMaxPower, strength, dexterity, agility, money, experience) {
            acquireDefensiveSkill(new Shield()); 
            acquireDefensiveSkill(new MagicShield());
        }
        ~Sorcerer(){}
};
class Mage : public Player{
    public:
        Mage(const string &name="Paladin", unsigned int level=1, double healthPower=10, const string &type="Paladin", double maxPower=10,
                      double magicPower=12, double magicMaxPower=12, double strength=5, double dexterity=0.8, double agility=0.08, double money=8,
                      double experience=0): Player(name, level, healthPower, type, maxPower, magicPower, magicMaxPower, strength, dexterity, agility, money, experience) {
			acquireDefensiveSkill(new Shield()); 
			acquireDefensiveSkill(new Barrier());
        }
        ~Mage(){}
};
class Enemy : public Living{
    protected:
        double damage;
        double defence;
        double dodge_rate;
        vector<Spell*> under_a_spell;
    public:
        Enemy(const string& name = "default", unsigned int level = 1, double healthPower = 1, double damage = 1, double defence = 1, double dodgeProbability = 1, const string& type = "default") : Living(name, level, healthPower, type, healthPower), damage(damage), defence(defence), dodge_rate(dodgeProbability) {}
        void displayStats();
        int defendFrom(Spell* );
        void release_me_from_my_spell();
        void cleanup_spell_space();
        bool defendFrom(int );
        int attack();
        void recover();
        virtual ~Enemy(){}
};
class DarkBeasts : public Enemy{
    public:
        DarkBeasts(const string &name="Dragon", unsigned int level=1, double healthPower=1,
                        double damage=1, double defence=1, double dodgeProbability=0.1, const string &type="Dragon") :
               Enemy(name, level, healthPower, damage, defence, dodgeProbability, type) {}

        ~DarkBeasts(){}
};
class Undead : public Enemy{
    public:
        Undead(const string &name="Exoskeleton", unsigned int level=1, double healthPower=1,
                             double damage=1, double defence=1, double dodgeProbability=0.1, const string &type="Exoskeleton") :
                    Enemy(name, level, healthPower, damage, defence, dodgeProbability, type) {}
        ~Undead(){}
};
class Demons : public Enemy{
    public:
        Demons(const string &name="Spirit", unsigned int level=1, double healthPower=1, double damage=1, double defence=1, double dodgeProbability=0.1, const string &type="Spirit") :Enemy(name, level, healthPower, damage, defence, dodgeProbability, type) {}
        ~Demons(){}
};
