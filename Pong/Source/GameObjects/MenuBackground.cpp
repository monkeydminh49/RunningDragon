#include "MenuBackground.h"

MenuBackground::MenuBackground()
{
	Init();
}

void MenuBackground::Init()
{
	currentMapIndex = 0;
	backgroundMap = vector<vector<int>>{menu_forest};
	backgroundMaps.push_back(backgroundMap);
	backgroundMap = vector<vector<int>>{menu_desert};
	backgroundMaps.push_back(backgroundMap);
	backgroundMap = vector<vector<int>>{menu_winter};
	backgroundMaps.push_back(backgroundMap);
	
	// Background
	Texture* backgroundTexture = DATA->getTexture("night_sky");
	background.setTexture(*backgroundTexture);
	background.setScale(0.62f, 0.62f);

	// Music
	DATA->getMusic("menu")->setLoop(true);
	DATA->getMusic("menu")->play();

	UpdateMap();
}

void MenuBackground::Update(float deltaTime)
{
	for (auto tile : tiles) {
		tile->Move(-50.f * deltaTime, 0.0f);
		if (tile->GetPosition().x <= -24) tile->SetPosition(Vector2f(tile->GetPosition().x + 2 * screenWidth, tile->GetPosition().y));
	}
}

void MenuBackground::Draw(RenderWindow* window)
{	
	window->draw(background);
	for (int i = 0; i < tiles.size(); ++i) {
		tiles[i]->Draw(window);
	}
}

void MenuBackground::NextMap()
{
	currentMapIndex++;
	currentMapIndex %= backgroundMaps.size();
}

void MenuBackground::UpdateMap()
{
	tiles.clear();
	Vector2f position;
	bool passible;
	Texture* texture;
	GameTile* tile;
	string path = paths[currentMapIndex];
	string texturePath;

	for (int i = 0; i < gridHeight; i++) {
		for (int j = 0; j < gridWidth * 2; j++) {
			if (backgroundMaps[currentMapIndex][i][j] == 0) {
				continue;
			}
			texturePath = path + to_string(backgroundMaps[currentMapIndex][i][j]);
			texture = DATA->getTexture(texturePath);;

			passible = true;
			if (i >= 17) passible = false;
			tile = new GameTile(texture, Vector2f(0.0f, 0.0f), passible, true);
			position = Vector2f(tileSize / 2.0f, tileSize / 2.0f);
			position.x += j * tileSize;
			position.y += i * tileSize;
			tile->SetPosition(position);

			tiles.push_back(tile);
		}
	}
}

