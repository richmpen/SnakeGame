#pragma once
#include "Mathematics.h"

namespace Snake
{
    struct GameData;
    struct PlayStateData;

    struct LevelData {
        std::vector<std::vector<int>> grid;

        sf::Texture borderTexture;
        sf::Sprite borderSprite;

        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;

        sf::SoundBuffer portalBuffer;
        sf::Sound portalSound;

        float portalX = 0.f;
        float portalY = 0.f;

        sf::Texture portalFirstTexture;
        sf::Sprite portalFirstSprite;

        sf::Texture portalSecondTexture;
        sf::Sprite portalSecondSprite;

        bool firstPortalUsed = false;
        bool secondPortalUsed = false;

        float portal_SpawnTimer = 0.0f;
        float portal_LifeTime = 0.0f;
        float portalSpawnInterval = PORTAL_SPAWN_INTERVAL;
        float portal_LifeTimeDuration = PORTAL_LIFE_TIME_DURATION;
    };

    void InitLevel(LevelData& data);
    void UpdateLevel(LevelData& data, GameData& gameData, PlayStateData& playData, float DeltaTime);
    void DrawLevel(LevelData& data, GameData& gameData, sf::RenderWindow& window);
}
