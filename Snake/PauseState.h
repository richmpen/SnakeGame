#pragma once
#include "GameData.h"

namespace Snake 
{
	struct GameData;

	struct PauseDialogData
	{
		sf::Font font;
		sf::Text text;
		sf::Text promptText;
		sf::Text textTimerPerPlay;

		sf::RectangleShape background;

		MenuItem PauseItem;
		MenuItem PausePlayContinueGame;
		MenuItem PauseExitMainMenu;

		float timePerPlayState = 0.f;
		bool timerStart = false;

		Menu menu;
	};

	void InitPauseDialog(PauseDialogData& data, GameData& gameData);
	void ShutdownPauseDialog(PauseDialogData& data, GameData& gameData);
	void ControlPauseDialog(PauseDialogData& data, GameData& gameData, const sf::Event& event);
	void UpdatePauseDialog(PauseDialogData& data, GameData& gameData, float DeltaTime);
	void DrawPauseDialog(PauseDialogData& data, GameData& gameData, sf::RenderWindow& window);

}