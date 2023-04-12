#pragma once
#include "SFML/Graphics.hpp"

class Animation :public sf::Sprite {
public:
	Animation();
	Animation(sf::Texture* texture, sf::Vector2i frameNum, float frameTime);
	void CalculateRectSize();
	void CalculateRectUV();
	void ApplyRect();
	virtual void Update(float detaTime, int start, int end);
	virtual void Reset();

	void setModeEndFrame(bool stop);
	void setFrameTime(float frameTime);

	sf::Vector2i getFrameNum() { return m_frameNum; }
	sf::Vector2i getCurrentFrame() { return m_currentFrame; }
	sf::IntRect m_rect;

protected:
	sf::Vector2i m_rectUV;
	sf::Vector2i m_frameNum;
	sf::Vector2i m_currentFrame;

	float m_frameTime;
	float m_currentTime;

	sf::Vector2i m_rectSize;

	bool m_modeStopAtEndFrame;

};