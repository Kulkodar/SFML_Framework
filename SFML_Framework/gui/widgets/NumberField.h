#pragma once

#include "EditBox.h"

/**
 * @brief A number field implementation of the edit field
 */
class NumberField : public EditBox
{

  public: // Constructor
    /**
     * @param id Unique id of the GUIWidget
     * @param size NumberField size
     * @param pos Initial position of the NumberField
     * @param imageset GUIImageset
     * @param handler Inputhandler to subscribe to the text event
     * @param charSize textSize
     */
    NumberField( std::string const& id, sf::Vector2f size, sf::Vector2f pos, GUIImageset& imageset,
                 InputHandler& handler, int charSize = 30 );
    /**Deleted copy Constructor!*/
    NumberField( NumberField& other ) = delete;
    /**Deleted move Constructor!*/
    NumberField( NumberField&& ) = delete;
    ~NumberField();

  public: // Methods
    /**
     * @brief
     * @param text
     */
    void handleTextInput( char32_t text ) override;

  public: // Operators
    /**Deleted copy assignment operator!*/
    NumberField& operator=( const NumberField& other ) = delete;
    /**Deleted move assignment operator!*/
    NumberField& operator=( NumberField&& ) = delete;

  protected: // Attributes
    // String as a number
    int number;

  public: // Getter Setter
    /**
     * @return the String as a number
     */
    int getNumber();
    /**
     * @brief Sets the string to the given number
     * @param num new number
     */
    void setNumber( int num );
};
