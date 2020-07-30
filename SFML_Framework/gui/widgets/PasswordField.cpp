#include "PasswordField.h"

PasswordField::PasswordField( std::string const& id, sf::Vector2f size, sf::Vector2f pos, GUIImageset& imageset,
                              InputHandler& handler, int charSize )
    : EditBox( id, size, pos, imageset, handler, charSize )
{
    buffer = "";
}

PasswordField::~PasswordField()
{
}

void PasswordField::handleTextInput( char32_t text )
{
    //    if ( isActive )
    //    {
    //        if ( text == 18 )
    //            isActive = 0;
    //        else if ( text == 8 )
    //        {
    //            sf::String buffer = label.getText( );
    //            if ( this->buffer.getSize( ) != 0 )
    //            {
    //                this->buffer.erase( buffer.getSize( ) - 1, 1 );
    //                buffer.erase( buffer.getSize( ) - 1, 1 );
    //            }
    //
    //            label.setText( buffer );
    //        }
    //        else
    //        {
    //            if ( buffer.isEmpty( ) )
    //                buffer = text;
    //            else
    //                buffer.insert( buffer.getSize( ) - 1, text );
    //            label.setText( label.getText( ) + "*" );
    //        }
    //    }
}

sf::String& PasswordField::getPassword()
{
    return buffer;
}
