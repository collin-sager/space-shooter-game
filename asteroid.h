// standard libraries
#include <iostream>

// SFML libraries
#include <SFML/Graphics.hpp>
#include "XYData.h"
#include "kinematics.h"

#ifndef ASTEROID_H
#define ASTEROID_H

/**
 * @brief this class constructs all sizes of asteroids and 
 * assigns their kinematic properties and appearance
 */
class Asteroid : public Kinematics {

public:

    /**
     * @brief parameterized constructor
     * @param size large medium or small
     * @param x x location of spawn if applicable
     * @param y y location of spawn if applicable
     * @param levelNum to be used for increasing asteroid speed
     * as game goes on
     */
    Asteroid(char size, double x, double y, int levelNum);

    /**
     * @brief draws asteroid
     * @param window where to draw
     */
    void draw(sf::RenderWindow &window);

    /**
     * @brief spawns asteroid in random location away from center 
     * at beginning of game
     */
    XYData spawnRandomAsteroid();

    /**
     * @brief getter
     */
    char getSize() const;

    /**
     * @brief setter
     */
    void setSize(char size);
    
private:

    sf::CircleShape _asteroid;  // spaceship object
    char _size; // large medium or small

};

#endif // ASTEROID_H

