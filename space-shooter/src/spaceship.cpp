// standard libraries
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

// SFML libraries
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

// program header files
#include "spaceship.h"
#include "constants.h"


// namespaces
using namespace std;
using namespace sf;

Spaceship::Spaceship() {

    _invincible = true; // start levels and lives invincible
    _lifeStartTime = spaceshipClock.getElapsedTime(); // log time level or life starts

    // set initial kinematic data
    setRadius(SPACESHIP_RADIUS);
    setVelocityX(0);
    setVelocityY(0);
    setAccelerationX(0);
    setAccelerationY(0);
    setDeceleration(SPACESHIP_DECELERATION);
    setRotation(180);
    setMaxVelocity(SPACESHIP_MAX_VELOCITY);

    // spaceship attributes
    _spaceship.setPointCount(4);
    _spaceship.setOrigin(13,20);
    _spaceship.setPoint(0, Vector2f(0,0));
    _spaceship.setPoint(1, Vector2f(13,5));
    _spaceship.setPoint(2, Vector2f(26,0));
    _spaceship.setPoint(3, Vector2f(13,40));
    
    _spaceship.setFillColor(Color::Transparent);
    _spaceship.setOutlineThickness(2);
    _spaceship.setOutlineColor(Color::Blue);
}

void Spaceship::pointAtMouse(sf::Vector2i mousePosition) {

    // CALLED EVERY FRAME!

    // get angle between mouse position and spaceship position using atan(Dx/Dy)
    if (mousePosition.y != getPosition().Y) // avoid division by 0
        mouseSpaceshipAngle = DEGREES_PER_RADIAN*atan( (mousePosition.x - getPosition().X) / (mousePosition.y - getPosition().Y) );

    // deal with bounds of atan function by adjusting angle based on quadrant
    if((mousePosition.y - getPosition().Y) < 0) {
        mouseSpaceshipAngle = -mouseSpaceshipAngle;
    } else {
        mouseSpaceshipAngle = 180-mouseSpaceshipAngle;
    }
 
    // perform INCREMENTAL rotation: only rotate spaceship by difference between current direction and where mouse is
    _spaceship.rotate(mouseSpaceshipAngle - getRotation());

    // update current rotation value to reflect new state
    setRotation(mouseSpaceshipAngle);
}

void Spaceship::draw(sf::RenderWindow &window) {

    // CALLED EVERY FRAME!

    // update position of spacehip
     _spaceship.setPosition(getPosition().X, getPosition().Y);

    // if spaceship is invincible, it will blink
    
    sf::Time currentTime = spaceshipClock.getElapsedTime(); // get current time
    int timeSinceLifeStart = (currentTime - _lifeStartTime).asMilliseconds(); // get time in level or life

    invincibilityCheck(timeSinceLifeStart); // check to see if spaceship is still invincible

    // if it is, display half the time (200 ms on, 200 ms off)
    if(_invincible) {
        if((timeSinceLifeStart % 400 ) < 200 ) { window.draw(_spaceship); } 
    }
    else { // if not invincible, always draw
        window.draw(_spaceship);
    }
}

void Spaceship::invincibilityCheck(double timeSinceLifeStart) {

    // if more time has passed than the allotted invincibility time, set to not invincible
    if(timeSinceLifeStart <= INVINCIBLE_DURATION)
        _invincible = true;

    else
        _invincible = false;
}

// getters
bool Spaceship::getInvincibility() const      { return _invincible;    }
sf::Time  Spaceship::getLifeStartTime() const { return _lifeStartTime; }

// setters
void Spaceship::setInvinvibility(bool state) { _invincible = state; }
void Spaceship::setLifeStartTime(sf::Time currentTime) { _lifeStartTime = currentTime; }