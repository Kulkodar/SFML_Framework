#include "GUIWindow.h"

GUIWindow::GUIWindow( std::string const& id, sf::Vector2f size, float scrolbarSize, sf::Vector2f pos, GUIImageset& img )
    : GUIWidget( id )
{
    this->base.setFillColor( sf::Color::White );
    this->base.setPosition( pos );
    this->base.setSize( size );

    this->delta = sf::Vector2f( 0, 0 );
    this->insideBounds = size;

    this->scrollBarV = new ScrollBar( "", {scrolbarSize, size.y},
                                      {base.getGlobalBounds().left - scrolbarSize, base.getGlobalBounds().top},
                                      insideBounds.y, img, 1 );
    this->scrollBarH = new ScrollBar(
        "", {size.x, scrolbarSize},
        {base.getGlobalBounds().left, base.getGlobalBounds().top + base.getGlobalBounds().height + scrolbarSize},
        insideBounds.x, img, 0 );
}

GUIWindow::~GUIWindow()
{
    for( auto* k : childs )
        delete k;
}

void GUIWindow::draw( Window& window, int currentStencilValue )
{
    if( !hiden )
    {
        glColorMask( 0, 0, 0, 0 );
        glStencilFunc( GL_EQUAL, currentStencilValue, 0xff );
        glStencilOp( GL_KEEP, GL_KEEP, GL_INCR );
        glStencilMask( 0xff );

        window.draw( base );
        glColorMask( 1, 1, 1, 1 );

        for( auto& w : childs )
        {
            w->setPosition( {w->getPosition().x + delta.x, w->getPosition().y + delta.y} );
            w->draw( window, currentStencilValue + 1 );
        }

        scrollBarV->draw( window, currentStencilValue );
        scrollBarH->draw( window, currentStencilValue );
    }
}

void GUIWindow::handleEvents( InputHandler& handler, sf::View* view )
{
    // Check Mouseover
    if( !disabled )
    {
        sf::Vector2f mapedPos = ( view != nullptr ) ? handler.getMousePosMapped( *view ) : handler.getMousePos();
        if( base.getGlobalBounds().contains( mapedPos.x, mapedPos.y ) )
        {
            for( auto& w : childs )
                w->handleEvents( handler );
        }

        scrollBarV->handleEvents( handler, view );
        scrollBarH->handleEvents( handler, view );

        delta.y = last.y - scrollBarV->getThumb().getValue().y;
        delta.x = last.x - scrollBarH->getThumb().getValue().x;
        last.x = scrollBarH->getThumb().getValue().x;
        last.y = scrollBarV->getThumb().getValue().y;
    }
}

void GUIWindow::update( float delta )
{
    if( !disabled )
        for( auto& w : childs )
            w->update( delta );
}

void GUIWindow::disable( bool dsiabled )
{
    for( auto& w : childs )
        w->disable( dsiabled );
}

void GUIWindow::addChid( GUIWidget* child, sf::Vector2u pos )
{
    childs.push_back( child );
    child->setPosition( (sf::Vector2f)pos );

    if( pos.y + child->getSize().y > insideBounds.y )
    {
        insideBounds.y = pos.y + child->getSize().y;
        scrollBarV->resize( insideBounds.y );
    }
    if( pos.x + child->getSize().x > insideBounds.x )
    {
        insideBounds.x = pos.x + child->getSize().x;
        scrollBarH->resize( insideBounds.x );
    }
}

GUIWidget* GUIWindow::getChid( std::string const& ID )
{
    for( auto& w : childs )
        if( w->getId() == ID )
            return w;
    return nullptr;
}

sf::Vector2f GUIWindow::getOrigin()
{
    return sf::Vector2f( 0, 0 );
}

sf::Vector2f GUIWindow::getPosition()
{
    return sf::Vector2f( 0, 0 );
}

sf::Vector2f GUIWindow::getSize()
{
    return sf::Vector2f( 0, 0 );
}

void GUIWindow::setOrigin( sf::Vector2f oo )
{
}

void GUIWindow::setPosition( sf::Vector2f pos )
{
}

void GUIWindow::setSize( sf::Vector2f size )
{
}
