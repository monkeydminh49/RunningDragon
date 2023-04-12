#pragma once
#include "GameStateBase.h"
#include "../GameObjects/MenuBackground.h"
#include "../GameManager/ScoreManager.h"
class GSEnd : public GameStateBase {
public:
	GSEnd();
	virtual ~GSEnd();

	void Exit();
	void Pause();
	void Resume();

	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
private:
	std::list<GameButton*> m_ListBtn;
	sf::Text m_Title;
	sf::Text m_currentScore;
	sf::Text m_bestScore;
};