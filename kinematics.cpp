#include <iostream>

#include "kinematics.h"
#include "constants.h"

using namespace std;

void Kinematics::update() {

    // apply acceleration to velocity
        _velocity.X += _acceleration.X;
        _velocity.Y += _acceleration.Y;

    // apply deceleration to velocity
        // X
        if ( ( abs(_velocity.X) - _deceleration ) > 0) { // if applying deceleration does not switch velocity's sign, apply deceleration
            
            if(_velocity.X > 0) { _velocity.X -= _deceleration; } // velocity is positive
            else                { _velocity.X += _deceleration; } // velocity is negative

        } else { // if applying deceleration would have switched sign, set velocity to 0 instead
            _velocity.X = 0;
        }

        // Y
        if ( ( abs(_velocity.Y) - _deceleration ) > 0) { // if applying deceleration does not switch velocity's sign, apply deceleration
            
            if(_velocity.Y > 0) { _velocity.Y -= _deceleration; } // velocity is positive
            else                { _velocity.Y += _deceleration; } // velocity is negative

        } else { // if applying deceleration would have switched sign, set velocity to 0 instead
            _velocity.Y = 0;
        }

    // enforce velocity maximum
        // X
        if ( abs(_velocity.X) > _maxVelocity ) {                 // if over max velocity
            if(_velocity.X > 0) { _velocity.X =  _maxVelocity; } // max velocity is positive
            else                { _velocity.X = -_maxVelocity; } // max velocity is negative
        }

        // Y
        if ( abs(_velocity.Y) > _maxVelocity ) {                 // if over max velocity
            if(_velocity.Y > 0) { _velocity.Y =  _maxVelocity; } // max velocity is positive
            else                { _velocity.Y = -_maxVelocity; } // max velocity is negative
        }

    // apply velocity to position
        _position.X += _velocity.X;
        _position.Y += _velocity.Y;
        
    // apply scren wrap (keep spaceship on screen by wrapping to other side)

        // ex. if spaceship goes off right bound and has rightward velocity, set position to left bound
        if(_position.X > (SCREEN_SIZE+_radius) && _velocity.X > 0) { _position.X -= (SCREEN_SIZE+2*_radius); }
        if(_position.X < -_radius      && _velocity.X < 0) { _position.X += (SCREEN_SIZE+2*_radius); }
        if(_position.Y > (SCREEN_SIZE+_radius) && _velocity.Y > 0) { _position.Y -= (SCREEN_SIZE+2*_radius); }
        if(_position.Y < -_radius      && _velocity.Y < 0) { _position.Y += (SCREEN_SIZE+2*_radius); }
}

// getters
double Kinematics::getRadius      () const { return _radius;       }
XYData Kinematics::getPosition    () const { return _position;     }
XYData Kinematics::getVelocity    () const { return _velocity;     }
XYData Kinematics::getAcceleration() const { return _acceleration; }
double Kinematics::getDeceleration() const { return _deceleration; }
double Kinematics::getRotation    () const { return _rotation;     }
double Kinematics::getMaxVelocity () const { return _maxVelocity;  }

// setters
void Kinematics::setRadius       (double radius      ) { _radius     =     radius;       }
void Kinematics::setPositionX    (double position    ) { _position.X =     position;     }
void Kinematics::setPositionY    (double position    ) { _position.Y =     position;     }
void Kinematics::setVelocityX    (double velocity    ) { _velocity.X =     velocity;     }
void Kinematics::setVelocityY    (double velocity    ) { _velocity.Y =     velocity;     }
void Kinematics::setAccelerationX(double acceleration) { _acceleration.X = acceleration; }
void Kinematics::setAccelerationY(double acceleration) { _acceleration.Y = acceleration; }
void Kinematics::setDeceleration (double deceleration) { _deceleration =   deceleration; }
void Kinematics::setRotation     (double rotation    ) { _rotation =       rotation;     }
void Kinematics::setMaxVelocity  (double maxVelocity ) { _maxVelocity =    maxVelocity;  }