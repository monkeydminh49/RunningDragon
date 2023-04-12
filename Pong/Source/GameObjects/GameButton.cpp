#include "GameButton.h"

GameButton::GameButton()
{
	m_isHandling = false;
	textureIndex = 0;
	m_delay = 0;
}

GameButton::~GameButton()
{
}

void GameButton::Init(std::string name)
{
	this->setTexture(DATA->getTexture("btn/" + name));
	m_ListTexture.push_back(DATA->getTexture("btn/" + name));
	this->setSize(Vector2f(35.f, 35.f));
	this->setOrigin(this->getSize() / 2.0f);
}

void GameButton::Update(float deltaTime)
{
	m_delay += deltaTime;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_delay > 0.2f) {
		HandleTouchEvent();
		m_delay = 0;
	}
	if (isHandling()) {
		this->setScale(1.2f, 1.2f);
	}
	else {
		this->setScale(1.f, 1.f);
	}
}

void GameButton::Render(sf::RenderWindow* window)
{
	window->draw(*this);
}


void GameButton::HandleTouchEvent()
{
	if (isHandling())
	{
		if (m_ListTexture.size() > 1) {
			textureIndex++;
			textureIndex %= m_ListTexture.size();
			this->setTexture(m_ListTexture[textureIndex]);
		}
		m_btnClickFunc();
	}
}

bool GameButton::isHandling()
{
	if (this->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*WConnect->getWindow()))) {
		return true;
	}
	return false;
}

void GameButton::addTexture(Texture* texture)
{
	m_ListTexture.push_back(texture);
}

void GameButton::SetTextureIndex(int textureIndex)
{
	this->textureIndex = textureIndex;
}

void GameButton::setOnClick(void(*Func)())
{

	m_btnClickFunc = Func;
}
