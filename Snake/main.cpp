#include "GameData.h"
#include <iostream>

using namespace Snake;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake!");
    window.setFramerateLimit(60);

    GameData gameData;
    InitGame(gameData);

    sf::Clock gameClock;
    sf::Time lastTime = gameClock.getElapsedTime();

    while (window.isOpen()) {

        sf::sleep(sf::milliseconds(16));

        gameData.mauseLocalPosition = sf::Mouse::getPosition(window);

        ControlGame(gameData, window);
        
        if (!window.isOpen())
        {
            break;
        }

        sf::Time currentTime = gameClock.getElapsedTime();
        float DeltaTime = currentTime.asSeconds() - lastTime.asSeconds();
        lastTime = currentTime;
    
        if (UpdateGame(gameData, DeltaTime))
        {
            window.clear();
            DrawGame(gameData, window);
            window.display();
        }
        else
        {
            window.close();
        }
    }

    ShutdownGame(gameData);

    return 0;
}


