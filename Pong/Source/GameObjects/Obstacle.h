#pragma once
#include "GameTile.h"
#include <vector>
#include "Player.h"
#include "Coin.h"
class Obstacle
{
protected: 
	Vector2f position;
	vector <pair< GameTile*, Coin* >> tiles;
	int isPass;

public:
	Obstacle();
	virtual void Init() = 0;
	virtual bool CheckCollision(Player &player) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void SetSpeed(float speed) = 0;
	virtual Vector2f GetPosition();
	virtual void Draw(RenderWindow* window);
	virtual Vector2f GetCoinPosition() = 0;
	virtual Coin* GetCoin() = 0;
	int GetPassingState();
	void SetPassingState(int isPass);
};