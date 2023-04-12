#pragma once
#include <SFML/Graphics.hpp>
#include "../Collider.h"
#include "../GameConfig.h"
using namespace sf;

class Block
{
public:
	Block();
	Block(Vector2f position);
	Block(Texture* texture, float speed, Vector2f position);
	~Block();

	void Update(float deltaTime);
	void Draw(RenderWindow* window);
	void Move(float dx, float dy);
	void OnCollision(Vector2f direction);
	void SetPosition(float dx, float dy);
	void SetMovable(bool movable);
	void SetSpeed(float speed);
	float GetSpeed();

	Vector2f GetPosition();
	Collider GetCollider();
	float GetSize();
	bool isGrounded;
	bool isConnected;

protected:
	static float size;
	RectangleShape body;
	Vector2f velocity;
	float speed;
	bool isMovable;
};

