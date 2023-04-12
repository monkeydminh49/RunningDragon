#pragma once
#include "GameMap.h"
class MenuBackground : public GameMap, public CSingleton<MenuBackground>
{
public:
	MenuBackground();
	void Init();
	void Update(float deltaTime);
	void Draw(RenderWindow* window);
	void NextMap();
	void UpdateMap();
private:
	vector<vector<int>> backgroundMap;
	vector<vector<vector<int>>> backgroundMaps;
};

