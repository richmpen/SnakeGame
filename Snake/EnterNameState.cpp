#include "EnterNameState.h"

namespace Snake
{
	void InitEnterName(EnterNameData& data, GameData& gameData)
	{
		assert(data.font.loadFromFile(ASSET_FOLDER + "Roboto-Black.ttf"));
		assert(data.openBuffer.loadFromFile(ASSET_FOLDER + "Audio/popUpName.wav"));
		assert(data.keyTapBuffer.loadFromFile(ASSET_FOLDER + "Audio/keyTap.wav"));

		data.keyTapSound.setBuffer(data.keyTapBuffer);
		data.keyTapSound.setVolume(30.f);

		data.openSound.setBuffer(data.openBuffer);
		SoundPlay(data.openSound, gameData);

		data.background.setFillColor(sf::Color(0, 0, 0, 220));
		data.background.setSize(sf::Vector2f(400, 250));
		data.background.setOutlineThickness(5.f);
		data.background.setOutlineColor(sf::Color::White);
		data.background.setOrigin(data.background.getGlobalBounds().width / 2, data.background.getGlobalBounds().height / 2);

		TextInit(data.enterNameText, "ADD NAME?", 50, sf::Color::White, data.font);
		data.enterNameText.setOrigin(GetItemOrigin(data.enterNameText, { 0.5f, 0.5f }));

		TextInit(data.enterScoreText, "Your Score: " + std::to_string(gameData.snakeScore), 35, sf::Color::White, data.font);
		data.enterScoreText.setOrigin(GetItemOrigin(data.enterScoreText, { 0.5f, 0.5f }));

		data.menu.rootitem.children.push_back(&data.enterNameYes);
		data.menu.rootitem.children.push_back(&data.enterNameNo);

		data.menu.rootitem.childrenOrientation = Orientation::Horizontal;
		data.menu.rootitem.childrenAlignment = Alignment::Middle;
		data.menu.rootitem.childrenSpacing = 40.f;

		TextInit(data.enterNameYes.text, "Yes", 30, sf::Color::White, data.font);
		data.enterNameYes.text.setString("Yes");
		data.enterNameYes.text.setFont(data.font);
		data.enterNameYes.text.setCharacterSize(30);

		TextInit(data.enterNameNo.text, "No", 30, sf::Color::White, data.font);
		data.enterNameNo.text.setString("No");
		data.enterNameNo.text.setFont(data.font);
		data.enterNameNo.text.setCharacterSize(30);

		TextInit(data.recordNameText, "", 30, sf::Color::White, data.font);
		data.recordNameText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f - 115.f, WINDOW_HEIGHT / 2.f - 50.f));

		data.recordNameBackground.setSize(sf::Vector2f(250, 50));
		data.recordNameBackground.setFillColor(sf::Color(255, 255, 255, 100));
		data.recordNameBackground.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f - 30.f));
		data.recordNameBackground.setOrigin(data.recordNameBackground.getGlobalBounds().width / 2, data.recordNameBackground.getGlobalBounds().height / 2);

		TextInit(data.alertLineSize, "", 18, sf::Color(241, 75, 92), data.font);
		data.alertLineSize.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f - 20.f, WINDOW_HEIGHT / 2.f - 80.f));

		InitMenuItem(data.menu.rootitem);
		SelectMenuItem(data.menu, &data.enterNameNo);
	}

	void ShutdownEnterName(EnterNameData& data, GameData& gameData){}

	void ControlEnterName(EnterNameData& data, GameData& gameData, const sf::Event& event)
	{
		if (data.enterNameVisible)
		{
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128 && event.text.unicode != 13)
				{
					SoundPlay(data.keyTapSound, gameData);
					
					if (event.text.unicode == 8)
					{
						if (!data.recordName.empty())
						{
							data.recordName.pop_back();
						}
					}
					else
					{
						if (data.recordName.size() < data.maxLengthLine)
						{
							data.recordName += static_cast<char>(event.text.unicode);
						}
						else if (data.recordName.size() == data.maxLengthLine)
						{
							data.alertLineSize.setString("max: " + std::to_string(data.maxLengthLine));
						}
					}

					data.recordNameText.setString(data.recordName);
				}
			}
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Enter)
			{
				SoundPlay(gameData.selectSound, gameData);
				if (data.enterNameVisible)
				{
					if (data.menu.selectedItem == &data.enterNameNo)
					{
						data.enterNameNo.text.setString("No");
						data.enterNameYes.text.setString("Yes");
						data.enterNameVisible = false;
					}
					else if (data.recordName.size() > data.minLengthLine)
					{
						if (data.menu.selectedItem == &data.enterNameYes)
						{
							gameData.record.insert({ gameData.snakeScore, data.recordName });
							SerializeGame(gameData);
							if (gameData.GameWin)
							{
								SwitchGameState(gameData, StateType::GameWin);
							}
							else if (!gameData.GameWin)
							{
								SwitchGameState(gameData, StateType::GameOver);
							}
						}
					}
					else
					{
						data.enterNameYes.text.setFillColor(sf::Color(255, 255, 255, 100));
						data.alertLineSize.setString("min: " + std::to_string(data.minLengthLine));
					}
				}
				else
				{
					if (data.menu.selectedItem == &data.enterNameNo)
					{
						if (gameData.GameWin)
						{
							SwitchGameState(gameData, StateType::GameWin);
						}
						else if(!gameData.GameWin)
						{
							SwitchGameState(gameData, StateType::GameOver);
						}
					}
					else if (data.menu.selectedItem == &data.enterNameYes)
					{
						data.enterNameNo.text.setString("Back");
						data.enterNameYes.text.setString("Enter");
						data.enterNameVisible = true;
						data.recordName = "XYZ";
						data.recordNameText.setString(data.recordName);
					}
				}
			}

			Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;
			if (orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				SoundPlay(gameData.selectSound, gameData);
				SelectedPrevMenuItem(data.menu);
			}
			else if (orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				SoundPlay(gameData.selectSound, gameData);
				SelectedNextMenuItem(data.menu);
			}
		}
	}

	void UpdateEnterName(EnterNameData& data, GameData& gameData, float DeltaTime)
	{
		if (data.enterNameVisible)
		{
			data.enterNameText.setString("ENTER NAME");
			data.menuPosition = sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f + 23.f);
			data.enterNameText.setOrigin(GetItemOrigin(data.enterNameText, { 0.5f, 0.5f }));
		}
		else
		{
			data.menuPosition = sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f - 30.f);
		}
	}

	void DrawEnterName(EnterNameData& data, GameData& gameData, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();
		data.background.setPosition(viewSize.x / 2, viewSize.y / 2 - 65.f);
		window.draw(data.background);

		data.enterNameText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f - 160.f);
		window.draw(data.enterNameText);

		data.enterScoreText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f - 110.f);
		window.draw(data.enterScoreText);

		DrawMenu(data.menu, window, data.menuPosition, { 0.5f, 0.8f });

		if (data.enterNameVisible)
		{
			window.draw(data.recordNameBackground);
			window.draw(data.recordNameText);
			window.draw(data.alertLineSize);
		}
	}
}
