#pragma once

#include <unordered_map>

#include <Signal.h>

#include <SFML/Graphics.hpp>

/**
 * @brief Helper class to handler user input
 */
class InputHandler
{
  public: // Constructor
    InputHandler();
    /**Deleted copy Constructor!*/
    InputHandler( InputHandler& other ) = delete;
    /**Deleted move Constructor!*/
    InputHandler( InputHandler&& ) = delete;
    ~InputHandler();

  public: // Methods
    /**
     * @brief Updates the buttonstates and keystates
     */
    void update();
    /**
     * @brief Prozesses all inut events
     * @param e Event
     */
    void handleEvents( sf::Event& e );

  public: // Events
    Signal<char32_t> textInput;

  public: // Operators
    /**Deleted copy assignment operator!*/
    InputHandler& operator=( const InputHandler& other ) = delete;
    /**Deleted move assignment operator!*/
    InputHandler& operator=( InputHandler&& ) = delete;

  protected: // Attributes
    // Key and Button state maps
    std::unordered_map<unsigned int, bool> keyPressed;
    std::unordered_map<unsigned int, bool> keyDown;
    std::unordered_map<unsigned int, bool> keyReleased;
    std::unordered_map<unsigned int, bool> mButtonPressed;
    std::unordered_map<unsigned int, bool> mButtonDown;
    std::unordered_map<unsigned int, bool> mButtonReleased;
    //---

    // Event booleans
    bool mouseMoveEvent;
    bool mouseWheelScrolled;
    float mouseScrollDelta;
    //---

    sf::Vector2i currentMousePos;  /// Mouse position buffer
    sf::Vector2i previousMousePos; /// Last mouse position buffer

    sf::RenderWindow* window; /// Reference to a sfml window to map the coursor position

  public: // Getter Setter
    /**
     * @brief Returns the state of the key
     * @param key Key to retrive the state
     * @return True if key is pressed ,falls other so
     */
    bool isKeyPressed( sf::Keyboard::Key key );
    /**
     * @brief Returns the state of the key
     * @param key Key to retrive the state
     * @return True if key is down ,falls other so
     */
    bool isKeyDown( sf::Keyboard::Key key );
    /**
     * @brief Returns the state of the key
     * @param key Key to retrive the state
     * @return True if key is up ,falls other so
     */
    bool isKeyReleased( sf::Keyboard::Key key );
    /**
     * @brief Returns the state of the key
     * @param button Button to retrive the state
     * @return True if Button is pressed ,falls other so
     */
    bool isMButtonPressed( sf::Mouse::Button button );
    /**
     * @brief Returns the state of the key
     * @param button Button to retrive the state
     * @return True if Button is down ,falls other so
     */
    bool isMButtonDown( sf::Mouse::Button button );
    /**
     * @brief Returns the state of the key
     * @param button Button to retrive the state
     * @return True if Button is up ,falls other so
     */
    bool isMButtonReleased( sf::Mouse::Button button );
    /**
     * @return True if mouse was moved between the last frame and the current
     */
    bool isMouseMoved();
    /**
     * @return True if mousewheel was moved between the last frame and the
     * current
     */
    bool isMouseWheelScrolled();
    /**
     * @return Amount the scroll whell has moved as float
     */
    float getMWheelDelta();
    /**
     * @return Current mouse position
     */
    sf::Vector2f getMousePos();
    /**
     * @return Previous mouse position
     */
    sf::Vector2f getPrevMousePos();
    /**
     * @return the differrence between the current and previous mousepos
     */
    sf::Vector2f getMouseDelta();
    /**
     * @return Current mouse position mapped to a view
     * @param v view to map the mouse position
     */
    sf::Vector2f getMousePosMapped( sf::View v );
    /**
     * @return Previous mouse position mapped to a view
     * @param v view to map the mouse position
     */
    sf::Vector2f getPrevMousePosMapped( sf::View v );
    /**
     * @return the differrence between the current and previous mousepos
     * @param v view to map the mouse position
     */
    sf::Vector2f getMouseDeltaMapped( sf::View v );
    /**
     * @brief set the internal window to map the mouse position
     * @param window Window to use to map
     */
    void setWindow( sf::RenderWindow& window );
    /**
     * @return internal window
     */
    sf::RenderWindow* getWindow();
};
