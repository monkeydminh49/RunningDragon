#include "Coin.h"

Coin::Coin(Vector2f position)
{
	this->setSize(Vector2f(32.f, 32.f));
	this->setOrigin(this->getSize() / 2.0f);
	this->setTexture(DATA->getTexture("coin"));
	this->setPosition(position);
	animation = new Animation(DATA->getTexture("coin"), Vector2i(9, 1), 0.1f);
}

void Coin::Update(float deltaTime)
{
	animation->Update(deltaTime, 1, 8);
	this->setTextureRect(animation->m_rect);
}

void Coin::Draw(RenderWindow* window)
{
	window->draw(*this);
}

