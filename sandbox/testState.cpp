#include <iostream>

#include "SFML_Framework/gui/widgets/ColorPicker.h"
#include "SFML_Framework/gui/widgets/Spinner.h"
#include "testState.h"

testState::testState( Game& game, GUIImageset& img )
    : State( game, sf::Vector2f( 500, 500 ) )
    , sizeXSlider( "", sf::Vector2f( 10, 100 ), sf::Vector2f( 10, 390 ), sf::Vector2f( 10, 10 ), 1, img, 1 )
    , sizeYSlider( "", sf::Vector2f( 10, 100 ), sf::Vector2f( 30, 390 ), sf::Vector2f( 10, 10 ), 1, img, 1 )
    , posXSlider( "", sf::Vector2f( 10, 100 ), sf::Vector2f( 50, 390 ), sf::Vector2f( 10, 10 ), 1, img, 1 )
    , posYSlider( "", sf::Vector2f( 10, 100 ), sf::Vector2f( 70, 390 ), sf::Vector2f( 10, 10 ), 1, img, 1 )
    , charSlider( "", sf::Vector2f( 10, 100 ), sf::Vector2f( 90, 390 ), sf::Vector2f( 10, 10 ), 1, img, 1 )
    , moveable( "", "Moveable", sf::Vector2f( 10, 10 ), sf::Vector2f( 110, 420 ), img, 10 )
    , hide( "", "Hide", sf::Vector2f( 10, 10 ), sf::Vector2f( 110, 440 ), img, 10 )
    , disable( "", "Disable", sf::Vector2f( 10, 10 ), sf::Vector2f( 110, 460 ), img, 10 )
{

    testWidget = new ColorPicker( "", sf::Vector2f( 20, 20 ), sf::Vector2f( 0, 0 ), sf::Vector2f( 200, 100 ), 50, img );

    sizeXSlider.ValueChanged.connect(
        [&]( float f ) { testWidget->setSize( sf::Vector2f( f * 2, testWidget->getSize().y ) ); } );

    sizeYSlider.ValueChanged.connect(
        [&]( float f ) { testWidget->setSize( sf::Vector2f( testWidget->getSize().x, f / 3 ) ); } );

    posXSlider.ValueChanged.connect(
        [&]( float f ) { testWidget->setPosition( sf::Vector2f( f + 10, testWidget->getPosition().y ) ); } );

    posYSlider.ValueChanged.connect(
        [&]( float f ) { testWidget->setPosition( sf::Vector2f( testWidget->getPosition().x, f + 10 ) ); } );

    charSlider.ValueChanged.connect(
        [&]( float f ) { ( (ColorPicker*)testWidget )->setColor( sf::Color( f, f, f, 255 ) ); } );

    moveable.CheckboxChecked.connect( [&]( bool b ) { testWidget->setMoveable( b ); } );

    hide.CheckboxChecked.connect( [&]( bool b ) { testWidget->hide( b ); } );

    disable.CheckboxChecked.connect( [&]( bool b ) { testWidget->disable( b ); } );

    rect.setSize( {1000, 1000} );
}

testState::~testState()
{
    game.getWindow().onResize.disconnect( funct );
}

void testState::display( Window& window )
{
    window.getSFMLWindow().setView( cam.getView() );
    //    window.draw( rect );
    testWidget->draw( window, 0 );

    sizeXSlider.draw( window, 0 );
    sizeYSlider.draw( window, 0 );
    posXSlider.draw( window, 0 );
    posYSlider.draw( window, 0 );
    charSlider.draw( window, 0 );
    moveable.draw( window, 0 );
    hide.draw( window, 0 );
    disable.draw( window, 0 );
}

void testState::handleEvents( InputHandler& handler )
{
    testWidget->handleEvents( handler, &cam.getView() );

    sizeXSlider.handleEvents( handler, &cam.getView() );
    sizeYSlider.handleEvents( handler, &cam.getView() );
    posXSlider.handleEvents( handler, &cam.getView() );
    posYSlider.handleEvents( handler, &cam.getView() );
    charSlider.handleEvents( handler, &cam.getView() );
    moveable.handleEvents( handler, &cam.getView() );
    hide.handleEvents( handler, &cam.getView() );
    disable.handleEvents( handler, &cam.getView() );
}

void testState::pause()
{
}

void testState::resume()
{
}

void testState::update( float delta )
{
}
