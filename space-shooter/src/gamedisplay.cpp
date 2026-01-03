#include "gamedisplay.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <string>
#include <fstream>

using namespace std;
using namespace sf;

namespace {
    const string FONT_PATH = "assets/fonts/arcade1.ttf";
    const string SCORE_FILE = "data/scores.txt";
}

GameDisplay::GameDisplay()
{
    // load font, throw error if not found
    if (!myFont.loadFromFile(FONT_PATH)) // load font
        cout << "Couldn't load font" << endl; 

    // initialize booleans to...
    _scoreboardUpdated = false; // scoreboard not yet updated
    _localFileReadFrom = false; // local high score file not yet read from
    _listSorted = false; // score and name lists read in but not yet sorted
    _playAgain = false; // not yet ready to play again

}

void GameDisplay::pickLevel(sf::RenderWindow &window, int levelNum, int score, int lives) {

    // CALLED EVERY FRAME!

    if(lives == 0) // if lives is down to 0, game is over
        gameOver(window, score);

    else if(levelNum == 0) // game starts at level 1, level 0 is for home screen
        mainMenu(window);

    else // play game
        levelN(window, levelNum, score, lives);

}

void GameDisplay::mainMenu(sf::RenderWindow &window) const {

    // CALLED EVERY FRAME! - when game is on level 0

    // display game title
    Text homeScreenTop;
    homeScreenTop.setFont(myFont);
    homeScreenTop.setString("ASTEROIDS");
    homeScreenTop.setFillColor(Color::White);
    homeScreenTop.setPosition(90, 150);
    homeScreenTop.setCharacterSize(105);
    window.draw(homeScreenTop);

    // display CONTROLS
    Text homeScreenBottom;
    homeScreenBottom.setFont(myFont);
    homeScreenBottom.setString("PRESS 'ENTER' TO START");
    homeScreenBottom.setFillColor(Color::Blue);
    homeScreenBottom.setPosition(210, 380);
    homeScreenBottom.setCharacterSize(30);
    window.draw(homeScreenBottom);

    RectangleShape titleBorder;
    titleBorder.setSize(sf::Vector2f(660, 125));
    titleBorder.setPosition(70, 150);
    titleBorder.setFillColor(Color::Transparent);
    titleBorder.setOutlineThickness(4);
    titleBorder.setOutlineColor(Color::White);
    window.draw(titleBorder);

    Text controls1;
    controls1.setFont(myFont);
    controls1.setString("CONTROLS: WASD TO MOVE SPACESHIP");
    controls1.setFillColor(Color::White);
    controls1.setPosition(100, 500);
    controls1.setCharacterSize(30);
    window.draw(controls1);

    Text controls2;
    controls2.setFont(myFont);
    controls2.setString("MOVE MOUSE TO AIM SPACESHIP");
    controls2.setFillColor(Color::White);
    controls2.setPosition(150, 540);
    controls2.setCharacterSize(30);
    window.draw(controls2);

    Text controls3;
    controls3.setFont(myFont);
    controls3.setString("CLICK/SPACE TO SHOOT, ESC TO QUIT");
    controls3.setFillColor(Color::White);
    controls3.setPosition(75, 580);
    controls3.setCharacterSize(30);
    window.draw(controls3);

    // display DIRECTIONS
    Text gameplay1;
    gameplay1.setFont(myFont);
    gameplay1.setString("GAMEPLAY: SHOOT ASTEROIDS TO GET");
    gameplay1.setFillColor(Color::White);
    gameplay1.setPosition(100, 650);
    gameplay1.setCharacterSize(30);
    window.draw(gameplay1);

    Text gameplay2;
    gameplay2.setFont(myFont);
    gameplay2.setString(" POINTS AND ADVANCE TO THE NEXT LEVEL");
    gameplay2.setFillColor(Color::White);
    gameplay2.setPosition(60, 690);
    gameplay2.setCharacterSize(30);
    window.draw(gameplay2);

    
    
}

void GameDisplay::levelN(sf::RenderWindow &window, int levelNum, int score, int lives) {

    // CALLED EVERY FRAME! - when game is on level 1+

    // append current level, score, and lives onto strings with their titles
    // then display in top left corner of screen

    string levelAsString = to_string(levelNum);
    string levelText = "LEVEL ";
    levelText += levelAsString;

    string scoreAsString = to_string(score);
    string scoreText = "SCORE: ";
    scoreText += scoreAsString;

    string livesAsString = to_string(lives);
    string livesText = "LIVES: ";
    livesText += livesAsString;

    Text levelDisplay;
    levelDisplay.setFont(myFont);
    levelDisplay.setFillColor(Color::White);
    levelDisplay.setPosition(20, 20);
    levelDisplay.setCharacterSize(30);
    levelDisplay.setString(levelText);
    window.draw(levelDisplay);

    Text scoreDisplay;
    scoreDisplay.setFont(myFont);
    scoreDisplay.setFillColor(Color::White);
    scoreDisplay.setPosition(20, 60);
    scoreDisplay.setCharacterSize(30);
    scoreDisplay.setString(scoreText);
    window.draw(scoreDisplay);

    Text livesDisplay;
    livesDisplay.setFont(myFont);
    livesDisplay.setFillColor(Color::White);
    livesDisplay.setPosition(20, 100);
    livesDisplay.setCharacterSize(30);
    livesDisplay.setString(livesText);
    window.draw(livesDisplay);

}

void GameDisplay::gameOver(sf::RenderWindow &window, int score) const {

    // CALLED EVERY FRAME! - when lives == 0

    // display game over and score

    Text homeScreenTop;
    homeScreenTop.setFont(myFont);
    homeScreenTop.setString("GAME OVER");
    homeScreenTop.setFillColor(Color::White);
    homeScreenTop.setPosition(90, 50);
    homeScreenTop.setCharacterSize(105);
    window.draw(homeScreenTop);

    string scoreAsString = to_string(score); // append score to title
    string scoreText = "Score: ";
    scoreText += scoreAsString;

    Text scoreDisplay;
    scoreDisplay.setFont(myFont);
    scoreDisplay.setFillColor(Color::White);
    scoreDisplay.setPosition(225, 155);
    scoreDisplay.setCharacterSize(80);
    scoreDisplay.setString(scoreText);
    window.draw(scoreDisplay);

}

void GameDisplay::userEntersName(sf::RenderWindow &window, string name, int score) {

    // CALLED EVERY FRAME! - when lives == 0

    // update the name the user has typed each frame so that name updates on screen
    Text enter;
    enter.setFont(myFont);
    enter.setFillColor(Color::White);
    enter.setPosition(230, 250);
    enter.setCharacterSize(30);
    enter.setString("Enter your name: ");
    window.draw(enter);

    Text nameDisplay;
    nameDisplay.setFont(myFont);
    nameDisplay.setFillColor(Color::Blue);
    nameDisplay.setPosition(500, 250);
    nameDisplay.setCharacterSize(30);
    nameDisplay.setString(name);
    window.draw(nameDisplay);

    // write to local high score file ONCE after user has entered a three letter name
    if(!_scoreboardUpdated && name.length() == 3) {
        writeToScoreFile(name, score);
        _scoreboardUpdated = true;
    }
}

void GameDisplay::readAndDisplayScores(sf::RenderWindow &window) {

    // CALLED EVERY FRAME! - when lives == 0

    // if name and score lists in program have not been loaded yet, load them
    if(_scoreboardUpdated) {

        // open file for reading
        _fileName = SCORE_FILE;
        _fileIn.open(_fileName);
        if(!_fileIn.is_open()) {
            cout << "Could not open " << _fileName << " for reading" << endl;
        }

        // until file ends, read each string.  names and scores alternate in file
        if(!_localFileReadFrom) {
            string input = "";
            while(_fileIn >> input) {        // read name
                _nameList.push_back(input);  // push to names list
                _fileIn >> input;            // read score
                _scoreList.push_back(input); // push to scores list
            }
            _localFileReadFrom = true; // mark that file has been read from
        }

        // if list hasn't been soreted yet, sort it
        if(!_listSorted) {
            sortLists();
            _listSorted = true;
        }

        // display prompt to play again
        Text playAgain;
        playAgain.setFont(myFont);
        playAgain.setFillColor(Color::White);
        playAgain.setPosition(200, 295);
        playAgain.setCharacterSize(30);
        playAgain.setString("Play Again? ( Enter / Esc )");
        window.draw(playAgain);

        // now that names and scores lists are both sorted, display the first 10 of each (top 10 scores)
        int highScoreListSize = 10;
        for(int i = 0; i < highScoreListSize; i++) {
            if(i < (int)_nameList.size()) {

                // DISPLAY LIST NUMBER
                string numDisplay = "";
                numDisplay += to_string(i+1);
                numDisplay += ".";

                Text numberDisplay;
                numberDisplay.setFont(myFont);
                numberDisplay.setFillColor(Color::White);
                numberDisplay.setPosition(250, 407+30*(i+1));
                numberDisplay.setCharacterSize(30);
                numberDisplay.setString(numDisplay);
                window.draw(numberDisplay);

                // DISPLAY NAMES
                Text nameDisplay;
                nameDisplay.setFont(myFont);
                nameDisplay.setFillColor(Color::White);
                nameDisplay.setPosition(350, 407+30*(i+1)); // stagger each list item so it is below the previous
                nameDisplay.setCharacterSize(30);
                nameDisplay.setString(_nameList.at(i));
                window.draw(nameDisplay);

                // DISPLAY CORRESPONDING SCORE
                Text scoreDisplay;
                scoreDisplay.setFont(myFont);
                scoreDisplay.setFillColor(Color::White);
                scoreDisplay.setPosition(480, 407+30*(i+1));
                scoreDisplay.setCharacterSize(30);
                scoreDisplay.setString(to_string(_scoreListInt.at(i))); // stagger each list item so it is below the previous
                window.draw(scoreDisplay);
            }
        }

        // make box around table and add header
        RectangleShape scoreBorder;
        scoreBorder.setSize(sf::Vector2f(700, 370));
        scoreBorder.setPosition(50, 380);
        scoreBorder.setFillColor(Color::Transparent);
        scoreBorder.setFillColor(Color::Transparent);
        scoreBorder.setOutlineThickness(4);
        scoreBorder.setOutlineColor(Color::White);
        window.draw(scoreBorder);

        RectangleShape headerBorder;
        headerBorder.setSize(sf::Vector2f(700, 50));
        headerBorder.setPosition(50, 380);
        headerBorder.setFillColor(Color::Transparent);
        headerBorder.setFillColor(Color::Transparent);
        headerBorder.setOutlineThickness(4);
        headerBorder.setOutlineColor(Color::White);
        window.draw(headerBorder);

        Text headerText;
        headerText.setFont(myFont);
        headerText.setFillColor(Color::White);
        headerText.setPosition(193, 385);
        headerText.setCharacterSize(30);
        headerText.setString("High Scores On This Computer");
        window.draw(headerText);

        _playAgain = true; // allow user to play again

        _fileIn.close(); // close file
    }
}

void GameDisplay::writeToScoreFile(string name, int score) {

    // write players new score to file
    _fileName = SCORE_FILE;
    _fileOut.open(_fileName, ios_base::app); // APPEND not rewrite

    // make sure file can open
    if(!_fileOut.is_open()) {
        cout << "Could not open " << _fileName << " for writing" << endl;
    }

    _fileOut << name << " " << score << endl; // write to file

    _fileIn.close(); // close file

}

void GameDisplay::sortLists() {

    // add score strings to list as ints
    for(size_t i = 0; i < _scoreList.size(); i++) {
        _scoreListInt.push_back(stoi(_scoreList.at(i)));
    }

    // for every element in scorelist
    for(size_t i = 0; i < _scoreListInt.size(); i++) {

        // set first position element to minimum
        int maxValue = _scoreListInt.at(i);
        int maxLocation = i;

        // search remaining vector
        for(size_t j = i + 1; j < _scoreListInt.size(); j++) {

            // if a smaller value than current minimum is found
            if( _scoreListInt.at(j) > maxValue ) {

            // update minimum
            maxValue = _scoreListInt.at(j);
            maxLocation = j;
            }
        }

        // perform swap in style of selection sort (if minimum not already in first position)
        if((int)i != maxLocation) {

            // set temp to element
            int temps = _scoreListInt.at(i); // words
            string tempi = _nameList.at(i); // counts

            // swap min into elements location 

            // deal with deleting first element
            int tempMax = maxLocation;
            if(maxLocation != 0)
                tempMax--;

            // erase
            _scoreListInt.erase(_scoreListInt.begin()+i); // words
            _nameList.erase(_nameList.begin()+i);  // counts

            // insert
            _scoreListInt.insert(_scoreListInt.begin()+i, _scoreListInt.at(tempMax)); // words
            _nameList.insert(_nameList.begin()+i, _nameList.at(tempMax)); // counts

            // swap element (temp) into mins location

            // erase
            _scoreListInt.erase(_scoreListInt.begin()+maxLocation); // words
            _nameList.erase(_nameList.begin()+maxLocation); // counts

            // insert
            _scoreListInt.insert(_scoreListInt.begin()+maxLocation, temps); // words
            _nameList.insert(_nameList.begin()+maxLocation, tempi); // counts
        }
    }
}

// getter
bool GameDisplay::getPlayAgain() {
    return _playAgain;
}
