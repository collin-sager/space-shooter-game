// standard libraries
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

// SFML libraries
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "bullet.h"
#include "constants.h"

using namespace std;
using namespace sf;

Bullet::Bullet(double x, double y, double direction) {

    // set initial properties
    _bullet.setRadius(BULLET_RADIUS);
    _bullet.setOrigin(BULLET_RADIUS,BULLET_RADIUS);
    _bullet.setFillColor(Color::Yellow);
    setMaxVelocity(BULLET_VELOCITY);

    // transformation needed due to axis used by SFML
    double tempVelocityX = BULLET_VELOCITY*sin((180-direction)/DEGREES_PER_RADIAN);
    double tempVelocityY = BULLET_VELOCITY*cos((180-direction)/DEGREES_PER_RADIAN);

    // set velocity
    setVelocityX(tempVelocityX);
    setVelocityY(tempVelocityY);

    // set initial position and advance from center of ship
    // so bullet "comes out of tip of spaceship"
    setPositionX(x+3*tempVelocityX);
    setPositionY(y+3*tempVelocityY);

    // get time when bullet is created
    _spawnTime = bulletClock.getElapsedTime();
}

void Bullet::draw(sf::RenderWindow &window) {

    // CALLED EVERY FRAME!

    // perform position change and then draw to screen
    _bullet.setPosition(getPosition().X, getPosition().Y);
    window.draw(_bullet);
}

bool Bullet::removeBullet() const {

    // CALLED EVERY FRAME!

    // if time elapsed since spawn is greater than lifetime, remove
    Time currentTime = bulletClock.getElapsedTime();
    if((currentTime - _spawnTime).asMilliseconds() > BULLET_ACTIVE_TIME)
        return true;
    else
        return false;
}