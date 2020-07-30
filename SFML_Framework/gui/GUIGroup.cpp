#include "GUIGroup.h"

GUIGroup::GUIGroup( std::string const& ID )
    : GUIWidget( ID )
{
    this->hiden = 0;
}

GUIGroup::~GUIGroup()
{
    for( auto* k : group )
        delete k;
}

void GUIGroup::handleEvents( InputHandler& handler, sf::View* view )
{
    if( !disabled )
        for( auto elem : group )
            elem->handleEvents( handler, view );
}
void GUIGroup::update( float delta )
{
    if( !disabled )
        for( auto elem : group )
            elem->update( delta );
}
void GUIGroup::draw( Window& window, int currentStencilValue )
{
    if( !hiden )
        for( auto elem : group )
            elem->draw( window, currentStencilValue );
}

void GUIGroup::disable( bool dsiabled )
{
    this->disabled = dsiabled;
}

void GUIGroup::addWidget( GUIWidget* widget )
{
    group.push_back( widget );
}

bool GUIGroup::removeWidget( std::string const& id )
{
    for( unsigned int i = 0; i < group.size(); i++ )
    {
        if( group[i]->getId() == id )
        {
            GUIWidget* buffer = group[i];
            group.erase( group.begin() + i );
            delete buffer;
            return 1;
        }
    }
    return 0;
}

GUIWidget* GUIGroup::getWidget( std::string const& id )
{
    for( unsigned int i = 0; i < group.size(); i++ )
        if( group[i]->getId() == id )
            return group[i];
    return nullptr;
}
