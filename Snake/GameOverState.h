#pragma once
#include <assert.h>
#include "GameData.h"

namespace Snake
{
	struct GameData;

	struct GameOverData
	{
		sf::Font font;

		sf::Text gameOverText;
		sf::Text gameOverScoreText;
		sf::Text promptText;

		sf::RectangleShape background;

		MenuItem GameOverPlayNextGame;
		MenuItem GameOverExitMainMenu;

		sf::Text recordNameText;
		sf::Text recordScoreText;

		sf::RectangleShape recordBackground;

		sf::SoundBuffer gameOverSoundBuffer;
		sf::Sound gameOverSound;

		Menu menu;
	};

	void InitGameOver(GameOverData& data, GameData& gameData);
	void ShutdownGameOver(GameOverData& data, GameData& gameData);
	void ControlGameOver(GameOverData& data, GameData& gameData, const sf::Event& event);
	void UpdateGameOver(GameOverData& data, GameData& gameData, float DeltaTime);
	void DrawGameOver(GameOverData& data, GameData& gameData, sf::RenderWindow& window);
}