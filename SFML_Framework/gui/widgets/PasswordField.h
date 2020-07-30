#pragma once

#include "EditBox.h"

/**
 * @brief simple password field
 */
class PasswordField : public EditBox
{
  public: // Constructor
    /**
     * @param id Unique id of the GUIWidget
     * @param size edit box size
     * @param pos edit box position
     * @param imageset GUIImageset
     * @param game Reference to the current game
     * @param charSize Text size default = 30
     */
    PasswordField( std::string const& id, sf::Vector2f size, sf::Vector2f pos, GUIImageset& imageset,
                   InputHandler& handler, int charSize = 30 );
    /**Deleted copy Constructor!*/
    PasswordField( PasswordField& other ) = delete;
    /**Deleted move Constructor!*/
    PasswordField( PasswordField&& ) = delete;
    ~PasswordField();

  public: // Methods
  private:
    /**
     * Handles the text input.
     * @param text Ascii character.
     */
    void handleTextInput( char32_t text ) override;

  public: // Operators
    /**Deleted copy assignment operator!*/
    PasswordField& operator=( const PasswordField& other ) = delete;
    /**Deleted move assignment operator!*/
    PasswordField& operator=( PasswordField&& ) = delete;

  protected: // Attributes
    // Actual string
    sf::String buffer;

  public: // Getter Setter
    /**
     * @return the password.
     */
    sf::String& getPassword();
};
