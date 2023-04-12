#include "GSMenu.h"

GSMenu::GSMenu()
{
}

GSMenu::~GSMenu()
{
}

void GSMenu::Exit()
{
}

void GSMenu::Pause()
{
}

void GSMenu::Resume()
{
}

void GSMenu::Init()
{
	printf("Menu\n");

	// Title
	title.setTexture(*DATA->getTexture("title"));

	// Background;
	MenuBackground::GetInstance();

	// Player
	Texture* texture = DATA->getTexture("dino");
	player = new Player(texture, Vector2i(20, 1), 0.1f);
	player->SetSpeed(300.0f);

	TextBox* button;
	// PlayButton
	button = new TextBox("PLAY", Vector2f(screenWidth / 2, screenHeight / 2 + screenHeight / 10));
	button->SetPosition(Vector2f(screenWidth / 2 - 35, screenHeight / 2 + screenHeight / 10 - 20));
	button->setOnClick([]() {
		DATA->getMusic("menu")->stop();
		GSM->ChangeState(StateTypes::PLAY);
	});
	m_ListBtn.push_back(button);

	//About Button
	button = new TextBox("ABOUT", Vector2f(screenWidth / 2, screenHeight / 2 + screenHeight / 10 + 60));
	button->SetPosition(Vector2f(screenWidth / 2 - 40, screenHeight / 2 + screenHeight / 10 + 60 - 20));
	button->setOnClick([]() {GSM->ChangeState(StateTypes::ABOUT); });
	m_ListBtn.push_back(button);

	//Exit Button
	button = new TextBox("EXIT", Vector2f(screenWidth / 2, screenHeight / 2 + screenHeight / 10 + 60*2));
	button->SetPosition(Vector2f(screenWidth / 2 - 30, screenHeight / 2 + screenHeight / 10+60*2 - 20));
	button->setOnClick([]() {WConnect->getWindow()->close(); });
	m_ListBtn.push_back(button);

	GameButton* btn;
	//turn on music
	btn = new GameButton();
	btn->Init("settings");
	btn->setOrigin(btn->getSize() / 2.f);
	btn->setPosition(screenWidth - screenWidth / 20, screenHeight / 10);
	btn->setOnClick([]() {
		GSM->ChangeState(StateTypes::SETTING);
	});
	m_ListBtn.push_back(btn);
	
	ScoreManager::GetInstance()->readFile();
}

void GSMenu::Update(float deltaTime)
{	
	MenuBackground::GetInstance()->Update(deltaTime);
	player->CheckCollision(MenuBackground::GetInstance()->GetTiles());
	player->Update(deltaTime);
	for (auto btn : m_ListBtn) {
		btn->Update(deltaTime);
	}
}

void GSMenu::Render(sf::RenderWindow* window)
{
	MenuBackground::GetInstance()->Draw(window);
	player->Draw(window);
	window->draw(title);
	for (auto btn : m_ListBtn) {
		btn->Render(window);
	}
}

Player* GSMenu::GetPlayer()
{
	return player;
}

GameMap* GSMenu::GetGameMap()
{
	return MenuBackground::GetInstance();
}
