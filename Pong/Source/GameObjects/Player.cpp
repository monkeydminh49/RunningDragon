#include "Player.h"
#include <iostream>

Player::Player()
{
}

Player::Player(Texture* texture, Vector2i frameNum, float frameTime)
    :animation(texture, frameNum, frameTime)
{
    top.setSize(Vector2f(playerSize, playerSize));
    top.setOrigin(top.getSize() / 2.0f);
    top.setPosition(playerSize*4, playerSize*6);
    top.setTexture(texture);
    bodyTexture = DATA->getTexture("egg");
    isMovable = true;
    stunTime = 0;
    speed = playerSpeed;
    needHealing = false;
    isAlive = true;
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    Vector2f direction;

    for (int i = 0; i < body.size(); i++) {
        Block* block = body[i];
        Collider tmp = block->GetCollider();
        Collider tmp1 = GetCollider();
        if (tmp.CheckCollision(tmp1, direction, 1.0f)) {
            OnCollision(direction);
        }
        if (block->GetPosition().y >= screenHeight - tileSize * 2.0f - playerSize/2.0f) block->isGrounded = true;
        if ((block->isGrounded && !block->isConnected)
            || (block->GetPosition().x > screenWidth || block->GetPosition().x < 0 || block->GetPosition().y > screenHeight)) {
            delete block;
            body.erase(body.begin() + i);
        }
    }

    for (auto block1 : body) {
        Collider tmp = block1->GetCollider();
        for (auto block2 : body) {
            if (block1 == block2) continue;
            Collider tmp1 = block2->GetCollider();
            if (tmp.CheckCollision(tmp1, direction, 1.0f)) {
                block2->OnCollision(direction);
                block2->isGrounded = false;
            }
        }
    }

    velocity.x *= slowDownRate;
    int start = 0, end = 3;
    animation.setFrameTime(0.1f);

    bool tmp = isMovable;
	
    if (!isMovable) {
		if (stunTime == 0.f)
        {
			DATA->getSound("punch")->setVolume(40);
            DATA->playSound("punch");
			
        }
        stunTime += deltaTime;
        if (stunTime > 1.5f) {
            isMovable = true;
            stunTime = 0;
        }
        else {
            start = 16, end = 19;
            animation.setFrameTime(0.08f);
        }
    }

    if (tmp != isMovable) {
        needHealing = true;
    }
    if (needHealing) {
        stunCoolDown += deltaTime;
        if (stunCoolDown > 0.6f) {
            needHealing = false;
            stunCoolDown = 0;
        }
        else {
            isMovable = true;
            start = 0, end = 3;
            animation.setFrameTime(0.1f);
        }
    }

	
    if (Keyboard::isKeyPressed(Keyboard::D) && isMovable) {
        velocity.x += speed;
        start = 4, end = 9;
        animation.setFrameTime(0.1f);
    }
    if (Keyboard::isKeyPressed(Keyboard::A) && isMovable) {
        velocity.x -= speed;
        start = 10, end = 15;
        animation.setFrameTime(0.11f);
    }
   
    velocity.y += 981.0f * deltaTime;
    animation.Update(deltaTime, start, end);
    top.setTextureRect(animation.m_rect);
    top.move(velocity*deltaTime);
    
    for (int i = 0; i < body.size(); i++) {
        Block* block = body[i];
        if (block->GetPosition().x > top.getPosition().x + top.getSize().x / 2
            || block->GetPosition().x < top.getPosition().x - top.getSize().x / 2) {
            block->isConnected = false;
        }
        block->SetMovable(isMovable);
        block->Update(deltaTime);
        block->SetSpeed(speed);
    }

}

void Player::Draw(RenderWindow* window)
{
    window->draw(top);
    for (auto block : body) block->Draw(window);
}

void Player::OnCollision(Vector2f direction)
{   
    if (direction.x < 0.0f) {
        // Collision on the left
        velocity.x = 0.0f;
        isMovable = false;
    }
    else if (direction.x > 0.0f) {
        // Collision on the right
        velocity.x = 0.0f;
    }
    else if (direction.y < 0.0f) {
        // Collision on the bottom
        velocity.y = 0.0f; 
    }
    else if (direction.y > 0.0f) {
        // Collision on the top
        velocity.y = 0.0f;  
    }
}
\
Vector2f Player::GetPosition()
{
    return top.getPosition();
}

Collider Player::GetCollider()
{
    return Collider(top);
}

bool Player::isAddable(vector<GameTile*> tiles)
{
    RectangleShape nextPos = RectangleShape(top.getSize() / 2.0f);
    nextPos.setPosition(top.getPosition().x, top.getPosition().y - top.getSize().y);
    Collider tmp = Collider(nextPos);
    for (auto& tile : tiles) {
        Collider tmp1 = tile->GetCollider();
        Vector2f direction;
        if (tmp.CheckCollision(tmp1, direction, 0.0f) && !tile->Passible()) {
            return false;
        }
    }
    return true;
}

bool Player::Movable()
{
    return isMovable;
}


void Player::AddBlock()
{
    float blockSize = top.getSize().x;
    top.move(0, -blockSize);
    velocity.y = 0;


    Vector2f position = top.getPosition();
    Block* block = new Block(bodyTexture, speed, Vector2f(position.x, position.y + blockSize));

    body.push_back(block);

}

void Player::RemoveBlock()
{
    if (body.size() >= 1) {
        delete body[0];
        body.erase(body.begin());
    }
}

bool Player::CheckCollision(vector<GameTile*> tiles)
{
    bool flag = false;
    Vector2f direction;

    for (auto tile : tiles) {
        if (tile == nullptr) continue;
        Collider tmp = tile->GetCollider();
        Collider tmp1 = GetCollider();
        if (!tile->Passible() && tmp.CheckCollision(tmp1, direction, 1.0f)) {
            flag = true;
            OnCollision(direction);
        }
        for (auto block : body) {
            Collider d = block->GetCollider();
            if (!tile->Passible() && tmp.CheckCollision(d, direction, 1.0f)) {
                block->OnCollision(direction);
            }
        }
    }

    return flag;
}

void Player::Move(float dx, float dy)
{
    top.move(dx, dy);
}

void Player::SetSpeed(float speed)
{
    this->speed = speed;
}

float Player::GetSpeed()
{
    return speed;
}

vector<Block*> Player::GetBody()
{
    return body;
}

void Player::SetAlive(bool alive)
{
    isAlive = alive;
}

bool Player::GetAlive()
{
    return isAlive;
}

