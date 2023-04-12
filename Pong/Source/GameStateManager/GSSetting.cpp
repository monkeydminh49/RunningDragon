#include "GSSetting.h"

GSSetting::GSSetting()
{
}

GSSetting::~GSSetting()
{
}

void GSSetting::Exit()
{
}

void GSSetting::Pause()
{
}

void GSSetting::Resume()
{
}

void GSSetting::Init()
{
	//Choose map button
	Text* text = new Text();
	text->setString("Choose map:");
	text->setFont(*DATA->getFont("PressStart2P-vaV7"));
	text->setCharacterSize(16);
	text->setPosition(Vector2f(screenWidth / 2 - 160, screenHeight / 2 - 30));
	m_ListText.push_back(text);

	TextBox* btn;
	btn = new TextBox("Forest", Vector2f(50, 50));
	btn->SetFont(DATA->getFont("PressStart2P-vaV7"));
	btn->SetCharacterSize(18);
	btn->setPosition(Vector2f(screenWidth / 2 + 100, screenHeight / 2 - 23));
	btn->SetPosition(Vector2f(screenWidth / 2 + 50, screenHeight / 2 - 33));
	btn->setOutlineThickness(0.0f);
	btn->AddText("Desert");
	btn->AddText("Winter");
	btn->setOnClick([]() {
		MenuBackground::GetInstance()->NextMap();
		MenuBackground::GetInstance()->UpdateMap();
	});
	map = btn;
	m_ListBtn.push_back(btn);

	GameButton* button;
	//close button
	button = new GameButton();
	button->Init("close_2");
	button->setOrigin(button->getSize() / 2.f);
	button->setPosition(screenWidth - screenWidth / 20, screenHeight / 10);
	button->setOnClick([]() {GSM->ChangeState(StateTypes::MENU); });
	m_ListBtn.push_back(button);

	// Music on/off
	button = new GameButton();
	button->Init("music");
	button->addTexture(DATA->getTexture("btn/music_off"));
	button->setSize(sf::Vector2f(60, 60));
	if (DATA->getMusic("menu")->getStatus() != SoundSource::Playing) {
		button->setTexture(DATA->getTexture("btn/music_off"));
		button->SetTextureIndex(1);
	}
	button->setOrigin(button->getSize() / 2.f);
	button->setPosition(screenWidth/2 - 100, screenHeight/2 + 100);
	button->setOnClick([]() {
		if (DATA->getAllowMusic()) {
			DATA->setAllowMusic(false);
			DATA->getMusic("menu")->pause();
		}
		else {
			DATA->setAllowMusic(true);
			DATA->getMusic("menu")->play();
		}
	});
	m_ListBtn.push_back(button);

	// Sound on/off
	button = new GameButton();
	button->Init("sound");
	button->addTexture(DATA->getTexture("btn/sound_off"));
	button->setSize(sf::Vector2f(60, 60));
	if (!DATA->getAllowSound()) {
		button->setTexture(DATA->getTexture("btn/sound_off"));
		button->SetTextureIndex(1);
	}
	button->setOrigin(button->getSize() / 2.f);
	button->setPosition(screenWidth / 2 + 100, screenHeight / 2 + 100);
	button->setOnClick([]() {
		if (DATA->getAllowSound()) {
			DATA->setAllowSound(false);
		}
		else {
			DATA->setAllowSound(true);
		}});
	m_ListBtn.push_back(button);

	//Tile Game
	text = new Text();
	text->setString("SETTINGS");
	text->setFont(*DATA->getFont("ARCADECLASSIC"));
	text->setCharacterSize(50);
	text->setPosition(screenWidth/2-110,screenHeight/5);
	m_ListText.push_back(text);
}

void GSSetting::Update(float deltaTime)
{	
	MenuBackground::GetInstance()->Update(deltaTime);
	map->SetCurrentText(MenuBackground::GetInstance()->currentMapIndex);
	for (auto btn : m_ListBtn) {
		btn->Update(deltaTime);
	}
}

void GSSetting::Render(sf::RenderWindow* window)
{	
	MenuBackground::GetInstance()->Draw(window);
	for (auto text : m_ListText) {
		window->draw(*text);
	}
	for (auto btn : m_ListBtn) {
		btn->Render(window);
	}
}
