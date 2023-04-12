#pragma once
#include "Animation.h"
#include "../GameManager/ResourceManager.h"
using namespace sf;
class Coin : public RectangleShape
{
public:
	Coin(Vector2f position);
	void Update(float deltaTime);
	void Draw(RenderWindow* window);
private:
	Animation* animation;
};