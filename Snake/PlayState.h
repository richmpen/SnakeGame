#pragma once
#include "GameData.h"
#include <assert.h>
#include "Snake.h"
#include "Apple.h"
#include "Level.h"


namespace Snake
{
	struct GameData;

	struct PlayStateData
	{
		SnakeData snake;
		AppleData apple;
		LevelData level;
		
		sf::Font font;
		sf::Text scoreText;
		sf::Text infoText;
		sf::Text extraScoreText;

		sf::RectangleShape shapeScoreBackground;
		sf::RectangleShape shapeInfoBackground;

		sf::Texture pauseTexture;
		sf::Texture playTexture;
		sf::Sprite pauseSprite;

		sf::SoundBuffer soundGameStartBuffer;

		sf::Sound soundGameStart;
		sf::Music backgroundMusic;

		sf::Text textTimerPerPlay;
		float timePerPlay = TIME_PER_PLAY;
		bool timerStart = false;
		
		sf::RectangleShape mouseCursor;
	};

	void InitPlayState(PlayStateData& data, GameData& gameData);
	void ShutdownPlayState(PlayStateData& data, GameData& gameData);
	void ControlPlayState(PlayStateData& data, GameData& gameData, const sf::Event& event);
	void UpdatePlayState(PlayStateData& data, GameData& gameData, float DeltaTime);
	void DrawPlayState(PlayStateData& data, GameData& gameData, sf::RenderWindow& window);
}