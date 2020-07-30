#pragma once

#include "Label.h"
#include <SFML/System.hpp>

#include "../GUIImageset.h"
#include "../GUIWidget.h"

/**
 * @brief A simple check box widget
 */
class Checkbox : public GUIWidget
{
  public: // Constructor
    /**
     * @param id Unique id to find this GUIWidget in a container.
     * @param text Label text.
     * @param size Size of the check box.
     * @param pos Position of the check box.
     * @param imageset GUIImageset.
     * @param charSize size of the chars in pixsel
     */
    Checkbox( std::string const& id, std::string const& text, sf::Vector2f size, sf::Vector2f pos,
              GUIImageset& imageset, int charSize = 10 );
    /**Deleted copy Constructor!*/
    Checkbox( Checkbox& other ) = delete;
    /**Deleted move Constructor!*/
    Checkbox( Checkbox&& ) = delete;
    ~Checkbox();

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

  public: // Operators
    /**Deleted copy assignment operator!*/
    Checkbox& operator=( const Checkbox& other ) = delete;
    /**Deleted move assignment operator!*/
    Checkbox& operator=( Checkbox&& ) = delete;

  protected: // Attributes
    // uv
    sf::IntRect uvNormal;
    // uv
    sf::IntRect uvMouseover;
    // Click lock
    bool clickLock;
    // Check box state
    bool state;
    // Checkbox shape.
    sf::RectangleShape base;
    sf::RectangleShape mark;
    // Checkbox Label
    Label label;

  public: // Getter Setter
    /**
     * Sets the state.
     * @param state New state.
     */
    void setState( bool state );
    ///@return Current state.
    bool getState() const;

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

    /**@return Checkbox Label.*/
    Label& getLabel();
};
