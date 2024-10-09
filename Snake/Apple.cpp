#include "Apple.h"
#include "GameData.h"
#include "PlayState.h"
#include "Mathematics.h"

namespace Snake
{
    void InitApple(AppleData& data, PlayStateData& playData, GameData& gameData)
    {
        assert(data.appleTexture.loadFromFile(ASSET_FOLDER + "Apple.png"));
        assert(data.eatBuffer.loadFromFile(ASSET_FOLDER + "Audio/eat.wav"));

        data.eatSound.setBuffer(data.eatBuffer);

        data.appleSprite.setTexture(data.appleTexture);
        SetSpriteSize(data.appleSprite, BLOCK_SIZE, BLOCK_SIZE);
        SetSpriteOrigin(data.appleSprite, 0.f, 0.f);

        assert(data.largeAppleTexture.loadFromFile(ASSET_FOLDER + "largeApple.png"));
        assert(data.poisonedAppleTexture.loadFromFile(ASSET_FOLDER + "poisonedApple.png"));
        assert(data.reverseAppleTexture.loadFromFile(ASSET_FOLDER + "reverseApple.png"));

        data.largeAppleSprite.setTexture(data.largeAppleTexture);
        SetSpriteSize(data.largeAppleSprite, BLOCK_SIZE, BLOCK_SIZE);
        SetSpriteOrigin(data.largeAppleSprite, 0.f, 0.f);

        data.poisonedAppleSprite.setTexture(data.poisonedAppleTexture);
        SetSpriteSize(data.poisonedAppleSprite, BLOCK_SIZE, BLOCK_SIZE);
        SetSpriteOrigin(data.poisonedAppleSprite, 0.f, 0.f);

        data.reverseAppleSprite.setTexture(data.reverseAppleTexture);
        SetSpriteSize(data.reverseAppleSprite, BLOCK_SIZE, BLOCK_SIZE);
        SetSpriteOrigin(data.reverseAppleSprite, 0.f, 0.f);

        data.poisonedApple_DebuffSpeed = 0;
    }



    void UpdateApple(AppleData& data, GameData& gameData, PlayStateData& playData, float DeltaTime)
    {

        if (SpriteCollision(playData.snake.snakeBody[0], data.appleSprite))
        {
            GameItemRespawn(data.appleSprite, playData, data.appleX, data.appleY);
            SoundPlay(data.eatSound, gameData);
            SnakeSegmentAdd(SNAKE_SEGMENTS_ADD, playData);
            gameData.snakeScore += gameData.extraPoints;
        }

        if (std::uint8_t(gameData.mods) & std::uint8_t(Mods::AppleMod)) {

            data.apple_SpawnTimer += DeltaTime;
            data.specialAppleTimer -= DeltaTime;

            if (!data.specialAppleOnField && data.apple_SpawnTimer >= APPLE_MOD_SPAWN_INTERVAL)
            {
                data.apple_SpawnTimer = 0.f;
                data.specialAppleOnField = true;
                data.specialAppleTimer = APPLE_MOD_TIMER_INTERVAL;

                data.activeSpecialApple = rand() % 3;
                switch (data.activeSpecialApple)
                {
                case 0:
                    GameItemRespawn(data.largeAppleSprite, playData, data.appleX, data.appleY);
                    break;
                case 1:
                    GameItemRespawn(data.poisonedAppleSprite, playData, data.appleX, data.appleY);
                    break;
                case 2:
                    GameItemRespawn(data.reverseAppleSprite, playData, data.appleX, data.appleY);
                    break;
                }
            }

            if (data.specialAppleTimer <= 0.f && data.specialAppleOnField)
            {
                data.specialAppleOnField = false;
                data.specialAppleTimer = 0.f;
                data.activeSpecialApple = -1;
            }

            if (data.activeSpecialApple == 0 && SpriteCollision(playData.snake.snakeBody[0], data.largeAppleSprite))
            {
                GameItemRespawn(data.largeAppleSprite, playData, data.appleX, data.appleY);
                SoundPlay(data.eatSound, gameData);
                SnakeSegmentAdd(SNAKE_SEGMENTS_ADD, playData);
                gameData.snakeScore += gameData.extraPoints * LARGE_APPLE_SCORE_BONUS_MULTIPLIER;
                data.specialAppleOnField = false;
                data.activeSpecialApple = -1;
            }

            if (data.activeSpecialApple == 1 && SpriteCollision(playData.snake.snakeBody[0], data.poisonedAppleSprite))
            {
                GameItemRespawn(data.poisonedAppleSprite, playData, data.appleX, data.appleY);
                SoundPlay(data.eatSound, gameData);
                SnakeSegmentAdd(SNAKE_SEGMENTS_ADD, playData);
                gameData.snakeScore += gameData.extraPoints;
                data.poisonedApple_TimerEffect = POISONED_APPLE_TIMER_EFFECT;
                data.poisonedApple_DebuffSpeed = POISONED_APPLE_DEBUFF_SPEED;
                data.specialAppleOnField = false;
                data.activeSpecialApple = -1;
            }

            if (data.activeSpecialApple == 2 && SpriteCollision(playData.snake.snakeBody[0], data.reverseAppleSprite))
            {
                GameItemRespawn(data.reverseAppleSprite, playData, data.appleX, data.appleY);
                SoundPlay(data.eatSound, gameData);
                SnakeSegmentAdd(SNAKE_SEGMENTS_ADD, playData);
                gameData.snakeScore += gameData.extraPoints;
                data.reverseApple_TimerEffect = REVERSE_APPLE_TIMER_EFFECT;
                data.specialAppleOnField = false;
                data.activeSpecialApple = -1;
            }

            data.poisonedApple_TimerEffect -= DeltaTime;
            data.reverseApple_TimerEffect -= DeltaTime;

            if (data.poisonedApple_TimerEffect <= 0.f)
            {
                data.poisonedApple_DebuffSpeed = 0;
            }

            if (data.reverseApple_TimerEffect > 0.f)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && playData.snake.dir != Up)
                {
                    playData.snake.nextDir = Down;
                    playData.snake.dir = Down;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && playData.snake.dir != Down)
                {
                    playData.snake.nextDir = Up;
                    playData.snake.dir = Up;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && playData.snake.dir != Left)
                {
                    playData.snake.nextDir = Right;
                    playData.snake.dir = Right;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && playData.snake.dir != Right)
                {
                    playData.snake.nextDir = Left;
                    playData.snake.dir = Left;
                }
            }
            else
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && playData.snake.dir != Down)
                {
                    playData.snake.nextDir = Up;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && playData.snake.dir != Up)
                {
                    playData.snake.nextDir = Down;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && playData.snake.dir != Right)
                {
                    playData.snake.nextDir = Left;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && playData.snake.dir != Left)
                {
                    playData.snake.nextDir = Right;
                }
            }
        }
    }



    void DrawApple(AppleData& data, GameData& gameData, sf::RenderWindow& window)
    {
        window.draw(data.appleSprite);

        if (std::uint8_t(gameData.mods) & std::uint8_t(Mods::AppleMod)) {
            if (data.specialAppleOnField)
            {
                switch (data.activeSpecialApple)
                {
                case 0:
                    window.draw(data.largeAppleSprite);
                    break;
                case 1:
                    window.draw(data.poisonedAppleSprite);
                    break;
                case 2:
                    window.draw(data.reverseAppleSprite);
                    break;
                }
            }
        }

       
    }






}
