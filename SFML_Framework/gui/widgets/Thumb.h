#pragma once

#include "../GUIImageset.h"
#include "../GUIWidget.h"

enum ThumbType
{
    HorizontalSlider,
    VerticalSlider,
    HorizontalSroller,
    VerticalScroller,
    ColorPickerT
};

/**
 * @brief Simple thumb
 */
class Thumb : public GUIWidget
{
  public: // Constructor
    /**
     * @param id Unique id to find the Widget in a container
     * @param pos Position of the Thumb
     * @param size Size of the Thumb
     * @param img GUIImageset
     * @param type ThumbType
     */
    Thumb( std::string const& id, sf::Vector2f pos, sf::Vector2f size, GUIImageset& img, ThumbType type );
    /**Deleted copy Constructor!*/
    Thumb( Thumb& other ) = delete;
    /**Deleted move Constructor!*/
    Thumb( Thumb&& ) = delete;
    ~Thumb();

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
     * @brief Moves the Thumb to a specific location ,clamp to the region it is allowed to be
     * @param pos New poisition
     */
    void moveThumb( sf::Vector2f pos );
    /**
     * @brief Resizes the region
     * @param size New region size
     */
    void resize( sf::Vector2f size );

  public: // Operators
    /**Deleted copy assignment operator!*/
    Thumb& operator=( const Thumb& other ) = delete;
    /**Deleted move assignment operator!*/
    Thumb& operator=( Thumb&& ) = delete;

  protected: // Attributes
    ThumbType type;

    sf::Vector2f value;
    sf::Vector2f maxValue;
    sf::Vector2f minValue;

    sf::FloatRect region;

    sf::RectangleShape base;

    // UV's
    sf::IntRect uvNormal;
    sf::IntRect uvMouseOver;

    // Outside click prevention
    bool clickLock;
    // Mouse over state.
    bool isMouseOver;

    sf::Vector2f lastMousepos;

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

    /**
     * @brief
     * @param region
     */
    void setRegion( sf::FloatRect region );

    /**
     * @return the region of the Thumb
     */
    sf::FloatRect getRegion() const;
    /**
     * @return the current Thumb value
     */
    sf::Vector2f getValue() const;

    /**
     * @brief sets the value of the Thumb
     * @param val New value
     */
    void setValue( sf::Vector2f val );

    /**
     * @param max Max value of the Thumb
     */
    void setMaxValue( sf::Vector2f max );
    /**
     * @param min Min value of the Thumb
     */
    void setMinValue( sf::Vector2f min );

    /**
     * @return the max value of the Tumb
     */
    sf::Vector2f getMaxValue();
    /**
     * @return the min value of the Thumb
     */
    sf::Vector2f getMinValue();
};