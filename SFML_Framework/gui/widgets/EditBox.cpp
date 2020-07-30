#include "EditBox.h"
#include <SFML/Graphics.hpp>

EditBox::EditBox( const std::string& id, sf::Vector2f size, sf::Vector2f pos, GUIImageset& imageset,
                  InputHandler& handler, int charSize )
    : GUIWidget( id )
    , handler( handler )
    , label( "", "", sf::Vector2f( 0, 0 ), imageset, charSize )
{
    // Set attributes to default
    this->isActive = 0;
    this->clickLock = 0;
    //---

    // Create base shape.
    base.setSize( size );
    base.setPosition( pos );
    base.setFillColor( sf::Color::White );
    base.setTexture( &imageset.guiTexture );
    base.setTextureRect( imageset.UVs[UVType::EditBoxBase] );
    //---

    // Subscribe text input event
    funcID = handler.textInput.connect_member( this, &EditBox::handleTextInput );

    calulateLabelPostion();
}

EditBox::~EditBox()
{
    handler.textInput.disconnect( funcID );
}

void EditBox::handleEvents( InputHandler& handler, sf::View* view )
{
    sf::Vector2f mapedPos = ( view != nullptr ) ? handler.getMousePosMapped( *view ) : handler.getMousePos();
    if( !disabled )
    {
        // Check Mouseover
        if( base.getGlobalBounds().contains( mapedPos.x, mapedPos.y ) )
        {
            // Run olny if widget is not moveable
            if( !moveable )
            {
                // Check Button press.
                if( handler.isMButtonPressed( sf::Mouse::Left ) )
                {
                    isActive = 1;
                    if( !clickLock )
                        EventClicked.emit();
                    clickLock = 1;
                }
                else if( handler.isMButtonReleased( sf::Mouse::Left ) )
                {
                    if( clickLock )
                    {
                        EventReleased.emit();
                    }
                    clickLock = 0;
                }
            }
        } // Outside click prevention.
        else if( handler.isMButtonPressed( sf::Mouse::Left ) )
        {
            clickLock = 1;
            isActive = 0;
        }
        else if( handler.isMButtonReleased( sf::Mouse::Left ) )
            clickLock = 0;

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

void EditBox::update( float delta )
{
}

void EditBox::draw( Window& window, int currentStencilValue )
{
    if( !hiden )
    {
        glColorMask( 1, 1, 1, 1 );
        glStencilFunc( GL_EQUAL, currentStencilValue, 0xff );
        glStencilOp( GL_KEEP, GL_KEEP, GL_INCR );

        window.draw( base );

        label.draw( window, ++currentStencilValue );
    }
}
void EditBox::disable( bool disabled )
{
    this->disabled = disabled;

    label.disable( disabled );

    base.setFillColor( sf::Color( disabled ? 0x666666ff : 0xffffffff ) );
}

void EditBox::handleTextInput( char32_t text )
{
    if( isActive )
    {
        sf::String buffer = this->label.getText();

        if( text == 18 )
            isActive = 0;
        else if( text == 8 )
        {
            if( buffer.getSize() != 0 )
            {
                int pos = buffer.getSize();
                pos--;
                buffer.erase( pos, 1 );
                this->label.setText( buffer );
                ValueChanged.emit(0);
            }
        }
        else
        {
            this->label.setText( buffer += sf::String( text ) );
            ValueChanged.emit(0);
        }
    }
}

void EditBox::calulateLabelPostion()
{
    label.setCharSize( base.getSize().y );
    label.setPosition( sf::Vector2f( base.getGlobalBounds().left, base.getGlobalBounds().top ) );
}

sf::Vector2f EditBox::getOrigin()
{
    return base.getOrigin();
}

sf::Vector2f EditBox::getPosition()
{
    return base.getPosition();
}

sf::Vector2f EditBox::getSize()
{
    return base.getSize();
}

void EditBox::setOrigin( sf::Vector2f oo )
{
    base.setOrigin( oo );
    calulateLabelPostion();
}

void EditBox::setPosition( sf::Vector2f pos )
{
    base.setPosition( pos );
    calulateLabelPostion();
}

void EditBox::setSize( sf::Vector2f size )
{
    base.setSize( size );
    calulateLabelPostion();
}

Label& EditBox::getLabel()
{
    return label;
}
