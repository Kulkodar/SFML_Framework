#pragma once

#include <string>

#include <SFML/Graphics.hpp>

enum UVType
{
    ButtonNormal = 0,
    ButtonMouseover,
    ButtonClicked,
    CheckboxNormal,
    CheckboxMouseover,
    CheckboxMark,
    ProgressBarBase,
    ProgressBarBar,
    SliderVerticalBase,
    SliderVerticalThumb,
    SliderVerticalThumbHover,
    SliderHorizontalBase,
    SliderHorizontalThumb,
    SliderHorizontalThumbHover,
    EditBoxBase,
    RadialCheckBoxBase,
    RadialCheckBoxMouseover,
    RadialCheckBoxBaseMark,
    ScrollBarBase,
    ScrollBarThumbBase,
    ScrollBarThumbMouseOver,
    ScrollBarBaseH,
    ScrollBarThumbBaseH,
    ScrollBarThumbMouseOverH,
    DropDownListLeftNormal,
    DropDownListLeftHover,
    DropDownListRightNormal,
    DropDownListRightHover,
    DropDownListBack,
    DropDownListBackBottom,
    SpinnerUpHover,
    SpinnerUpNormal,
    SpinnerDownHover,
    SpinnerDownNormal,
    ColorPickerThumbNormal,
    ColorPickerThumbHover,
    ColorPickerButton
};

/**
 * @class GUIImageset
 * @brief Container of information for GUIWidget like UV's.
 * @author AtomicDragon
 * @file GUIImageset.h
 */
class GUIImageset
{
  public: // Constructor
    /**
     * @param configFile Path to the configuration file
     */
    GUIImageset( std::string const& configFile );
    /**
     * Deleted copy Constructor!
     */
    GUIImageset( GUIImageset& other ) = delete;
    /**
     * Deleted move Constructor!
     */
    GUIImageset( GUIImageset&& ) = delete;
    ~GUIImageset();

  public: // Methods
  public: // Operators
    /**
     * Deleted copy assignment operator!
     */
    GUIImageset& operator=( const GUIImageset& other ) = delete;
    /**
     * Deleted move assignment operator!
     */
    GUIImageset& operator=( GUIImageset&& ) = delete;

  public: // Attributes
    /// Font for the gui.
    sf::Font guiFont;
    /// GUI text color.
    sf::Color guiTextColor;
    /// GUI text outline color.
    sf::Color guiTextOutlineColor;
    /// Texture of the GUI.
    sf::Texture guiTexture;
    /// Outline strength.
    float outlineThicness;

    /// Array of UV cords.
    sf::IntRect UVs[37];

  public: // Getter Setter
};

