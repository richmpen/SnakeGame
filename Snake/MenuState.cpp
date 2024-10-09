#include "MenuState.h"
#include "Const.h"
#include "GameData.h"

namespace Snake
{
	void InitMainMenu(MainMenuData& data, GameData& gameData)
	{
		assert(data.font.loadFromFile(ASSET_FOLDER + "Roboto-Black.ttf"));
		assert(data.backgroundMenuTexture.loadFromFile(ASSET_FOLDER + "BackgroundMenu.png"));
		assert(data.checkboxOffTexture.loadFromFile(ASSET_FOLDER + "check_box_off.png"));
		assert(data.checkboxOnTexture.loadFromFile(ASSET_FOLDER + "check_box_on.png"));

		TextInit(data.menu.rootitem.promptText, "SNAKE", 140, sf::Color(255, 255, 255, 80), data.font);

		data.backgroundMenuSprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		data.backgroundMenuSprite.setTexture(data.backgroundMenuTexture);
		SetSpriteSize(data.backgroundMenuSprite, WINDOW_WIDTH, WINDOW_HEIGHT);
		SetSpriteOrigin(data.backgroundMenuSprite, 0.5f, 0.5f);

		data.menu.rootitem.childrenOrientation = Orientation::Vertical;
		data.menu.rootitem.childrenAlignment = Alignment::Middle;
		data.menu.rootitem.childrenSpacing = 25.f;

		data.menu.rootitem.children.push_back(&data.StartGameItem);
		data.menu.rootitem.children.push_back(&data.DifficultyItem);
		data.menu.rootitem.children.push_back(&data.RecordsTableItem);
		data.menu.rootitem.children.push_back(&data.SettingsItem);
		data.menu.rootitem.children.push_back(&data.ExitItem);

		TextInit(data.StartGameItem.text, "Start Game", 35, sf::Color::White, data.font);
		TextInit(data.StartGameItem.promptText, "Start Game", 80, sf::Color::White, data.font);
		data.StartGameItem.childrenOrientation = Orientation::Vertical;
		data.StartGameItem.childrenAlignment = Alignment::Middle;
		data.StartGameItem.childrenSpacing = 25.f;

		data.StartGameItem.children.push_back(&data.StartSesion);
		data.StartGameItem.children.push_back(&data.appleMod);
		data.StartGameItem.children.push_back(&data.portalsMod);

		TextInit(data.StartSesion.text, "START", 40, sf::Color::White, data.font);
		TextInit(data.appleMod.text, "Apple Mod", 30, sf::Color::White, data.font);
		TextInit(data.portalsMod.text, "Portals Mod", 30, sf::Color::White, data.font);

		TextInit(data.DifficultyItem.text, "Difficulty", 35, sf::Color::White, data.font);
		TextInit(data.DifficultyItem.promptText, "Difficulty", 80, sf::Color(255, 255, 255, 200), data.font);
		
		data.DifficultyItem.childrenOrientation = Orientation::Vertical;
		data.DifficultyItem.childrenAlignment = Alignment::Middle;
		data.DifficultyItem.childrenSpacing = 25.f;

		data.DifficultyItem.children.push_back(&data.difficulty_Simple);
		data.DifficultyItem.children.push_back(&data.difficulty_HarderSimple);
		data.DifficultyItem.children.push_back(&data.difficulty_Medium);
		data.DifficultyItem.children.push_back(&data.difficulty_EasierHard);
		data.DifficultyItem.children.push_back(&data.difficulty_Hard);
		
		TextInit(data.difficulty_Simple.text, "Simple", 30, sf::Color::White, data.font);
		TextInit(data.difficulty_HarderSimple.text, "Harder-Simple", 30, sf::Color::White, data.font);
		TextInit(data.difficulty_Medium.text, "Medium", 30, sf::Color::White, data.font);
		TextInit(data.difficulty_EasierHard.text, "Easier-Hard", 30, sf::Color::White, data.font);
		TextInit(data.difficulty_Hard.text, "Hard", 30, sf::Color::White, data.font);

		TextInit(data.RecordsTableItem.text, "Records Table", 35, sf::Color::White, data.font);
		TextInit(data.RecordsTableItem.promptText, "Records Table", 80, sf::Color(255, 255, 255, 200), data.font);

		data.RecordsTableItem.childrenOrientation = Orientation::Vertical;
		data.RecordsTableItem.childrenAlignment = Alignment::Middle;
		data.RecordsTableItem.childrenSpacing = 25.f;

		data.RecordsTableItem.children.push_back(&data.records);
	
		TextInit(data.recordNameText, "", 35, sf::Color::White, data.font);
		TextInit(data.recordScoreText, "", 35, sf::Color::White, data.font);
		
		data.recordsBackground.setSize(sf::Vector2f(600, 480));
		data.recordsBackground.setPosition(sf::Vector2f(WINDOW_WIDTH/2, WINDOW_HEIGHT/2+150));
		data.recordsBackground.setFillColor(sf::Color(0, 0, 0, 225));
		data.recordsBackground.setOutlineThickness(5.f);
		data.recordsBackground.setOutlineColor(sf::Color::White);
		data.recordsBackground.setOrigin(data.recordsBackground.getGlobalBounds().width / 2, data.recordsBackground.getGlobalBounds().height / 2);

		TextInit(data.SettingsItem.text, "Settings", 35, sf::Color::White, data.font);
		TextInit(data.SettingsItem.promptText, "Settings", 80, sf::Color(255, 255, 255, 200), data.font);

		data.SettingsItem.childrenOrientation = Orientation::Vertical;
		data.SettingsItem.childrenAlignment = Alignment::Middle;
		data.SettingsItem.childrenSpacing = 25.f;

		data.SettingsItem.children.push_back(&data.sound);
		data.SettingsItem.children.push_back(&data.music);
		
		TextInit(data.sound.text, "Sound", 30, sf::Color::White, data.font);
		TextInit(data.music.text, "Music", 30, sf::Color::White, data.font);

		TextInit(data.ExitItem.text, "Exit", 35, sf::Color::White, data.font);
		TextInit(data.ExitItem.promptText, "Are you sure?", 80, sf::Color::White, data.font);

		data.ExitItem.childrenOrientation = Orientation::Horizontal;
		data.ExitItem.childrenAlignment = Alignment::Middle;
		data.ExitItem.childrenSpacing = 25.f;
		data.ExitItem.children.push_back(&data.exitYes);
		data.ExitItem.children.push_back(&data.exitNo);

		TextInit(data.exitYes.text, "Yes", 30, sf::Color::White, data.font);

		TextInit(data.exitNo.text, "No", 30, sf::Color::White, data.font);

		InitMenuItem(data.menu.rootitem);
		SelectMenuItem(data.menu, &data.StartGameItem);
	}

	void ShutdownMainMenu(MainMenuData& data, GameData& gameData){}

	void ControlMainMenu(MainMenuData& data, GameData& gameData, const sf::Event& event)
	{
		if (!data.menu.selectedItem)
		{
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			SoundPlay(gameData.selectSound, gameData);
			if(event.key.code == sf::Keyboard::Enter)
			{
				if (data.menu.selectedItem == &data.StartGameItem)
				{
					OpenSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.StartSesion)
				{
					SwitchGameState(gameData, StateType::Play);
				}
				else if (data.menu.selectedItem == &data.appleMod)
				{
					gameData.mods = (Mods)((std::uint8_t)gameData.mods ^ (std::uint8_t)Mods::AppleMod);
				}
				else if (data.menu.selectedItem == &data.portalsMod)
				{
					gameData.mods = (Mods)((std::uint8_t)gameData.mods ^ (std::uint8_t)Mods::Portals);
				}
				else if (data.menu.selectedItem == &data.DifficultyItem)
				{
					OpenSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.difficulty_Simple)
				{
					gameData.difficulty = Difficulty::Simple;
				}
				else if (data.menu.selectedItem == &data.difficulty_HarderSimple)
				{
					gameData.difficulty = Difficulty::HarderSimple;
				}
				else if (data.menu.selectedItem == &data.difficulty_Medium)
				{
					gameData.difficulty = Difficulty::Medium;
				}
				else if (data.menu.selectedItem == &data.difficulty_EasierHard)
				{
					gameData.difficulty = Difficulty::EasierHard;
				}
				else if (data.menu.selectedItem == &data.difficulty_Hard)
				{
					gameData.difficulty = Difficulty::Hard;
				}
				else if (data.menu.selectedItem == &data.SettingsItem)
				{
					OpenSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.sound)
				{
					gameData.settings = (Settings)((std::uint8_t)gameData.settings ^ (std::uint8_t)Settings::Sound);
				}
				else if (data.menu.selectedItem == &data.music)
				{
					gameData.settings = (Settings)((std::uint8_t)gameData.settings ^ (std::uint8_t)Settings::Music);
				}
				else if (data.menu.selectedItem == &data.ExitItem)
				{
					OpenSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.exitYes)
				{
					SwitchGameState(gameData, StateType::None);
				}
				else if (data.menu.selectedItem == &data.exitNo)
				{
					CloseSelectedItem(data.menu);
				}
				else 
				{
					OpenSelectedItem(data.menu);
				}
			}
			else if (event.key.code == sf::Keyboard::B)
			{
				CloseSelectedItem(data.menu);
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				CloseSelectedItem(data.menu);
			}

			Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				SelectedPrevMenuItem(data.menu);
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				SelectedNextMenuItem(data.menu);
			}
		}
	}

	void UpdateMainMenu(MainMenuData& data, GameData& gameData, float DeltaTime)
	{
	
		for (auto& child : data.DifficultyItem.children)
		{
			child->checkbox.setPosition(child->text.getPosition().x + 200.f, child->text.getPosition().y + 20.f);
			SetSpriteSize(child->checkbox, 40.f, 40.f);
			SetSpriteOrigin(child->checkbox, 0.5f, 0.5f);
		}
		for (auto& child : data.SettingsItem.children)
		{
			child->checkbox.setPosition(child->text.getPosition().x + 200.f, child->text.getPosition().y + 20.f);
			SetSpriteSize(child->checkbox, 40.f, 40.f);
			SetSpriteOrigin(child->checkbox, 0.5f, 0.5f);
		}
		for (auto& child : data.StartGameItem.children)
		{
			child->checkbox.setPosition(child->text.getPosition().x + 200.f, child->text.getPosition().y + 20.f);
			SetSpriteSize(child->checkbox, 40.f, 40.f);
			SetSpriteOrigin(child->checkbox, 0.5f, 0.5f);
		}

		bool Simple = ((std::uint8_t)gameData.difficulty & (std::uint8_t)Difficulty::Simple);
		Simple ? data.difficulty_Simple.checkbox.setTexture(data.checkboxOnTexture) : data.difficulty_Simple.checkbox.setTexture(data.checkboxOffTexture);

		bool HarderSimple = ((std::uint8_t)gameData.difficulty & (std::uint8_t)Difficulty::HarderSimple);
		HarderSimple ? data.difficulty_HarderSimple.checkbox.setTexture(data.checkboxOnTexture) : data.difficulty_HarderSimple.checkbox.setTexture(data.checkboxOffTexture);

		bool Medium = ((std::uint8_t)gameData.difficulty & (std::uint8_t)Difficulty::Medium);
		Medium ? data.difficulty_Medium.checkbox.setTexture(data.checkboxOnTexture) : data.difficulty_Medium.checkbox.setTexture(data.checkboxOffTexture);

		bool EasierHard = ((std::uint8_t)gameData.difficulty & (std::uint8_t)Difficulty::EasierHard);
		EasierHard ? data.difficulty_EasierHard.checkbox.setTexture(data.checkboxOnTexture) : data.difficulty_EasierHard.checkbox.setTexture(data.checkboxOffTexture);

		bool Hard = ((std::uint8_t)gameData.difficulty & (std::uint8_t)Difficulty::Hard);
		Hard ? data.difficulty_Hard.checkbox.setTexture(data.checkboxOnTexture) : data.difficulty_Hard.checkbox.setTexture(data.checkboxOffTexture);

		bool Sound = ((std::uint8_t)gameData.settings & (std::uint8_t)Settings::Sound) != (std::uint8_t)Settings::Empty;
		Sound ? data.sound.checkbox.setTexture(data.checkboxOnTexture) : data.sound.checkbox.setTexture(data.checkboxOffTexture);

		bool Music = ((std::uint8_t)gameData.settings & (std::uint8_t)Settings::Music) != (std::uint8_t)Settings::Empty;
		Music ? data.music.checkbox.setTexture(data.checkboxOnTexture) : data.music.checkbox.setTexture(data.checkboxOffTexture);
		
		bool AppleMod = ((std::uint8_t)gameData.mods & (std::uint8_t)Mods::AppleMod) != (std::uint8_t)Mods::Empty;
		AppleMod ? data.appleMod.checkbox.setTexture(data.checkboxOnTexture) : data.appleMod.checkbox.setTexture(data.checkboxOffTexture);

		bool Portals = ((std::uint8_t)gameData.mods & (std::uint8_t)Mods::Portals) != (std::uint8_t)Mods::Empty;
		Portals ? data.portalsMod.checkbox.setTexture(data.checkboxOnTexture) : data.portalsMod.checkbox.setTexture(data.checkboxOffTexture);
	}

	void DrawMainMenu(MainMenuData& data, GameData& gameData, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		window.draw(data.text);
		window.draw(data.backgroundMenuSprite);

		if (data.menu.selectedItem->parent == &data.RecordsTableItem)
		{
			if (gameData.record.empty()){
				data.RecordsTableItem.promptText.setString("Records not found..");	
			}
			else 
			{
				window.draw(data.recordsBackground);
				int index = 0;
				for (auto item = gameData.record.rbegin(); item != gameData.record.rend(); ++item)
				{
					if (index >= MAX_MENU_RECORD_VISIBLE) break;
					data.recordNameText.setPosition(viewSize.x / 2 - 260.f, viewSize.y / 2.5f + index * 45.f);
					data.recordNameText.setString(item->second );

					data.recordScoreText.setPosition(viewSize.x / 1.35f, viewSize.y / 2.5f + index * 45.f);
					data.recordScoreText.setString(std::to_string(item->first));

					window.draw(data.recordNameText);
					window.draw(data.recordScoreText);
					index++;
				}
			}
		}
		
		if (data.menu.selectedItem->parent == &data.DifficultyItem)
		{
			for (auto& child : data.DifficultyItem.children)
			{
				window.draw(child->checkbox);				
			}
		
		}
		else if (data.menu.selectedItem->parent == &data.SettingsItem)
		{
			for (auto& child : data.SettingsItem.children)
			{
				window.draw(child->checkbox);
			}

		}
		else if (data.menu.selectedItem->parent == &data.StartGameItem)
		{
			for (auto& child : data.StartGameItem.children)
			{
				window.draw(child->checkbox);
			}

		}

		sf::Text* promptText = &GetCurrentMenuContext(data.menu)->promptText;
		promptText->setOrigin(GetItemOrigin(*promptText, { 0.5f, 0.f }));
		promptText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*promptText);

		DrawMenu(data.menu, window, viewSize / 2.f, { 0.5f, 0.f });
	}
}
