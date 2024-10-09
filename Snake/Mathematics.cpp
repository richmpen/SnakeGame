#include "Mathematics.h"
#include "GameData.h"
#include "PlayState.h"


namespace Snake
{
	bool SpriteCollision(sf::Sprite& Sprite_A, sf::Sprite& Sprite_B)
	{
		return Sprite_A.getGlobalBounds().intersects(Sprite_B.getGlobalBounds());
	}

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}

	void SetSpriteOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
	}

	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition)
	{
		sf::FloatRect textSize = text.getLocalBounds();
		return {
			(textSize.left + textSize.width) * relativePosition.x,
			(textSize.top + textSize.height) * relativePosition.y,
		};
	}

	void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin)
	{
		sf::FloatRect totalRect;

		for (auto it = items.begin(); it != items.end(); ++it)
		{
			sf::FloatRect itemRect = (*it)->getGlobalBounds();

			if (orientation == Orientation::Horizontal)
			{
				totalRect.width += itemRect.width + (it != items.end() - 1 ? spacing : 0.f);
				totalRect.height = std::max(totalRect.height, itemRect.height);
			}
			else
			{
				totalRect.width = std::max(totalRect.width, itemRect.width);
				totalRect.height += itemRect.height + (it != items.end() - 1 ? spacing : 0.f);
			}
		}

		totalRect.left = position.x - origin.x * totalRect.width;
		totalRect.top = position.y - origin.y * totalRect.height;
		sf::Vector2f currentPos = { totalRect.left, totalRect.top };

		for (auto it = items.begin(); it != items.end(); ++it)
		{
			sf::FloatRect itemRect = (*it)->getGlobalBounds();
			sf::Vector2f itemOrigin;

			if (orientation == Orientation::Horizontal)
			{
				itemOrigin.y = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
				itemOrigin.x = 0.f;
				currentPos.y = totalRect.top + itemOrigin.y * totalRect.height;
			}
			else
			{
				itemOrigin.y = 0.f;
				itemOrigin.x = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
				currentPos.x = totalRect.left + itemOrigin.x * totalRect.width;
			}

			(*it)->setOrigin(GetItemOrigin(**it, itemOrigin));
			(*it)->setPosition(currentPos);
			window.draw(**it);

			if (orientation == Orientation::Horizontal)
			{
				currentPos.x += itemRect.width + spacing;
			}
			else
			{
				currentPos.y += itemRect.height + spacing;
			}


		}
	}
   
	void SoundPlay(sf::Sound& sound, GameData& gameData)
	{
		if (gameData.settings == Settings::Sound || gameData.settings == Settings::Default)
		{
			sound.play();
		}
	}

	void MusicPlay(sf::Music& music, GameData& gameData) 
	{
		if (gameData.settings == Settings::Music || gameData.settings == Settings::Default)
		{
			music.play();
		}
	}

	void TextInit(sf::Text& item, const std::string& text, int size, sf::Color color, sf::Font& font) {
		item.setString(text);
		item.setFont(font);
		item.setCharacterSize(size);
		item.setFillColor(color);
	}

	void GameItemRespawn(sf::Sprite& itemSprite, PlayStateData& playData, float& x, float& y)
	{
		const int maxIterations = 1000;
		int iterations = 0;
		bool positionValid = false;

		while (!positionValid && iterations < maxIterations)
		{
			x = ((rand() % (ROW - 2)) + 1);
			y = ((rand() % (COL - 2)) + 1);

			positionValid = true;

			for (auto segment : playData.snake.snakeBody)
			{
				if (itemSprite.getGlobalBounds().intersects(segment.getGlobalBounds())) {
					positionValid = false;
				}
				else if ((segment.getPosition().x / BLOCK_SIZE) == x &&
					(segment.getPosition().y / BLOCK_SIZE) == y)
				{
					positionValid = false;
					break;
				}
				
			}

			if (itemSprite.getGlobalBounds().intersects(playData.level.portalFirstSprite.getGlobalBounds()) ||
				itemSprite.getGlobalBounds().intersects(playData.level.portalSecondSprite.getGlobalBounds()) || 
				itemSprite.getGlobalBounds().intersects(playData.apple.appleSprite.getGlobalBounds()) ||
				itemSprite.getGlobalBounds().intersects(playData.apple.largeAppleSprite.getGlobalBounds()) ||
				itemSprite.getGlobalBounds().intersects(playData.apple.poisonedAppleSprite.getGlobalBounds()) ||
				itemSprite.getGlobalBounds().intersects(playData.apple.reverseAppleSprite.getGlobalBounds()))
			{
				positionValid = false;
			}

			if (playData.level.grid[y][x] == 1)
			{
				positionValid = false;
			}

			iterations++;
		}

		itemSprite.setPosition(x * BLOCK_SIZE, y * BLOCK_SIZE);
	}

	void SnakeSegmentAdd(int count, PlayStateData& playData)
	{
		for (int i = 0; i < count; ++i)
		{
			sf::Sprite newSegment = playData.snake.snakeSegmentSprite;
			newSegment.setPosition(playData.snake.snakeBody.back().getPosition());
			playData.snake.snakeBody.push_back(newSegment);
		}
	}

	bool SerializeGame(const GameData& gameData) {
		std::ofstream file(RECORDS_TABLE_FILE);
		if (file.is_open()) {
			for (const auto& recordItem : gameData.record) {
				file << recordItem.first << " " << recordItem.second << std::endl;
			}
			file.close();
			return true;
		}
		return false;
	}
	bool DeserializeGame(GameData& gameData) {
		std::ifstream file(RECORDS_TABLE_FILE);
		if (file.is_open()) {

			int score;
			std::string name;

			while (file >> score >> name) {
				gameData.record.insert({ score, name });
			}
			file.close();
			return true;
		}
		return false;
	}
}