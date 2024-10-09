#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Const.h"
#include "Mathematics.h"
#include <assert.h>
#include "MenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "GameWinState.h"
#include "EnterNameState.h"
#include <fstream>



namespace Snake
{
    enum class Difficulty : std::uint8_t
    {
        Simple = 1 << 0,
        HarderSimple = 1 << 1,
        Medium = 1 << 2,
        EasierHard = 1 << 3,
        Hard = 1 << 4,

        Default = Simple,
        Empty = 0
    };

    enum class Settings : std::uint8_t
    {
        Sound = 1 << 0,
        Music = 1 << 1,

        Default = Sound | Music,
        Empty = 0
    };

    enum class Mods : std::uint8_t
    {
        AppleMod = 1 << 0,
        Portals = 1 << 1,

        Empty = 0
    };

    enum class StateSwitch
    {
        None,
        Push,
        Pop,
        Switch,
    };

    enum class StateType
    {
        None = 0,
        MainMenu,
        Play,
        Pause,
        GameOver,
        GameWin,
        EnterName,
    };

    struct StateData
    {
        StateType type = StateType::None;
        void* data = nullptr;
        bool isVisible = false;
    };

    struct GameData
    {
        std::string playerName;
        bool GameWin = false;

        std::multimap<int, std::string> record;
        int snakeScore = 0;
        int extraPoints = 0;

        Difficulty difficulty = Difficulty::Default;
        Settings settings = Settings::Default;
        Mods mods = Mods::Empty;

        std::vector<StateData> stateStack;
        StateSwitch stateSwitch = StateSwitch::None;
        StateType pauseState = StateType::None;
        bool pauseStateIsVisible = false;
        
        sf::SoundBuffer collisionBaffer;
        sf::Sound collisionSound;

        sf::SoundBuffer selectSoundBuffer;
        sf::Sound selectSound;

        sf::Vector2i mauseLocalPosition;
    };


    void InitGame(GameData& gameData);
    void ControlGame(GameData& gameData, sf::RenderWindow& window);
    bool UpdateGame(GameData& gameData, float DeltaTime);
    void DrawGame(GameData& gameData, sf::RenderWindow& window);
    void ShutdownGame(GameData& gameData);

    void PushGameState(GameData& gameData, StateType state, bool isVisible);
    void PopGameState(GameData& gameData);
    void SwitchGameState(GameData& gameData, StateType newState);

    void InitGameState(GameData& gameData, StateData& state);
    void ShutdownGameState(GameData& gameData, StateData& state);
    void ControlWindowEventGameState(GameData& gameData, StateData& state, sf::Event& event);
    void UpdateGameState(GameData& gameData, StateData& state, float DeltaTime);
    void DrawGameState(GameData& gameData, StateData& state, sf::RenderWindow& window);
}