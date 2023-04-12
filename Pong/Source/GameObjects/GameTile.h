#pragma once
#include <SFML/Graphics.hpp>
#include "../GameConfig.h"
#include "Block.h"
#include <string>
using namespace std;
using namespace sf;

class GameTile : public Block
{
public:
	GameTile();
	GameTile(Texture* texture, Vector2f position, bool isPassible, bool isExit);
	GameTile(Texture* texture, Vector2f position, Vector2f size, bool isPassible, bool isExit);

	void SetPosition(Vector2f posistion);
	void SetPosition(float x, float y);
	Vector2f GetPosition();

	Vector2f GetSize();

	Collider GetCollider();

	bool Passible();
	void Move(float dx, float dy);


	void Draw(RenderWindow* window);
	void Update(float deltaTime);

private:
	
	bool isPassible;
	bool isExit;
};

