#pragma once

#include "GUIWidget.h"

/**
 * @brief A group of GUIWidget
 */
class GUIGroup : public GUIWidget
{
  public: // Constructor
    /**
     * @param ID Unique id to find the Widget in a container
     */
    GUIGroup( std::string const& ID );
    /**Deleted copy Constructor!*/
    GUIGroup( GUIGroup& other ) = delete;
    /**Deleted move Constructor!*/
    GUIGroup( GUIGroup&& ) = delete;
    ~GUIGroup();

  public: // Methods
    /**
     * @brief Handles user input
     * @param handler user input handler
     * @param view View to map the coursor position
     */
    void handleEvents( InputHandler& handler, sf::View* view = nullptr ) override;
    /**
     * Updates the Widget
     * @param delta Current frame time
     */
    void update( float delta ) override;
    /**
     * Draws the Widget
     * @param window Target window
     * @param currentStencilValue OpenGL stencil value/ Layer to draw on
     */
    void draw( Window& window, int currentStencilValue ) override;
    /**
     * Disables/Enables the widget
     * @param disabled State of the widget
     */
    void disable( bool disabled ) override;
    /**
     * Adds a GUIWidget to the group
     * The group deletes the Widget
     * @param widget
     */
    void addWidget( GUIWidget* widget );
    /**
     * Removes a widget from this group
     * @param id Id of the widget
     * @return If widget was found and removed
     */
    bool removeWidget( std::string const& id );

  public: // Operators
    /**Deleted copy assignment operator!*/
    GUIGroup& operator=( const GUIGroup& other ) = delete;
    /**Deleted move assignment operator!*/
    GUIGroup& operator=( GUIGroup&& ) = delete;

  protected: // Attributes
    /// Group of GUIWidgets
    std::vector<GUIWidget*> group;

  public: // Getter Setter
    /**
     * Searches for a GUIWiddget in the container
     * @param id Id of the GUIWiddget
     * @return Nullptr if nothing is found else the GUIWIdget
     */
    GUIWidget* getWidget( std::string const& id );
};
