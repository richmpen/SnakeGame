#include "GameData.h"


namespace Snake
{
    void InitGame(GameData& gameData)
    {
		assert(gameData.selectSoundBuffer.loadFromFile(ASSET_FOLDER + "Audio/select.wav"));
		assert(gameData.collisionBaffer.loadFromFile(ASSET_FOLDER + "Audio/collision.wav"));

		DeserializeGame(gameData);

		gameData.collisionSound.setBuffer(gameData.collisionBaffer);
		gameData.collisionSound.setVolume(20);
		gameData.selectSound.setBuffer(gameData.selectSoundBuffer);
		gameData.selectSound.setVolume(20);

		gameData.stateSwitch = StateSwitch::None;
		gameData.pauseState = StateType::None;
		gameData.pauseStateIsVisible = false;

        SwitchGameState(gameData, StateType::MainMenu);
    }

    void ControlGame(GameData& gameData, sf::RenderWindow& window)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (gameData.stateStack.size() > 0)
            {
                ControlWindowEventGameState(gameData, gameData.stateStack.back(), event);
            }
        }
    }

    bool UpdateGame(GameData& gameData, float DeltaTime)
    {
        if (gameData.stateSwitch == StateSwitch::Switch)
        {
            while (gameData.stateStack.size() > 0)
            {
                ShutdownGameState(gameData, gameData.stateStack.back());
                gameData.stateStack.pop_back();
            }
        }
        else if (gameData.stateSwitch == StateSwitch::Pop)
        {
            if (gameData.stateStack.size() > 0)
            {
                ShutdownGameState(gameData, gameData.stateStack.back());
                gameData.stateStack.pop_back();
            }
        }

		if (gameData.pauseState != StateType::None)
		{
			gameData.stateStack.push_back({ gameData.pauseState, nullptr, gameData.pauseStateIsVisible });
			InitGameState(gameData, gameData.stateStack.back());
		}

		gameData.stateSwitch = StateSwitch::None;
		gameData.pauseState = StateType::None;
		gameData.pauseStateIsVisible = false;

		if (gameData.stateStack.size() > 0)
		{
			UpdateGameState(gameData, gameData.stateStack.back(), DeltaTime);
			return true;
		}

		return false;
    }

	

    void DrawGame(GameData& gameData, sf::RenderWindow& window)
    {
        if (gameData.stateStack.size() > 0)
        {
            std::vector<StateData*> visibleGameStates;
            for (auto it = gameData.stateStack.rbegin(); it != gameData.stateStack.rend(); ++it)
            {
                visibleGameStates.push_back(&(*it));
                if (it->isVisible)
                {
                    break;
                }
            }

            for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
            {
                DrawGameState(gameData, **it, window);
            }
        }
    }

	void ShutdownGame(GameData& gameData)
	{
		while (gameData.stateStack.size() > 0)
		{
			ShutdownGameState(gameData, gameData.stateStack.back());
			gameData.stateStack.pop_back();
		}

		gameData.stateSwitch = StateSwitch::None;
		gameData.pauseState = StateType::None;
		gameData.pauseStateIsVisible = false;
	}

	void PushGameState(GameData& gameData, StateType state, bool isVisible)
	{
		gameData.pauseState = state;
		gameData.pauseStateIsVisible = isVisible;
		gameData.stateSwitch = StateSwitch::Push;
	}

	void PopGameState(GameData& gameData)
	{
		gameData.pauseState = StateType::None;
		gameData.pauseStateIsVisible = false;
		gameData.stateSwitch = StateSwitch::Pop;
	}

	void SwitchGameState(GameData& gameData, StateType newState)
	{
		gameData.pauseState = newState;
		gameData.pauseStateIsVisible = false;
		gameData.stateSwitch = StateSwitch::Switch;
	}

	void InitGameState(GameData& gameData, StateData& state)
	{
		switch (state.type)
		{
		case StateType::MainMenu:
		{
			state.data = new MainMenuData();
			InitMainMenu(*(MainMenuData*)state.data, gameData );
			break;
		}
		case StateType::Play:
		{
			state.data = new PlayStateData();
			InitPlayState(*(PlayStateData*)state.data, gameData);
			break;
		}
		case StateType::GameOver:
		{
			state.data = new GameOverData();
			InitGameOver(*(GameOverData*)state.data, gameData);
			break;
		}
		case StateType::GameWin:
		{
			state.data = new GameWinData();
			InitGameWin(*(GameWinData*)state.data, gameData);
			break;
		}
		case StateType::EnterName:
		{
			state.data = new EnterNameData();
			InitEnterName(*(EnterNameData*)state.data, gameData);
			break;
		}
		case StateType::Pause:
		{
			state.data = new PauseDialogData();
			InitPauseDialog(*(PauseDialogData*)state.data, gameData);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void ShutdownGameState(GameData& gameData, StateData& state)
	{
		switch (state.type)
		{
		case StateType::MainMenu:
		{
			ShutdownMainMenu(*(MainMenuData*)state.data, gameData);
			delete (MainMenuData*)state.data;
			break;
		}
		case StateType::Play:
		{
			ShutdownPlayState(*(PlayStateData*)state.data, gameData);
			delete (PlayStateData*)state.data;
			break;
		}
		case StateType::GameOver:
		{
			ShutdownGameOver(*(GameOverData*)state.data, gameData);
			delete (GameOverData*)state.data;
			break;
		}
		case StateType::GameWin:
		{
			ShutdownGameWin(*(GameWinData*)state.data, gameData);
			delete (GameWinData*)state.data;
			break;
		}
		case StateType::EnterName:
		{
			ShutdownEnterName(*(EnterNameData*)state.data, gameData);
			delete (EnterNameData*)state.data;
			break;
		}
		case StateType::Pause:
		{
			ShutdownPauseDialog(*(PauseDialogData*)state.data, gameData);
			delete (PauseDialogData*)state.data;
			break;
		}
		default:
			assert(false);
			break;
		}

		state.data = nullptr;
	}

	void ControlWindowEventGameState(GameData& gameData, StateData& state, sf::Event& event)
	{
		switch (state.type)
		{
		case StateType::MainMenu:
		{
			ControlMainMenu(*(MainMenuData*)state.data, gameData, event);
			break;
		}
		case StateType::Play:
		{
			ControlPlayState(*(PlayStateData*)state.data, gameData, event);
			break;
		}
		case StateType::GameOver:
		{
			ControlGameOver(*(GameOverData*)state.data, gameData, event);
			break;
		}
		case StateType::GameWin:
		{
			ControlGameWin(*(GameWinData*)state.data, gameData, event);
			break;
		}
		case StateType::EnterName:
		{
			ControlEnterName(*(EnterNameData*)state.data, gameData, event);
			break;
		}
		case StateType::Pause:
		{
			ControlPauseDialog(*(PauseDialogData*)state.data, gameData, event);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void UpdateGameState(GameData& gameData, StateData& state, float DeltaTime)
	{
		switch (state.type)
		{
		case StateType::MainMenu:
		{
			UpdateMainMenu(*(MainMenuData*)state.data, gameData, DeltaTime);
			break;
		}
		case StateType::Play:
		{
			UpdatePlayState(*(PlayStateData*)state.data, gameData, DeltaTime);
			break;
		}
		case StateType::GameOver:
		{
			UpdateGameOver(*(GameOverData*)state.data, gameData, DeltaTime);
			break;
		}
		case StateType::GameWin:
		{
			UpdateGameWin(*(GameWinData*)state.data, gameData, DeltaTime);
			break;
		}
		case StateType::EnterName:
		{
			UpdateEnterName(*(EnterNameData*)state.data, gameData, DeltaTime);
			break;
		}
		case StateType::Pause:
		{
			UpdatePauseDialog(*(PauseDialogData*)state.data, gameData, DeltaTime);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void DrawGameState(GameData& gameData, StateData& state, sf::RenderWindow& window)
	{
		switch (state.type)
		{
		case StateType::MainMenu:
		{
			DrawMainMenu(*(MainMenuData*)state.data, gameData, window);
			break;
		}
		case StateType::Play:
		{
			DrawPlayState(*(PlayStateData*)state.data, gameData, window);
			break;
		}
		case StateType::GameOver:
		{
			DrawGameOver(*(GameOverData*)state.data, gameData, window);
			break;
		}
		case StateType::GameWin:
		{
			DrawGameWin(*(GameWinData*)state.data, gameData, window);
			break;
		}
		case StateType::EnterName:
		{
			DrawEnterName(*(EnterNameData*)state.data, gameData, window);
			break;
		}
		case StateType::Pause:
		{
			DrawPauseDialog(*(PauseDialogData*)state.data, gameData, window);
			break;
		}
		default:
			assert(false);
			break;
		}
	}
}
