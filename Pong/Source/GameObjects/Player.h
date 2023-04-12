#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Block.h"
#include "Animation.h"
#include "../GameConfig.h"
#include "../Collider.h"
#include "GameTile.h"
#include "../GameManager/ResourceManager.h"
using namespace sf;
using namespace std;

class Player
{
public:
	Player();
	Player(Texture* texture, Vector2i frameNum, float frameTime);
	~Player();

	void Update(float deltaTime);
	void Draw(RenderWindow* window);
	void OnCollision(Vector2f direction);

	void AddBlock();
	void RemoveBlock();
	bool CheckCollision(vector<GameTile*> tiles);
	void Move(float dx, float dy);
	void SetSpeed(float speed);
	float GetSpeed();
	vector<Block*> GetBody();
	void SetAlive(bool alive);
	bool GetAlive();
	
	
	Vector2f GetPosition();
	Collider GetCollider();
	bool isAddable(vector<GameTile*> tiles);
	bool Movable();

private:
	RectangleShape top;
	vector<Block*> body;
	float speed;
	Animation animation;
	Vector2f velocity;
	bool isMovable;
	float stunTime;
	float stunCoolDown;
	bool needHealing;
	Texture* bodyTexture;
	bool isAlive;
};

