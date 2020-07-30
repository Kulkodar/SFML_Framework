#include "AssetManager.h"

AssetManager::AssetManager()
{
    // create default texture
    uint8_t data[4 * 4];

    data[0] = 0x00;
    data[1] = 0x00;
    data[2] = 0x00;
    data[3] = 0xff;

    data[4] = 0xff;
    data[5] = 0x00;
    data[6] = 0xff;
    data[7] = 0xff;

    data[8] = 0xff;
    data[9] = 0x00;
    data[10] = 0xff;
    data[11] = 0xff;

    data[12] = 0x00;
    data[13] = 0x00;
    data[14] = 0x00;
    data[15] = 0xff;

    this->defaultTexture = new sf::Texture;
    this->defaultTexture->create( 2, 2 );
    this->defaultTexture->update( (uint8_t*)data );
    //---
}

AssetManager::~AssetManager()
{
    clearAll();
}

void AssetManager::clearAll()
{
    clearFonts();
    clearTextures();
    clearSounds();
    clearMusic();
    clearImagesets();
}

void AssetManager::clearFonts()
{
    // deletes all fonts
    for( auto k : fonts )
        if( k.second != nullptr )
            delete k.second;
    fonts.clear();
    //---
}

void AssetManager::clearMusic()
{
    // deletes all Music objects
    for( auto k : music )
        if( k.second != nullptr )
            delete k.second;
    music.clear();
    //---
}

void AssetManager::clearSounds()
{
    // deletes all SoundBuffers
    for( auto k : sounds )
        if( k.second != nullptr )
            delete k.second;
    sounds.clear();
    //---
}

void AssetManager::clearTextures()
{
    // deletes all textures
    for( auto k : textures )
        if( k.second != nullptr )
            delete k.second;
    textures.clear();
    //---
}

void AssetManager::clearImagesets()
{
    // deletes all imagesets
    for( auto k : imagesets )
        if( k.second != nullptr )
            delete k.second;
    imagesets.clear();
    //---
}

sf::Font* AssetManager::getFont( std::string fileName )
{
    // check if font is not in the map
    if( fonts[fileName] == nullptr )
    {
        // loads the font
        fonts[fileName] = new sf::Font;
        if( !fonts[fileName]->loadFromFile( fileName ) )
        {
            // TODO: default font
        }
    }
    // return font pointer
    return fonts[fileName];
}

sf::Music* AssetManager::getMusic( std::string fileName )
{
    // check if Music is not in the map
    if( music[fileName] == nullptr )
    {
        // loads the SoundBuffer
        music[fileName] = new sf::Music;
        if( !music[fileName]->openFromFile( fileName ) )
        {
            // TODO: default Music
        }
    }
    // return SoundBuffer pointer
    return music[fileName];
}

sf::SoundBuffer* AssetManager::getSound( std::string fileName )
{
    // check if SoundBuffer is not in the map
    if( sounds[fileName] == nullptr )
    {
        // loads the SoundBuffer
        sounds[fileName] = new sf::SoundBuffer;
        if( !sounds[fileName]->loadFromFile( fileName ) )
        {
            // TODO: default SoundBuffer
        }
    }
    // return SoundBuffer pointer
    return sounds[fileName];
}

sf::Texture* AssetManager::getTexture( std::string fileName )
{
    // check if texture is not in the map
    if( textures[fileName] == nullptr )
    {
        // load the texture
        textures[fileName] = new sf::Texture;
        if( !textures[fileName]->loadFromFile( fileName ) )
        {
            // copies the default texture to the key
            *textures[fileName] = *defaultTexture;
        }
    }
    // return the pointer
    return textures[fileName];
}

GUIImageset* AssetManager::getImageset( std::string fileName )
{
    // check if SoundBuffer is not in the map
    if( imagesets[fileName] == nullptr )
    {
        // loads the SoundBuffer
        imagesets[fileName] = new GUIImageset( fileName );
    }
    // return SoundBuffer pointer
    return imagesets[fileName];
}
