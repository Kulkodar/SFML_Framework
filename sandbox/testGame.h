#pragma once
#include "SFML_Framework/Game.h"
/**
 * @file testGame.h
 * Description
 *
 * @author AtomicDragon
 */

/**
 * @class testGame
 *
 * @brief
 */
class testGame : public Game
{
  public: // Constructor
    testGame( sf::Vector2i windowSize, std::string windowTitle, int refreshrate, sf::ContextSettings settings );
    /**
     * Deleted copy Constructor!
     */
    testGame( testGame& other ) = delete;
    /**
     * Deleted move Constructor!
     */
    testGame( testGame&& ) = delete;
    ~testGame();

  public: // Methods
    void test( char c );

  public: // Operators
    /**
     * Deleted copy assignment operator!
     */
    testGame& operator=( const testGame& other ) = delete;
    /**
     * Deleted move assignment operator!
     */
    testGame& operator=( testGame&& ) = delete;

  protected: // Attributes
  public:    // Getter Setter
};
