#pragma once
/**
 * @file testState.h
 * Description
 *
 * @author AtomicDragon
 */
#include "SFML_Framework/Camera.h"
#include "SFML_Framework/Game.h"
#include "SFML_Framework/State.h"
#include "SFML_Framework/gui/GUIWidget.h"
#include "SFML_Framework/gui/widgets/Button.h"
#include "SFML_Framework/gui/widgets/Checkbox.h"
#include "SFML_Framework/gui/widgets/DropDownList.h"
#include "SFML_Framework/gui/widgets/NumberField.h"
#include "SFML_Framework/gui/widgets/PasswordField.h"
#include "SFML_Framework/gui/widgets/ScrollBar.h"
#include "SFML_Framework/gui/widgets/Slider.h"
#include "SFML_Framework/gui/widgets/Thumb.h"

/**
 * @class testState
 *
 * @brief
 */
class testState : public State
{
  public: // Constructor
    testState( Game& game, GUIImageset& img );
    /**
     * Deleted copy Constructor!
     */
    testState( testState& other ) = delete;
    /**
     * Deleted move Constructor!
     */
    testState( testState&& ) = delete;
    ~testState();

  public: // Methods
    void display( Window& window ) override;
    void handleEvents( InputHandler& handler ) override;
    void pause() override;
    void resume() override;
    void update( float delta ) override;

  public: // Operators
    /**
     * Deleted copy assignment operator!
     */
    testState& operator=( const testState& other ) = delete;
    /**
     * Deleted move assignment operator!
     */
    testState& operator=( testState&& ) = delete;

  protected: // Attributes
    GUIWidget* testWidget;
    sf::RectangleShape rect;

    Slider sizeXSlider;
    Slider sizeYSlider;

    Slider posXSlider;
    Slider posYSlider;

    Slider charSlider;

    Checkbox moveable;
    Checkbox hide;
    Checkbox disable;

    int funct;

  public: // Getter Setter
};
