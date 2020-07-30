#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include <SFML_Framework/gui/GUIWidget.h>
#include <SFML_Framework/Game.h>
#include <SFML_Framework/Camera.h>

/**
 * @brief A simple GUI handler
 */
class GUI
{
public: // Constructor
    /**
     * @param game Reference to the Game
     * @param viewSize Size of the GUI view
     */
    GUI( Game& game, sf::Vector2f viewSize );
    /**Deleted copy Constructor!*/
    GUI( GUI& other ) = delete;
    /**Deleted move Constructor!*/
    GUI( GUI&& ) = delete;
    ~GUI();

public: // Methods
    /**
     * @brief Processes user input
     * @param handler
     */
    void handleEvents( InputHandler& handler );
    /**
     * Update the GUI and it's GUIWidgets.
     * @param delta Current frame time.
     */
    void update( float delta );
    /**
     * Draws the GUI and it's GUIWidgets.
     * @param window Target Window.
     */
    void draw( Window& window );
    /**
     * Adds a widget to the container.
     * @param widget Widget to add.
     */
    void addWidget( GUIWidget* widget );
    /**
     * Removes a widget from this group
     * @param id Id of the widget.
     * @return If widget was found and removed.
     */
    bool removeWidget( std::string const& id );

    void hide( bool hiden );
    void disable( bool disabled );

public: // Operators
    /**Deleted copy assignment operator!*/
    GUI& operator=( const GUI& other ) = delete;
    /**Deleted move assignment operator!*/
    GUI& operator=( GUI&& ) = delete;

protected: // Attributes
    /// GUIWidget container
    std::vector<GUIWidget*> widgets;
    /// Reference to the game
    Game& game;
    /// Camera used to display GUIWidgets
    Camera cam;
    /// onResize event id
    int funcID;

    bool hiden;
    bool disabled;

public: // Getter Setter
    /**
     * Searches for a GUIWiddget in the container.
     * @param id Id of the GUIWiddget.
     * @return Nullptr if nothing is found else the GUIWIdget.
     */
    GUIWidget* getWidget( std::string const& id );
    /**
     * @return the camera used in the GUI
     */
    Camera& getCam();

    bool isHiden();
    bool isDisabled();
};
