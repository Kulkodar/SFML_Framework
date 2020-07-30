#include "NumberField.h"

NumberField::NumberField( std::string const& id, sf::Vector2f size, sf::Vector2f pos, GUIImageset& imageset,
                          InputHandler& handler, int charSize )
    : EditBox( id, size, pos, imageset, handler, charSize )
{
    this->number = 0;
    this->label.setText( "0" );
}

NumberField::~NumberField()
{
}

void NumberField::handleTextInput( char32_t text )
{
    if( isActive )
    {
        if( text == 18 )
            isActive = 0;
        else
        {
            std::string buffer = this->label.getText().toAnsiString();
            if( text == 8 )
            {

                if( buffer.length() != 0 )
                {
                    buffer.pop_back();

                    this->label.setText( buffer );
                    this->number /= 10;
                }

                this->label.setText( buffer );
            }
            else
            {
                if( text == '-' )
                {
                    this->number *= -1;
                    this->label.setText( std::to_string( this->number ) );
                }
                if( 48 <= text && text <= 57 )
                {
                    buffer.push_back( text );
                    this->number = number * 10 + ( text - 48 );
                    this->label.setText( std::to_string( this->number ) );
                }
            }
        }
    }
}

int NumberField::getNumber()
{
    return this->number;
}

void NumberField::setNumber( int num )
{
    this->number = num;
    label.setText( std::to_string( num ) );
}
