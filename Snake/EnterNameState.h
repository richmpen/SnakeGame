#pragma once
#include <assert.h>
#include "GameData.h"

namespace Snake
{
	struct GameData;

	struct EnterNameData
	{
		sf::Font font;
		sf::Text enterNameText;
		sf::Text enterScoreText;

		sf::RectangleShape background;

		MenuItem enterNameYes;
		MenuItem enterNameNo;

		bool enterNameVisible = false;
		sf::Vector2f menuPosition;

		std::string recordName;
		sf::Text recordNameText;
		sf::Text alertLineSize;

		sf::RectangleShape recordNameBackground;

		sf::SoundBuffer openBuffer;
		sf::Sound openSound;
		sf::SoundBuffer keyTapBuffer;
		sf::Sound keyTapSound;

		const std::size_t maxLengthLine = 8;
		const std::size_t minLengthLine = 2;

		Menu menu;
	};

	void InitEnterName(EnterNameData& data, GameData& gameData);
	void ShutdownEnterName(EnterNameData& data, GameData& gameData);
	void ControlEnterName(EnterNameData& data, GameData& gameData, const sf::Event& event);
	void UpdateEnterName(EnterNameData& data, GameData& gameData, float DeltaTime);
	void DrawEnterName(EnterNameData& data, GameData& gameData, sf::RenderWindow& window);
}