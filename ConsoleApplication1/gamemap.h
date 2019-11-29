#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <vector>
#include <set>
#include <string>
#include <utility>
#include <algorithm>
#include <memory.h> 
#include <fstream>

#define OK 1
#define ERROR -1
typedef int Status;

struct state {
	char** save_map;
	std::pair<int, int> player_pos;
	std::vector<std::pair<int, int> > box_pos;
};

class Game_Map {
public:
	Game_Map():map(NULL),map_height(0),map_length(0) {};
	~Game_Map() {};
protected:
	const char EMPTY = ' ';
	const char BLOCK = '1';
	const char BOX = '2';
	const char TARGET = '3';
	const char TARGET_BOX = '4';
	const char PLAYER = '5';
	char** map;
	int map_height;
	int map_length;
	std::pair<int, int> player_pos;
	std::vector<std::pair<int, int> > box_pos;
	std::vector<std::pair<int, int> > target_pos;
	Status Print_Map(void);
	void Clear_Map(void);
	void Save_State(state &save_state);
};

class Random_Game_Map: virtual protected Game_Map {
public:
	Random_Game_Map(int height = 10, int length = 10);
	~Random_Game_Map();
protected:
	Status Create_Map(void);
	void Random_Create_Map(void);
	std::pair<int, int> Create_Item(const char item);
	bool Check_Map(void);
};

class Normal_Game_Map : virtual protected Game_Map{
public:
	Normal_Game_Map(int num_map = 1);
	~Normal_Game_Map();
private:
	void Data_Transform(char &ch);
};
