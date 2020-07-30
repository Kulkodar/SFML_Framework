#pragma once

#include "Button.h"      // Base class: Button
#include "NumberField.h" // Base class: NumberField

/**
 * @brief A Button special for the Spinner
 */
class SpinnerButton : public Button
{
  public: // Constructor
    /**
     * @param size Size of the SpinnerButton
     * @param pos Position of the SpinnerButton
     * @param imageset A GUIImageset
     * @param down if the SpinnerButton points downwards
     */
    SpinnerButton( sf::Vector2f size, sf::Vector2f pos, GUIImageset& imageset, bool down );

  public:    // Methods
  protected: // Attributes
};

/**
 * @class Spinner
 * @brief A NumberField with buttons
 * @author AtomicDragon
 * @file Spinner.h
 */
class Spinner : public NumberField
{
  public: // Constructor
    /**
     * @param id Unique id of the GUIWidget
     * @param size NumberField size
     * @param pos Initial position of the NumberField
     * @param imageset GUIImageset
     * @param handler Inputhandler to subscribe to the text event
     * @param charSize textSize
     */
    Spinner( std::string const& id, sf::Vector2f size, sf::Vector2f pos, GUIImageset& imageset, InputHandler& handler,
             int charSize = 30 );
    ~Spinner();

  public: // Methods
    /**
     * @brief Handles user input
     * @param handler user input handler
     * @param view View to map the coursor position
     */
    void handleEvents( InputHandler& handler, sf::View* view = nullptr ) override;
    /**
     * Updates the Widget
     * @param delta Current frame time
     */
    void update( float delta ) override;
    /**
     * Draws the Widget
     * @param window Target window
     * @param currentStencilValue OpenGL stencil value/ Layer to draw on
     */
    void draw( Window& window, int currentStencilValue ) override;
    /**
     * Disables/Enables the widget
     * @param disabled State of the widget
     */
    void disable( bool disabled ) override;

  public:    // Operators
  protected: // Attributes
    /** Button to increase the value*/
    SpinnerButton up;
    /** Button to decrease the value*/
    SpinnerButton down;

  public: // Getter Setter
    /**@return Size of the widget.*/
    sf::Vector2f getSize() override;
    /**@return Position of the widget.*/
    sf::Vector2f getPosition() override;
    /**@return Origin of the widget.*/
    sf::Vector2f getOrigin() override;

    /**
     * Sets the size of the widget.
     * @param size New widget size.
     */
    void setSize( sf::Vector2f size ) override;
    /**
     * Sets the position of the widget.
     * @param pos New widget position.
     */
    void setPosition( sf::Vector2f pos ) override;
    /**
     * Sets the origin of the widget.
     * @param oo New widget origin.
     */
    void setOrigin( sf::Vector2f oo ) override;
};
