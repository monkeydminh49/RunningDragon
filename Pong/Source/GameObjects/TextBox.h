#pragma once
#include "GameButton.h"
#include <windows.h>
#include <shellapi.h>

using namespace sf;
using namespace std;

class TextBox : public GameButton
{
public:
	TextBox();
	TextBox(string input, Vector2f position);

	~TextBox();
	void Init(string input, Vector2f position, Vector2f size);
	void Render(RenderWindow* window);
	void Update(float deltaTime);
	void SetPosition(Vector2f position);
	void HandleTouchEvent();
	void SetCharacterSize(float size);
	void SetFont(Font* font);
	void AddText(string input);
	void NextText();
	void SetCurrentText(int index);
private:
	Text* text;
	vector<string> m_ListText;
	float time;
	Font* font;
	int m_currentTextIndex;
};

