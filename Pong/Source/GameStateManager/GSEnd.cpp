#include "GSEnd.h"

GSEnd::GSEnd()
{
}

GSEnd::~GSEnd()
{
}

void GSEnd::Exit()
{
}

void GSEnd::Pause()
{
}

void GSEnd::Resume()
{
}

void GSEnd::Init()
{	
	if (DATA->getMusic("gameover")->getStatus() != SoundSource::Playing)DATA->playMusic("gameover");

	GameButton* button;
	//menu Button
	button = new GameButton();
	button->Init("menu");
	button->setOrigin(button->getSize() / 2.f);
	button->setSize(sf::Vector2f(50, 50));
	button->setPosition(screenWidth / 2 + screenWidth / 12, screenHeight - screenHeight / 5);
	button->setOnClick([]() {
		DATA->playMusic("menu");
		GSM->ChangeState(StateTypes::MENU);
		ScoreManager::GetInstance()->writeFile();
		DATA->getMusic("gameover")->stop();
	});
	m_ListBtn.push_back(button);

	//replay Button
	button = new GameButton();
	button->Init("restart");
	button->setOrigin(button->getSize() / 2.f);
	button->setSize(sf::Vector2f(50, 50));
	button->setPosition(screenWidth / 2 - screenWidth / 12, screenHeight - screenHeight / 5);
	button->setOnClick([]() {
		GSM->ChangeState(StateTypes::PLAY);
		ScoreManager::GetInstance()->writeFile();
		DATA->getMusic("gameover")->stop();
		});
	m_ListBtn.push_back(button);

	//HighScore Button
	button = new GameButton();
	button->Init("prize");
	button->setOrigin(button->getSize() / 2.f);
	button->setSize(sf::Vector2f(50, 50));
	button->setPosition(screenWidth / 2, screenHeight - screenHeight / 5);
	button->setOnClick([]() {GSM->ChangeState(StateTypes::HIGHSCORE); });
	m_ListBtn.push_back(button);

	//Tile Game
	m_Title.setString("END GAME!");
	m_Title.setCharacterSize(60);
	m_Title.setFont(*DATA->getFont("ARCADE"));
	m_Title.setPosition(screenWidth / 2 - 120, screenHeight / 5);

	//Best Score
	m_bestScore.setCharacterSize(35);
	m_bestScore.setString("BEST SOCRE ...... "+std::to_string(ScoreManager::GetInstance()->getBestScore()));
	m_bestScore.setFont(*DATA->getFont("ARCADE"));
	m_bestScore.setPosition(screenWidth / 2 - 180, screenHeight / 2 - 50);

	//current Score
	m_currentScore.setString("YOUR SOCRE ...... " + std::to_string(ScoreManager::GetInstance()->getCurrentScore()));
	m_currentScore.setFont(*DATA->getFont("ARCADE"));
	m_currentScore.setPosition(screenWidth / 2 - 150, screenHeight / 2);
}

void GSEnd::Update(float deltaTime)
{
	MenuBackground::GetInstance()->Update(deltaTime);
	for (auto btn : m_ListBtn) {
		btn->Update(deltaTime);
	}
}

void GSEnd::Render(sf::RenderWindow* window)
{
	MenuBackground::GetInstance()->Draw(window);
	for (auto btn : m_ListBtn) {
		btn->Render(window);
	}
	window->draw(m_Title);
	window->draw(m_bestScore);
	window->draw(m_currentScore);
}
