#include "ColorPicker.h"

ColorPicker::ColorPicker( std::string const& id, sf::Vector2f size, sf::Vector2f pos, sf::Vector2f pickerSize,
                          float squareSize, GUIImageset& img, int charSize )
    : GUIWidget( id )
    , R( "", sf::Vector2f( pickerSize.x - squareSize, pickerSize.y / 3.0f ),
         sf::Vector2f( sf::Vector2f( pos.x, pos.y ) ), sf::Vector2f( pickerSize.y / 3.0f, pickerSize.y / 3.0f ), 1, img,
         0 )
    , G( "", sf::Vector2f( pickerSize.x - squareSize, pickerSize.y / 3.0f ),
         sf::Vector2f( pos.x, pos.y + pickerSize.y / 3.0f ), sf::Vector2f( pickerSize.y / 3.0f, pickerSize.y / 3.0f ),
         1, img, 0 )
    , B( "", sf::Vector2f( pickerSize.x - squareSize, pickerSize.y / 3.0f ),
         sf::Vector2f( pos.x, pos.y + 2 * pickerSize.y / 3.0f ),
         sf::Vector2f( pickerSize.y / 3.0f, pickerSize.y / 3.0f ), 1, img, 0 )

{
    this->colorButtonBase.setPosition( pos );
    this->colorButtonBase.setSize( size );
    this->colorButtonBase.setTexture( &img.guiTexture );
    this->colorButtonBase.setTextureRect( img.UVs[UVType::ColorPickerButton] );

    this->colorButtonCol.setPosition( pos );
    this->colorButtonCol.setSize( size );

    this->background.setPosition( pos );
    this->background.setSize( pickerSize );

    this->color.a = 255;
    this->color.r = 0;
    this->color.g = 0;
    this->color.b = 0;

    this->clickLock = 0;
    this->showPicker = 0;

    this->colDisplay.setPosition(
        sf::Vector2f( pos.x + pickerSize.x - squareSize, pos.y + ( pickerSize.y - squareSize ) / 2.0f ) );
    this->colDisplay.setSize( sf::Vector2f( squareSize, squareSize ) );
    this->colDisplay.setFillColor( color );
    this->colorButtonCol.setFillColor( color );

    R.getThumb().setMaxValue( sf::Vector2f( 255, 1 ) );
    G.getThumb().setMaxValue( sf::Vector2f( 255, 1 ) );
    B.getThumb().setMaxValue( sf::Vector2f( 255, 1 ) );

    R.ValueChanged.connect( [&]( float val ) {
        color.r = R.getThumb().getValue().x;
        ColorChanged.emit( color );
    } );
    G.ValueChanged.connect( [&]( float val ) {
        color.g = G.getThumb().getValue().x;
        ColorChanged.emit( color );
    } );
    B.ValueChanged.connect( [&]( float val ) {
        color.b = B.getThumb().getValue().x;
        ColorChanged.emit( color );
    } );
}

ColorPicker::~ColorPicker()
{
}

void ColorPicker::handleEvents( InputHandler& handler, sf::View* view )
{
    if( showPicker )
    {
        sf::Vector2f mapedPos = ( view != nullptr ) ? handler.getMousePosMapped( *view ) : handler.getMousePos();
        // Check Mouseover
        if( background.getGlobalBounds().contains( mapedPos.x, mapedPos.y ) )
        {
            R.handleEvents( handler );
            G.handleEvents( handler );
            B.handleEvents( handler );
            this->colDisplay.setFillColor( color );
            this->colorButtonCol.setFillColor( color );
        }
        else
        {
            showPicker = 0;
        }
    }
    else
    {
        sf::Vector2f mapedPos = ( view != nullptr ) ? handler.getMousePosMapped( *view ) : handler.getMousePos();
        // Check Mouseover
        if( colorButtonBase.getGlobalBounds().contains( mapedPos.x, mapedPos.y ) )
        {
            // Run olny if widget is not moveable
            if( !moveable )
            {
                // Check Button press.
                if( handler.isMButtonPressed( sf::Mouse::Left ) )
                {
                    EventClicked.emit();
                    showPicker = 1;
                }
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
        }
    }
}
void ColorPicker::update( float delta )
{
}
void ColorPicker::draw( Window& window, int currentStencilValue )
{
    if( !hiden )
    {
        glStencilFunc( GL_EQUAL, currentStencilValue, 0xff );
        glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
        glStencilMask( 0xff );

        if( showPicker == true )
        {
            window.draw( background );
            R.draw( window, currentStencilValue );
            G.draw( window, currentStencilValue );
            B.draw( window, currentStencilValue );
            window.draw( colDisplay );
        }
        else
        {
            window.draw( colorButtonCol );
            window.draw( colorButtonBase );
        }
        //        window.draw( background );
        //        window.draw( colDisplay );
        //        R.draw( window, currentStencilValue );
        //        G.draw( window, currentStencilValue );
        //        B.draw( window, currentStencilValue );
    }
}
void ColorPicker::disable( bool disabled )
{
    this->disabled = disabled;

    background.setFillColor( sf::Color( disabled ? 0x666666ff : 0xffffffff ) );
}

sf::Vector2f ColorPicker::getSize()
{
    return background.getSize();
}
sf::Vector2f ColorPicker::getPosition()
{
    return background.getPosition();
}
sf::Vector2f ColorPicker::getOrigin()
{
    return background.getOrigin();
}

void ColorPicker::setSize( sf::Vector2f size )
{
}
void ColorPicker::setPosition( sf::Vector2f pos )
{
}
void ColorPicker::setOrigin( sf::Vector2f oo )
{
}

sf::Color ColorPicker::getColor()
{
    return color;
}

void ColorPicker::setColor( sf::Color color )
{
    this->color = color;
    R.getThumb().setValue( sf::Vector2f( color.r, 0 ) );
    G.getThumb().setValue( sf::Vector2f( color.g, 0 ) );
    B.getThumb().setValue( sf::Vector2f( color.b, 0 ) );
}
