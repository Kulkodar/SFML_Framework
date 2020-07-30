#include "Game.h"

#include "State.h"

State::State( Game& game, sf::Vector2f viewSize )
    : game( game )
    , cam( viewSize, sf::Vector2f( viewSize.x / 2.0f, viewSize.y / 2.0f ), viewSize.x / viewSize.y )
{
    funcID = game.getWindow().onResize.connect_member( &cam, &Camera::windowResized );
    cam.windowResized( game.getWindow().getSize() );
}

State::~State()
{
    game.getWindow().onResize.disconnect( funcID );
}
