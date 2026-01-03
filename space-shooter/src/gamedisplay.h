#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H

class GameDisplay {

public:

    /**
     * @brief default constructor (loads font, sets booleans to false)
     */
    GameDisplay();

    /**
     * @brief calls the appropriate level to be displayed depending on current level number
     * @param window where to display (passed to other functions)
     * @param levelNum used to call right level, passed to other functions
     * @param score game score, passed to other functions
     * @param lives number of lives left, passed to other functions
     */
    void pickLevel(sf::RenderWindow &window, int levelNum, int score, int lives);

    /**
     * @brief called when level == 0, displays home screen
     * @param window where to display
     */
    void mainMenu(sf::RenderWindow &window) const;

    /**
     * @brief displays level, score, and lives in top left of each level
     * @param window where to display
     * @param level level number
     * @param core game score
     * @param lives number of lives
     */
    void levelN(sf::RenderWindow &window, int levelNum, int score, int lives);

    /**
     * @brief displays initial text in game over screen (more is added by readAndDisplayScores())
     * @param window where to display
     * @param score game score
     */
    void gameOver(sf::RenderWindow &window, int score) const;

    /**
     * @brief prompts user to enter their name and updates screen as they do
     * @param window where to display
     * @param name the name the user entered
     * @param score users score
     */
    void userEntersName(sf::RenderWindow &window, std::string name, int score);

    /**
     * @brief reads in whole list of scores saved on this computer. sorts in order of decreasing score,
     * creates and displays a table of the top 10 high scores
     * @param window where to display
     */
    void readAndDisplayScores(sf::RenderWindow &window);

    /**
     * @brief updates the local file that holds all game scores at the end of each game
     * @param name players name
     * @param score players score
     */
    void writeToScoreFile(std::string name, int score);

    /**
     * @brief sorts local high score list from highest to lowest score
     */
    void sortLists();

    /**
     * @brief only let user play again after they have entered their name
     */
    bool getPlayAgain();
    
private:

    sf::Font myFont; // font for all displays in game

    std::string _fileName; // the file that will be read from and written to
    std::ifstream _fileIn; // variable for file when reading
    std::ofstream _fileOut; // variable for file when writing

    std::vector<std::string> _nameList; // all names read in from local file
    std::vector<std::string> _scoreList; // all scores read in from local file
    std::vector<int> _scoreListInt; // a copy of the score list made with ints so that it can be sorted

    // various booleans
    bool _scoreboardUpdated; // used to update high score board only once at end of game
    bool _localFileReadFrom; // used to read from local file only once
    bool _listSorted; // used to sort the list only once
    bool _playAgain; // used to allow player to play again in game.cpp

};

#endif // GAMEDISPLAY_H