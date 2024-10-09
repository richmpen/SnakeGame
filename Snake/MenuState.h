#pragma once
#include "Const.h"
#include "Menu.h"


namespace Snake
{
	struct GameData;

	struct MainMenuData
	{
		sf::Font font;
		sf::Text text;
		sf::Text promptText;

		sf::Texture backgroundMenuTexture;
		sf::Sprite backgroundMenuSprite;

		sf::Texture checkboxOffTexture;
		sf::Texture checkboxOnTexture;

		MenuItem StartGameItem;
		MenuItem StartSesion;
		MenuItem appleMod;
		MenuItem portalsMod;

		MenuItem DifficultyItem;
		MenuItem difficulty_Simple;
		MenuItem difficulty_HarderSimple;
		MenuItem difficulty_Medium;
		MenuItem difficulty_EasierHard;
		MenuItem difficulty_Hard;

		MenuItem RecordsTableItem;
		MenuItem records;
		sf::RectangleShape recordsBackground;
		sf::Text recordNameText;
		sf::Text recordScoreText;
		
		MenuItem SettingsItem;
		MenuItem sound;
		MenuItem music;

		MenuItem ExitItem;
		MenuItem exitYes;
		MenuItem exitNo;

		Menu menu;
	};

	void InitMainMenu(MainMenuData& data, GameData& gameData);
	void ShutdownMainMenu(MainMenuData& data, GameData& gameData);
	void ControlMainMenu(MainMenuData& data, GameData& gameData, const sf::Event& event);
	void UpdateMainMenu(MainMenuData& data, GameData& gameData, float DeltaTime);
	void DrawMainMenu(MainMenuData& data, GameData& gameData, sf::RenderWindow& window);
}