#pragma once
#include "GameStateBase.h"
#include "../GameObjects/MenuBackground.h"
#include "../GameObjects/TextBox.h"

class GSSetting : public GameStateBase {
public:
	GSSetting();
	virtual ~GSSetting();

	void Exit();
	void Pause();
	void Resume();

	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
private:
	sf::Sprite m_Background;
	vector<Text*> m_ListText;
	std::list<GameButton*> m_ListBtn;
	TextBox* map;
};