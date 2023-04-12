#include "GameTile.h"
#include <iostream>
using namespace std;

GameTile::GameTile()
{
}

GameTile::GameTile(Texture* texture, Vector2f position, bool isPassible, bool isExit)
    : Block(texture, mapSpeed, position), isPassible(isPassible), isExit(isExit) {
    body.setSize(Vector2f(tileSize, tileSize));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(position);
    body.setTexture(texture);
    if (!isExit) body.setFillColor(Color(255, 255, 255, 128));
}

GameTile::GameTile(Texture *texture, Vector2f position, Vector2f size, bool isPassible, bool isExit)
: Block(texture, mapSpeed, position), isPassible(isPassible), isExit(isExit) {
    body.setSize(size);
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(position);
    body.setTexture(texture);
}

void GameTile::SetPosition(Vector2f position)
{
    body.setPosition(position);
}

void GameTile::SetPosition(float x, float y)
{
    body.setPosition(x, y);
}

Vector2f GameTile::GetPosition()
{
    return body.getPosition();
}

Vector2f GameTile::GetSize()
{
    return body.getSize();
}

Collider GameTile::GetCollider()
{   
    return Collider(body);
}


bool GameTile::Passible()
{
    return isPassible;
}

void GameTile::Move(float dx, float dy)
{
    body.move(dx, dy);
}

void GameTile::Draw(RenderWindow* window)
{
    window->draw(body);
}

void GameTile::Update(float deltaTime)
{   
}
