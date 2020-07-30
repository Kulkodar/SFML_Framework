#pragma once

#include "../GUIImageset.h"
#include "../GUIWidget.h"
#include "Thumb.h"

/**
 * @brief A simple slider
 */
class Slider : public GUIWidget
{
  public: // Constructor
    /**
     * @param id Unique id of the GUIWidget.
     * @param size slider size.
     * @param pos slider position.
     * @param thumbSize size of the thumb
     * @param stepSize Size of the steps to move the thumb a bit
     * @param imageset GUIImageset.
     */
    Slider( std::string const& id, sf::Vector2f size, sf::Vector2f pos, sf::Vector2f thumbSize, float stepSize,
            GUIImageset& img, bool vertical = 0 );
    /**Deleted copy Constructor!*/
    Slider( Slider& other ) = delete;
    /**Deleted move Constructor!*/
    Slider( Slider&& ) = delete;
    ~Slider();

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
    Slider& operator=( const Slider& other ) = delete;
    /**Deleted move assignment operator!*/
    Slider& operator=( Slider&& ) = delete;

  protected: // Attributes
    /// Base shape.
    sf::RectangleShape base;

    /// Slider thumb
    Thumb thumb;

    /// Outside click prevention
    bool clickLock;
    /// Mouse over state.
    bool isMouseOver;

    /// Last mouse position.
    sf::Vector2f lastMousepos;

    /// Vertical state
    bool vertical;

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

    /**@return Returns the Thumb*/
    Thumb& getThumb();
    /**
     * @return True if the Slider is vertical
     */
    bool isVertical() const;
};

