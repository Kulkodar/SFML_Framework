#include "DropDownList.h"
#include <SFML/OpenGL.hpp>

DropDownListItem::DropDownListItem( const std::string& text, sf::Vector2f size, GUIImageset& img, uint charsize )
    : label( "", text, sf::Vector2f( 0, 0 ), img, charsize )
{
    base.setSize( size );
    base.setPosition( 0, 0 );
    base.setFillColor( sf::Color::Blue );
}

DropDownListItem::~DropDownListItem()
{
}

void DropDownListItem::draw( Window& window, int currentStencilValue, sf::Vector2f pos )
{
    glStencilFunc( GL_EQUAL, currentStencilValue, 0xff );
    glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
    glStencilMask( 0xff );

    base.setPosition( pos );
    label.setPosition( pos );
    //    window.draw( base );
    label.draw( window, currentStencilValue );
}

void DropDownListItem::disable( bool disable )
{
    label.disable( disable );
}

bool DropDownListItem::isMouseover( sf::Vector2f mappedMPos )
{
    return base.getGlobalBounds().contains( mappedMPos.x, mappedMPos.y );
}

void DropDownListItem::setSize( sf::Vector2f size, int charSize )
{
    base.setSize( size );
    label.setCharSize( charSize );
}

DropDownList::DropDownList( std::string const& id, sf::Vector2f size, sf::Vector2f pos, GUIImageset& img )
    : GUIWidget( id )
    , img( img )
    , bar( "", {10, size.y * 5}, {pos.x + size.x, pos.y + size.y}, size.y * 5, img, 1 )
{
    this->backdropUnfold = 1;
    this->numDisItems = 5;
    this->currentItem = -1;
    this->lock = 0;
    this->lock2 = 0;
    this->offset = 0;
    this->mouseOver = 0;

    bar.ValueChanged.connect( [&]( float f ) { offset = -( f / 100.0f ) * ( items.size() - 5 ) * base.getSize().y; } );

    float triSize = size.y;
    base.setPosition( pos );
    base.setSize( {size.x - triSize, size.y} );
    base.setTexture( &img.guiTexture );
    base.setTextureRect( img.UVs[UVType::DropDownListLeftNormal] );

    backdrop.setPosition( {pos.x + size.x + triSize, pos.y} );
    backdrop.setSize( {size.x, size.y} );
    backdrop.setTexture( &img.guiTexture );
    backdrop.setTextureRect( img.UVs[UVType::DropDownListBack] );

    backdropEnd.setSize( {size.x, size.y * 0.4f} );
    backdropEnd.setTexture( &img.guiTexture );
    backdropEnd.setTextureRect( img.UVs[UVType::DropDownListBackBottom] );

    base2.setSize( {triSize, size.y} );
    base2.setPosition( pos.x + size.x - triSize, pos.y );
    base2.setTexture( &img.guiTexture );
    base2.setTextureRect( img.UVs[UVType::DropDownListRightNormal] );
}

DropDownList::~DropDownList()
{
}

void DropDownList::disable( bool disabled )
{
    this->disabled = disabled;

    base.setFillColor( sf::Color( disabled ? 0x666666ff : 0xffffffff ) );
    base2.setFillColor( sf::Color( disabled ? 0x666666ff : 0xffffffff ) );
    backdrop.setFillColor( sf::Color( disabled ? 0x666666ff : 0xffffffff ) );
    backdropEnd.setFillColor( sf::Color( disabled ? 0x666666ff : 0xffffffff ) );

    for( auto& i : items )
        i->disable( disabled );
}

void DropDownList::draw( Window& window, int currentStencilValue )
{
    if( !disabled )
    {
        if( items.size() >= 5 && backdropUnfold )
            bar.draw( window, currentStencilValue );

        glStencilFunc( GL_EQUAL, currentStencilValue, 0xff );
        glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
        glStencilMask( 0xff );

        window.draw( base );

        glStencilFunc( GL_EQUAL, currentStencilValue, 0xff );
        glStencilOp( GL_KEEP, GL_KEEP, GL_INCR );
        glStencilMask( 0xff );
        if( backdropUnfold )
        {
            backdrop.setPosition( base.getPosition() );
            for( unsigned int i = 0; i < numDisItems && i < items.size(); i++ )
            {
                backdrop.move( 0, base.getSize().y );
                window.draw( backdrop );
            }
            backdrop.move( 0, base.getSize().y );
            backdropEnd.setPosition( backdrop.getPosition() );
            window.draw( backdropEnd );
            for( unsigned int i = 0; i < items.size(); i++ )
            {
                items[i]->draw( window, currentStencilValue + 1,
                                {base.getPosition().x + base.getSize().x * 0.1f,
                                 offset + base.getPosition().y + ( i + 1 ) * base.getSize().y} );
            }
        }
        if( currentItem != -1 )
            items[currentItem]->draw( window, currentStencilValue, base.getPosition() );

        glStencilFunc( GL_EQUAL, currentStencilValue, 0xff );
        glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
        glStencilMask( 0xff );
        window.draw( base2 );
    }
}

sf::Vector2f DropDownList::getOrigin()
{
    return base.getOrigin();
}

sf::Vector2f DropDownList::getPosition()
{
    return base.getPosition();
}

sf::Vector2f DropDownList::getSize()
{
    return {base.getSize().x + base2.getSize().x, base.getSize().y};
}

void DropDownList::setOrigin( sf::Vector2f oo )
{
}

void DropDownList::setPosition( sf::Vector2f pos )
{
    base.setPosition( pos );
    base2.setPosition( pos.x + base.getSize().x, pos.y );

    bar.setPosition( {pos.x + base.getSize().x + base2.getSize().x, pos.y + base.getSize().y} );
}

void DropDownList::setSize( sf::Vector2f size )
{
    float triSize = size.y;
    sf::Vector2f pos = base.getPosition();

    base.setSize( {size.x - triSize, size.y} );

    backdrop.setPosition( {pos.x + size.x + triSize, pos.y} );
    backdrop.setSize( {size.x, size.y} );

    backdropEnd.setSize( {size.x, size.y * 0.4f} );

    base2.setSize( {triSize, size.y} );
    base2.setPosition( size.x - triSize, 0 );

    bar.setPosition( {pos.x + base.getSize().x + base2.getSize().x, pos.y + base.getSize().y} );
    bar.setSize( {10, size.y * 5} );

    for( auto& i : items )
        i->setSize( size, base.getSize().y * 0.7f );
}

void DropDownList::handleEvents( InputHandler& handler, sf::View* view )
{
    sf::Vector2f mapedPos = ( view != nullptr ) ? handler.getMousePosMapped( *view ) : handler.getMousePos();
    itemRegion.left = base.getPosition().x;
    itemRegion.top = base.getPosition().y + base.getSize().y;
    itemRegion.width = base.getSize().x + base2.getSize().x;
    itemRegion.height = base.getSize().y + base.getSize().y * ( ( items.size() > 5 ) ? 5 : items.size() );

    mouseRegion.left = base.getPosition().x;
    mouseRegion.top = base.getPosition().y;
    mouseRegion.width = base.getSize().x + bar.getSize().x + 2 + base2.getSize().x;
    mouseRegion.height = base.getSize().y + base.getSize().y * ( ( items.size() > 5 ) ? 5 : items.size() );

    if( items.size() >= 5 && backdropUnfold )
        bar.handleEvents( handler, view );

    if( backdropUnfold )
        if( !mouseRegion.contains( mapedPos.x, mapedPos.y ) )
            backdropUnfold = 0;

    if( itemRegion.contains( mapedPos.x, mapedPos.y ) )
    {
        if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
        {
            if( !lock )
            {
                lock = 1;
                for( unsigned int i = 0; i < items.size(); i++ )
                    if( items[i]->isMouseover( mapedPos ) )
                    {
                        currentItem = i;
                        backdropUnfold = 0;
                        ItemSelected.emit( i );
                    }
            }
        }
        else
            lock = 0;
    }
    else if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
    {
        lock = 1;
    }
    else
        lock = 0;

    if( base2.getGlobalBounds().contains( mapedPos.x, mapedPos.y ) )
    {
        if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
        {
            if( !lock2 )
            {
                lock2 = 1;
                backdropUnfold = !backdropUnfold;
            }
        }
        else
            lock2 = 0;
    }
    else if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
    {
        lock2 = 1;
    }
    else
    {
        lock2 = 0;
    }
}

void DropDownList::update( float delta )
{
}

void DropDownList::addItem( const std::string& name )
{
    items.push_back( new DropDownListItem( name, {base.getSize().x + base2.getSize().x, base.getSize().y}, img,
                                           base.getSize().y * 0.7f ) );

    if( items.size() > 5 )
    {
        bar.resize( base.getSize().y * items.size() );
    }
}

void DropDownList::select( int i )
{
    if( i < items.size() && i >= 0 )
    {
        currentItem = i;
        ItemSelected.emit( i );
    }
    else
    {
        currentItem = -1;
        ItemSelected.emit( i );
    }
}

void DropDownList::remove( int i )
{
    if( i < items.size() && i >= 0 )
        items.erase(items.begin() + i);
    select(i);
}

DropDownListItem* DropDownList::getItem( int i)
{
    if( i < items.size() && i >= 0 )
        return items[i];
    else
        return nullptr;
}
