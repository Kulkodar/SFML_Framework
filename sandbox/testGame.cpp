#include "testGame.h"
#include <SFML/OpenGL.hpp>
#include <chrono>
#include <thread>

testGame::testGame( sf::Vector2i windowSize, std::string windowTitle, int refreshrate, sf::ContextSettings settings )
    : Game( windowSize, windowTitle, refreshrate, settings )
{
    //    TextInput.connect_member( this, &testGame::test );
}

testGame::~testGame()
{
}

void testGame::test( char c )
{
    //    std::cout << c << " " <<  (int)c << std::endl;
}
