#include "Application.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;
Application::Application()
{
}

Application::~Application()
{
    if (window != nullptr) delete window;
}


void Application::init()
{   
	window = new RenderWindow(VideoMode(screenWidth, screenHeight), titleGame, Style::Close);
    window->setFramerateLimit(120);
    window->setVerticalSyncEnabled(false);

    GameStateMachine::GetInstance()->ChangeState(StateTypes::INTRO);
    WConnect->setWindow(window);
    srand(time(NULL));
}


void Application::update(float deltaTime)
{
    if (GameStateMachine::GetInstance()->NeedToChangeState()) {
        GameStateMachine::GetInstance()->PerformStateChange();
    }
    GameStateMachine::GetInstance()->currentState()->Update(deltaTime);
}

void Application::render()
{   
    window->clear(Color::Black);
    GameStateMachine::GetInstance()->currentState()->Render(window);
    window->display();
}

void Application::run()
{
    init();

    Event event;

    // Clock
    Clock clock;
    double deltaTime = 0.0f;

    while (window->isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        if (deltaTime > 1.0f / 20) deltaTime = 1.0f / 20;

        while (window->pollEvent(event))
        {
            if (event.type == Event::Closed)
                window->close();

            if (event.type == Event::KeyPressed)
            {
                Player* player = GameStateMachine::GetInstance()->currentState()->GetPlayer();
                GameMap* gameMap = GameStateMachine::GetInstance()->currentState()->GetGameMap();

                if (Keyboard::Key::W == event.key.code && player->Movable())
                {   
                    if (player->isAddable(gameMap->GetTiles())) {
                        DATA->getSound("jump")->setVolume(60);
						DATA->playSound("jump");
                        player->AddBlock();
                    }
                }
                if (Keyboard::Key::S == event.key.code && player->Movable())
                {
                    player->RemoveBlock();
                }
            }
        }
        update(deltaTime);
        render();
    }
}


