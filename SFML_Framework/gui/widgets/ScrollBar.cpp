#include "ScrollBar.h"
#include "Thumb.h"

ScrollBar::ScrollBar( std::string const& id, sf::Vector2f size, sf::Vector2f pos, float windowsize, GUIImageset& img,
                      bool vertical )
    : GUIWidget( id )
    , thumb( "", pos, sf::Vector2f( 30, 30 ), img,
             ( vertical ? ThumbType::VerticalScroller : ThumbType::HorizontalSroller ) )
{
    // Set attributes to default
    this->isMouseOver = false;
    this->lastMousepos = {10000, 0};
    this->clickLock = false;
    this->windowSize = windowsize;
    this->vertical = vertical;
    //---

    // Create base shape
    base.setPosition( pos );
    base.setSize( size );
    base.setFillColor( sf::Color::White );
    base.setTexture( &img.guiTexture );
    base.setTextureRect( img.UVs[( vertical ? ScrollBarBase : ScrollBarBaseH )] );
    //---

    resize( windowsize );
    calculateThumbSize();

    thumb.ValueChanged.connect( [&]( float f ) { ValueChanged.emit( f ); } );
}

ScrollBar::~ScrollBar()
{
}

void ScrollBar::draw( Window& window, int currentStencilValue )
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

void ScrollBar::update( float delta )
{
}

void ScrollBar::handleEvents( InputHandler& handler, sf::View* view )
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
            else if( handler.isMButtonReleased( sf::Mouse::Left ) )
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

void ScrollBar::disable( bool dsiabled )
{

    disabled = dsiabled;

    thumb.disable( dsiabled );

    base.setFillColor( sf::Color( disabled ? 0x666666ff : 0xffffffff ) );
}

void ScrollBar::resize( float windowsize )
{

    this->windowSize = windowsize;
    calculateThumbSize();
}

sf::Vector2f ScrollBar::getOrigin()
{

    return base.getOrigin();
}

sf::Vector2f ScrollBar::getPosition()
{

    return base.getPosition();
}

sf::Vector2f ScrollBar::getSize()
{

    return base.getSize();
}

void ScrollBar::setOrigin( sf::Vector2f oo )
{

    base.setOrigin( oo );
}

void ScrollBar::setPosition( sf::Vector2f pos )
{

    base.setPosition( pos );
    calculateThumbSize();
}

void ScrollBar::setSize( sf::Vector2f size )
{

    base.setSize( size );
    calculateThumbSize();
}

void ScrollBar::calculateThumbSize()
{
    if( vertical )
    {
        float t = base.getSize().y / windowSize;
        t = ( ( t > 1 ) ? 1 : t );

        float x = base.getSize().y * t;
        x = ( ( x > 30 ) ? x : 30 );

        thumb.setSize( sf::Vector2f( base.getSize().x, x ) );
        thumb.setOrigin( sf::Vector2f( 0, x / 2.0f ) );
        thumb.setRegion( sf::FloatRect( sf::Vector2f( base.getPosition().x, base.getPosition().y + x / 2.0f ),
                                        sf::Vector2f( 0, base.getSize().y - x ) ) );
    }
    else
    {
        float t = base.getSize().x / windowSize;
        t = ( ( t > 1 ) ? 1 : t );

        float x = base.getSize().x * t;
        x = ( ( x > 30 ) ? x : 30 );

        thumb.setSize( sf::Vector2f( x, base.getSize().y ) );
        thumb.setOrigin( sf::Vector2f( x / 2.0f, 0 ) );
        thumb.setRegion( sf::FloatRect( sf::Vector2f( base.getPosition().x + x / 2.0f, base.getPosition().y ),
                                        sf::Vector2f( base.getSize().x - x, 0 ) ) );
    }
}

Thumb& ScrollBar::getThumb()
{

    return thumb;
}

bool ScrollBar::isVertical() const
{
    return vertical;
}
