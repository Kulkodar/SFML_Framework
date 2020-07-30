#include "Checkbox.h"

Checkbox::Checkbox( std::string const& id, std::string const& text, sf::Vector2f size, sf::Vector2f pos,
                    GUIImageset& imageset, int charSize )
    : GUIWidget( id )
    , label( "", text, sf::Vector2f( 0, 0 ), imageset, charSize )
{
    // Set attributes to default
    this->uvMouseover = imageset.UVs[UVType::CheckboxMouseover];
    this->uvNormal = imageset.UVs[UVType::CheckboxNormal];
    this->clickLock = 0;
    this->state = 0;
    //---

    // Create base shape
    base.setSize( size );
    base.setPosition( pos );
    base.setTexture( &imageset.guiTexture );
    base.setTextureRect( this->uvNormal );
    base.setFillColor( sf::Color::White );
    //---

    // Create check mark shape.
    mark.setSize( size );
    mark.setPosition( pos );
    mark.setTexture( &imageset.guiTexture );
    mark.setTextureRect( imageset.UVs[UVType::CheckboxMark] );
    mark.setFillColor( sf::Color::White );
    //---
}

Checkbox::~Checkbox()
{
}

void Checkbox::disable( bool disable )
{
    disabled = disable;

    label.disable( disable );

    base.setFillColor( sf::Color( disabled ? 0x666666ff : 0xffffffff ) );
    mark.setFillColor( sf::Color( disabled ? 0x666666ff : 0xffffffff ) );
}

void Checkbox::draw( Window& window, int currentStencilValue )
{
    if( !hiden )
    {
        glStencilFunc( GL_EQUAL, currentStencilValue, 0xff );
        glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
        glStencilMask( 0xff );

        window.draw( base );
        label.draw( window, currentStencilValue );

        if( state )
            window.draw( mark );
    }
}

void Checkbox::handleEvents( InputHandler& handler, sf::View* view )
{
    sf::Vector2f mapedPos = ( view != nullptr ) ? handler.getMousePosMapped( *view ) : handler.getMousePos();
    if( !disabled )
    {
        // Check mouse over
        if( base.getGlobalBounds().contains( mapedPos.x, mapedPos.y ) )
        {
            if( !moveable )
            {
                base.setTextureRect( uvMouseover );
                if( handler.isMButtonPressed( sf::Mouse::Left ) )
                {
                    EventClicked.emit();
                    state = !state;
                    CheckboxChecked.emit( state );
                }
                else if( handler.isMButtonReleased( sf::Mouse::Left ) )
                {
                    if( clickLock )
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
            if( handler.isMButtonReleased( sf::Mouse::Left ) )
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

    float posX = 0, posY = 0;
    posY = base.getPosition().y + base.getSize().y / 2.0f - ( label.getCharSize() / 2.0f * 1.25f );
    posX = base.getPosition().x + base.getSize().x;

    label.setPosition( {posX, posY} );
}

void Checkbox::update( float delta )
{
}

sf::Vector2f Checkbox::getOrigin()
{
    return base.getOrigin();
}

sf::Vector2f Checkbox::getPosition()
{
    return base.getPosition();
}

sf::Vector2f Checkbox::getSize()
{
    return base.getSize();
}

bool Checkbox::getState() const
{
    return state;
}

void Checkbox::setOrigin( sf::Vector2f oo )
{
    base.setOrigin( oo );
    mark.setOrigin( oo );
}

void Checkbox::setPosition( sf::Vector2f pos )
{
    base.setPosition( pos );
    mark.setPosition( pos );
}

void Checkbox::setSize( sf::Vector2f size )
{
    base.setSize( size );
    mark.setSize( size );
}

void Checkbox::setState( bool state )
{
    this->state = state;
}

Label& Checkbox::getLabel()
{
    return label;
}
