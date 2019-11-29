#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
#include <memory.h>
#include <stack>
#include "gamemap.h"

#define OK 1
#define ERROR -1
typedef int Status;

class Game: virtual protected Game_Map {
public:
	Game() {};
	~Game() {};
	Status Play(void);
protected:
	Status Push(void);
	bool Judge(void);
	std::stack<state> stk;
};
class Random_Game : virtual public Game, virtual protected Random_Game_Map {
public:
	Random_Game(int height = 10, int length = 10) :Game(), Random_Game_Map(height, length) {};
	~Random_Game() {};
	Status Play(void);
protected:
};
class Normal_Game :virtual public Game, virtual protected Normal_Game_Map {
public:
	Normal_Game(int game_num = 1) :Game(), Normal_Game_Map(game_num) {};
	~Normal_Game() {};
};
