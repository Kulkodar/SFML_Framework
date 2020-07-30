#pragma once

#include "../GUIImageset.h"
#include "../GUIWidget.h"
#include "Slider.h"
#include "Thumb.h"

/**
 * @class ColorPicker
 * @brief A color picker
 * @author AtomicDragon
 * @file ColorPicker.h
 */
class ColorPicker : public GUIWidget
{
  public: // Constructor
    ColorPicker( std::string const& id, sf::Vector2f size, sf::Vector2f pos, sf::Vector2f pickerSize, float squareSize,
                 GUIImageset& img, int charSize = 30 );
    ~ColorPicker();

  public: // Methoden
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

  protected: // Attributes
    sf::RectangleShape colorButtonBase;
    sf::RectangleShape colorButtonCol;

    sf::RectangleShape background;
    Slider R;
    Slider G;
    Slider B;
    sf::RectangleShape colDisplay;

    sf::Color color;

    bool showPicker;

    bool clickLock;

  public: // Getter Setter
    /**@return Size of the widget*/
    sf::Vector2f getSize() override;
    /**@return Position of the widget*/
    sf::Vector2f getPosition() override;
    /**@return Origin of the widget*/
    sf::Vector2f getOrigin() override;

    /**
     * Sets the size of the widget
     * @param size New widget size
     */
    void setSize( sf::Vector2f size ) override;
    /**
     * Sets the position of the widget
     * @param pos New widget position
     */
    void setPosition( sf::Vector2f pos ) override;
    /**
     * Sets the origin of the widget
     * @param oo New widget origin
     */
    void setOrigin( sf::Vector2f oo ) override;

    /**
     * @return selected color
     */
    sf::Color getColor();

    /**
     * @param color Sets a specific color
     */
    void setColor( sf::Color color );
};
