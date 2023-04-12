#pragma once
#include "GameTile.h"
#include "Obstacle.h"
#include "GapWall.h"
#include "../GameManager/ResourceManager.h"

class GameMap
{
public:
	GameMap();
	void Init();
	virtual void Draw(RenderWindow* window);
	virtual void Update(float deltaTime);
	Sprite GetBackground();
	vector<GameTile*> GetTiles();
	vector<Obstacle*> GetObstacles();
	void AddTile(GameTile* tile);
	void SetSpeed(float speed);
	float GetSpeed();
	void ChangeMap(int mapIndex);
	void UpdateMap();
	int currentMapIndex;

private:
	vector<vector<int>> gameMap;
	vector<vector<vector<int>>> gameMaps;

protected:
	vector<GameTile*> tiles;
	vector<Obstacle*> obstacles;
	vector<Block*> obstaclesPos;
	vector<string> paths = { "Forest/", "Desert/", "Winter/" };
	Sprite background;
	float speed;
	
};

