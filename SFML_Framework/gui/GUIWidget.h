#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <string>

#include "../Window.h"
#include "../SignalSlot.h"

/**
 * @brief Template class of a GUIWidget used in the GUI
 */
class GUIWidget
{
  public: // Constructor
    /**@param id Unique id to find the Widget in a container*/
    GUIWidget( std::string const& id );
    GUIWidget();
    /**Deleted copy Constructor!*/
    GUIWidget( GUIWidget& other ) = delete;
    /**Deleted move Constructor!*/
    GUIWidget( GUIWidget&& ) = delete;
    virtual ~GUIWidget();

  public: // Methods
    /**
     * @brief Handles user input
     * @param handler user input handler
     * @param view View to map the coursor position
     */
    virtual void handleEvents( InputHandler& handler, sf::View* view = nullptr ) = 0;
    /**
     * Updates the Widget
     * @param delta Current frame time
     */
    virtual void update( float delta ) = 0;
    /**
     * Draws the Widget
     * @param window Target window
     * @param currentStencilValue OpenGL stencil value/ Layer to draw on
     */
    virtual void draw( Window& window, int currentStencilValue ) = 0;
    /**
     * Disables/Enables the widget
     * @param disabled State of the widget
     */
    virtual void disable( bool disabled );
    /**
     * Hides or unhides the widget
     * @param hiden State
     */
    void hide( bool hiden );

  public: // Events
    Signal<bool> CheckboxChecked;
    Signal<> EventClicked;
    Signal<> EventReleased;
    Signal<sf::Vector2f> Moved;
    Signal<float> ValueChanged;
    Signal<int> ItemSelected;
    Signal<sf::Color> ColorChanged;

  public: // Operators
    /**Deleted copy assignment operator!*/
    GUIWidget& operator=( const GUIWidget& other ) = delete;
    /**Deleted move assignment operator!*/
    GUIWidget& operator=( GUIWidget&& ) = delete;

  protected: // Attributes
    /// Disabled state
    bool disabled;
    /// Hiden state
    bool hiden;
    /// Unique id to find it in a container
    std::string id;
    /// Movable state
    bool moveable;

  public: // Getter Setter
    /**@return disabled state*/
    bool isDisabled() const;
    /**@return hidden state*/
    bool isHiden() const;
    /**@return movable state*/
    bool isMoveable() const;

    /**@return Widget id*/
    std::string const& getId() const;

    /**
     * Enables disables widget moving
     * @param moveable State
     */
    void setMoveable( bool moveable );

    /**@return Size of the widget*/
    virtual sf::Vector2f getSize();
    /**@return Position of the widget*/
    virtual sf::Vector2f getPosition();
    /**@return Origin of the widget*/
    virtual sf::Vector2f getOrigin();

    /**
     * Sets the size of the widget
     * @param size New widget size
     */
    virtual void setSize( sf::Vector2f size );
    /**
     * Sets the position of the widget
     * @param pos New widget position
     */
    virtual void setPosition( sf::Vector2f pos );
    /**
     * Sets the origin of the widget
     * @param oo New widget origin
     */
    virtual void setOrigin( sf::Vector2f oo );
};
