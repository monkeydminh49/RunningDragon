#pragma once
#include <SFML/Graphics.hpp>
#include "../GameManager/WindowConnector.h"
#include "../GameManager/ResourceManager.h"
#include <iostream>
using namespace std;
using namespace sf;

class GameButton :public sf::RectangleShape{
public:
	GameButton();
	~GameButton();

	virtual void Init(std::string name);
	virtual void Update(float deltaTime);
	virtual void Render(sf::RenderWindow* window);

	virtual void HandleTouchEvent();
	bool isHandling();
	void addTexture(Texture* texture);
	void SetTextureIndex(int textureIndex);
	void setOnClick(void (*Func)());
protected:
	void (*m_btnClickFunc)();
	bool m_isHandling;
	vector<Texture*> m_ListTexture;
	int textureIndex;
	float m_delay;
};