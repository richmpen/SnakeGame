#include "GameWinState.h"

namespace Snake
{
	void InitGameWin(GameWinData& data, GameData& gameData)
	{
		assert(data.font.loadFromFile(ASSET_FOLDER + "Roboto-Black.ttf"));
		assert(data.gameWinSoundBuffer.loadFromFile(ASSET_FOLDER + "Audio/Win.wav"));

		data.gameWinSound.setBuffer(data.gameWinSoundBuffer);
		SoundPlay(data.gameWinSound, gameData);

		data.background.setFillColor(sf::Color::Black);

		TextInit(data.gameWinText, "Game Win", 70, sf::Color::Green, data.font);
		data.gameWinText.setOrigin(GetItemOrigin(data.gameWinText, { 0.5f, 0.5f }));

		TextInit(data.gameWinScoreText, "Your Score: " + std::to_string(gameData.snakeScore), 50, sf::Color::White, data.font);
		data.gameWinScoreText.setOrigin(GetItemOrigin(data.gameWinScoreText, { 0.5f, 0.5f }));

		TextInit(data.recordNameText, "", 35, sf::Color::White, data.font);
		TextInit(data.recordScoreText, "", 35, sf::Color::White, data.font);
		TextInit(data.promptText, "Records:", 30, sf::Color::White, data.font);


		data.recordBackground.setSize(sf::Vector2f(350, 250));
		data.recordBackground.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 80));
		data.recordBackground.setFillColor(sf::Color(0, 0, 0, 100));
		data.recordBackground.setOutlineThickness(5.f);
		data.recordBackground.setOutlineColor(sf::Color::White);
		data.recordBackground.setOrigin(data.recordBackground.getGlobalBounds().width / 2, data.recordBackground.getGlobalBounds().height / 2);

		data.menu.rootitem.children.push_back(&data.GameWinPlayNextGame);
		data.menu.rootitem.children.push_back(&data.GameWinExitMainMenu);

		data.menu.rootitem.childrenOrientation = Orientation::Horizontal;
		data.menu.rootitem.childrenAlignment = Alignment::Middle;
		data.menu.rootitem.childrenSpacing = 40.f;

		TextInit(data.GameWinPlayNextGame.text, "Restart", 30, sf::Color::White, data.font);
		TextInit(data.GameWinExitMainMenu.text, "Main menu", 30, sf::Color::White, data.font);
		

		InitMenuItem(data.menu.rootitem);
		SelectMenuItem(data.menu, &data.GameWinPlayNextGame);

	}

	void ShutdownGameWin(GameWinData& data, GameData& gameData){}

	void ControlGameWin(GameWinData& data, GameData& gameData, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			SoundPlay(gameData.selectSound, gameData);
			if (event.key.code == sf::Keyboard::Enter)
			{
				if (data.menu.selectedItem == &data.GameWinExitMainMenu)
				{
					SwitchGameState(gameData, StateType::MainMenu);
				}
				else if (data.menu.selectedItem == &data.GameWinPlayNextGame)
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

	void UpdateGameWin(GameWinData& data, GameData& gameData, float DeltaTime){}

	void DrawGameWin(GameWinData& data, GameData& gameData, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();
		data.background.setSize(viewSize);
		window.draw(data.background);

		data.gameWinText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f - 300.f);
		window.draw(data.gameWinText);

		data.gameWinScoreText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f - 200.f);
		window.draw(data.gameWinScoreText);

		data.promptText.setPosition(viewSize.x / 2.f, viewSize.y / 2 - 85.f);
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