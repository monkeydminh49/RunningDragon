#include "GSAbout.h"

GSAbout::GSAbout()
{
}

GSAbout::~GSAbout()
{
}

void GSAbout::Exit()
{
}

void GSAbout::Pause()
{
}

void GSAbout::Resume()
{
}

void GSAbout::Init()
{

	// About
	about = new Sprite();
	about->setTexture(*DATA->getTexture("about"));
	about->setPosition(Vector2f(-175, -25));
	
	// Facebook
	facebook = new TextBox("MinhDunk", Vector2f(screenWidth - 250, screenHeight / 2 + screenHeight / 10 + 60 * 2));
	facebook->setOutlineThickness(0.0f);
	facebook->SetCharacterSize(15);
	facebook->SetPosition(Vector2f(screenWidth - 315, screenHeight / 2 + screenHeight / 10 + 60 * 2 - 13));
	facebook->SetFont(DATA->getFont("PressStart2P-vaV7"));
	facebook->setOnClick([](){ 
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			ShellExecute(0, 0, L"https://www.facebook.com/minhdunk", 0, 0, SW_SHOW);
		}
	});

	GameButton* button;
	//close Button
	button = new GameButton();
	button->Init("close_2");
	button->setOrigin(button->getSize() / 2.f);
	button->setSize(sf::Vector2f(45, 45));
	button->setPosition(screenWidth - screenWidth / 15, screenHeight / 8);
	button->setOnClick([]() {GSM->ChangeState(StateTypes::MENU); });
	m_ListBtn.push_back(button);

	//Tile Game
	m_Title.setString("ABOUT");
	m_Title.setFont(*DATA->getFont("ARCADECLASSIC"));
	m_Title.setCharacterSize(50);
	m_Title.setPosition(screenWidth / 2 - 80, screenHeight / 5 - 25);
}

void GSAbout::Update(float deltaTime)
{
	MenuBackground::GetInstance()->Update(deltaTime);
	for (auto btn : m_ListBtn) {
		btn->Update(deltaTime);
	}
	facebook->Update(deltaTime);
}

void GSAbout::Render(sf::RenderWindow* window)
{
	MenuBackground::GetInstance()->Draw(window);
	for (auto btn : m_ListBtn) {
		btn->Render(window);
	}
	window->draw(m_Title);
	window->draw(*about);
	facebook->Render(window);
}
