#include <GL/gl.h>
#include <SFML/Window/Event.hpp>

#include "Window.h"

Window::Window( sf::Vector2i size, std::string const& title, sf::Uint32 style, sf::ContextSettings settings )
    : window( sf::VideoMode( size.x, size.y ), title, style, settings )
{
    // Disable framerate limiting ; handled in the game loop
    window.setFramerateLimit( 0 );

    glClearColor( 0, 0, 0, 1 );
    glEnable( GL_STENCIL_TEST );
}

Window::~Window()
{
}

void Window::clear()
{
    //    glColorMask( 0, 0, 0, 0 );
    glStencilMask( 0xff );
    glClearStencil( 0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void Window::handleEvents( InputHandler& handler )
{
    // Poll all events.
    sf::Event e;
    while( window.pollEvent( e ) )
    {
        switch( e.type )
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                onResize.emit( sf::Vector2u( e.size.width, e.size.height ) );
                break;
            default: // User input processes the InputHandler.
                handler.handleEvents( e );
        }
    }
}

void Window::draw( const sf::Drawable& drawable )
{
    window.draw( drawable );
}

void Window::update()
{
    window.display();
}

void Window::close()
{
    window.close();
}

sf::RenderWindow& Window::getSFMLWindow()
{
    return window;
}

bool Window::isOpen()
{
    return window.isOpen();
}

void Window::setSize( sf::Vector2u size )
{
    window.setSize( size );
    onResize.emit( size );
}

sf::Vector2u Window::getSize()
{
    return window.getSize();
}
