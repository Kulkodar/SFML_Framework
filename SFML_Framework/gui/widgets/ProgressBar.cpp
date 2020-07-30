#include "ProgressBar.h"

ProgressBar::ProgressBar( std::string const& id, std::string const& text, sf::Vector2f size, sf::Vector2f pos,
                          GUIImageset& imageset, int charsize )
    : GUIWidget( id )
    , label( "", text, sf::Vector2f( 0, 0 ), imageset, charsize )
{
    // Set attributes.
    this->val = 0;
    this->uv = imageset.UVs[UVType::ProgressBarBar];
    this->lastMousepos = sf::Vector2f( 10000, 0 );
    this->clickLock = 0;
    //---

    // Create base shape
    base.setSize( size );
    base.setPosition( pos );
    base.setFillColor( sf::Color::White );
    base.setTexture( &imageset.guiTexture, 1 );
    base.setTextureRect( imageset.UVs[UVType::ProgressBarBase] );
    //---

    // Create overlay.
    bar.setSize( size );
    bar.setPosition( pos );
    bar.setFillColor( sf::Color::White );
    bar.setTexture( &imageset.guiTexture );
    //---

    setValue( 50 );
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::draw( Window& window, int currentStencilValue )
{
    if( !hiden )
    {
        glStencilFunc( GL_EQUAL, currentStencilValue, 0xff );
        glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
        glStencilMask( 0xff );
        window.draw( base );
        window.draw( bar );
        label.draw( window, currentStencilValue );
    }
}

void ProgressBar::handleEvents( InputHandler& handler, sf::View* view )
{
    if( !disabled )
    {
        sf::Vector2f mapedPos = ( view != nullptr ) ? handler.getMousePosMapped( *view ) : handler.getMousePos();
        // Check Mouseover
        if( !base.getGlobalBounds().contains( mapedPos.x, mapedPos.y ) )
        {
            // Outside click prevention.
            if( handler.isMButtonPressed( sf::Mouse::Left ) )
                clickLock = 1;
            else if( handler.isMButtonReleased( sf::Mouse::Left ) )
                clickLock = 0;
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

void ProgressBar::update( float delta )
{
}

void ProgressBar::disable( bool dsiabled )
{
    disabled = dsiabled;
    label.disable( dsiabled );

    base.setFillColor( sf::Color( disabled ? 0x666666ff : 0xffffffff ) );
    bar.setFillColor( sf::Color( disabled ? 0x666666ff : 0xffffffff ) );
}

void ProgressBar::changeValue( float value )
{
    if( !disabled )
    {
        this->val += value;
        if( val > 100.0000f )
            val = 100.0000f;

        sf::IntRect b = uv;
        b.width *= ( val / 100.0f );
        bar.setTextureRect( b );

        bar.setSize( {( base.getSize().x * ( (float)b.width / uv.width ) ), base.getSize().y} );
        label.setPosition(
            {base.getPosition().x + base.getSize().x / 2.0f - label.getSize().y / 2.0f, base.getPosition().y} );
    }
}

void ProgressBar::setValue( float value )
{
    this->val = value;
    if( val > 100.0000f )
        val = 100.0000f;

    if( !disabled )
    {
        bar.setSize( {base.getSize().x * ( val / 100.0f ), base.getSize().y} );
        sf::IntRect b = uv;
        b.width = b.width * ( val / 100.0f );
        bar.setTextureRect( b );
    }
}

sf::Vector2f ProgressBar::getOrigin()
{
    return base.getOrigin();
}

sf::Vector2f ProgressBar::getPosition()
{
    return base.getPosition();
}

sf::Vector2f ProgressBar::getSize()
{
    return base.getSize();
}

void ProgressBar::setOrigin( sf::Vector2f oo )
{
    base.setOrigin( oo );
    bar.setOrigin( oo );
}

void ProgressBar::setPosition( sf::Vector2f pos )
{
    base.setPosition( pos );
    bar.setPosition( pos );
    label.setPosition(
        {base.getPosition().x + base.getSize().x / 2.0f - label.getSize().y / 2.0f, base.getPosition().y} );
}

void ProgressBar::setSize( sf::Vector2f size )
{
    base.setSize( size );
    bar.setSize( size );
    label.setPosition(
        {base.getPosition().x + base.getSize().x / 2.0f - label.getSize().y / 2.0f, base.getPosition().y} );
}

float ProgressBar::getValue() const
{
    return val;
}

Label& ProgressBar::getLabel()
{
    return label;
}
