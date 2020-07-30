#pragma once

#include <SFML/Graphics/View.hpp>

/**
 * @brief A virtual camera with letterbox suport
 */
class Camera
{
  public: // Constructor
    /**
     * @param size Internal size of the camera
     * @param origin Internal size of the camera
     * @param aspectratio Target aspect ratio
     */
    Camera( sf::Vector2f size, sf::Vector2f origin, float aspectratio );
    ~Camera();

  public: // Methods
    /**
     * @brief function to handle Window resize event
     * @param size New Window size
     */
    void windowResized( sf::Vector2u size );

  protected:             // Attributes
    sf::View v;          /// Internal view with a viewport
    sf::Vector2f size;   /// Size of the view
    sf::Vector2f origin; /// Midpoint of the view
    float aspectRatio;   /// Window aspect ratio

  public: // Getter Setter
    /**
     * @return a refference to the internal view
     */
    sf::View& getView();
    /**
     * @return the target aspect ratio
     */
    float getAspectRatio() const;
    /**
     * @param origin new Midpoint of the camera
     */
    void setOrigin( sf::Vector2f origin );
    /**
     * @return current midpoint of the camera
     */
    sf::Vector2f getOrigin();
    /**
     * @param size New internal view size
     */
    void setSize( sf::Vector2f size );
    /**
     * @return internal view size
     */
    sf::Vector2f getSize();
};
