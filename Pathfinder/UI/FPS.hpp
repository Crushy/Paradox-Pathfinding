#pragma once
#pragma warning( disable : 26440 26432 26455)
#include <SFML/Graphics.hpp>  // Old school header, need to ignore a bunch of warnings
#pragma warning( default : 26440 26432 26455)
#include <iostream>

class FPS
{
public:
	FPS() noexcept : mFrame(0), mFps(0) {}

	void Initialize() {
		try {
			if (!font.loadFromFile("./Resources/AnkaCoder-b.ttf"))
			{
				std::cout << "Could not load font";
			}
			text.setFont(font);
			text.setString("FPS: 00");
			text.setCharacterSize(24); // in pixels, not points!
			text.setFillColor(sf::Color::Yellow);
		}
		catch (const std::exception&) {
			std::cout << "FPS Counter Error: Failed to construct FPS counter" << std::endl;
		}
	}

	// Update the frame count.
	void Update()
	{
		if (mClock.getElapsedTime().asSeconds() >= FPS_UPDATE_INTERVAL)
		{
			mFps = mFrame;
			mFrame = 0;
			mClock.restart();
		}

		++mFrame;
	}

	const unsigned int GetFramesPerSecond() const noexcept { return static_cast<int>(round(mFps / FPS_UPDATE_INTERVAL)); }
	
	void DrawFPSCount(sf::RenderWindow* window) {
		if (window == nullptr) {
			std::cout << "FPS Counter Error: Invalid Window";
		};

		text.setString("FPS: " + std::to_string(this->GetFramesPerSecond()));

		// Hack to draw an outline around the text
		text.setFillColor(sf::Color::Black);
		text.setPosition(0, 1);
		window->draw(text);

		text.setPosition(0, -1);
		window->draw(text);

		text.setPosition(1, 0);
		window->draw(text);

		text.setPosition(-1, 0);
		window->draw(text);
		// /Hack to draw a black outline around the text

		text.setFillColor(sf::Color::White);
		text.setPosition(0, 0);
		window->draw(text);
	}
private:
	unsigned int mFrame;
	unsigned int mFps;
	sf::Clock mClock;

	sf::Font font;
	sf::Text text;

	const float FPS_UPDATE_INTERVAL = .1f; //In seconds
};
