#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Const.h"

namespace Snake
{
    struct GameData;
    struct PlayStateData;
    struct AppleData
    {
        float appleX = 0.f;
        float appleY = 0.f;

        sf::Texture appleTexture;
        sf::Sprite appleSprite;

        sf::Texture largeAppleTexture;
        sf::Sprite largeAppleSprite;

        sf::Texture poisonedAppleTexture;
        sf::Sprite poisonedAppleSprite;
        float poisonedApple_TimerEffect = 0.f;
        float poisonedApple_DebuffSpeed = 0;

        sf::Texture reverseAppleTexture;
        sf::Sprite reverseAppleSprite;
        float reverseApple_TimerEffect = 0.f;

        sf::SoundBuffer eatBuffer;
        sf::Sound eatSound;

        float apple_SpawnTimer = 0.f;
        float specialAppleTimer = 0.f;
        bool specialAppleOnField = false;
        int activeSpecialApple = -1;
    };

    void InitApple(AppleData& data, PlayStateData& playData, GameData& gameData);
    void UpdateApple(AppleData& data, GameData& gameData, PlayStateData& playData, float DeltaTime);
    void DrawApple(AppleData& data, GameData& gameData, sf::RenderWindow& window);
}
