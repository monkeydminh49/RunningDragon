#pragma once
#include "GameStateBase.h"
#include "../GameObjects/MenuBackground.h"
#include "../GameObjects/TextBox.h"
#include <windows.h>
#include <shellapi.h>
class GSAbout : public GameStateBase {
public:
	GSAbout();
	virtual ~GSAbout();

	void Exit();
	void Pause();
	void Resume();

	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
private:
	TextBox* facebook;
	Sprite* about;
	std::list<GameButton*> m_ListBtn;
	sf::Text m_Title;
};