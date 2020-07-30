#include "GUIWidget.h"

GUIWidget::GUIWidget( std::string const& id )
    : id( id )
{
    this->disabled = false;
    this->moveable = false;
    this->hiden = false;
}

GUIWidget::GUIWidget()
    : GUIWidget( "" )
{
}

GUIWidget::~GUIWidget()
{
    EventClicked.disconnect_all();
    EventReleased.disconnect_all();
    CheckboxChecked.disconnect_all();
    Moved.disconnect_all();
    ValueChanged.disconnect_all();
}

void GUIWidget::disable( bool disabled )
{
    this->disabled = disabled;
}

bool GUIWidget::isDisabled() const
{
    return disabled;
}

bool GUIWidget::isHiden() const
{
    return hiden;
}

std::string const& GUIWidget::getId() const
{
    return id;
}

bool GUIWidget::isMoveable() const
{
    return this->moveable;
}

void GUIWidget::hide( bool hiden )
{
    this->hiden = hiden;
    disable( hiden );
}

void GUIWidget::setMoveable( bool moveable )
{
    this->moveable = moveable;
}

sf::Vector2f GUIWidget::getOrigin()
{
    return sf::Vector2f( 0, 0 );
}

sf::Vector2f GUIWidget::getPosition()
{
    return sf::Vector2f( 0, 0 );
}

sf::Vector2f GUIWidget::getSize()
{
    return sf::Vector2f( 0, 0 );
}

void GUIWidget::setOrigin( sf::Vector2f oo )
{
}

void GUIWidget::setPosition( sf::Vector2f pos )
{
}

void GUIWidget::setSize( sf::Vector2f size )
{
}
