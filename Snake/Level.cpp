#include "Level.h"
#include "GameData.h"
#include "PlayState.h"

namespace Snake
{
    void InitLevel(LevelData& data)
    {
        assert(data.borderTexture.loadFromFile(ASSET_FOLDER + "Border.png"));
        assert(data.backgroundTexture.loadFromFile(ASSET_FOLDER + "Background.png"));
        assert(data.portalFirstTexture.loadFromFile(ASSET_FOLDER + "portal_first.png"));
        assert(data.portalSecondTexture.loadFromFile(ASSET_FOLDER + "portal_second.png"));
        assert(data.portalBuffer.loadFromFile(ASSET_FOLDER + "Audio/portal.wav"));

        data.grid = std::vector<std::vector<int>>(ROW, std::vector<int>(COL, 0));

        data.portalSound.setBuffer(data.portalBuffer);
        data.portalSound.setVolume(30);

        data.borderSprite.setTexture(data.borderTexture);
        SetSpriteSize(data.borderSprite, BLOCK_SIZE, BLOCK_SIZE);

        data.backgroundSprite.setTexture(data.backgroundTexture);
        data.backgroundSprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
        SetSpriteSize(data.backgroundSprite, WINDOW_WIDTH, WINDOW_HEIGHT);
        SetSpriteOrigin(data.backgroundSprite, 0.5f, 0.5f);

        data.portalFirstSprite.setTexture(data.portalFirstTexture);
        SetSpriteSize(data.portalFirstSprite, BLOCK_SIZE, BLOCK_SIZE);
        SetSpriteOrigin(data.portalFirstSprite, 0.0f, 0.0f);

        data.portalSecondSprite.setTexture(data.portalSecondTexture);
        SetSpriteSize(data.portalSecondSprite, BLOCK_SIZE, BLOCK_SIZE);
        SetSpriteOrigin(data.portalSecondSprite, 0.0f, 0.0f);
    }

    void UpdateLevel(LevelData& data, GameData& gameData, PlayStateData& playData, float DeltaTime)
    {
        if (std::uint8_t(gameData.mods) & std::uint8_t(Mods::Portals)) {

            data.portal_SpawnTimer += DeltaTime;

            if (data.portal_SpawnTimer >= data.portalSpawnInterval)
            {
                data.portal_SpawnTimer = 0.0f;
                data.portal_LifeTime = 0.0f;
                data.firstPortalUsed = false;
                data.secondPortalUsed = false;

                GameItemRespawn(data.portalFirstSprite, playData, data.portalX, data.portalY);
                GameItemRespawn(data.portalSecondSprite, playData, data.portalX, data.portalY);
            }

            if (data.portal_LifeTime < data.portal_LifeTimeDuration)
            {
                data.portal_LifeTime += DeltaTime;
            }
            else
            {
                data.firstPortalUsed = true;
                data.secondPortalUsed = true;
            }

            if (!data.firstPortalUsed)
            {
                if (SpriteCollision(playData.snake.snakeBody[0], data.portalFirstSprite))
                {
                    playData.snake.snakeBody[0].setPosition(data.portalSecondSprite.getPosition().x + BLOCK_SIZE/2, data.portalSecondSprite.getPosition().y + BLOCK_SIZE/2);
                    SoundPlay(data.portalSound, gameData);
                    data.firstPortalUsed = true;
                    data.secondPortalUsed = true;
                }
            }

            if (!data.secondPortalUsed) {
                if (SpriteCollision(playData.snake.snakeBody[0], data.portalSecondSprite))
                {
                    playData.snake.snakeBody[0].setPosition(data.portalFirstSprite.getPosition().x + BLOCK_SIZE/2, data.portalFirstSprite.getPosition().y + BLOCK_SIZE/2);
                    SoundPlay(data.portalSound, gameData);
                    data.secondPortalUsed = true;
                    data.firstPortalUsed = true;
                }
            }
        }

        if (data.grid[playData.snake.snakeBody[0].getPosition().x / BLOCK_SIZE][playData.snake.snakeBody[0].getPosition().y / BLOCK_SIZE] == 1) {
            SoundPlay(gameData.collisionSound, gameData);
            PushGameState(gameData, StateType::EnterName, false);
        }
    }

    void DrawLevel(LevelData& data, GameData& gameData, sf::RenderWindow& window)
    {
        window.draw(data.backgroundSprite);

        if (std::uint8_t(gameData.mods) & std::uint8_t(Mods::Portals)) {
            if (!data.firstPortalUsed && data.portal_LifeTime < data.portal_LifeTimeDuration)
            {
                window.draw(data.portalFirstSprite);
            }
            if (!data.secondPortalUsed && data.portal_LifeTime < data.portal_LifeTimeDuration) 
            {
                window.draw(data.portalSecondSprite);
            }
        }

        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                if (i == 0 || i == ROW - 1 || j == 0 || j == COL - 1) {
                    data.grid[i][j] = 1;
                    data.borderSprite.setPosition(sf::Vector2f(j * BLOCK_SIZE, i * BLOCK_SIZE));
                    window.draw(data.borderSprite);
                }
                
            }
        }
    }
}
