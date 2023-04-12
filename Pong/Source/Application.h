#pragma once
#include <SFML/Graphics.hpp>
#include "GameStateManager/GameStateMachine.h"
#include "GameStateManager/GameStateBase.h"
#include "GameConfig.h"
#include "Collider.h"
#include "GameObjects/Animation.h"
#include "GameObjects/Player.h"	
#include "GameObjects/GameMap.h"	
#include "GameObjects/GameTile.h"	
#include "GameObjects/TextBox.h"
#include <vector>
using namespace sf;

class Application {
private:
	RenderWindow* window;
	TextBox* play;
public:
	Application();
	~Application();
	void init();
	void update(float deltaTime);
	void render();
	void run();
};


