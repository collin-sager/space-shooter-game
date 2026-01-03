// standard libraries
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

// SFML libraries
#include <SFML/Graphics.hpp>

// program header files
#include "asteroid.h"
#include "constants.h"

// namespaces
using namespace std;
using namespace sf;

Asteroid::Asteroid(char size, double x, double y, int levelNum) {

    // called when any new asteroid is instantiated

    // initialize kinematics for all asteroid types
    setAccelerationX(0);
    setAccelerationY(0);
    setDeceleration(0);
    setRotation(0);

    // initializeation of large asteroid
    if(size == 'L') { 

        _size = 'L'; // update private size

        // start position is random
        XYData initialPosition = spawnRandomAsteroid(); 
        setPositionX( initialPosition.X );
        setPositionY( initialPosition.Y );

        // assign random velocity
        setVelocityX((1.0*rand()/RAND_MAX)*ASTEROID_MAX_VELOCITY_L-(ASTEROID_MAX_VELOCITY_L/2)); 
        setVelocityY((1.0*rand()/RAND_MAX)*ASTEROID_MAX_VELOCITY_L-(ASTEROID_MAX_VELOCITY_L/2)); 

        // add velocity boost at higher levels. separate from above because sign dependent
        if(getVelocity().X > 0) { setVelocityX(getVelocity().X + levelNum/10); }
        else                    { setVelocityY(getVelocity().X - levelNum/10); }

        if(getVelocity().Y > 0) { setVelocityY(getVelocity().Y + levelNum/10); }
        else                    { setVelocityY(getVelocity().Y - levelNum/10); }

        // set other data
        setMaxVelocity(ASTEROID_MAX_VELOCITY_L);
        setRadius(ASTEROID_RADIUS_L); 
        _asteroid.setRadius(ASTEROID_RADIUS_L);
        _asteroid.setOrigin(ASTEROID_RADIUS_L, ASTEROID_RADIUS_L);
    }

    if(size == 'M') { 
        
        _size = 'M'; // update private size

        // position is set to location of previous asteroid (large turns to medium)
        setPositionX( x );
        setPositionY( y );

        // assign random velocity
        setVelocityX((1.0*rand()/RAND_MAX)*ASTEROID_MAX_VELOCITY_M-(ASTEROID_MAX_VELOCITY_M/2)); 
        setVelocityY((1.0*rand()/RAND_MAX)*ASTEROID_MAX_VELOCITY_M-(ASTEROID_MAX_VELOCITY_M/2));

        // add velocity boost at higher levels. separate from above because sign dependent
        if(getVelocity().X > 0) { setVelocityX(getVelocity().X + levelNum/8); }
        else                    { setVelocityX(getVelocity().X - levelNum/8); }

        if(getVelocity().Y > 0) { setVelocityY(getVelocity().Y + levelNum/8); }
        else                    { setVelocityY(getVelocity().Y - levelNum/8); }

        // set other data
        setMaxVelocity(ASTEROID_MAX_VELOCITY_M);
        setRadius(ASTEROID_RADIUS_M); // assign radius
        _asteroid.setRadius(ASTEROID_RADIUS_M);
        _asteroid.setOrigin(ASTEROID_RADIUS_M, ASTEROID_RADIUS_M);
    }

    if(size == 'S') { 

        _size = 'S'; // update private size

        // position is set to location of previous asteroid (medium turns to small)
        setPositionX( x );
        setPositionY( y );

        // assign random velocity
        setVelocityX((1.0*rand()/RAND_MAX)*ASTEROID_MAX_VELOCITY_S-(ASTEROID_MAX_VELOCITY_S/2)); 
        setVelocityY((1.0*rand()/RAND_MAX)*ASTEROID_MAX_VELOCITY_S-(ASTEROID_MAX_VELOCITY_S/2)); 

        // add velocity boost at higher levels. separate from above because sign dependent
        if(getVelocity().X > 0) { setVelocityX(getVelocity().X + levelNum/6); }
        else                    { setVelocityX(getVelocity().X - levelNum/6); }

        if(getVelocity().Y > 0) { setVelocityY(getVelocity().Y + levelNum/6); }
        else                    { setVelocityY(getVelocity().Y - levelNum/6); }

        // set other data
        setMaxVelocity(ASTEROID_MAX_VELOCITY_S);
        setRadius(ASTEROID_RADIUS_S);
        _asteroid.setRadius(ASTEROID_RADIUS_S);
        _asteroid.setOrigin(ASTEROID_RADIUS_S, ASTEROID_RADIUS_S);
    }

    // set all asteroids to same appearance
    _asteroid.setFillColor(Color::Transparent);
    _asteroid.setOutlineThickness(2);
    _asteroid.setOutlineColor(Color::White);
}

void Asteroid::draw(sf::RenderWindow &window) {

    // CALLED EVERY FRAME!

    // perform position change and then draw to screen
    _asteroid.setPosition(getPosition().X, getPosition().Y);
    window.draw(_asteroid);
}

XYData Asteroid::spawnRandomAsteroid() {

    // called when new large asteroid is formed (beginning of levels)

    // initialize return and guard values
    double x = 0;
    double y = 0;
    XYData returnValue;
    bool done = false;

    // keep generating random locations until it is out of middle area
    while(!done) {
        
        // randomly assign location within range
        x = (1.0*rand()/RAND_MAX)*(ASTEROID_SPAWN_RANGE_HIGH - ASTEROID_SPAWN_RANGE_LOW)+ASTEROID_SPAWN_RANGE_LOW;
        y = (1.0*rand()/RAND_MAX)*(ASTEROID_SPAWN_RANGE_HIGH - ASTEROID_SPAWN_RANGE_LOW)+ASTEROID_SPAWN_RANGE_LOW;

        // if asteroid is out of center bounds end loop
        if( !(x > ASTEROID_SPAWN_BOUND_LOW
           && x < ASTEROID_SPAWN_BOUND_HIGH
           && y > ASTEROID_SPAWN_BOUND_LOW
           && y < ASTEROID_SPAWN_BOUND_HIGH)) { done = true; }
    }

    // return random location
    returnValue.X = x;
    returnValue.Y = y;  
    return returnValue;

}

// getter
char Asteroid::getSize() const {
    return _size;
}

// setter
void Asteroid::setSize(char size) {
    _size = size;
}
