// standard libraries
#include <iostream>

// SFML libraries
#include <SFML/Graphics.hpp>

// program header files
#include "game.h"
#include "spaceship.h"
#include "XYData.h"
#include "constants.h"

// namespaces
using namespace std;
using namespace sf;

int main() {

    // create window of defined size
    RenderWindow window( VideoMode(SCREEN_SIZE, SCREEN_SIZE), "SFML Test" );

    // create an event object once to store future events
    sf::Event event; 

    // play again or not
    bool playAgain = true;

    // initialize new games until user quits (go will return true to keep playing, false to quit)
    while(playAgain) {
        Game asteroids; 
    
        // start game
        playAgain = asteroids.go(window, event); 
    }

    // once game ends, close window
    window.close();

    // end program successfully
    return 0; 

}