#pragma once
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "Map.h"
using namespace std;
static int choice;
static Map map_grid;
void worldbuilding();
int options();
void action(int);
void supply_the_markets();
void move(int);
void end();
