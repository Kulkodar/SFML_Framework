#include "GUIImageset.h"
#include <fstream>
#include <sstream>

GUIImageset::GUIImageset( std::string const& configFile )
{
    std::stringstream ss;
    std::string buffer;
    std::ifstream file( configFile );

    getline( file, buffer );
    guiTexture.loadFromFile( buffer );
    getline( file, buffer );
    guiFont.loadFromFile( buffer );

    getline( file, buffer );
    ss << buffer;
    getline( ss, buffer, ',' );
    guiTextColor.r = std::stoi( buffer );
    getline( ss, buffer, ',' );
    guiTextColor.g = std::stoi( buffer );
    getline( ss, buffer, ',' );
    guiTextColor.b = std::stoi( buffer );
    getline( ss, buffer, ',' );
    guiTextColor.a = std::stoi( buffer );
    ss.clear();

    getline( file, buffer );
    ss << buffer;
    getline( ss, buffer, ',' );
    guiTextOutlineColor.r = std::stoi( buffer );
    getline( ss, buffer, ',' );
    guiTextOutlineColor.g = std::stoi( buffer );
    getline( ss, buffer, ',' );
    guiTextOutlineColor.b = std::stoi( buffer );
    getline( ss, buffer, ',' );
    guiTextOutlineColor.a = std::stoi( buffer );
    ss.clear();

    getline( file, buffer );
    outlineThicness = std::stof( buffer );

    for( int i = 0; i < 37; i++ )
    {
        getline( file, buffer );
        ss << buffer;

        getline( ss, buffer, ',' );
        UVs[i].left = std::stoi( buffer );
        getline( ss, buffer, ',' );
        UVs[i].top = std::stoi( buffer );
        getline( ss, buffer, ',' );
        UVs[i].width = std::stoi( buffer );
        getline( ss, buffer, ',' );
        UVs[i].height = std::stoi( buffer );
    }
}

GUIImageset::~GUIImageset()
{
}
