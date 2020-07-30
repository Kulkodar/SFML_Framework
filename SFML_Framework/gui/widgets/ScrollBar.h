#pragma once

#include "../GUIImageset.h"
#include "../GUIWidget.h"
#include "Thumb.h"

/**
 * @brief Horizontal version of a scrollbar
 */
class ScrollBar : public GUIWidget
{
  public: // Constructor
    /**
     * @param id Unique id of the GUIWidget.
     * @param size scroll bar size.
     * @param pos scroll bar position.
     * @param windowsize Size of the virtual window.
     * @param imageset GUIImageset.
     */
    ScrollBar( std::string const& id, sf::Vector2f size, sf::Vector2f pos, float windowsize, GUIImageset& img,
               bool vertical );
    /**Deleted copy Constructor!*/
    ScrollBar( ScrollBar& other ) = delete;
    /**Deleted move Constructor!*/
    ScrollBar( ScrollBar&& ) = delete;
    ~ScrollBar();

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
    /**
     * Resize the Scrollbar.
     * @param windowsize New size.
     */
    void resize( float windowsize );

  private:
    /**Recalculates the size of the thumb.*/
    void calculateThumbSize();

  public: // Operators
    /**Deleted copy assignment operator!*/
    ScrollBar& operator=( const ScrollBar& other ) = delete;
    /**Deleted move assignment operator!*/
    ScrollBar& operator=( ScrollBar&& ) = delete;

  protected: // Attributes
    /// Base shape
    sf::RectangleShape base;
    /// Thumb
    Thumb thumb;
    /// virtual window size
    float windowSize;

    /// Mouse over flag
    bool isMouseOver;
    /// Outside click prevention
    bool clickLock;

    /// last mousepos buffer
    sf::Vector2f lastMousepos;

    /// vertical state
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

    /**@return Thumb*/
    Thumb& getThumb();
    /**
     * @return True if Scrollbar is vertical
     */
    bool isVertical() const;
};
