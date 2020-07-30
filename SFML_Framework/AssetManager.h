#pragma once

#include <map>

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML_Framework/gui/GUIImageset.h>

/**
 * @brief A asset container that loads the assets as they needed
 */
class AssetManager
{
  public: // Constructor
    AssetManager();
    /**Deleted copy Constructor!*/
    AssetManager( AssetManager& other ) = delete;
    /**Deleted move Constructor!*/
    AssetManager( AssetManager&& ) = delete;
    ~AssetManager();

  public: // Methods
    /**
     * Deletes all assets.
     */
    void clearAll();

    /**Deletes all fonts in the map.*/
    void clearFonts();
    /**Deletes all Music objects in the map.*/
    void clearMusic();
    /**Deletes all SoundBuffers in the map.*/
    void clearSounds();
    /**Deletes all textures in the map.*/
    void clearTextures();
    /**Deletes all Imagesets in the map.*/
    void clearImagesets();

  public: // Operators
    /**Deleted copy assignment operator!*/
    AssetManager& operator=( const AssetManager& other ) = delete;
    /**Deleted move assignment operator!*/
    AssetManager& operator=( AssetManager&& ) = delete;

  protected: // Attributes
    /// Map of all loaded fonts.
    std::map<std::string, sf::Font*> fonts;
    // Default font if no file was found.
    //    sf::Font* defaultFont;

    /// Map of all loaded Music objects.
    std::map<std::string, sf::Music*> music;
    /// Default Music object if no file was found.
    // sf::Texture* defaultTexture;

    /// Map of all loaded SoundBuffers.
    std::map<std::string, sf::SoundBuffer*> sounds;
    /// Default SoundBuffer if no file was found.
    // sf::Texture* defaultTexture;

    /// Map of all loaded textures.
    std::map<std::string, sf::Texture*> textures;
    /// Default texture if no file was found.
    sf::Texture* defaultTexture;

    /// Map of all loaded Imagsets.
    std::map<std::string, GUIImageset*> imagesets;
    /// Default texture if no file was found.
    //    sf::Texture* defaultTexture;

  public: // Getter Setter
    /**
     * Creates a new texture if it was not loaded before.
     * If no file was found ,a default texture will be returned.
     *
     * @param fileName Relative path to the font file.
     * @return A font pointer.
     */
    sf::Font* getFont( std::string fileName );
    /**
     * Creates a new Music Object if it was not loaded before.
     * If no file was found ,a default Music will be returned.
     *
     * @param fileName Relative path to the Music file.
     * @return A SoundBuffer pointer.
     */
    sf::Music* getMusic( std::string fileName );
    /**
     * Creates a new SoundBuffer if it was not loaded before.
     * If no file was found ,a default SoundBuffer will be returned.
     *
     * @param fileName Relative path to the SoundBuffer file.
     * @return A SoundBuffer pointer.
     */
    sf::SoundBuffer* getSound( std::string fileName );
    /**
     * Creates a new texture if it was not loaded before.
     * If no file was found ,a default texture will be returned.
     *
     * @param fileName Relative path to the texture file.
     * @return A texture pointer.
     */
    sf::Texture* getTexture( std::string fileName );

    /**
     * Creates a new texture if it was not loaded before.
     * If no file was found ,a default texture will be returned.
     *
     * @param fileName Relative path to the texture file.
     * @return A texture pointer.
     */
    GUIImageset* getImageset( std::string fileName );
};
