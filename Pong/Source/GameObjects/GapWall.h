#pragma once
#include "Obstacle.h"
#include "Player.h"
#include "Coin.h"
#include <algorithm>
#include <random>
class GapWall : public Obstacle
{
public:
	GapWall(Vector2f position);
	void Init();
	bool CheckCollision(Player& player);
	void Update(float deltaTime);
	void SetSpeed(float speed);
	Vector2f GetPosition();
	void Draw(RenderWindow* window);
	Vector2f GetCoinPosition();
	Coin* GetCoin();

private:
	float speed;
	Coin* coin;
};

