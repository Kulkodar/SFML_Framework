#include "Thumb.h"

Thumb::Thumb( std::string const& id, sf::Vector2f pos, sf::Vector2f size, GUIImageset& img, ThumbType type )
    : GUIWidget( id )
{
    this->maxValue = {100, 100};
    this->minValue = {0, 0};
    this->value = {0, 0};
    this->type = type;

    this->isMouseOver = false;
    this->clickLock = false;

    this->lastMousepos = {0, 0};

    base.setPosition( pos );
    base.setSize( size );
    base.setOrigin( size.x / 2.0f, size.y / 2.0f );
    base.setTexture( &img.guiTexture );

    region.top = 0;
    region.left = 0;
    this->region.height = 100;
    this->region.width = 100;

    switch( type )
    {
        case HorizontalSlider:
            uvMouseOver = img.UVs[UVType::SliderHorizontalThumbHover];
            uvNormal = img.UVs[UVType::SliderHorizontalThumb];
            break;
        case VerticalSlider:
            uvMouseOver = img.UVs[UVType::SliderVerticalThumbHover];
            uvNormal = img.UVs[UVType::SliderVerticalThumb];
            break;
        case HorizontalSroller:
            uvMouseOver = img.UVs[UVType::ScrollBarThumbMouseOverH];
            uvNormal = img.UVs[UVType::ScrollBarThumbBaseH];
            break;
        case VerticalScroller:
            uvMouseOver = img.UVs[UVType::ScrollBarThumbMouseOver];
            uvNormal = img.UVs[UVType::ScrollBarThumbBase];
            break;
        case ColorPickerT:
            uvMouseOver = img.UVs[UVType::ColorPickerThumbHover];
            uvNormal = img.UVs[UVType::ColorPickerThumbNormal];
            break;
    }

    base.setTextureRect( uvNormal );
}

Thumb::~Thumb()
{
}

void Thumb::disable( bool dsiabled )
{
    disabled = dsiabled;

    base.setFillColor( sf::Color( disabled ? 0x666666ff : 0xffffffff ) );
}

void Thumb::draw( Window& window, int currentStencilValue )
{
    if( !hiden )
    {
        glStencilFunc( GL_EQUAL, currentStencilValue, 0xff );
        glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
        glStencilMask( 0x00 );

        window.draw( base );
    }
}

void Thumb::handleEvents( InputHandler& handler, sf::View* view )
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
                base.setTextureRect( uvMouseOver );
                if( handler.isMButtonReleased( sf::Mouse::Left ) )
                {
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
        if( !clickLock )
        {
            if( handler.isMButtonDown( sf::Mouse::Left ) && handler.isMouseMoved() )
            {
                sf::Vector2f p = getPosition();
                sf::Vector2f delta =
                    ( view != nullptr ) ? handler.getMouseDeltaMapped( *view ) : handler.getMouseDelta();
                p.x += delta.x;
                p.y += delta.y;
                moveThumb( p );
                Moved.emit( delta );
            }
        }
    }
}

void Thumb::update( float delta )
{
}

sf::Vector2f Thumb::getOrigin()
{
    return base.getOrigin();
}

sf::Vector2f Thumb::getPosition()
{
    return base.getPosition();
}

sf::Vector2f Thumb::getSize()
{
    return base.getSize();
}

void Thumb::setOrigin( sf::Vector2f oo )
{
    base.setOrigin( oo );
}

void Thumb::setRegion( sf::FloatRect region )
{
    this->region = region;
    setValue( value );
}

sf::FloatRect Thumb::getRegion() const
{
    return region;
}

sf::Vector2f Thumb::getValue() const
{
    return value;
}

void Thumb::setPosition( sf::Vector2f pos )
{
    sf::Vector2f buffer;
    buffer.x = base.getPosition().x - region.left;
    buffer.y = base.getPosition().y - region.top;

    region.left = pos.x;
    region.top = pos.y;

    base.setPosition( sf::Vector2f( region.left + buffer.x, region.top + buffer.y ) );
}

void Thumb::setSize( sf::Vector2f size )
{
    base.setSize( size );
}

void Thumb::moveThumb( sf::Vector2f pos )
{
    if( !region.contains( pos.x, pos.y ) )
    {
        if( pos.x < region.left )
            pos.x = region.left;
        if( pos.x > region.left + region.width )
            pos.x = region.left + region.width;

        if( pos.y < region.top )
            pos.y = region.top;
        if( pos.y > region.top + region.height )
            pos.y = region.top + region.height;
    }
    base.setPosition( pos );

    sf::Vector2f percent;

    if( region.width != 0 )
        percent.x = ( base.getPosition().x - region.left ) / region.width;
    if( region.height != 0 )
        percent.y = ( base.getPosition().y - region.top ) / region.height;

    value.x = minValue.x + ( maxValue.x - minValue.x ) * percent.x;
    value.y = minValue.y + ( maxValue.y - minValue.y ) * percent.y;

    if( type == HorizontalSlider || type == HorizontalSroller )
        ValueChanged.emit( value.x );
    if( type == VerticalSlider || type == VerticalScroller )
        ValueChanged.emit( value.y );
}

void Thumb::setValue( sf::Vector2f val )
{
    if( val.x < minValue.x )
        val.x = minValue.x;
    else if( val.x > maxValue.x )
        val.x = maxValue.x;
    if( val.y < minValue.y )
        val.y = minValue.y;
    else if( val.y > maxValue.y )
        val.y = maxValue.y;

    sf::Vector2f percent( ( val.x - minValue.x ) / ( maxValue.x - minValue.x ),
                          ( val.y - minValue.y ) / ( maxValue.y - minValue.y ) );

    base.setPosition( sf::Vector2f( region.left + percent.x * region.width, region.top + percent.y * region.height ) );

    value.x = val.x;
    value.y = val.y;

    if( type == HorizontalSlider || type == HorizontalSroller )
        ValueChanged.emit( value.x );
    if( type == VerticalSlider || type == VerticalScroller )
        ValueChanged.emit( value.y );
}

void Thumb::resize( sf::Vector2f size )
{
    sf::Vector2f percent( value.x / maxValue.x, value.y / maxValue.y );

    region.height = size.y;
    region.width = size.x;

    base.setPosition( sf::Vector2f( region.left + percent.x * region.width, region.top + percent.y * region.height ) );
}

void Thumb::setMaxValue( sf::Vector2f max )
{
    this->maxValue = max;
}
void Thumb::setMinValue( sf::Vector2f min )
{
    this->minValue = min;
}

sf::Vector2f Thumb::getMaxValue()
{
    return this->maxValue;
}
sf::Vector2f Thumb::getMinValue()
{
    return this->minValue;
}
