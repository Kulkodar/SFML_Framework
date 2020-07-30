#pragma once

#ifndef GAME_H
#warning Game must be include before
#endif

#include "Camera.h"
#include "Game.h"
#include "Window.h"
#include <SFML/Graphics.hpp>

class Game;

/**
 * @brief An interface for a State
 */
class State
{
  public: // Constructor
    /**
     * @param game Refrerence to the Game
     * @param viewSize Size of the Cammera
     */
    State( Game& game, sf::Vector2f viewSize );
    /**Deleted copy Constructor!*/
    State( State& other ) = delete;
    /**Deleted move Constructor!*/
    State( State&& ) = delete;

    virtual ~State();

  public: // Methods
    /**
     * @brief Polls all events and delegate all user input events to the
     * Inputhandler
     * @param handler A reference to a Inputhandler
     */
    virtual void handleEvents( InputHandler& handler ) = 0;
    /**
     * Updates the state
     * @param delta Time between the last frame
     */
    virtual void update( float delta ) = 0;
    /**
     * Renders the state
     * @param window Target window
     */
    virtual void display( Window& window ) = 0;

    /**Pauses the state*/
    virtual void pause() = 0;
    /**Resumes the state*/
    virtual void resume() = 0;

  public: // Operators
    /**Deleted copy assignment operator!*/
    State& operator=( const State& other ) = delete;
    /**Deleted move assignment operator!*/
    State& operator=( State&& ) = delete;

  protected:    // Attributes
    Game& game; // Reference to a game frame
    Camera cam; // Virtual Camera used in the State
    int funcID; /// Funciton if of the onResize even @see Window.h

  public: // Getter Setter
};
