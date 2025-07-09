#pragma once
#include "characters.h"
class monsterList {
    public:
        monsterList();
        ~monsterList();
        Enemy* at(int );
        void add(Enemy* );
        void vanish(int );
        void checkEnchantments();
        void subdue(int , int);
        int size() const {return list_size;}
    private:
        typedef struct monster_node{
            Enemy* monster;
            int round;
            monster_node* next;
        }* monster_node_ptr;
        monster_node_ptr head;
        monster_node_ptr curr;
        monster_node_ptr temp;
        int list_size;
};