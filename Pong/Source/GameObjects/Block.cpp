#include "Block.h"

Block::Block()
{
}

Block::Block(Vector2f position)
{   
    speed = mapSpeed;
    body.setSize(Vector2f(size, size));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(position.x, position.y);
    isMovable = true;
}

Block::Block(Texture* texture, float speed, Vector2f position)
    :speed(speed)
{   
    speed = mapSpeed;
    isConnected = true;
    isGrounded = false;
    body.setSize(Vector2f(size, size));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(position.x, position.y);
    body.setOutlineColor(Color::Black);
    body.setOutlineThickness(0.0f);
    body.setTexture(texture);
    isMovable = true;
}

Block::~Block()
{
}

float Block::size = 48.0f;
      
void Block::Update(float deltaTime)
{
    velocity.x *= slowDownRate;

    if (Keyboard::isKeyPressed(Keyboard::D) && isConnected && isMovable) {
        velocity.x += speed;
    }

    if (Keyboard::isKeyPressed(Keyboard::A) && isConnected && isMovable) {
        velocity.x -= speed;
    }

    velocity.y += 981.0f * deltaTime;
    body.move(velocity * deltaTime);

}

void Block::Draw(RenderWindow* window)
{
    window->draw(body);
}

void Block::Move(float dx, float dy)
{
    body.move(dx, dy);
}

void Block::OnCollision(Vector2f direction)
{
    if (direction.x < 0.0f) {
        // Collision on the left
        velocity.x = 0.0f;
    }
    else if (direction.x > 0.0f) {
        // Collision on the right
        velocity.x = 0.0f;
    }
    else if (direction.y < 0.0f) {
        // Collision on the bottom
        velocity.y = 0.0f;
         isGrounded = true;
    }
    else if (direction.y > 0.0f) {
        // Collision on the top
        velocity.y = 0.0f;
    }
}


void Block::SetPosition(float dx, float dy)
{
    body.setPosition(dx, dy);
}

void Block::SetMovable(bool movable)
{
    isMovable = movable;
}

void Block::SetSpeed(float speed)
{
    this->speed = speed;
}

float Block::GetSpeed()
{
    return speed;
}

Vector2f Block::GetPosition()
{
    return body.getPosition();
}

Collider Block::GetCollider()
{
    return Collider(body);
}

float Block::GetSize()
{
    return body.getSize().x;
}



