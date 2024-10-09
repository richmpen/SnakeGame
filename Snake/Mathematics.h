#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Const.h"
#include <string>


namespace Snake
{
	struct GameData;
	struct PlayStateData;

	enum class Orientation
	{
		Horizontal,
		Vertical
	};

	enum class Alignment
	{
		Min,
		Middle,
		Max
	};

	bool SpriteCollision(sf::Sprite& Sprite_A, sf::Sprite& Sprite_B);

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);

	void SetSpriteOrigin(sf::Sprite& sprite, float originX, float originY);

	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);

	void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin);

	void SoundPlay(sf::Sound& sound, GameData& gameData);

	void MusicPlay(sf::Music& music, GameData& gameData);

	void TextInit(sf::Text& item, const std::string& text, int size, sf::Color color, sf::Font& font);

	void GameItemRespawn(sf::Sprite& itemSprite, PlayStateData& playData, float& x, float& y);

	void SnakeSegmentAdd(int count, PlayStateData& playData);

	bool SerializeGame(const GameData& gameData);

	bool DeserializeGame(GameData& gameData);
}