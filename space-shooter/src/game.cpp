// standard libraries
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

// SFML libraries
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

// program header files
#include "game.h"
#include "constants.h"

// namespaces
using namespace std;
using namespace sf;

// default constructor
Game::Game() {

    // initialize values to...

        // all keys to not pressed
        for(int i = 0; i < 29; i++) {
            _keys.push_back(false);
        }
        _mouse = false; // mouse not clicked

    // gameplay attributes/data
        _reloaded = true;  // spaceship ready to shoot
        _levelDone = true; // level not done
        _quit = false;     // not quitting
        _restart = false;  // not restarting
        _previousWasUnpressed = true; // no key pressed

        _score = 0; // score starts at 0
        _lives = 3; // start with 3 lives
        _levelNumber = 0; // start at level 0 (home screen, game begins at level 1)
        _previousPositionPressed = 0; // default previous key
        
        _name = ""; // no name yet inputted
}

// calls all game mechanics
bool Game::go(sf::RenderWindow &window, sf::Event &event) {

    // initialize last time
    _lastTime = programClock.getElapsedTime();

    // seed PRNG
    srand(time(0));

    // this loop level is for each LEVEL of the game
    while(!_quit && (_lives > 0)) {

        startLevel(); // begin level tasks

        // this loop level is for each FRAME of the game
        while(!_quit && !_levelDone && _lives > 0) {

            
            // get and process user input
            getUserInput(window, event);
            _quit = processUserInput(window, event);

            // short circuit frame if user quits
            if(_quit)
                return false;

            ///////// START OBJECT UPDATE //////////
            // all in-game objects (spacehip, asteroids, bullets, test each for collisions and remove if needed)
            if(_levelNumber > 0) {

                _spaceship.update(); // spacehip

                for(size_t i = 0; i < _asteroidList.size(); i++) { // asteroids
                    _asteroidList.at(i).update();
                }

                for(size_t i = 0; i < _bulletList.size(); i++) { // bullets
                    _bulletList.at(i).update();
                    _bulletList.at(i).removeBullet();
                }

                collisionTest(); // collision test and bullet removal
                removeBullets();
            }
            ///////// END OBJECT UPDATE //////////


            ///////// START DRAWING //////////
            // all game objects including home screen and game over screen
            window.clear(); // clear window first
            gameDisplay.pickLevel(window, _levelNumber, _score, _lives); // always drawn 
            
            if(_levelNumber > 0) { // sometimes drawn (if in game)

                _spaceship.draw(window); // spaceship

                for(size_t i = 0; i < _asteroidList.size(); i++) { // asteroids
                    _asteroidList.at(i).draw(window);
                }

                for(size_t i = 0; i < _bulletList.size(); i++) { // bullets
                    _bulletList.at(i).draw(window);
                }
            }

            // enforce framerate and then display current frame
            enforceFramerate();
            window.display();
            ///////// END DRAWING //////////

            // level ends when all asteroids have been destroyed
            if(_levelNumber > 0 && _asteroidList.size() == 0) {
                _levelDone = true;
            }
        }
        endLevel(); // perform end level functions
    }

    // this loop happens AFTER the game is over (all lives have been lost), called once per frame
    while(!_restart ) {

        // continue getting and processing user input
        getUserInput(window, event);
        _quit = processUserInput(window, event);

        if(_quit) // quit if user wants to
            return false;

        writeUserName();

        ///////// START DRAWING //////////
        window.clear();
        gameDisplay.pickLevel(window, _levelNumber, _score, _lives); // calls home screen, in game level, or game over screen
        gameDisplay.readAndDisplayScores(window); // reads in high scores from file, sorts list, and displays top 10
        gameDisplay.userEntersName(window, _name, _score); // allows user to input a 3 letter name which will be displayed on scoreboard

        // enforce framerate and then display current frame
        enforceFramerate();
        window.display();
        ///////// END DRAWING //////////

        if(_keys.at(26) && gameDisplay.getPlayAgain()) // if user enters Y, play game again (exit this loop)
            _restart = true;
    }
    return true; // if execution gets to here, game ends and a new one is reinitialized
}

void Game::startLevel() {

    _bulletList.clear(); // removes all bullets from screen
    
    _spaceship.setLifeStartTime(programClock.getElapsedTime()); // starts timer so player can be invincible for short amount of time
    
    // add appropriate number of asteroids to asteroid list
    if(_levelNumber > 0) {

        int numberOfAsteroids = 2 + 2*_levelNumber; // more asteroids per level

        for(int i = 0; i < numberOfAsteroids; i++) { // spawn appropriate amount of asteroids
            Asteroid asteroid('L', 0, 0, _levelNumber);
            _asteroidList.push_back(asteroid);
        }
    }

    // reset levelDone to false
    _levelDone = false;

    // reset spaceship to be stationary at center of screen
    _spaceship.setPositionX(SCREEN_SIZE/2);
    _spaceship.setPositionY(SCREEN_SIZE/2);
    _spaceship.setVelocityX(0);
    _spaceship.setVelocityY(0);
}

void Game::endLevel() {
    
    // incremend level number
        _levelNumber++;
}

void Game::getUserInput(sf::RenderWindow &window, sf::Event &event) {

    // CALLED EVERY FRAME!

    while(window.pollEvent(event)) {

        if(event.type == Event::MouseButtonPressed) // mouse pressed and unpressed
            _mouse = true;
        else if(event.type == Event::MouseButtonReleased) 
            _mouse = false;

        // toggle keys ON
        if(event.type == Event::KeyPressed) { 
            if (event.key.code == Keyboard::A) { _keys.at(0)  = true; }
            if (event.key.code == Keyboard::B) { _keys.at(1)  = true; }
            if (event.key.code == Keyboard::C) { _keys.at(2)  = true; }
            if (event.key.code == Keyboard::D) { _keys.at(3)  = true; }
            if (event.key.code == Keyboard::E) { _keys.at(4)  = true; }
            if (event.key.code == Keyboard::F) { _keys.at(5)  = true; }
            if (event.key.code == Keyboard::G) { _keys.at(6)  = true; }
            if (event.key.code == Keyboard::H) { _keys.at(7)  = true; }
            if (event.key.code == Keyboard::I) { _keys.at(8)  = true; }
            if (event.key.code == Keyboard::J) { _keys.at(9)  = true; }
            if (event.key.code == Keyboard::K) { _keys.at(10) = true; }
            if (event.key.code == Keyboard::L) { _keys.at(11) = true; }
            if (event.key.code == Keyboard::M) { _keys.at(12) = true; }
            if (event.key.code == Keyboard::N) { _keys.at(13) = true; }
            if (event.key.code == Keyboard::O) { _keys.at(14) = true; }
            if (event.key.code == Keyboard::P) { _keys.at(15) = true; }
            if (event.key.code == Keyboard::Q) { _keys.at(16) = true; }
            if (event.key.code == Keyboard::R) { _keys.at(17) = true; }
            if (event.key.code == Keyboard::S) { _keys.at(18) = true; }
            if (event.key.code == Keyboard::T) { _keys.at(19) = true; }
            if (event.key.code == Keyboard::U) { _keys.at(20) = true; }
            if (event.key.code == Keyboard::V) { _keys.at(21) = true; }
            if (event.key.code == Keyboard::W) { _keys.at(22) = true; }
            if (event.key.code == Keyboard::X) { _keys.at(23) = true; }
            if (event.key.code == Keyboard::Y) { _keys.at(24) = true; }
            if (event.key.code == Keyboard::Z) { _keys.at(25) = true; }
            if (event.key.code == Keyboard::Enter)  { _keys.at(26) = true; }
            if (event.key.code == Keyboard::Escape) { _keys.at(27) = true; }
            if (event.key.code == Keyboard::Space)  { _keys.at(28) = true; }
        }

        // toggle keys OFF
        if(event.type == Event::KeyReleased) { 
            if (event.key.code == Keyboard::A) { _keys.at(0)  = false; }
            if (event.key.code == Keyboard::B) { _keys.at(1)  = false; }
            if (event.key.code == Keyboard::C) { _keys.at(2)  = false; }
            if (event.key.code == Keyboard::D) { _keys.at(3)  = false; }
            if (event.key.code == Keyboard::E) { _keys.at(4)  = false; }
            if (event.key.code == Keyboard::F) { _keys.at(5)  = false; }
            if (event.key.code == Keyboard::G) { _keys.at(6)  = false; }
            if (event.key.code == Keyboard::H) { _keys.at(7)  = false; }
            if (event.key.code == Keyboard::I) { _keys.at(8)  = false; }
            if (event.key.code == Keyboard::J) { _keys.at(9)  = false; }
            if (event.key.code == Keyboard::K) { _keys.at(10) = false; }
            if (event.key.code == Keyboard::L) { _keys.at(11) = false; }
            if (event.key.code == Keyboard::M) { _keys.at(12) = false; }
            if (event.key.code == Keyboard::N) { _keys.at(13) = false; }
            if (event.key.code == Keyboard::O) { _keys.at(14) = false; }
            if (event.key.code == Keyboard::P) { _keys.at(15) = false; }
            if (event.key.code == Keyboard::Q) { _keys.at(16) = false; }
            if (event.key.code == Keyboard::R) { _keys.at(17) = false; }
            if (event.key.code == Keyboard::S) { _keys.at(18) = false; }
            if (event.key.code == Keyboard::T) { _keys.at(19) = false; }
            if (event.key.code == Keyboard::U) { _keys.at(20) = false; }
            if (event.key.code == Keyboard::V) { _keys.at(21) = false; }
            if (event.key.code == Keyboard::W) { _keys.at(22) = false; }
            if (event.key.code == Keyboard::X) { _keys.at(23) = false; }
            if (event.key.code == Keyboard::Y) { _keys.at(24) = false; }
            if (event.key.code == Keyboard::Z) { _keys.at(25) = false; }
            if (event.key.code == Keyboard::Enter)  { _keys.at(26) = false; }
            if (event.key.code == Keyboard::Escape) { _keys.at(27) = false; }
            if (event.key.code == Keyboard::Space)  { _keys.at(28) = false; }
        }
    }
}

int Game::processUserInput(sf::RenderWindow &window, sf::Event &event) {

    // CALLED EVERY FRAME!

    // exit game if x'ed out or escape is hit
    if(event.type == Event::Closed) return 1;
    if(_keys.at(27)) return 1;

    // game and menu controls
    if(_levelNumber == 0 && _keys.at(26)) {
        _levelDone = true;
    }

    // W/A/S/D: accelerate spaceship
        double xAccelerationSum = 0;
        double yAccelerationSum = 0;

        // effect is cumulative, ex w and s pressed at the same time cancel each other out
        if(_keys.at(22)) { yAccelerationSum -= SPACESHIP_ACCELERATION; }
        if(_keys.at(0))  { xAccelerationSum -= SPACESHIP_ACCELERATION; }
        if(_keys.at(18)) { yAccelerationSum += SPACESHIP_ACCELERATION; }
        if(_keys.at(3))  { xAccelerationSum += SPACESHIP_ACCELERATION; }

        // after checking all 4 keys, send to kinematic processor
        _spaceship.setAccelerationX(xAccelerationSum);
        _spaceship.setAccelerationY(yAccelerationSum);

    // rotates spaceship so it points at mouse pointer
    _spaceship.pointAtMouse(Mouse::getPosition(window));

    // if mouse is clicked and ship is reloaded, shoot, then set reloaded to false
    // this only allows the user to shoot once per click. user can use mouse or space but not both at same time
    if((_mouse ^ _keys.at(28)) && _reloaded) { 
        shoot();
        _reloaded = false;
    }

    // once mouse is unclicked, reload 
    if(!_mouse && !_keys.at(28)) _reloaded = true;

    return 0; // if execution gets here, game won't quit
}

void Game::collisionTest() {

    // CALLED EVERY FRAME!

    // for every asteroid currently in game
    for(size_t i = 0; i < _asteroidList.size(); i++) {
        
        // calculate distance to spaceship
        double distance = sqrt( pow(_spaceship.getPosition().X - _asteroidList.at(i).getPosition().X , 2)
                              + pow(_spaceship.getPosition().Y - _asteroidList.at(i).getPosition().Y , 2) );

        // if asteroid and spaceship are touching 
        // DO NOT DO IF SPACESHIP IS INVINCIBLE (see spaceship.cpp)
        if( (distance < (SPACESHIP_RADIUS + _asteroidList.at(i).getRadius()) - 20) && !_spaceship.getInvincibility()) {

            // if the asteroid touched is large, make two mediums and location of the large
            if(_asteroidList.at(i).getSize() == 'L') {
                Asteroid asteroid1('M', _asteroidList.at(i).getPosition().X, _asteroidList.at(i).getPosition().Y, _levelNumber);
                Asteroid asteroid2('M', _asteroidList.at(i).getPosition().X, _asteroidList.at(i).getPosition().Y, _levelNumber);
                _asteroidList.push_back(asteroid1);
                _asteroidList.push_back(asteroid2);
            }
            // if asteroid touched is medium, make two smalls at location of the medium
            else if(_asteroidList.at(i).getSize() == 'M') {
                Asteroid asteroid1('S', _asteroidList.at(i).getPosition().X, _asteroidList.at(i).getPosition().Y, _levelNumber);
                Asteroid asteroid2('S', _asteroidList.at(i).getPosition().X, _asteroidList.at(i).getPosition().Y, _levelNumber);
                _asteroidList.push_back(asteroid1);
                _asteroidList.push_back(asteroid2);
            }
            // delete the asteroid that was touched and remove a life from player
            _asteroidList.erase(_asteroidList.begin()+i);
            i--;
            if(_lives > 0)
                _lives--;

            // pause game for a second
            sleep(milliseconds(1000));

            // reset spaceship to stationary at center of screen
            _spaceship.setPositionX(400);
            _spaceship.setPositionY(400);
            _spaceship.setVelocityX(0);
            _spaceship.setVelocityY(0);
            _spaceship.setLifeStartTime(programClock.getElapsedTime()); // restart clock for invincibility
        }
    }

    // for every asteroid currently in game
    for(size_t i = 0; i < _asteroidList.size(); i++) {

        // for every bullet currently in game
        for(size_t j = 0; j < _bulletList.size(); j++) {

            // calculate distance between asteroid and bullet
            double distance = sqrt( pow(_bulletList.at(j).getPosition().X - _asteroidList.at(i).getPosition().X , 2)
                                  + pow(_bulletList.at(j).getPosition().Y - _asteroidList.at(i).getPosition().Y , 2) );

            // if asteroid and bullet are touching
            if( distance < (BULLET_RADIUS + _asteroidList.at(i).getRadius()) ) {

                // if the asteroid touched is large, make two mediums and location of the large, increment score
                if(_asteroidList.at(i).getSize() == 'L') {
                    Asteroid asteroid1('M', _asteroidList.at(i).getPosition().X, _asteroidList.at(i).getPosition().Y, _levelNumber);
                    Asteroid asteroid2('M', _asteroidList.at(i).getPosition().X, _asteroidList.at(i).getPosition().Y, _levelNumber);
                    _asteroidList.push_back(asteroid1);
                    _asteroidList.push_back(asteroid2);
                    _score+=10;
                }
                // if asteroid touched is medium, make two smalls at location of the medium, increment score
                else if(_asteroidList.at(i).getSize() == 'M') {
                    Asteroid asteroid1('S', _asteroidList.at(i).getPosition().X, _asteroidList.at(i).getPosition().Y, _levelNumber);
                    Asteroid asteroid2('S', _asteroidList.at(i).getPosition().X, _asteroidList.at(i).getPosition().Y, _levelNumber);
                    _asteroidList.push_back(asteroid1);
                    _asteroidList.push_back(asteroid2);
                    _score+=20;
                }
                // if asteroid touched is small, remove and make no new asteroids, increment score
                else {
                    _score += 40;
                }

                // get rid of both asteroid and bullet involved in collision
                _asteroidList.erase(_asteroidList.begin()+i);
                _bulletList.erase(_bulletList.begin()+j);  

                // go back in lists and break to avoid out of bounds (asteroid and bullet can no longer touch because they are gone)
                if(j > 0) { j--; }
                if(i > 0) { i--; }
                else { break; }
            }
        }
    }
}

void Game::shoot() {

    // called only when user presses space or mouse

    // only certain amount of bullets allowed on screen, if less than max make a new bullet
    // bullet will spawn with position and velocity
    if(_bulletList.size() < MAX_BULLETS) {
        Bullet newBullet(_spaceship.getPosition().X, _spaceship.getPosition().Y, _spaceship.getRotation());
        _bulletList.push_back(newBullet);
    }
}

void Game::removeBullets() {

    // CALLED EVERY FRAME!

    // remove all bullets that bullet object says should be removed (this calls function within bullet class)
    for(size_t i = 0; i < _bulletList.size(); i++) {
        if(_bulletList.at(i).removeBullet())
            _bulletList.erase(_bulletList.begin()+i);
    }
}

void Game::enforceFramerate() {

    // CALLED EVERY FRAME!

    _currentTime = programClock.getElapsedTime(); // get current time

    // compare to last time, if frame duration hasn't passed, wait and try again
    while((_currentTime - _lastTime).asMilliseconds() < FRAME_DURATION) {
        sleep(milliseconds(1));
        _currentTime = programClock.getElapsedTime();
    }

    _lastTime = _currentTime; // update last time
}

// getter
std::vector<bool> Game::getKeys() const{
    return _keys;
}

void Game::writeUserName() {

    // CALLED EVERY FRAME! - in game over loop only

    if(_name.length() == 3) // if user has already entered 3 letters, don't perform rest of function
        return;

    // ensure that key is released before it can be used to add another letter, otherwise 3 of same letter are instantly added to array
    if(_keys.at(_previousPositionPressed) == false) 
        _previousWasUnpressed = true;

    // get the current key that is pressed and once it is pressed, set boolean to false so it must be released before pressed again
    for(size_t i = 0; i < 26; i++) {
        if(_keys.at(i) == true) {
            if(_previousPositionPressed == (int)i && _previousWasUnpressed) { // for if same key is entered twice in a row
                _name += (char)(65+i);
                _previousPositionPressed = i;
                _previousWasUnpressed = false;
            }
            else if(_previousPositionPressed != (int)i) { // for if current letter is different from previous letter
                _name += (char)(65+i);
                _previousPositionPressed = i;
                _previousWasUnpressed = false;
            }
            break;
        }
    }
}

