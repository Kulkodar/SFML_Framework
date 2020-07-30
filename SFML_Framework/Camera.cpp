#include "Camera.h"

Camera::Camera( sf::Vector2f size, sf::Vector2f origin, float aspectratio )
{
    this->size = size;
    this->origin = origin;
    this->aspectRatio = aspectratio;

    this->v.setCenter( origin );
    this->v.setSize( size );
}

Camera::~Camera()
{
}

void Camera::windowResized( sf::Vector2u size )
{
    sf::Vector2f view( 0, 0 );
    sf::Vector2f vport( 0, 0 );

    view.y = size.y;
    view.x = view.y * aspectRatio;
    vport.x = ( size.x - view.x );

    if( vport.x < 0 )
    {
        vport.x = 0;
        view.x = size.x;
        view.y = view.x / aspectRatio;
        vport.y = ( size.y - view.y );
    }

    this->v.setViewport(
        sf::FloatRect( ( vport.x / size.x ) / 2.0f, ( vport.y / size.y ) / 2.0f, view.x / size.x, view.y / size.y ) );
}

sf::View& Camera::getView()
{
    return v;
}

float Camera::getAspectRatio() const
{
    return aspectRatio;
}

void Camera::setOrigin( sf::Vector2f origin )
{
    this->origin = origin;
    v.setCenter( origin );
}

sf::Vector2f Camera::getOrigin()
{
    return origin;
}

void Camera::setSize( sf::Vector2f size )
{
    this->size = size;
    v.setSize( size );
}

sf::Vector2f Camera::getSize()
{
    return size;
}
