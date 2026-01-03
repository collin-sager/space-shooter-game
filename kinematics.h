#include <iostream>

#include "XYData.h"

#ifndef KINEMATICS_H
#define KINEMATICS_H

class Kinematics {

public:

    /**
     * @brief Kinematics is a parent class of every moving object in the game. It contains all kinematic
     * parameters and this function performs updates to every appropriate kinematic parameter (namely
     * position, velocity, and rotation), each frame of the game
     */
    void update();

    /**
     * @brief getters
     */
    double getRadius      () const;
    XYData getPosition    () const;
    XYData getVelocity    () const;
    XYData getAcceleration() const;
    double getDeceleration() const;
    double getRotation    () const;
    double getMaxVelocity () const;

    /**
     * @brief gsetters
     */
    void setRadius       (double radius      );
    void setPositionX    (double position    );
    void setPositionY    (double position    );
    void setVelocityX    (double velocity    );
    void setVelocityY    (double velocity    );
    void setAccelerationX(double velocity    );
    void setAccelerationY(double velocity    );
    void setDeceleration (double deceleration);
    void setRotation     (double rotation    );
    void setMaxVelocity  (double maxVelocity );

private:

    // object size
    double _radius;

    // current kinematic state
    XYData _position;
    XYData _velocity;
    XYData _acceleration;
    double _deceleration;
    double _rotation;

    // kinematic bounds
    double _maxVelocity;

};



#endif // KINEMATICS_H