#pragma once

#include "../GUIImageset.h"
#include "../GUIWidget.h"
#include "Label.h"

/**
 * @brief A simple Button
 */
class Button : public GUIWidget
{
  public: // Constructor
    /**
     * @param id Unique id of the GUIWidget.
     * @param text Label text.
     * @param size Button size.
     * @param pos Button position.
     * @param imageset GUIImageset.
     * @param charSize Text size default = 30.
     */
    Button( std::string const& id, std::string const& text, sf::Vector2f size, sf::Vector2f pos, GUIImageset& imageset,
            int charSize = 30 );
    /**Deleted copy Constructor!*/
    Button( Button& other ) = delete;
    /**Deleted move Constructor!*/
    Button( Button&& ) = delete;
    ~Button();

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

  private:
    /**
     * @brief recalculates the Position of the Label
     */
    void calcLabelPos();

  public: // Operators
    /**Deleted copy assignment operator!*/
    Button& operator=( const Button& other ) = delete;
    /**Deleted move assignment operator!*/
    Button& operator=( Button&& ) = delete;

  protected: // Attributes
    /// Locks the click event
    bool clickLock;
    /// Button label
    Label label;
    /// Button shape.
    sf::RectangleShape base;
    // UV's
    sf::IntRect uvClicked;
    sf::IntRect uvMouseover;
    sf::IntRect uvNormal;

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

    /**@return Label of the Button.*/
    Label& getLabel();
};
