// standard libraries
#include <iostream>
#include <vector>

// SFML libraries
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

// program header files
#include "spaceship.h"
#include "asteroid.h"
#include "gamedisplay.h"
#include "bullet.h"


#ifndef GAME_H
#define GAME_H

/**
 * @brief performs all actions to play game and calls other classes where needed
 */
class Game {

public:

    /**
     * @brief default constructor
     */
    Game(); 

    /**
     * @brief calls loops of all major game functions and displays
     * @param window where to display
     * @param event used for getting user input
     */
    bool go(sf::RenderWindow &window, sf::Event &event); 

    /**
     * @brief performs functions when a level starts (sets timers, clears bullets,
     * resets various booleans, moves spaceship to center of screen)
     */
    void startLevel();

    /**
     * @brief performs functions when a level ends (increments level)
     */
    void endLevel();

    /**
     * @brief updates _keys vector when keys needed in game are pressed or released
     * @param window only used for closing window in this function
     * @param event used for getting user input
     */
    void getUserInput(sf::RenderWindow &window, sf::Event &event);

    /**
     * @brief performs appropriate actions when user presses keys (moves spaceship, starts/ends game, etc.
     * @param window to change
     * @param used for processing user inputs
     */
    int processUserInput(sf::RenderWindow &window, sf::Event &event); // toggle keys/mouse that are pressed/released

    /**
     * @brief tests for collisions between spaceship/asteroids and bullets/asteroids.
     * removes objects appropriately after collisions or decrements lives
     */
    void collisionTest();

    /**
     * @brief shoots a bullet from spaceship
     */
    void shoot();

    /**
     * @brief removes bullet from screen after bullet lifespan has passed
     */
    void removeBullets();

    /**
     * @brief forces framerate to 60 FPS with sleep()
     */
    void enforceFramerate();

    /**
     * @brief allows key state to be accessed outside of object
     */
    std::vector<bool> getKeys() const;

    /**
     * @brief at end of game, allows user to input their name for display on scoreboard
     */
    void writeUserName();

private:

    // user input/controls: true if clicked/pressed
        std::vector<bool> _keys; // A-Z = 0-25; Enter = 26; Escape = 27; Space = 28
        bool _mouse; 

    // display objects
        Spaceship _spaceship; // the object the user controls
        std::vector<Asteroid> _asteroidList; // vector of asteroids
        std::vector<Bullet> _bulletList;  // vector of bullets
        GameDisplay gameDisplay; // displays home/game over screen, level, score, lives

    // gameplay attributes/data
        // time objects
        sf::Clock programClock;
        sf::Time _lastTime;
        sf::Time _currentTime;

        // various booleans
        bool _reloaded; // prevents user from shooting by holding down space/click
        bool _levelDone; // used to start new levels
        bool _quit; // used to exit game
        bool _restart; // used to restart game from game over screen
        bool _previousWasUnpressed; // used to make sure user enters one letter at a time in writeUserName()

        // game data
        int _score; // users score
        int _lives; // users lives
        int _levelNumber; // current level number
        int _previousPositionPressed; // used to make sure user enters one letter at a time in writeUserName()

        std::string _name; // users name entered at end of game
        
};

#endif // GAME_H
