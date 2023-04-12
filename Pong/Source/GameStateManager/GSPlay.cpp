#include "GSPlay.h"
#include <iostream>
using namespace std;

GSPlay::GSPlay()
{
	m_currentScore = 0;
	m_currentTime = 0.f;
	level = 1;
	streak = 0;
	bonusTime = 0.0f;
}

GSPlay::~GSPlay()
{
}

void GSPlay::Exit()
{
}

void GSPlay::Pause()
{
	gameMap1->SetSpeed(0.f);
}

void GSPlay::Resume()
{
}

void GSPlay::Init()
{
	printf("Play game\n");
	
	DATA->getMusic("play")->setLoop(true);
	DATA->playMusic("play");

	GameButton* button;
	// Home button
	button = new GameButton();
	button->Init("Menu");
	button->setPosition(Vector2f(screenWidth - 60, 70 + button->getSize().y/2.0f));
	button->setOnClick([]() {
		DATA->getMusic("play")->stop();
		DATA->playMusic("menu");
		GSM->ChangeState(StateTypes::MENU); });
	m_ListBtn.push_back(button);

	// Init player
	player = new Player(DATA->getTexture("dino"), Vector2i(20, 1), 0.1f);

	// Init map
	gameMap1 = new GameMap();
	gameMap1->Init();
	gameMap1->ChangeMap(MenuBackground::GetInstance()->currentMapIndex);
	gameMap1->UpdateMap();
	cout << "Level:    " << level << "     Speed:    " << gameMap1->GetSpeed() << endl;

	m_Score.setFont(*DATA->getFont("ARCADE"));
	m_Score.setString("0");
	m_Score.setCharacterSize(50);
	m_Score.setFillColor(sf::Color::White);
	m_Score.setPosition(60, 60);

	// Streak
	streakText.setFont(*DATA->getFont("ARCADE"));
	streakText.setString("Streaks: " + to_string(streak));
	streakText.setCharacterSize(25);
	streakText.setFillColor(sf::Color::White);
	streakText.setPosition(60, 120);

	// Bonus
	bonusPoint.setFont(*DATA->getFont("ARCADE"));
	bonusPoint.setString("+" + to_string(0));
	bonusPoint.setCharacterSize(40);
	bonusPoint.setFillColor(sf::Color::White);
	bonusPoint.setPosition(180, screenHeight / 9);
}

void GSPlay::Update(float deltaTime)
{	
	bonusTime -= deltaTime;

	bool tmp = player->GetAlive();
	if (player->GetPosition().x <= -playerSize  || player->GetPosition().y > screenHeight) {
		if (m_currentTime >= (level - 1) * 10.0f) {
			m_currentTime = 0;
			level++;
		}
		else {
			player->SetAlive(false);
			if (m_currentTime >= 0.4f) {
				Pause();
			}
			if (tmp != player->GetAlive()) {
				DATA->playSound("lost_life");
				DATA->getMusic("play")->stop();
			}
			if (m_currentTime >= 3.0f) {
				ScoreManager::GetInstance()->setCurrentScore(m_currentScore);
				ScoreManager::GetInstance()->UpdateHighScore();
				GSM->ChangeState(StateTypes::END);
			}
		}
	}
	
	m_currentTime += deltaTime;
	if (m_currentTime >= level*10.0f) {
		level++;
		if (gameMap1->GetSpeed() < 400) {
			gameMap1->SetSpeed(gameMap1->GetSpeed() + 50);
			player->SetSpeed(player->GetSpeed() + 50);
		}
		else {
			gameMap1->SetSpeed(gameMap1->GetSpeed() + 50);
			player->SetSpeed(player->GetSpeed() + 50);
		}
		cout << "Level:    " << level << "     Speed:    " << gameMap1->GetSpeed() << endl;
	}
	for (auto obstacle : gameMap1->GetObstacles()){
		if ((obstacle->GetCoinPosition().y >= (int)player->GetPosition().y - 16 &&
			obstacle->GetCoinPosition().y <= (int)player->GetPosition().y + 16)
			&& obstacle->GetCoinPosition().x <= player->GetPosition().x + playerSize && !obstacle->GetPassingState()){
			obstacle->SetPassingState(true);
			DATA->getSound("coin")->setVolume(40);
			DATA->playSound("coin");
			streak++;
			int bonus = 10 * level * (streak + 1);
			bonusPoint.setString("+" + to_string(bonus));
			bonusPoint.setFillColor(Color(255, 255, 255, 255));
			bonusTime = 2.0f;
			m_currentScore += 10*level*(streak+1);
			m_Score.setString(std::to_string(m_currentScore));
		}
		else if (obstacle->GetCoinPosition().x < player->GetPosition().x - playerSize && obstacle->GetPassingState() == 0) {
			streak = 0;
			obstacle->SetPassingState(2);
		}
		if (obstacle->CheckCollision(*player)) {}
	}

	bonusPoint.setFillColor(Color(255, 255, 255, std::max(0.f, bonusTime*255/2.0f)));
	streakText.setString("Streaks: " + to_string(streak));

	if (player->CheckCollision(gameMap1->GetTiles())) {}
	player->Update(deltaTime);
	gameMap1->Update(deltaTime);
	for (auto btn : m_ListBtn) btn->Update(deltaTime);
	
}

void GSPlay::Render(sf::RenderWindow* window)
{
	window->draw(gameMap1->GetBackground());
	player->Draw(window);
	gameMap1->Draw(window);
	for (auto btn : m_ListBtn) window->draw(*btn);
	window->draw(m_Score);
	if (streak > 1) window->draw(streakText);
	window->draw(bonusPoint);
}

Player* GSPlay::GetPlayer()
{
	return player;
}

GameMap* GSPlay::GetGameMap()
{
	return gameMap1;
}
