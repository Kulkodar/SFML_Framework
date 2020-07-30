#pragma once

#include "Checkbox.h"

/**
 * @brief A radial version of the check box
 */
class RadialCheckBox : public Checkbox
{
  public: // Constructor
    /**
     * @param id Unique id to find this GUIWidget in a container
     * @param text Label text
     * @param size Size of the check box
     * @param pos Position of the check box
     * @param imageset GUIImageset
     * @param charSize text size
     */
    RadialCheckBox( std::string const& id, std::string const& text, sf::Vector2f size, sf::Vector2f pos,
                    GUIImageset& imageset, int charSize = 30 );
    /**Deleted copy Constructor!*/
    RadialCheckBox( RadialCheckBox& other ) = delete;
    /**Deleted move Constructor!*/
    RadialCheckBox( RadialCheckBox&& ) = delete;
    ~RadialCheckBox();

  public: // Methods
  public: // Operators
    /**Deleted copy assignment operator!*/
    RadialCheckBox& operator=( const RadialCheckBox& other ) = delete;
    /**Deleted move assignment operator!*/
    RadialCheckBox& operator=( RadialCheckBox&& ) = delete;

  protected: // Attributes
  public:    // Getter Setter
};

