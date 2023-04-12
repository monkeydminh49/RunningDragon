#include "Obstacle.h"

Obstacle::Obstacle()
{
	isPass = false;
}

Vector2f Obstacle::GetPosition()
{
	return position;
}

void Obstacle::Draw(RenderWindow* window)
{
	for (auto tile : tiles) tile.first->Draw(window);
}

int Obstacle::GetPassingState()
{
	return isPass;
}

void Obstacle::SetPassingState(int isPass)
{
	this->isPass = isPass;
}

