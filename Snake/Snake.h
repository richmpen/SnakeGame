#pragma once
#include "Mathematics.h"

namespace Snake
{
    struct GameData;
    struct PlayStateData;

    enum Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    struct SnakeData
    {
        std::vector<sf::Sprite> snakeBody;

        Direction dir = Up;
        Direction nextDir = Up;

        int snakeX = ROW * 20 + 20;
        int snakeY = COL * 20 + 20;

        sf::Texture snakeHeadTexture;
        sf::Sprite snakeHeadSprite;

        sf::Texture snakeSegmentTexture;
        sf::Sprite snakeSegmentSprite;

        int moveDelay;
        int moveCounter = 0;
    };

    void InitSnake(SnakeData& data);
    void UpdateSnake(SnakeData& data, GameData& gameData, PlayStateData& playData, float DeltaTime);
    void DrawSnake(SnakeData& data, sf::RenderWindow& window);
}
