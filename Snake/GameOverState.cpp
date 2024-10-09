#include "GameOverState.h"

namespace Snake
{
	void InitGameOver(GameOverData& data, GameData& gameData)
	{
		assert(data.font.loadFromFile(ASSET_FOLDER + "Roboto-Black.ttf"));
		assert(data.gameOverSoundBuffer.loadFromFile(ASSET_FOLDER + "Audio/Lose.wav"));

		data.gameOverSound.setBuffer(data.gameOverSoundBuffer);
		SoundPlay(data.gameOverSound, gameData);

		data.background.setFillColor(sf::Color::Black);

		TextInit(data.gameOverText, "Game Over", 70, sf::Color::Red, data.font);
		data.gameOverText.setOrigin(GetItemOrigin(data.gameOverText, { 0.5f, 0.5f }));

		TextInit(data.gameOverScoreText, "Your Score: " + std::to_string(gameData.snakeScore), 50, sf::Color::White, data.font);
		data.gameOverScoreText.setOrigin(GetItemOrigin(data.gameOverScoreText, { 0.5f, 0.5f }));

		TextInit(data.recordNameText, "", 35, sf::Color::White, data.font);
		TextInit(data.recordScoreText, "", 35, sf::Color::White, data.font);
		TextInit(data.promptText, "Records:", 30, sf::Color::White, data.font);

		data.recordBackground.setSize(sf::Vector2f(350,250));
		data.recordBackground.setPosition(sf::Vector2f(WINDOW_WIDTH /2, WINDOW_HEIGHT /2+80));
		data.recordBackground.setFillColor(sf::Color(0, 0, 0, 100));
		data.recordBackground.setOutlineThickness(5.f);
		data.recordBackground.setOutlineColor(sf::Color::White);
		data.recordBackground.setOrigin(data.recordBackground.getGlobalBounds().width / 2, data.recordBackground.getGlobalBounds().height / 2);
		
		data.menu.rootitem.children.push_back(&data.GameOverPlayNextGame);
		data.menu.rootitem.children.push_back(&data.GameOverExitMainMenu);

		data.menu.rootitem.childrenOrientation = Orientation::Horizontal;
		data.menu.rootitem.childrenAlignment = Alignment::Middle;
		data.menu.rootitem.childrenSpacing = 40.f;

		TextInit(data.GameOverPlayNextGame.text, "Restart", 30, sf::Color::White, data.font);
		TextInit(data.GameOverExitMainMenu.text, "Main menu", 30, sf::Color::White, data.font);

		InitMenuItem(data.menu.rootitem);
		SelectMenuItem(data.menu, &data.GameOverPlayNextGame);
	}

	void ShutdownGameOver(GameOverData& data, GameData& gameData){}

	void ControlGameOver(GameOverData& data, GameData& gameData, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			SoundPlay(gameData.selectSound, gameData);
			if (event.key.code == sf::Keyboard::Enter)
			{
				if (data.menu.selectedItem == &data.GameOverExitMainMenu)
				{
					SwitchGameState(gameData, StateType::MainMenu);
				}
				else if (data.menu.selectedItem == &data.GameOverPlayNextGame)
				{
					SwitchGameState(gameData, StateType::Play);
				}
			}
			Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;
			if (orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				SelectedPrevMenuItem(data.menu);
			}
			else if (orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				SelectedNextMenuItem(data.menu);
			}
		}
	}

	void UpdateGameOver(GameOverData& data, GameData& gameData, float DeltaTime){}

	void DrawGameOver(GameOverData& data, GameData& gameData, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();
		data.background.setSize(viewSize);
		window.draw(data.background);

		data.gameOverText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f-300.f);
		window.draw(data.gameOverText);

		data.gameOverScoreText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f - 200.f);
		window.draw(data.gameOverScoreText);

		data.promptText.setPosition(viewSize.x / 2.f, viewSize.y / 2 - 85.f );
		data.promptText.setOrigin(GetItemOrigin(data.promptText, { 0.5f, 0.5f }));
		window.draw(data.promptText);

		sf::Vector2f menuPosition = sf::Vector2f(viewSize.x / 2.f, viewSize.y / 2.f + 250.f);
		if (gameData.record.empty()) {
			data.promptText.setString("Records not found..");
			data.promptText.setOrigin(GetItemOrigin(data.promptText, { 0.5f, 0.5f }));
			menuPosition = sf::Vector2f(viewSize.x / 2.f, viewSize.y / 2.f + 30.f);
		}
		else 
		{
			int index = 0;
			for (auto item = gameData.record.rbegin(); item != gameData.record.rend(); ++item)
			{
				if (index >= MAX_GAMEOVER_RECORD_VISIBLE) break;
				data.recordNameText.setPosition(viewSize.x / 2 - 160.f, viewSize.y / 2.2f + index * 45.f);
				data.recordNameText.setString(item->second);

				data.recordScoreText.setPosition(viewSize.x / 1.7f, viewSize.y / 2.2f + index * 45.f);
				data.recordScoreText.setString(std::to_string(item->first));
	
				window.draw(data.recordNameText);
				window.draw(data.recordScoreText);
				index++;
			}
				window.draw(data.recordBackground);
		}

		DrawMenu(data.menu, window, menuPosition, { 0.5f, 0.8f });
	}
}