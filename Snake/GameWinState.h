#pragma once
#include <assert.h>
#include "GameData.h"

namespace Snake
{
	struct GameData;

	struct GameWinData
	{
		sf::Font font;

		sf::Text gameWinText;
		sf::Text gameWinScoreText;
		sf::Text promptText;

		sf::RectangleShape background;

		MenuItem GameWinPlayNextGame;
		MenuItem GameWinExitMainMenu;

		sf::Text recordNameText;
		sf::Text recordScoreText;
		sf::RectangleShape recordBackground;

		sf::SoundBuffer gameWinSoundBuffer;
		sf::Sound gameWinSound;

		Menu menu;
	};

	void InitGameWin(GameWinData& data, GameData& gameData);
	void ShutdownGameWin(GameWinData& data, GameData& gameData);
	void ControlGameWin(GameWinData& data, GameData& gameData, const sf::Event& event);
	void UpdateGameWin(GameWinData& data, GameData& gameData, float DeltaTime);
	void DrawGameWin(GameWinData& data, GameData& gameData, sf::RenderWindow& window);
}