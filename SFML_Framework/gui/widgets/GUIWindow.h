#pragma once

#include "../GUIWidget.h"
#include "ScrollBar.h"

/**
 * @author AtomicDragon
 */
class GUIWindow : public GUIWidget
{
  public: // Constructor
    /**
     * @param id Unique id of the GUIWidget
     * @param size window dimensions
     * @param scrolbarSize size of the Scrollbars
     * @param pos window position
     * @param img GUIImageset
     */
    GUIWindow( std::string const& id, sf::Vector2f size, float scrolbarSize, sf::Vector2f pos, GUIImageset& img );
    /**Deleted copy Constructor!*/
    GUIWindow( GUIWindow& other ) = delete;
    /**Deleted move Constructor!*/
    GUIWindow( GUIWindow&& ) = delete;
    ~GUIWindow();

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
     * @brief Adds a GUIWidget to the window
     * @param child GUIWidget to add
     * @param pos Start position to draw
     */
    void addChid( GUIWidget* child, sf::Vector2u pos );

  public: // Operators
    /**
     * Deleted copy assignment operator!
     */
    GUIWindow& operator=( const GUIWindow& other ) = delete;
    /**
     * Deleted move assignment operator!
     */
    GUIWindow& operator=( GUIWindow&& ) = delete;

  protected: // Attributes
    sf::RectangleShape base;
    std::vector<GUIWidget*> childs;

    sf::Vector2f delta;
    sf::Vector2f insideBounds;
    sf::Vector2f last;

    ScrollBar* scrollBarV;
    ScrollBar* scrollBarH;

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
     * @param size New widget position.
     */
    void setPosition( sf::Vector2f pos ) override;
    /**
     * Sets the origin of the widget.
     * @param size New widget origin.
     */
    void setOrigin( sf::Vector2f oo ) override;

    /**
     * @return A GUIWidget if id was found else nullptr
     * @param ID ID of the GUIWidget
     */
    GUIWidget* getChid( std::string const& ID );
};
