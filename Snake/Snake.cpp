#include "Snake.h"
#include "GameData.h"

namespace Snake
{
    void InitSnake(SnakeData& data)
    {
        assert(data.snakeHeadTexture.loadFromFile(ASSET_FOLDER + "snake_head.png"));
        assert(data.snakeSegmentTexture.loadFromFile(ASSET_FOLDER + "snake_body.png"));

        data.snakeHeadSprite.setTexture(data.snakeHeadTexture);
        SetSpriteSize(data.snakeHeadSprite, BLOCK_SIZE, BLOCK_SIZE);
        SetSpriteOrigin(data.snakeHeadSprite, 0.5f, 0.5f);

        data.snakeBody.push_back(data.snakeHeadSprite);
        data.snakeBody[0].setPosition(data.snakeX, data.snakeY);
        data.snakeBody[0].setRotation(270.f);

        data.snakeSegmentSprite.setTexture(data.snakeSegmentTexture);
        SetSpriteSize(data.snakeSegmentSprite, BLOCK_SIZE, BLOCK_SIZE);
        SetSpriteOrigin(data.snakeSegmentSprite, 0.5f, 0.5f);
    }

    void UpdateSnake(SnakeData& data, GameData& gameData, PlayStateData& playData, float DeltaTime)
    {
        for (int i = 3; i < data.snakeBody.size(); ++i)
        {
            if (SpriteCollision(data.snakeBody[0], data.snakeBody[i]))
            {
                SoundPlay(gameData.collisionSound, gameData);
                PushGameState(gameData, StateType::EnterName, false);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && data.dir != Down)
        {
            data.nextDir = Up;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && data.dir != Up)
        {
            data.nextDir = Down;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && data.dir != Right)
        {
            data.nextDir = Left;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && data.dir != Left)
        {
            data.nextDir = Right;
        }

        if (++data.moveCounter >= data.moveDelay)
        {
            data.dir = data.nextDir;

            for (int i = data.snakeBody.size(); i < SNAKE_START_SEGMENTS_COUNT; i++)
            {
                data.snakeSegmentSprite.setPosition(data.snakeBody[0].getPosition());
                data.snakeBody.push_back(data.snakeSegmentSprite);
            }

            for (int i = data.snakeBody.size() - 1; i > 0; --i)
            {
                data.snakeBody[i].setPosition(data.snakeBody[i - 1].getPosition());
                data.snakeBody[i].setRotation(data.snakeBody[i - 1].getRotation());
            }

            sf::Vector2f segmentSize(BLOCK_SIZE, BLOCK_SIZE);

            switch (data.dir)
            {
            case Up:
                data.snakeBody[0].move(0, -segmentSize.y);
                data.snakeBody[0].setRotation(270);
                break;
            case Down:
                data.snakeBody[0].move(0, segmentSize.y);
                data.snakeBody[0].setRotation(90);
                break;
            case Left:
                data.snakeBody[0].move(-segmentSize.x, 0);
                data.snakeBody[0].setRotation(180);
                break;
            case Right:
                data.snakeBody[0].move(segmentSize.x, 0);
                data.snakeBody[0].setRotation(0);
                break;
            default:
                break;
            }

            data.moveCounter = 0;
        }
    }

    void DrawSnake(SnakeData& data, sf::RenderWindow& window)
    {
        for (auto& snakeSection : data.snakeBody)
        {
            window.draw(snakeSection);
        }
    }
}
