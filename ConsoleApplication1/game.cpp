#include "game.h"
#include <conio.h>
Status Game::Push() {
	const int dx[] = { 0, -1, 0, 1 };
	const int dy[] = { -1, 0, 1, 0 };
	char ch = _getch();
	if (ch == 0 || ch == 0xE0)	ch = _getch();
	int px = this->player_pos.first, py = this->player_pos.second;
	int pxx, pyy, bxx, byy;
	int twist = -1;
	switch (ch) {
		//左键
	case 'a':
	case 75: {
		twist = 0;
		pxx = px + dx[0], pyy = py + dy[0];
		break;
	}
		   //上键
	case 'w':
	case 72: {
		twist = 1;
		pxx = px + dx[1], pyy = py + dy[1];
		break;
	}
		   //右键
	case 'd':
	case 77: {
		twist = 2;
		pxx = px + dx[2], pyy = py + dy[2];
		break;
	}
		   //下键
	case 's':
	case 80: {
		twist = 3;
		pxx = px + dx[3], pyy = py + dy[3];
		break;
	}
	case 'z': {
		if (stk.empty()) return -1;
		state save_state = stk.top(); stk.pop();
		char** save_map = save_state.save_map;
		for (int i = 0; i < map_height; i++) {
			for (int j = 0; j < map_length; j++) {
				map[i][j] = save_map[i][j];
			}
		}
		player_pos = save_state.player_pos;
		box_pos = save_state.box_pos;
		return -1;
	}
	default: {
		return 0;
	}
	}
	//无法行走
	if (map[pxx][pyy] == BLOCK) {
		return 0;
	}
	//推到了箱子
	auto result = find(box_pos.begin(), box_pos.end(), std::pair<int, int>{pxx, pyy});
	int index = result - box_pos.begin();
	if (result != box_pos.end()) {
		int bx = box_pos[index].first;
		int by = box_pos[index].second;
		bxx = bx + dx[twist], byy = by + dy[twist];
		//但箱子不能往这个方向走
		if (map[bxx][byy] == BLOCK || map[bxx][byy] == BOX || map[bxx][byy] == TARGET_BOX) {
			return 0;
		}
		map[bx][by] = EMPTY;
		box_pos[index] = std::pair<int, int>{ bxx, byy };
		map[bxx][byy] = (find(target_pos.begin(), target_pos.end(), box_pos[index]) != target_pos.end()) ?  TARGET_BOX: BOX;
	}
	this->player_pos.first = pxx, this->player_pos.second = pyy;
	map[px][py] = EMPTY;
	auto find_player = find(target_pos.begin(), target_pos.end(), player_pos);
	for (auto a : target_pos) {
		if (map[a.first][a.second] == TARGET_BOX)	continue;
		if (map[a.first][a.second] == EMPTY)	map[a.first][a.second] = TARGET;
	}
	map[pxx][pyy] = PLAYER;
	return OK;
}

Status Game::Play() {
	system("cls");
	state current_state;
	Save_State(current_state);
	Print_Map();
	while (!Judge()) {
		int value = Push();
		if(value == 0)	continue;
		if (value == OK) {
			stk.push(current_state);
		}
		Save_State(current_state);
		system("cls");
		Print_Map();
	}
	std::cout << "You win!" << std::endl;
	return OK;
}

Status Random_Game::Play() {
	this->Create_Map();
	system("cls");
	Game::Play();
	return OK;
}
bool Game::Judge() {
	for (auto a : box_pos) {
		if (find(target_pos.begin(), target_pos.end(), a) == target_pos.end()) {
			return false;
		}
	}
	return true;
}