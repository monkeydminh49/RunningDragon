#include "GSHighScore.h"

GSHighScore::GSHighScore()
{
}

GSHighScore::~GSHighScore()
{
	for (auto it : m_ListBtn) {
		if (it != nullptr) {
			delete it;
		}
	}
	for (auto it : m_ListScore) {
		if (it != nullptr) {
			delete it;
		}
	}
}

void GSHighScore::Exit()
{
}

void GSHighScore::Pause()
{
}

void GSHighScore::Resume()
{
}

void GSHighScore::Init()
{
	GameButton* button;
	//close Button
	button = new GameButton();
	button->Init("close_2");
	button->setOrigin(button->getSize() / 2.f);
	button->setPosition(screenWidth - screenWidth / 20, screenHeight / 10);
	button->setOnClick([]() {GSM->ChangeState(StateTypes::END); });
	m_ListBtn.push_back(button);

	//Tile Game
	m_Title.setString("HIGH SCORE");
	m_Title.setCharacterSize(60);
	m_Title.setFont(*DATA->getFont("ARCADE"));
	m_Title.setPosition(screenWidth / 2 - 140, screenHeight / 5);

	vector <pair< string, int >> order = { {"1st", 40}, {"2nd", 35}, {"3rd", 30}, {"4th", 30},{ "5th", 30} };
	//ListScore
	for (int i = 0; i < ScoreManager::GetInstance()->getNum(); i++) {
		sf::Text* t = new sf::Text();
		t->setString(order[i].first);
		t->setCharacterSize(order[i].second);
		t->setFont(*DATA->getFont("ARCADE"));
		t->setPosition(screenWidth / 2 - 120, screenHeight / 2 - 70 + 40*i);
		m_ListScore.push_back(t);
		
		t = new sf::Text();
		t->setString(+" ....... ");
		t->setCharacterSize(30);
		t->setFont(*DATA->getFont("ARCADE"));
		t->setPosition(screenWidth / 2 - 50, screenHeight / 2 - 70 + 40*i);
		m_ListScore.push_back(t);
		
		t = new sf::Text();
		t->setString(std::to_string(ScoreManager::GetInstance()->getHighScore()[i]));
		t->setCharacterSize(order[i].second);
		t->setFont(*DATA->getFont("ARCADE"));
		t->setPosition(screenWidth / 2 + 70, screenHeight / 2 - 70 + 40*i);
		m_ListScore.push_back(t);
	}
}

void GSHighScore::Update(float deltaTime)
{	
	MenuBackground::GetInstance()->Update(deltaTime);
	for (auto btn : m_ListBtn) {
		btn->Update(deltaTime);
	}
	
}

void GSHighScore::Render(sf::RenderWindow* window)
{
	MenuBackground::GetInstance()->Draw(window);
	for (auto btn : m_ListBtn) {
		btn->Render(window);
	}
	for (auto it : m_ListScore) {
		window->draw(*it);
	}
	window->draw(m_Title);
}
