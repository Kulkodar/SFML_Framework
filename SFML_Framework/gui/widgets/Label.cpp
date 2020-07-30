#include "Label.h"

Label::Label( std::string const& id, std::string const& text, sf::Vector2f pos, GUIImageset& imageset, uint charsize )
    : GUIWidget( id )
    , label( text, imageset.guiFont, charsize )
{
    // Set attributes to default
    this->movementLock = 0;
    this->clickLock = 0;
    this->lastMousepos = {10000, 0};
    this->col = imageset.guiTextColor;
    //---

    // Create label
    label.setPosition( pos );
    label.setFillColor( imageset.guiTextColor );
    label.setOutlineColor( imageset.guiTextOutlineColor );
    label.setOutlineThickness( imageset.outlineThicness );
    //---
}

Label::~Label()
{
}

void Label::disable( bool diable )
{
    disabled = diable;
    if( diable )
        label.setFillColor( col * sf::Color( 0x666666ff ) );
    else
        label.setFillColor( col );
}

void Label::handleEvents( InputHandler& handler, sf::View* view )
{
    sf::Vector2f mapedPos = ( view != nullptr ) ? handler.getMousePosMapped( *view ) : handler.getMousePos();
    if( !disabled )
    {
        // Check Mouseover
        if( label.getGlobalBounds().contains( mapedPos.x, mapedPos.y ) )
        {
            if( !clickLock )

                movementLock = 0;
        }
        else
        {
            // outside click prevention
            if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
                clickLock = 1;
            else
                clickLock = 0;
        }

        // Move Widget
        if( moveable && !movementLock )
        {
            if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
            {
                if( lastMousepos.x != 10000 )
                {
                    sf::Vector2f p = getPosition();
                    sf::Vector2f delta = {mapedPos.x - lastMousepos.x, mapedPos.y - lastMousepos.y};
                    p.x += delta.x;
                    p.y += delta.y;
                    setPosition( p );
                    if( delta.x != 0 || delta.y != 0 )
                        Moved.emit( delta );
                }
                lastMousepos = mapedPos;
            }
            else
            {
                movementLock = 1;
                lastMousepos = {10000, 0};
            }
        }
    }
}

void Label::draw( Window& window, int currentStencilValue )
{
    if( !hiden )
    {
        glStencilFunc( GL_EQUAL, currentStencilValue, 0xff );
        glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
        glStencilMask( 0xff );

        window.draw( label );
    }
}

void Label::update( float delta )
{
}

void Label::setText( sf::String const& text )
{
    this->label.setString( text );
}

sf::Vector2f Label::getOrigin()
{
    return label.getOrigin();
}

sf::Vector2f Label::getPosition()
{
    return label.getPosition();
}

void Label::setOrigin( sf::Vector2f oo )
{
    label.setOrigin( oo );
}

void Label::setPosition( sf::Vector2f pos )
{
    label.setPosition( pos );
}

void Label::setCharSize( int size )
{
    label.setCharacterSize( size );
}

sf::Vector2f Label::getSize()
{
    return sf::Vector2f( label.getGlobalBounds().width, label.getGlobalBounds().height );
}

const sf::String& Label::getText() const
{
    return label.getString();
}

int Label::getCharSize() const
{
    return label.getCharacterSize();
}

void Label::setFillColor( sf::Color col )
{
    this->col = col;
    label.setFillColor( col );
}

sf::Color Label::getFillColor()
{
    return this->col;
}
