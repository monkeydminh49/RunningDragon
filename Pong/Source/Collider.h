#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Collider
{	
public:
	Collider(RectangleShape &body);
	~Collider();

	void Move(float dx, float dy);
	bool CheckCollision(Collider & other, Vector2f & direction, float push);
	Vector2f GetPosition();
	Vector2f GetHalfSize();

private:
	RectangleShape & body;
};

