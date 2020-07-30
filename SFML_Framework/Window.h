#pragma once

#include <string>
#include <unordered_map>

#include <Signal.h>

#include <SFML/Graphics.hpp>
#include <SFML_Framework/InputHandler.h>

/**
 * @brief A simple SFML RenderWindow Wraper to properly handle user input.
 */
class Window
{
  public: // Constructor
    /**
     * @param size Size of the new Window.
     * @param title The Title of the Window.
     * @param style Setting wich controll buttons or viewmode the window shuld
     * have.
     * @param settings Opengl specific settings.
     */
    Window( sf::Vector2i size, std::string const& title, sf::Uint32 style, sf::ContextSettings settings );
    /**Deleted copy Constructor!*/
    Window( Window& other ) = delete;
    /**Deleted move Constructor!*/
    Window( Window&& ) = delete;
    ~Window();

  public: // Methods
    /**
     * @brief Clears the Window
     */
    void clear();
    /**
     * @brief Polls all events and delegate all user input events to the
     * Inputhandler
     * @param handler A reference to a Inputhandler
     */
    void handleEvents( InputHandler& handler );
    /**
     * @brief Draws the given Drawable
     * @param drawable Thing to draw on screen
     */
    void draw( const sf::Drawable& drawable );
    /**
     * @brief Swaps the buffer
     */
    void update();
    /**
     * @brief Closes the Window
     */
    void close();

  public: // Event
    Signal<sf::Vector2u> onResize;

  public: // Operators
    /**Deleted copy assignment operator!*/
    Window& operator=( const Window& other ) = delete;
    /**Deleted move assignment operator!*/
    Window& operator=( Window&& ) = delete;

  protected:                 // Attributes
    sf::RenderWindow window; /// SFML RenderWindow

  public: // Getter Setter
    /**
     * @brief Retunrs a reference to the internal Window
     */
    sf::RenderWindow& getSFMLWindow();

    /**
     * @brief Returns the state of the Window
     * @return True if window is open false if not
     */
    bool isOpen();

    /**
     * @brief Resizes the Window
     * @param size new Window size
     */
    void setSize( sf::Vector2u size );

    /**
     * @brief Changes the size of the Window and trigger the onResize event
     * @return Returns the cirrent size of the Window
     */
    sf::Vector2u getSize();
};
