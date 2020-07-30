#include "Slider.h"

Slider::Slider( std::string const& id, sf::Vector2f size, sf::Vector2f pos, sf::Vector2f thumbSize, float stepSize,
                GUIImageset& img, bool vertical )
    : GUIWidget( id )
    , thumb( id, pos, thumbSize, img, ( vertical ? ThumbType::VerticalSlider : ThumbType::HorizontalSlider ) )
{
    thumb.ValueChanged.connect( [&]( float f ) { ValueChanged.emit( f ); } );

    // Set attributes to default.
    this->isMouseOver = false;
    this->lastMousepos = sf::Vector2f( 10000, 0 );
    this->clickLock = false;
    this->vertical = vertical;
    //---

    // Create base
    base.setPosition( pos );
    base.setSize( size );
    base.setTexture( &img.guiTexture );
    if( vertical )
        base.setTextureRect( img.UVs[UVType::SliderVerticalBase] );
    else
        base.setTextureRect( img.UVs[UVType::SliderHorizontalBase] );
    //---

    if( !vertical )
        thumb.setRegion(
            sf::FloatRect( sf::Vector2f( pos.x, pos.y + size.y / 2.0f ), sf::Vector2f( base.getSize().x, 0 ) ) );
    else
        thumb.setRegion(
            sf::FloatRect( sf::Vector2f( pos.x + size.x / 2.0f, pos.y ), sf::Vector2f( 0, base.getSize().y ) ) );
}

Slider::~Slider()
{
}

void Slider::draw( Window& window, int currentStencilValue )
{
    if( !hiden )
    {
        glStencilFunc( GL_EQUAL, currentStencilValue, 0xff );
        glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
        glStencilMask( 0x00 );

        window.draw( base );
        thumb.draw( window, currentStencilValue );
    }
}

void Slider::handleEvents( InputHandler& handler, sf::View* view )
{
    if( !disabled )
    {
        sf::Vector2f mapedPos = ( view != nullptr ) ? handler.getMousePosMapped( *view ) : handler.getMousePos();
        if( !moveable )
            thumb.handleEvents( handler, view );
        // Check Mouseover
        if( !base.getGlobalBounds().contains( mapedPos.x, mapedPos.y ) )
        {
            // Outside click prevention.
            if( handler.isMButtonPressed( sf::Mouse::Left ) )
                clickLock = 1;
            else
                clickLock = 0;
        }

        // Move whole Widget
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

void Slider::update( float delta )
{
}

void Slider::disable( bool dsiabled )
{
    disabled = dsiabled;
    thumb.disable( dsiabled );
    if( disabled )
        base.setFillColor( sf::Color( 0x666666ff ) );
    else
        base.setFillColor( sf::Color( 0xffffffff ) );
}

sf::Vector2f Slider::getOrigin()
{
    return base.getOrigin();
}

sf::Vector2f Slider::getPosition()
{
    return base.getPosition();
}

sf::Vector2f Slider::getSize()
{
    return base.getSize();
}

void Slider::setOrigin( sf::Vector2f oo )
{
    base.setOrigin( oo );
}

Thumb& Slider::getThumb()
{
    return thumb;
}

bool Slider::isVertical() const
{
    return vertical;
}

void Slider::setPosition( sf::Vector2f pos )
{
    base.setPosition( pos );
    if( vertical )
        thumb.setPosition( sf::Vector2f( pos.x + base.getSize().x / 2.0f, pos.y ) );
    else
        thumb.setPosition( sf::Vector2f( pos.x, pos.y + base.getSize().y / 2.0f ) );
}

void Slider::setSize( sf::Vector2f size )
{
    base.setSize( size );
    if( vertical )
    {
        thumb.resize( sf::Vector2f( 0, size.y ) );
        thumb.setPosition( base.getPosition() );
    }
    else
    {
        thumb.resize( sf::Vector2f( size.x, 0 ) );
        thumb.setPosition( base.getPosition() );
    }
}
