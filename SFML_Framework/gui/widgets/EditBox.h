#pragma once

#include "../../Game.h"
#include "../GUIImageset.h"
#include "../GUIWidget.h"
#include "Label.h"

/**
 * @brief A simple edit box for text and numbers
 */
class EditBox : public GUIWidget
{
  public: // Constructor
    /**
     * @param id Unique id of the GUIWidget.
     * @param size edit box size.
     * @param pos edit box position.
     * @param imageset GUIImageset.
     * @param game Reference to the current game.
     * @param charSize Text size default = 30.
     */
    EditBox( std::string const& id, sf::Vector2f size, sf::Vector2f pos, GUIImageset& imageset, InputHandler& handler,
             int charSize = 30 );
    /**Deleted copy Constructor!*/
    EditBox( EditBox& other ) = delete;
    /**Deleted move Constructor!*/
    EditBox( EditBox&& ) = delete;
    ~EditBox();

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
     * Handles the text input.
     * @param text Ascii character.
     */
    virtual void handleTextInput( char32_t text );
    /**Calculates the position of the label*/
    virtual void calulateLabelPostion();

  public: // Operators
    /**Deleted copy assignment operator!*/
    EditBox& operator=( const EditBox& other ) = delete;
    /**Deleted move assignment operator!*/
    EditBox& operator=( EditBox&& ) = delete;

  protected: // Attributes
    // Base shape of the edit box.
    sf::RectangleShape base;
    // Active state.
    bool isActive;
    // Reference to the InputHandler
    InputHandler& handler;
    // Button click lock.
    bool clickLock;
    // Editbox Label
    Label label;
    // Event function id buffer
    int funcID;

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

    /**@return Label of the editbox.*/
    Label& getLabel();
};

