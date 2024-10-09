#include "PauseState.h"
#include <assert.h>

namespace Snake 
{
	void InitPauseDialog(PauseDialogData& data, GameData& gameData)
	{
		assert(data.font.loadFromFile(ASSET_FOLDER + "Roboto-Black.ttf"));

		TextInit(data.text, "Pause", 70, sf::Color::White, data.font);
		data.text.setOrigin(GetItemOrigin(data.text, { 0.5f, 0.5f }));

		TextInit(data.promptText, " Exit or continue?", 30, sf::Color::White, data.font);
		data.promptText.setOrigin(GetItemOrigin(data.promptText, { 0.5f, 1.f }));
		
		data.background.setFillColor(sf::Color(0, 0, 0, 220));

		data.menu.rootitem.children.push_back(&data.PausePlayContinueGame);
		data.menu.rootitem.children.push_back(&data.PauseExitMainMenu);

		data.menu.rootitem.childrenOrientation = Orientation::Horizontal;
		data.menu.rootitem.childrenAlignment = Alignment::Middle;
		data.menu.rootitem.childrenSpacing = 40.f;

		TextInit(data.PausePlayContinueGame.text, "Continue", 30, sf::Color::White, data.font);

		TextInit(data.PauseExitMainMenu.text, "Main menu", 30, sf::Color::White, data.font);

		TextInit(data.textTimerPerPlay, "", 50, sf::Color::White, data.font);
		data.textTimerPerPlay.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2-30.f);
		data.timePerPlayState = TIME_PAUSE_TO_PLAY;

		InitMenuItem(data.menu.rootitem);
		SelectMenuItem(data.menu, &data.PausePlayContinueGame);
	}

	void ShutdownPauseDialog(PauseDialogData& data, GameData& gameData){}

	void ControlPauseDialog(PauseDialogData& data, GameData& gameData, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			SoundPlay(gameData.selectSound, gameData);
			if (event.key.code == sf::Keyboard::Enter)
			{
				if (data.menu.selectedItem == &data.PauseExitMainMenu)
				{
					SwitchGameState(gameData, StateType::MainMenu);
				}
				else if (data.menu.selectedItem == &data.PausePlayContinueGame)
				{
					data.timerStart = true;
				}
			}
			else if (event.key.code == sf::Keyboard::P || event.key.code == sf::Keyboard::Escape)
			{
				data.timerStart = true;
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

	void UpdatePauseDialog(PauseDialogData& data, GameData& gameData, float DeltaTime)
	{
		if (data.timerStart) {
			data.timePerPlayState -= DeltaTime;
			data.textTimerPerPlay.setString(std::to_string(static_cast<int>(std::ceil(data.timePerPlayState))));
		}
		if (data.timePerPlayState <= 0)
		{
			PopGameState(gameData);
			data.timerStart = false;
		}
	}

	void DrawPauseDialog(PauseDialogData& data, GameData& gameData, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();
		data.background.setSize(viewSize);
		data.text.setPosition(viewSize.x / 2.f, viewSize.y / 4.f);
		data.promptText.setPosition(viewSize.x / 2.f, viewSize.y / 4.f + 120.f);
		window.draw(data.background);
		window.draw(data.text);
		window.draw(data.promptText);
		DrawMenu(data.menu, window, sf::Vector2f(viewSize.x / 2.f, viewSize.y / 2.f + 30.f), { 0.5f, 0.8f });
		window.draw(data.textTimerPerPlay);
		data.textTimerPerPlay.setOrigin(GetItemOrigin(data.textTimerPerPlay, { 0.5f, 0.7f }));
	}
}
