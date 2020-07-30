#include "GUI.h"

GUI::GUI( Game& game, sf::Vector2f viewSize )
    : game( game )
    , cam( viewSize, sf::Vector2f( viewSize.x / 2.0f, viewSize.y / 2.0f ), viewSize.x / viewSize.y )
{
    funcID = game.getWindow().onResize.connect_member( &cam, &Camera::windowResized );
    cam.windowResized( game.getWindow().getSize() );
}

GUI::~GUI()
{
    game.getWindow().onResize.disconnect( funcID );

    for( auto* k : widgets )
        delete k;
}

void GUI::handleEvents( InputHandler& handler )
{
    for( auto widget : widgets )
        widget->handleEvents( handler, &cam.getView() );
}

void GUI::update( float delta )
{
    for( auto widget : widgets )
        widget->update( delta );
}

void GUI::draw( Window& window )
{
    window.getSFMLWindow().setView( cam.getView() );

    for( auto widget : widgets )
        widget->draw( window, 0 );
}

void GUI::addWidget( GUIWidget* widget )
{
    widgets.push_back( widget );
}

bool GUI::removeWidget( const std::string& id )
{
    for( unsigned int i = 0; i < widgets.size(); i++ )
    {
        if( widgets[i]->getId() == id )
        {
            GUIWidget* buffer = widgets[i];
            widgets.erase( widgets.begin() + i );
            delete buffer;
            return 1;
        }
    }
    return 0;
}

void GUI::hide( bool hiden ){}

void GUI::disable( bool disabled ){}

GUIWidget* GUI::getWidget( std::string const& id )
{
    for( auto widget : widgets )
        if( widget->getId() == id )
            return widget;
    return nullptr;
}

Camera& GUI::getCam()
{
    return cam;
}

bool GUI::isHiden()
{

}

bool GUI::isDisabled()
{

}
