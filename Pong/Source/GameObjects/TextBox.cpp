#include "TextBox.h"
#include <iostream>
using namespace std;
TextBox::TextBox()
{

	text = new Text();
}

TextBox::TextBox(string input, Vector2f position)
{
	time = 0.5f;
	m_currentTextIndex = 0;
	this->setSize(Vector2f(150.f, 40.f));
	this->setOrigin(this->getSize() / 2.0f);
	this->setFillColor(Color(255, 255, 255, 0));
	this->setOutlineColor(Color::White);
	this->setOutlineThickness(1.0f);
	this->setPosition(position);

	text = new Text();
	text->setString(input);
	text->setCharacterSize(30);
	text->setStyle(sf::Text::Regular);
	text->setFillColor(Color::Red);
	text->setOrigin(text->getLocalBounds().width / 2.0f, text->getLocalBounds().height / 2.0f);
	text->setPosition(200, 200);

	font = DATA->getFont("ARCADECLASSIC");
	m_ListText.push_back(input);
}

TextBox::~TextBox()
{
}

void TextBox::Init(string input, Vector2f position, Vector2f size)
{
	
	//this->setSize(size);
	//this->setOrigin(this->getSize() / 2.0f);
	//this->setPosition(position);
	//this->setFillColor(Color(255, 255, 255, 0));
	//this->setOutlineColor(Color::White);
	//this->setOutlineThickness(1.0f);
	//cout << this->getPosition().x << " " << this->getPosition().y << endl;

	//text = new Text();
	//text->setString(input);
	//text->setCharacterSize(30);
	//text->setStyle(sf::Text::Regular);
	//text->setFillColor(Color::Red);
	//text->setOrigin(text->getLocalBounds().width / 2.0f, text->getLocalBounds().height / 2.0f);
	//text->setPosition(position.x - text->getLocalBounds().width, position.y - text->getLocalBounds().height);
	//
}


void TextBox::Render(RenderWindow* window)
{
	text->setFont(*font);
	window->draw(*text);
	window->draw(*this);
}

void TextBox::Update(float deltaTime)
{
	text->setString(m_ListText[m_currentTextIndex]);

	m_delay += deltaTime;
	HandleTouchEvent();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isHandling() && m_delay > 0.2f) {
		NextText();
		m_btnClickFunc();
		m_delay = 0;
	}
	if (isHandling()) {
		text->setFillColor(Color(0, 0, 0, 255));
		text->setOutlineColor(Color::White);
		text->setOutlineThickness(2.0f);
	}
	else {
		text->setFillColor(Color::White);
		this->setFillColor(Color(255, 255, 255, 0));
		text->setOutlineThickness(0.0f);
	}
}

void TextBox::SetPosition(Vector2f position)
{
	text->setPosition(position.x, position.y);
}

void TextBox::HandleTouchEvent()
{
	m_isHandling = false;
	if (this->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*WConnect->getWindow())))
	{
		m_isHandling = true;
	}
}

void TextBox::SetCharacterSize(float size)
{
	text->setCharacterSize(size);
}

void TextBox::SetFont(Font* font)
{
	this->font = font;
}

void TextBox::AddText(string input)
{
	m_ListText.push_back(input);
}

void TextBox::NextText()
{
	m_currentTextIndex++;
	m_currentTextIndex %= m_ListText.size();
}

void TextBox::SetCurrentText(int index)
{
	m_currentTextIndex = index;
}
