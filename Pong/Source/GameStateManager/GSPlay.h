#pragma once
#include "GameStateBase.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/GameMap.h"
#include "../GameObjects/MenuBackground.h"
#include "../GameManager/ScoreManager.h"

class GSPlay : public GameStateBase {
public:
	GSPlay();
	virtual ~GSPlay();

	void Exit();
	void Pause();
	void Resume();

	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);

	Player* GetPlayer();
	GameMap* GetGameMap();
private:
	Player * player;
	GameMap* gameMap1;
	vector <GameButton*> m_ListBtn;
	int m_currentScore;
	float m_currentTime;
	sf::Text m_Score;
	float level;
	int streak;
	Text streakText;
	Text bonusPoint;
	float bonusTime;
};