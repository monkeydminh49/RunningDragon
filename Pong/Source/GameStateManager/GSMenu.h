#pragma once
#include "GameStateBase.h"
#include "../GameObjects/MenuBackground.h"
#include "../GameObjects/TextBox.h"
#include "../GameManager/ScoreManager.h"
class GSMenu : public GameStateBase {
public:
	GSMenu();
	virtual ~GSMenu();

	void Exit();
	void Pause();
	void Resume();

	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	
	Player* GetPlayer();
	GameMap* GetGameMap();
private:
	Sprite title;
	Player* player;
	std::list<GameButton*> m_ListBtn;
};