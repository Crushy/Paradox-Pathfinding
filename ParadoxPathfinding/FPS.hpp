#ifndef FPS_HPP
#define FPS_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

class FPS
{
public:
	/// @brief Constructor with initialization.
	///
	FPS() : mFrame(0), mFps(0) {

		if (!font.loadFromFile("./Resources/AnkaCoder-b.ttf"))
		{
			std::cout << "Could not load font";
		}
		text.setFont(font);
		text.setString("FPS: 00");
		text.setCharacterSize(24); // in pixels, not points!
		text.setColor(sf::Color::Yellow);
	
	}

	/// @brief Update the frame count.
	/// 
	void update();

	/// @brief Get the current FPS count.
	/// @return FPS count.
	const unsigned int getFPS() const { return static_cast<int>(round(mFps / FPS_UPDATE_INTERVAL)); }
	void DrawFPSCount(sf::RenderWindow& window);
private:
	unsigned int mFrame;
	unsigned int mFps;
	sf::Clock mClock;

	sf::Font font;
	sf::Text text;

	const float FPS_UPDATE_INTERVAL = .1f; //In seconds
};

void FPS::update()
{
	if (mClock.getElapsedTime().asSeconds() >= FPS_UPDATE_INTERVAL)
	{
		mFps = mFrame;
		mFrame = 0;
		mClock.restart();
	}

	++mFrame;
}

void FPS::DrawFPSCount(sf::RenderWindow& window) {
	text.setString("FPS: " + std::to_string(this->getFPS()));

	text.setColor(sf::Color::Black);
	text.setPosition(0, 1);
	window.draw(text);

	text.setPosition(0, -1);
	window.draw(text);

	text.setPosition(1, 0);
	window.draw(text);

	text.setPosition(-1, 0);
	window.draw(text);

	text.setColor(sf::Color::White);
	text.setPosition(0, 0);
	window.draw(text);
}

#endif