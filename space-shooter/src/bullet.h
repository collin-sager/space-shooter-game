#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "XYData.h"
#include "kinematics.h"

#ifndef BULLET_H
#define BULLET_H

/**
 * @brief this class constructs all bullets and assigns their kinematic
 * properties and appearance
 */
class Bullet : public Kinematics {

public:

    /**
     * @brief parameterized constructor
     * @param x x location of spawn
     * @param y y location of spawn
     * @param direction direction bullet will move
     */
    Bullet(double x, double y, double direction);

    /**
     * @brief draws bullet
     * @param window where to draw
     */
    void draw(sf::RenderWindow &window);

    /**
     * @brief bullets exist for finite time, checks state of bullet objects to see if 
     * they have existed longer than their lifespan.  function is called from game.cpp
     * to see if bullets should be removed from vector there
     * @return whether or not bullet should be removed
     */
    bool removeBullet() const;

private:

    sf::CircleShape _bullet; // object

    sf::Clock bulletClock; // timer

    sf::Time _spawnTime; // time at which bullet was spawned

};


#endif // BULLET_H