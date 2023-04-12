#include "GameMap.h"
#include <iostream>

GameMap::GameMap()
{
}

void GameMap::Init()
{	
	currentMapIndex = 0;
	gameMap = vector<vector<int>>{ retro_forest };
	gameMaps.push_back(gameMap);
	gameMap = vector<vector<int>>{ retro_desert };
	gameMaps.push_back(gameMap);
	gameMap = vector<vector<int>>{ retro_winter };
	gameMaps.push_back(gameMap);

	// Background
	Texture* backgroundTexture = DATA->getTexture("night_sky");
	background.setTexture(*backgroundTexture);
	background.setScale(0.62f, 0.62f);

	speed = mapSpeed;

	UpdateMap();

	Block* block;
	GapWall* obstacle;
	Vector2f pos = Vector2f(0, 0);
	for (int i = 0; i < 3; i++) {
		block = new Block(pos);
		obstaclesPos.push_back(block);
		pos.x += playerSize * 8;
	}

}

void GameMap::Draw(RenderWindow* window)
{	
	for (auto tile : tiles) tile->Draw(window);
	for (auto obstacle : obstacles) obstacle->Draw(window);
}

void GameMap::Update(float deltaTime)
{	
	for (auto tile : tiles) {
		tile->Move(-speed * deltaTime, 0.0f);
		if (tile->GetPosition().x <= -24) tile->SetPosition(Vector2f(tile->GetPosition().x + 2 * screenWidth, tile->GetPosition().y));
	}
	int size = obstaclesPos.size();
	
	GapWall* obstacle;
	for (auto block: obstaclesPos) {
		block->Move(-block->GetSpeed() * deltaTime, 0);
		if (block->GetPosition().x <= -block->GetSize()) {
			for (auto block: obstaclesPos) block->SetSpeed(speed);
			block->SetPosition(block->GetPosition().x + 8 * playerSize * size, 0);
			obstacle = new GapWall(block->GetPosition());
			if (obstacles.size()>2) {
				delete obstacles[0];
				obstacles.erase(obstacles.begin());
			}
			obstacles.push_back(obstacle);
		}
	}
	
	for (auto obstacle : obstacles) {
		obstacle->SetSpeed(speed);
		obstacle->Update(deltaTime);
	}
}

Sprite GameMap::GetBackground()
{
	return background;
}

vector<GameTile*> GameMap::GetTiles()
{
	return tiles;
}

vector<Obstacle*> GameMap::GetObstacles()
{
	return obstacles;
}

void GameMap::AddTile(GameTile* tile)
{	
	tiles.push_back(tile);
}

void GameMap::SetSpeed(float speed)
{
	this->speed = speed;
}

float GameMap::GetSpeed()
{
	return speed;
}

void GameMap::ChangeMap(int mapIndex)
{
	currentMapIndex = mapIndex;
}

void GameMap::UpdateMap()
{	
	
	tiles.clear();
	Vector2f position;
	bool passible;
	Texture* texture;
	GameTile* tile;
	string path = paths[currentMapIndex];
	string texturePath;

	for (int i = 0; i < gridHeight; i++) {
		for (int j = 0; j < gridWidth * 2; j++) {
			if (gameMaps[currentMapIndex][i][j] == 0) {
				continue;
			}
			texturePath = path + to_string(gameMaps[currentMapIndex][i][j]);
			texture = DATA->getTexture(texturePath);;

			passible = (i != 1 && i != 17 ? true : false);

			tile = new GameTile(texture, Vector2f(0.0f, 0.0f), passible, !passible);
			position = Vector2f(tileSize / 2.0f, tileSize / 2.0f);
			position.x += j * tileSize;
			position.y += i * tileSize;
			tile->SetPosition(position);

			tiles.push_back(tile);
		}
	}
}
