#include "InputHandler.h"

InputHandler::InputHandler()
{
    this->mouseMoveEvent = 0;
    this->mouseWheelScrolled = 0;
    this->mouseScrollDelta = 0;
    this->previousMousePos = this->currentMousePos = sf::Vector2i( 0, 0 );
    this->window = nullptr;
}

InputHandler::~InputHandler()
{
}

void InputHandler::update()
{
    mouseMoveEvent = false;

    for( auto& it : mButtonPressed )
        if( it.second )
        {
            mButtonDown[it.first] = true;
            it.second = false;
        }

    for( auto& it : mButtonReleased )
        if( it.second )
            it.second = false;

    if( mouseWheelScrolled )
    {
        mouseWheelScrolled = false;
        mouseScrollDelta = 0.0f;
    }

    for( auto& it : keyPressed )
        if( it.second )
        {
            keyDown[it.first] = true;
            it.second = false;
        }

    for( auto& it : keyReleased )
        if( it.second )
            it.second = false;

    previousMousePos = currentMousePos;
}

void InputHandler::handleEvents( sf::Event& e )
{
    switch( e.type )
    {
        case sf::Event::KeyPressed:
            keyPressed[e.key.code] = not keyDown[e.key.code];
            keyReleased[e.key.code] = false;
            break;
        case sf::Event::KeyReleased:
            keyPressed[e.key.code] = false;
            keyDown[e.key.code] = false;
            keyReleased[e.key.code] = true;
            break;
        case sf::Event::MouseButtonPressed:
            mButtonPressed[e.mouseButton.button] = not mButtonDown[e.mouseButton.button];
            mButtonReleased[e.mouseButton.button] = false;
            break;
        case sf::Event::MouseButtonReleased:
            mButtonPressed[e.mouseButton.button] = false;
            mButtonDown[e.mouseButton.button] = false;
            mButtonReleased[e.mouseButton.button] = true;
            break;
        case sf::Event::MouseMoved:
            currentMousePos = sf::Mouse::getPosition( *window );
            mouseMoveEvent = true;
            break;
        case sf::Event::MouseWheelScrolled:
            mouseWheelScrolled = true;
            mouseScrollDelta = e.mouseWheelScroll.delta;
        case sf::Event::TextEntered:
            textInput.emit( e.text.unicode );
            break;
        default:
            break;
    }
}

bool InputHandler::isKeyDown( sf::Keyboard::Key key )
{
    return keyDown[key];
}

bool InputHandler::isKeyPressed( sf::Keyboard::Key key )
{
    return keyPressed[key];
}

bool InputHandler::isKeyReleased( sf::Keyboard::Key key )
{
    return keyReleased[key];
}

bool InputHandler::isMButtonDown( sf::Mouse::Button button )
{
    return mButtonDown[button];
}

bool InputHandler::isMButtonPressed( sf::Mouse::Button button )
{
    return mButtonPressed[button];
}

bool InputHandler::isMButtonReleased( sf::Mouse::Button button )
{
    return mButtonReleased[button];
}

bool InputHandler::isMouseMoved()
{
    return mouseMoveEvent;
}

bool InputHandler::isMouseWheelScrolled()
{
    return mouseWheelScrolled;
}

float InputHandler::getMWheelDelta()
{
    return mouseScrollDelta;
}

sf::Vector2f InputHandler::getMousePos()
{
    return getMousePosMapped( window->getView() );
}

sf::Vector2f InputHandler::getPrevMousePos()
{
    return getPrevMousePosMapped( window->getView() );
}

sf::Vector2f InputHandler::getMouseDelta()
{
    return getMouseDeltaMapped( window->getView() );
}

sf::Vector2f InputHandler::getMousePosMapped( sf::View v )
{
    return window->mapPixelToCoords( currentMousePos, v );
}

sf::Vector2f InputHandler::getPrevMousePosMapped( sf::View v )
{
    return window->mapPixelToCoords( previousMousePos, v );
}

sf::Vector2f InputHandler::getMouseDeltaMapped( sf::View v )
{
    sf::Vector2f cur = getMousePosMapped( v );
    sf::Vector2f pre = getPrevMousePosMapped( v );

    return sf::Vector2f( cur.x - pre.x, cur.y - pre.y );
}

void InputHandler::setWindow( sf::RenderWindow& window )
{
    this->window = &window;
}

sf::RenderWindow* InputHandler::getWindow()
{
    return window;
}
