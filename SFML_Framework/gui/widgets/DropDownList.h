#pragma once

#include "../GUIWidget.h"
#include "Label.h"
#include "ScrollBar.h"

/**
 * @brief Helper class used in the DropDownList.
 */
class DropDownListItem
{
  public: // Constructor
    /**
     *
     * @param text Text of the item.
     * @param size Size of the item
     * @param img Reference to a GUIImageset.
     * @param charsize Size of the text.
     */
    DropDownListItem( std::string const& text, sf::Vector2f size, GUIImageset& img, uint charsize = 30 );
    /**Deleted copy Constructor!*/
    DropDownListItem( DropDownListItem& other ) = delete;
    /**Deleted move Constructor!*/
    DropDownListItem( DropDownListItem&& ) = delete;
    ~DropDownListItem();

  public: // Methods
    /**
     * Draws the item at a specific location.
     * @param window Target window.
     * @param currentStencilValue
     * @param pos Position where it should be drawn.
     */
    void draw( Window& window, int currentStencilValue, sf::Vector2f pos );

    /**
     * Disables the DropDownListItem.
     * @param disabled State.
     */
    void disable( bool disable );

  public: // Operators
    /**Deleted copy assignment operator!*/
    DropDownListItem& operator=( const DropDownListItem& other ) = delete;
    /**Deleted move assignment operator!*/
    DropDownListItem& operator=( DropDownListItem&& ) = delete;

  protected: // Attributes
    // Label to display
    Label label;
    // used to debug and mouse over calculation.
    sf::RectangleShape base;

  public: // Getter Setter
    /**
     * Checks if the given coordinates is in the boundary of the item.
     * @param mappedMPos Position mapped to the current view.
     * @return true if coordinates are inside the boundary.
     */
    bool isMouseover( sf::Vector2f mappedMPos );

    /**
     * Set's the size of the item.
     * @param size New size.
     * @param charSize New character size.
     */
    void setSize( sf::Vector2f size, int charSize );

    Label& getLabel()
    {
        return label;
    }
};

/**
 * @class DropDownList
 *
 * @brief A simple DropDownList widget.
 */
class DropDownList : public GUIWidget
{
  public: // Constructor
    /**
     * @param id Unique id of the GUIWidget.
     * @param size DropDownList size.
     * @param pos DropDownList position.
     * @param img GUIImageset.
     */
    DropDownList( std::string const& id, sf::Vector2f size, sf::Vector2f pos, GUIImageset& img );
    /**Deleted copy Constructor!*/
    DropDownList( DropDownList& other ) = delete;
    /**Deleted move Constructor!*/
    DropDownList( DropDownList&& ) = delete;
    ~DropDownList();

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
     *
     * @param name Name of the item.
     */
    void addItem( std::string const& name );

    /**
     * Selects an item.
     * @param i item index.
     */
    void select( int i );

    void remove( int i );

    DropDownListItem* getItem( int i );

  public: // Operators
    /**Deleted copy assignment operator!*/
    DropDownList& operator=( const DropDownList& other ) = delete;
    /**Deleted move assignment operator!*/
    DropDownList& operator=( DropDownList&& ) = delete;

  protected: // Attributes
    GUIImageset& img;

    ScrollBar bar;
    float offset;

    sf::RectangleShape base;
    sf::RectangleShape base2;
    sf::RectangleShape backdrop;
    sf::RectangleShape backdropEnd;

    sf::FloatRect itemRegion;
    sf::FloatRect mouseRegion;

    bool backdropUnfold;
    unsigned int numDisItems;

    std::vector<DropDownListItem*> items;
    int currentItem;

    bool lock;
    bool lock2;
    bool mouseOver;

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
