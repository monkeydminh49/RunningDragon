#include "GapWall.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

GapWall::GapWall(Vector2f position){
    this->position = position;
    speed = mapSpeed;
    isPass = false;
    coin = new Coin(Vector2f(0, 0));
    Init();
}

void GapWall::Init()
{
    Texture *glassTexture = DATA->getTexture("glass");
    GameTile* glass = new GameTile(glassTexture, position, Vector2f(playerSize, playerSize), true, true);
    
    Texture *groundTexture = DATA->getTexture("Wall01");
    GameTile* ground = new GameTile(groundTexture, position, Vector2f(playerSize, playerSize), false, true);

    GameTile* tmp;
    srand(time(NULL));
    int glassNum = rand() % (5 - 3 + 1) + 3;
    int wallNum = 10 - glassNum;
	

	
    for (int i = 0; i < glassNum-1; i++) {
        tmp = new GameTile();
        *tmp = *glass;
        tiles.emplace_back(pair<GameTile*, Coin*>{ tmp, NULL });
    }
    tmp = new GameTile();
    *tmp = *glass;
    tiles.emplace_back(pair<GameTile*, Coin*>{ tmp, coin });
    for (int i = 0; i < wallNum; i++) {
        tmp = new GameTile();
        *tmp = *ground;
        tiles.emplace_back(pair<GameTile*, Coin*>{ tmp, NULL });
    }
   
	
    std::random_shuffle(tiles.begin(), tiles.end());
	
    tiles[0].first->SetPosition(position.x,screenHeight - 32.0f*2 - tiles[0].first->GetSize().y/2.0f);
    Vector2f newPos = position;
    for (int i = 1; i < tiles.size(); i++) {
        newPos = position;
        newPos.y = tiles[i - 1].first->GetPosition().y - tiles[i-1].first->GetSize().y / 2.0f - tiles[i].first->GetSize().y / 2.0f;
        tiles[i].first->SetPosition(newPos);
        if (tiles[i].second != NULL) {
			tiles[i].second->setPosition(newPos);
        }
    }
}

bool GapWall::CheckCollision(Player &player)
{
    bool flag = false;
    Vector2f direction;

    Collider tmp1 = player.GetCollider();
	
    for (auto tile : tiles) {
        if (tile.first == nullptr) continue;
        Collider tmp = tile.first->GetCollider();
        if (!tile.first->Passible() && tmp.CheckCollision(tmp1, direction, 1.0f)) {
            flag = true;
            player.OnCollision(direction);
        }
        for (auto block : player.GetBody()) {
            Collider d = block->GetCollider();
            if (!tile.first->Passible() && tmp.CheckCollision(d, direction, 1.0f)) {
                block->OnCollision(direction);
            }
        }
    }

    return flag;
}

void GapWall::Update(float deltaTime)
{   
    if (coin != NULL) coin->Update(deltaTime);
    for (auto tile : tiles) {
        tile.first->Move(-speed * deltaTime, 0.0f);
        if (tile.second != NULL) {
			tile.second->move(-speed * deltaTime, 0.0f);
        }
    }
}

void GapWall::SetSpeed(float speed)
{
    this->speed = speed;
}

Vector2f GapWall::GetPosition()
{
    return tiles[0].first->GetPosition();
}

void GapWall::Draw(RenderWindow* window)
{
    Obstacle::Draw(window);
	if (coin!=NULL && GetPassingState() != 1)coin->Draw(window);

}

Vector2f GapWall::GetCoinPosition()
{
    return coin->getPosition();
}

Coin* GapWall::GetCoin()
{
    return coin;
}

