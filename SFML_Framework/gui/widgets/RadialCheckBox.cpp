#include "RadialCheckBox.h"

RadialCheckBox::RadialCheckBox( std::string const& id, std::string const& text, sf::Vector2f size, sf::Vector2f pos,
                                GUIImageset& imageset, int charSize )
    : Checkbox( id, text, size, pos, imageset, charSize )
{
    // Set attributes to default
    this->uvMouseover = imageset.UVs[UVType::RadialCheckBoxMouseover];
    this->uvNormal = imageset.UVs[UVType::RadialCheckBoxBase];
    //---

    // Create base shape
    base.setTextureRect( this->uvNormal );
    //---

    // Create check mark shape.
    mark.setTextureRect( imageset.UVs[UVType::RadialCheckBoxBaseMark] );
    //---
}

RadialCheckBox::~RadialCheckBox()
{
}
