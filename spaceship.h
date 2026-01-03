// standard libraries
#include <iostream>

// SFML libraries
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "XYData.h"
#include "kinematics.h"

#ifndef SPACESHIP_H
#define SPACESHIP_H

class Spaceship : public Kinematics {

public:


    /**
     * @brief contains all actions and properties unique to spaceships. 
     * this is the default constructor
     */
    Spaceship();

    /**
     * @brief applies rotation to the spaceship such that it points to wherever
     * mouse pointer is on screen.  used to aim for shooting
     * @param mousePosition x/y coordinates of the mouse relative to window
     */
    void pointAtMouse(sf::Vector2i mousePosition);

    /**
     * @brief draws spaceship
     * @param window where to display
     */
    void draw(sf::RenderWindow &window);

    /**
     * @brief stops collisions from causing player to lose a life, purpose is
     * for "fair" spawning during middle of a level
     */
    void invincibilityCheck(double timeSinceLifeStart);

    /**
     * @brief getters: life start time and invincibility status are a property of the
     * spacehip but are used outside of the class (see game.cpp)
     */
    sf::Time getLifeStartTime() const; 
    bool getInvincibility() const;

    /**
     * @brief setters
     */
    void setInvinvibility(bool state);
    void setLifeStartTime(sf::Time currentTime);
    
private:

    // objects/structs
    sf::ConvexShape _spaceship; // spaceship object

    // kinematic data specific to spaceship
    double mouseSpaceshipAngle;

    // time elements
    sf::Clock spaceshipClock;
    sf::Time _lifeStartTime;

    bool _invincible; // whether or not spaceship is invincible

};

#endif // SPACESHIP_H

