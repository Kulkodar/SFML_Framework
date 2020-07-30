#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include <SFML_Framework/AssetManager.h>
#include <SFML_Framework/State.h>
#include <SFML_Framework/Window.h>

enum changeType
{
    Null,
    Override,
    Push,
    Pop
};

/**
 * @brief Main framework for a game which handles the window, events and game
 * states
 */
class Game
{
  public: // Constructor
    /**
     * @param windowSize The size of the window
     * @param windowTitle The title of the window
     * @param refreshrate The target frame rate
     * @param settings Opengl window settings
     */
    Game( sf::Vector2i windowSize, std::string const& windowTitle, int refreshrate, sf::ContextSettings settings );
    /**Deleted copy Constructor!*/
    Game( Game& other ) = delete;
    /**Deleted move Constructor!*/
    Game( Game&& ) = delete;
    virtual ~Game();

  public: // Methods
    /**
     * Game loop
     * The loop continues as long as the window is open
     */
    void run();
    /**
     * Creates am order to change the state
     * @param type Type of change : override ,push or pop
     * @param state Next state ,not needed by pop
     */
    void changeState( changeType type, State* state );
    /**Closes the game.*/
    void closeGame();

  protected:
    /**Overrides current state*/
    void Override();
    /**Removes the top state from the stack*/
    void popState();
    /**Adds a state to the stack*/
    void pushState();

  public: // Operators
    /**Deleted copy assignment operator!*/
    Game& operator=( const Game& other ) = delete;
    /**Deleted move assignment operator!*/
    Game& operator=( Game&& ) = delete;

  protected: // Attributes
    /// next state
    State* bufferState;
    /// Current FPS
    float currentFPS;
    /// Current frame time
    float currentFramestime;
    /// Refreshrate of the window
    int refreshrate;
    /// State stack
    std::vector<State*> states;
    /// Type of state change
    changeType type;
    /// Game window.
    Window window;
    /// User input handler
    InputHandler handler;

  public:
    // Game's Assetmanager
    AssetManager assets;

  public: // Getter Setter
    /**
     * @return a state within the state stack
     * @param i Index
     */
    State* getState( unsigned int i );

    int getStateSize();

    /**@return current frames per second*/
    float getCurrentFramesPerSecond() const;
    /**@return current frame time*/
    float getCurrentFramestime() const;
    /**@return refresh rate of the window*/
    int getRefreshrate() const;
    /**@return the window of the game*/
    Window& getWindow();
    /**
     * Sets the refresh rate of the window
     * @param refreshrate New refresh rate
     */
    void setRefreshrate( int refreshrate );
    /**
     * @return the inputhandler used in the game
     */
    InputHandler& getHandler();
};

#endif // GAME_H
