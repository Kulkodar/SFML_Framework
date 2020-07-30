#include "Spinner.h"

SpinnerButton::SpinnerButton( sf::Vector2f size, sf::Vector2f pos, GUIImageset& imageset, bool down )
    : Button( "", "", size, pos, imageset, 10 )
{
    this->uvMouseover = imageset.UVs[down ? UVType::SpinnerDownHover : UVType::SpinnerUpHover];
    this->uvClicked = imageset.UVs[down ? UVType::SpinnerDownNormal : UVType::SpinnerUpNormal];
    this->uvNormal = imageset.UVs[down ? UVType::SpinnerDownNormal : UVType::SpinnerUpNormal];

    this->base.setTextureRect( this->uvNormal );
}

Spinner::Spinner( std::string const& id, sf::Vector2f size, sf::Vector2f pos, GUIImageset& imageset,
                  InputHandler& handler, int charSize )
    : NumberField( id, sf::Vector2f( size.x - size.y, size.y ), pos, imageset, handler, charSize )
    , up( sf::Vector2f( size.y, size.y / 2.0f ), sf::Vector2f( pos.x + base.getSize().x, pos.y ), imageset, 0 )
    , down( sf::Vector2f( size.y, size.y / 2.0f ), sf::Vector2f( pos.x + base.getSize().x, pos.y + size.y / 2.0f ),
            imageset, 1 )
{
    up.EventClicked.connect( [&]() {
        number += 1;
        this->label.setText( std::to_string( this->number ) );
    } );
    down.EventClicked.connect( [&]() {
        number -= 1;
        this->label.setText( std::to_string( this->number ) );
    } );
}

Spinner::~Spinner()
{
}

void Spinner::draw( Window& window, int currentStencilValue )
{
    if( !hiden )
    {
        glColorMask( 1, 1, 1, 1 );
        glStencilFunc( GL_EQUAL, currentStencilValue, 0xff );
        glStencilOp( GL_KEEP, GL_KEEP, GL_INCR );

        window.draw( base );

        up.draw( window, currentStencilValue );
        down.draw( window, currentStencilValue );

        label.draw( window, ++currentStencilValue );
    }
}

void Spinner::handleEvents( InputHandler& handler, sf::View* view )
{
    NumberField::handleEvents( handler );
    if( !moveable )
    {
        up.handleEvents( handler, view );
        down.handleEvents( handler, view );
    }
}

void Spinner::update( float delta )
{
    NumberField::update( delta );
}

void Spinner::disable( bool disabled )
{
    this->disabled = disabled;

    label.disable( disabled );
    up.disable( disabled );
    down.disable( disabled );

    base.setFillColor( sf::Color( disabled ? 0x666666ff : 0xffffffff ) );
}

sf::Vector2f Spinner::getSize()
{
    return base.getSize();
}
sf::Vector2f Spinner::getPosition()
{
    return base.getPosition();
}
sf::Vector2f Spinner::getOrigin()
{
    return base.getOrigin();
}

void Spinner::setSize( sf::Vector2f size )
{
    base.setSize( size );
    up.setSize( sf::Vector2f( size.y, size.y / 2.0f ) );
    down.setSize( sf::Vector2f( size.y, size.y / 2.0f ) );
    setPosition( base.getPosition() );
}
void Spinner::setPosition( sf::Vector2f pos )
{
    base.setPosition( pos );
    up.setPosition( sf::Vector2f( pos.x + base.getSize().x, pos.y ) );
    down.setPosition( sf::Vector2f( pos.x + base.getSize().x, pos.y + base.getSize().y / 2.0f ) );
    label.setPosition( pos );
}
void Spinner::setOrigin( sf::Vector2f oo )
{
    base.setOrigin( oo );
    up.setOrigin( oo );
    down.setOrigin( oo );
    label.setOrigin( oo );
}
