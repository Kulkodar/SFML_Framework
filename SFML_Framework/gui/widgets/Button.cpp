#include "Button.h"
#include <SFML/OpenGL.hpp>
#include <iostream>

Button::Button( std::string const& id, std::string const& text, sf::Vector2f size, sf::Vector2f pos,
                GUIImageset& imageset, int charSize )
    : GUIWidget( id )
    , label( "", text, sf::Vector2f( 0, 0 ), imageset, charSize )
{
    // Set Button variables.
    this->uvClicked = imageset.UVs[UVType::ButtonClicked];
    this->uvMouseover = imageset.UVs[UVType::ButtonMouseover];
    this->uvNormal = imageset.UVs[UVType::ButtonNormal];
    this->clickLock = 0;
    //---

    // Create Button shape.
    this->base.setSize( size );
    this->base.setPosition( pos );
    this->base.setTexture( &imageset.guiTexture );
    this->base.setTextureRect( this->uvNormal );
    this->base.setFillColor( sf::Color::White );
    //---

    calcLabelPos();
}

Button::~Button()
{
}

void Button::handleEvents( InputHandler& handler, sf::View* view )
{
    if( !disabled )
    {
        sf::Vector2f mapedPos = ( view != nullptr ) ? handler.getMousePosMapped( *view ) : handler.getMousePos();
        // Check Mouseover
        if( base.getGlobalBounds().contains( mapedPos.x, mapedPos.y ) )
        {
            // Run olny if widget is not moveable
            if( !moveable )
            {
                base.setTextureRect( uvMouseover );
                // Check Button press.
                if( handler.isMButtonDown( sf::Mouse::Left ) && !clickLock )
                    base.setTextureRect( uvClicked );
                if( handler.isMButtonPressed( sf::Mouse::Left ) )
                    EventClicked.emit();
                if( handler.isMButtonReleased( sf::Mouse::Left ) )
                {
                    if( !clickLock )
                        EventReleased.emit();
                    clickLock = 0;
                }
            }
        }
        else
        {
            // Outside click prevention.
            if( handler.isMButtonPressed( sf::Mouse::Left ) )
                clickLock = 1;
            else if( handler.isMButtonReleased( sf::Mouse::Left ) )
                clickLock = 0;
            base.setTextureRect( uvNormal );
        }

        // Move Widget
        if( moveable && !clickLock )
        {
            if( handler.isMouseMoved() && handler.isMButtonDown( sf::Mouse::Left ) )
            {
                sf::Vector2f p = getPosition();
                sf::Vector2f delta =
                    ( view != nullptr ) ? handler.getMouseDeltaMapped( *view ) : handler.getMouseDelta();
                p.x += delta.x;
                p.y += delta.y;
                setPosition( p );
                Moved.emit( delta );
            }
        }
    }
}

void Button::update( float delta )
{
}

void Button::draw( Window& window, int currentStencilValue )
{
    if( !hiden )
    {
        glStencilFunc( GL_EQUAL, currentStencilValue, 0xff );
        glStencilOp( GL_KEEP, GL_KEEP, GL_INCR );
        glStencilMask( 0xff );

        window.draw( base );

        label.draw( window, ++currentStencilValue );
    }
}

void Button::disable( bool disable )
{
    disabled = disable;

    label.disable( disable );

    base.setFillColor( sf::Color( disabled ? 0x666666ff : 0xffffffff ) );
}

void Button::calcLabelPos()
{
    float posX = 0, posY = 0;

    posY = base.getPosition().y + base.getSize().y / 2.0f - ( label.getCharSize() / 2.0f * 1.25f );
    posX = base.getPosition().x + ( base.getSize().x - label.getSize().x ) / 2.0f;

    label.setPosition( {posX, posY} );
}

sf::Vector2f Button::getPosition()
{
    return base.getPosition();
}

sf::Vector2f Button::getSize()
{
    return base.getSize();
}

sf::Vector2f Button::getOrigin()
{
    return base.getOrigin();
}

void Button::setPosition( sf::Vector2f pos )
{
    base.setPosition( pos );
    calcLabelPos();
}

void Button::setSize( sf::Vector2f size )
{
    base.setSize( size );
    calcLabelPos();
}

void Button::setOrigin( sf::Vector2f oo )
{
    base.setOrigin( oo );
    calcLabelPos();
}

Label& Button::getLabel()
{
    return this->label;
}
