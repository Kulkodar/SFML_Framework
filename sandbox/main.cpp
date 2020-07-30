#include <cstdlib>

#include <iostream>

#include "testGame.h"
#include "testState.h"

int main( int argc, char** argv )
{
    GUIImageset img( "resources/TaharezLook.imageset" );

    sf::ContextSettings settings;
    settings.stencilBits = 8;

    testGame game( {500, 500}, "GUI Test", 60, settings );

    game.changeState( changeType::Override, new testState( game, img ) );

    game.run();

    return 0;
}
