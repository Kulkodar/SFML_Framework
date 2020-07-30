#pragma once

#include "../GUIImageset.h"
#include "../GUIWidget.h"
#include "Label.h"

/**
 * @brief A GUI ProgressBar class
 */
class ProgressBar : public GUIWidget
{
  public: // Constructor
    /**
     * @param id unique id to find this widget in a container.
     * @param text Initial text to display
     * @param size Size of the ProgressBar.
     * @param pos Position of the ProgressBar.
     * @param imageset
     * @param charSize text size
     */
    ProgressBar( std::string const& id, std::string const& text, sf::Vector2f size, sf::Vector2f pos,
                 GUIImageset& imageset, int charsize = 30 );
    /**Deleted copy Constructor!*/
    ProgressBar( ProgressBar& other ) = delete;
    /**Deleted move Constructor!*/
    ProgressBar( ProgressBar&& ) = delete;
    ~ProgressBar();

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
     * Changes the value of progress (0 - 100).
     * @param value Value to add or subtract.
     */
    void changeValue( float value );
    /**
     * Sets the value of progress (0 - 100).
     * @param value New value.
     */
    void setValue( float value );

  public: // Operators
    /**
     * Deleted copy assignment operator!
     */
    ProgressBar& operator=( const ProgressBar& other ) = delete;
    /**
     * Deleted move assignment operator!
     */
    ProgressBar& operator=( ProgressBar&& ) = delete;

  protected: // Attributes
    /// Base shape.
    sf::RectangleShape base;
    /// Progress overlay
    sf::RectangleShape bar;
    /// Progress text.
    Label label;

    /// UV buffer.
    sf::IntRect uv;

    /// Last mouse position.
    sf::Vector2f lastMousepos;
    /// Mouse over state.
    bool movementLock;
    /// click lock
    bool clickLock;
    /// Progress value.
    float val;

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

    /**@return progress.*/
    float getValue() const;

    /**@return Progressbar label*/
    Label& getLabel();
};
