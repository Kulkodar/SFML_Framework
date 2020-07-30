#pragma once

#include "../GUIImageset.h"
#include "../GUIWidget.h"

/**
 * @class Label
 * @brief A GUI Label class
 * @author AtomicDragon
 * @file Label.h
 */
class Label : public GUIWidget
{
  public: // Constructor
    /**
     * @param id Unique id of the GUIWidget
     * @param text Label text
     * @param pos Label position
     * @param imageset GUIImageset
     * @param charSize Text size default = 30
     */
    Label( std::string const& id, std::string const& text, sf::Vector2f pos, GUIImageset& imageset,
           uint charsize = 30 );
    /**Deleted copy Constructor!*/
    Label( Label& other ) = delete;
    /**Deleted move Constructor!*/
    Label( Label&& ) = delete;
    ~Label();

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
    Label& operator=( const Label& other ) = delete;
    /**Deleted move assignment operator!*/
    Label& operator=( Label&& ) = delete;

  protected: // Attributes
    /// SFML text object
    sf::Text label;
    /// move lock
    bool movementLock;
    /// click lock
    bool clickLock;
    /// Move position
    sf::Vector2f lastMousepos;
    /// color buffer
    sf::Color col;

  public: // Getter Setter
    /**@return Size of the widget.*/
    sf::Vector2f getSize() override;
    /**@return Position of the widget.*/
    sf::Vector2f getPosition() override;
    /**@return Origin of the widget.*/
    sf::Vector2f getOrigin() override;

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

    /**@return The text of the label.*/
    const sf::String& getText() const;
    /**@return The height of the label.*/
    int getCharSize() const;

    /**
     * Sets the labels text.
     * @param text New text.
     */
    void setText( sf::String const& text );
    /**
     * Sets the height of the text.
     * @param size New text height.
     */
    void setCharSize( int size );

    /**
     * Changes the fill of the text.
     * @param col
     */
    void setFillColor( sf::Color col );

    /**@return the fill of the text.*/
    sf::Color getFillColor();
};
