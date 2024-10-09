#include "PlayState.h"


namespace Snake
{
	void InitPlayState(PlayStateData& data, GameData& gameData)
	{
		assert(data.backgroundMusic.openFromFile(ASSET_FOLDER + "Audio/Background_Music.wav"));
		assert(data.font.loadFromFile(ASSET_FOLDER + "Roboto-Black.ttf"));
		assert(data.pauseTexture.loadFromFile(ASSET_FOLDER + "pauseTexture.png"));
		assert(data.playTexture.loadFromFile(ASSET_FOLDER + "playTexture.png"));
		assert(data.soundGameStartBuffer.loadFromFile(ASSET_FOLDER + "Audio/gameStart.wav"));

		InitSnake(data.snake);
		InitApple(data.apple, data, gameData);
		InitLevel(data.level);

		data.soundGameStart.setBuffer(data.soundGameStartBuffer);
		data.soundGameStart.setVolume(50.f);
		SoundPlay(data.soundGameStart, gameData);

		data.backgroundMusic.setVolume(50);
		data.backgroundMusic.setLoop(true);
		MusicPlay(data.backgroundMusic, gameData);

		TextInit(data.scoreText, "", 25, sf::Color::White, data.font);
		data.scoreText.setPosition(sf::Vector2f(WINDOW_WIDTH - 220, 5));

		TextInit(data.infoText, "Mod: 0 | need : " + std::to_string(0), 25, sf::Color::White, data.font);
		data.infoText.setPosition(sf::Vector2f(50, 5));

		TextInit(data.extraScoreText, "", 16, sf::Color::White, data.font);
		data.extraScoreText.setPosition(sf::Vector2f(data.scoreText.getPosition().x + 130, data.scoreText.getPosition().y));

		data.shapeScoreBackground.setPosition(sf::Vector2f(data.scoreText.getPosition().x - 5, data.scoreText.getPosition().y));
		data.shapeScoreBackground.setSize(sf::Vector2f(167, 30));
		data.shapeScoreBackground.setOrigin(1.f, 0.5f);
		data.shapeScoreBackground.setFillColor(sf::Color(0,0,0,127)); 

		data.shapeInfoBackground.setPosition(sf::Vector2f(45,5));
		data.shapeInfoBackground.setSize(sf::Vector2f(335, 30));
		data.shapeInfoBackground.setOrigin(1.f, 0.5f);
		data.shapeInfoBackground.setFillColor(sf::Color(0, 0, 0, 127));

		data.pauseSprite.setTexture(data.pauseTexture);
		SetSpriteSize(data.pauseSprite, 36.f, 36.f);
		data.pauseSprite.setOrigin(0.5f, 0.5f);
		data.pauseSprite.setPosition(sf::Vector2f(data.scoreText.getPosition().x + 160, data.scoreText.getPosition().y - 3.5f));

		TextInit(data.textTimerPerPlay, "", 200, sf::Color::White, data.font);
		data.textTimerPerPlay.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

		data.mouseCursor.setSize(sf::Vector2f(5,5));
		data.mouseCursor.setOrigin(data.mouseCursor.getGlobalBounds().width/2, data.mouseCursor.getGlobalBounds().height / 2);
		data.mouseCursor.setFillColor(sf::Color(0, 0, 0, 0));

		gameData.snakeScore = 0;
		data.timerStart = true;
		GameItemRespawn(data.apple.appleSprite, data, data.apple.appleX, data.apple.appleY);
	}

	void ShutdownPlayState(PlayStateData& data, GameData& game){}

	void ControlPlayState(PlayStateData& data, GameData& gameData, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::P || event.key.code == sf::Keyboard::Escape)
			{
				if (!data.timerStart)
				{
					SoundPlay(gameData.selectSound, gameData);
					PushGameState(gameData, StateType::Pause, false);
					data.pauseSprite.setTexture(data.playTexture);

				}
			}
		}
		if (data.mouseCursor.getGlobalBounds().intersects(data.pauseSprite.getGlobalBounds()))
		{
			data.pauseSprite.setColor(sf::Color(255,255,255,150));
			if (!data.timerStart)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{

					PushGameState(gameData, StateType::Pause, false);
					data.pauseSprite.setTexture(data.playTexture);

				}
			}
		}
		else
		{
			data.pauseSprite.setColor(sf::Color::White);
			data.pauseSprite.setTexture(data.pauseTexture);
		}
	}

	void UpdatePlayState(PlayStateData& data, GameData& gameData, float DeltaTime)
	{

		if (data.timerStart) {
			data.timePerPlay -= DeltaTime;
			data.textTimerPerPlay.setString(std::to_string(static_cast<int>(std::ceil(data.timePerPlay))));
			
			
		}
		if (data.timePerPlay <= 0)
		{
			UpdateSnake(data.snake, gameData, data, DeltaTime);
			UpdateApple(data.apple, gameData, data, DeltaTime);
			UpdateLevel(data.level, gameData, data, DeltaTime);

			data.mouseCursor.setPosition(gameData.mauseLocalPosition.x, gameData.mauseLocalPosition.y);
			data.timerStart = false;

			switch (gameData.difficulty)
			{
			case Difficulty::Simple:
				if (gameData.snakeScore >= EXTRA_POINTS_SIMPLE * WIN_MULTIPLIER)
				{
					gameData.GameWin = true;
					PushGameState(gameData, StateType::EnterName, false);
				}
				gameData.extraPoints = EXTRA_POINTS_SIMPLE;
				data.extraScoreText.setString(" +" + std::to_string(gameData.extraPoints));
				data.extraScoreText.setFillColor(sf::Color(154, 227, 155));
				data.snake.moveDelay = 13 - 2 * (SNAKE_SPEED_SIMPLE + data.apple.poisonedApple_DebuffSpeed - 1);
				data.infoText.setString("Mod: Simple | need: " + std::to_string(EXTRA_POINTS_SIMPLE * WIN_MULTIPLIER));
				break;
			case Difficulty::HarderSimple:
				if (gameData.snakeScore >= EXTRA_POINTS_HARDER_SIMPLE * WIN_MULTIPLIER)
				{
					gameData.GameWin = true;
					PushGameState(gameData, StateType::EnterName, false);
				}
				gameData.extraPoints = EXTRA_POINTS_HARDER_SIMPLE;
				data.extraScoreText.setString(" +" + std::to_string(gameData.extraPoints));
				data.extraScoreText.setFillColor(sf::Color(32, 214, 81));
				data.snake.moveDelay = 14 - 2 * (SNAKE_SPEED_HARDER_SIMPLE + data.apple.poisonedApple_DebuffSpeed - 1);
				data.infoText.setString("Mod: Simple+ | need: " + std::to_string(EXTRA_POINTS_HARDER_SIMPLE * WIN_MULTIPLIER));
				break;
			case Difficulty::Medium:
				if (gameData.snakeScore >= EXTRA_POINTS_MEDIUM * WIN_MULTIPLIER)
				{
					gameData.GameWin = true;
					PushGameState(gameData, StateType::EnterName, false);
				}
				gameData.extraPoints = EXTRA_POINTS_MEDIUM;
				data.extraScoreText.setString(" +" + std::to_string(gameData.extraPoints));
				data.extraScoreText.setFillColor(sf::Color(205, 214, 32));
				data.snake.moveDelay = 14 - 2 * (SNAKE_SPEED_MEDIUM + data.apple.poisonedApple_DebuffSpeed - 1);
				data.infoText.setString("Mod: Medium | need: " + std::to_string(EXTRA_POINTS_MEDIUM * WIN_MULTIPLIER));
				break;
			case Difficulty::EasierHard:
				if (gameData.snakeScore >= EXTRA_POINTS_EASIER_HARD * WIN_MULTIPLIER)
				{
					gameData.GameWin = true;
					PushGameState(gameData, StateType::EnterName, false);
				}
				gameData.extraPoints = EXTRA_POINTS_EASIER_HARD;
				data.extraScoreText.setString(" +" + std::to_string(gameData.extraPoints));
				data.extraScoreText.setFillColor(sf::Color(230, 144, 16));
				data.snake.moveDelay = 15 - 2 * (SNAKE_SPEED_EASIER_HARD + data.apple.poisonedApple_DebuffSpeed - 1);
				data.infoText.setString("Mod: Medium+ | need: " + std::to_string(EXTRA_POINTS_EASIER_HARD * WIN_MULTIPLIER));
				break;
			case Difficulty::Hard:
				if (gameData.snakeScore >= EXTRA_POINTS_HARD * WIN_MULTIPLIER)
				{
					gameData.GameWin = true;
					PushGameState(gameData, StateType::EnterName, false);
				}
				gameData.extraPoints = EXTRA_POINTS_HARD;
				data.extraScoreText.setString(" +" + std::to_string(gameData.extraPoints));
				data.extraScoreText.setFillColor(sf::Color(230, 41, 16));
				data.snake.moveDelay = 15 - 2 * (SNAKE_SPEED_HARD + data.apple.poisonedApple_DebuffSpeed - 1);
				data.infoText.setString("Mod: Hard | need: " + std::to_string(EXTRA_POINTS_HARD * WIN_MULTIPLIER));
				break;

			default:
				break;
			}

		}

		data.scoreText.setString("Score: " + std::to_string(gameData.snakeScore));
	}

	void DrawPlayState(PlayStateData& data, GameData& gameData, sf::RenderWindow& window)
	{
		DrawLevel(data.level, gameData, window);
		DrawSnake(data.snake, window);
		DrawApple(data.apple, gameData, window);
		window.draw(data.shapeScoreBackground);
		window.draw(data.shapeInfoBackground);
		window.draw(data.scoreText);
		window.draw(data.infoText);
		window.draw(data.extraScoreText);
		window.draw(data.pauseSprite);
		window.draw(data.mouseCursor);
		data.textTimerPerPlay.setOrigin(GetItemOrigin(data.textTimerPerPlay, { 0.5f, 0.7f }));
		if (data.timerStart)
		{
			window.draw(data.textTimerPerPlay);
		}
	}
}