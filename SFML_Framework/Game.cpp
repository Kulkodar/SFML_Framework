#include "Game.h"
#include <chrono>
#include <thread>

Game::Game( sf::Vector2i windowSize, std::string const& windowTitle, int refreshrate, sf::ContextSettings settings )
    : window( sf::Vector2i( windowSize.x, windowSize.y ), windowTitle, sf::Style::Default, settings )
{
    // Set variables to default.
    this->bufferState = nullptr;
    this->currentFPS = 0;
    this->currentFramestime = 0;
    this->refreshrate = refreshrate;
    this->type = changeType::Null;

    this->handler.setWindow( this->window.getSFMLWindow() );
}

Game::~Game()
{
    // Delete all states.
    for( auto* k : states )
    {
        delete k;
    }
}

void Game::run()
{
    float delta = 1.0f / refreshrate;
    int frames = 0;
    sf::Clock fpscounter;
    sf::Clock timer;

    fpscounter.restart();

    while( window.isOpen() )
    {
        timer.restart();

        window.clear();

        handler.update();

        window.handleEvents( handler );

        if( states.size() > 0 )
        {
            states.back()->handleEvents( handler );
            states.back()->update( delta );
            states.back()->display( window );
        }

        window.update();

        frames++;
        if( fpscounter.getElapsedTime().asMilliseconds() > 1000 )
        {
            this->currentFPS = frames;
            frames = 0;
            fpscounter.restart();
        }

        switch( type )
        {
            case changeType::Override:
                Override();
                break;
            case changeType::Pop:
                popState();
                break;
            case changeType::Push:
                pushState();
                break;
            default:
                break;
        }
        bufferState = nullptr;
        type = changeType::Null;

        std::this_thread::sleep_for(
            std::chrono::milliseconds( ( 1000 / refreshrate ) - timer.getElapsedTime().asMilliseconds() ) );
        delta = timer.getElapsedTime().asSeconds();
        currentFramestime = delta;
    }
}

void Game::changeState( changeType type, State* state )
{
    bufferState = state;
    this->type = type;
}

void Game::closeGame()
{
    this->window.close();
}

void Game::Override()
{
    // Check if state stack is not empty.
    if( states.size() > 0 )
    {
        // Deletes state.
        State* state = states.back();
        states.pop_back();
        delete state;
    }
    // Adds the buffered state to the stack.
    states.push_back( bufferState );
}

void Game::popState()
{
    if( states.size() > 1 )
    {
        // Deletes state.
        State* state = states.back();
        states.pop_back();
        delete state;
        // Resumes the previous state.
        states.back()->resume();
    }
}

void Game::pushState()
{
    if( states.size() > 0 )
        states.back()->pause();

    states.push_back( bufferState );
}

State* Game::getState( unsigned int i )
{
    if( i > states.size() - 1 )
        return nullptr;
    return states[i];
}

int Game::getStateSize()
{
    return states.size();
}

float Game::getCurrentFramesPerSecond() const
{
    return currentFPS;
}

float Game::getCurrentFramestime() const
{
    return currentFramestime;
}

int Game::getRefreshrate() const
{
    return refreshrate;
}

Window& Game::getWindow()
{
    return window;
}

void Game::setRefreshrate( int refreshrate )
{
    this->refreshrate = refreshrate;
}

InputHandler& Game::getHandler()
{
    return handler;
}
