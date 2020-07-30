cmake_minimum_required( VERSION 3.17 )
project( SFML_Framework )

include( GNUInstallDirs )

set( CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON )
set( INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_PROJECT_NAME} )

find_package( SFML 2.5 COMPONENTS graphics window system REQUIRED )

add_library( SFML_Framework )

target_include_directories( SFML_Framework
		PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> )

target_link_libraries( SFML_Framework
		PUBLIC
		$<$<CONFIG:Debug>:gcov>
		GL
		sfml-system
		sfml-graphics
		sfml-audio )

target_compile_features( SFML_Framework
		PUBLIC
		cxx_std_20 )
target_compile_options( SFML_Framework
		PUBLIC
		-Wall
		-Wextra
		$<$<CONFIG:Release>: -O2 >
		$<$<CONFIG:Debug>: -O0 --coverage -fPIC > )

target_sources(
		SFML_Framework
		PRIVATE
		SFML_Framework/AssetManager.cpp
		SFML_Framework/Camera.cpp
		SFML_Framework/Game.cpp
		SFML_Framework/InputHandler.cpp
		SFML_Framework/State.cpp
		SFML_Framework/State.cpp
		SFML_Framework/Window.cpp
		SFML_Framework/gui/GUI.cpp
		SFML_Framework/gui/GUIGroup.cpp
		SFML_Framework/gui/GUIImageset.cpp
		SFML_Framework/gui/GUIWidget.cpp
		SFML_Framework/gui/widgets/Button.cpp
		SFML_Framework/gui/widgets/Checkbox.cpp
		SFML_Framework/gui/widgets/ColorPicker.cpp
		SFML_Framework/gui/widgets/DropDownList.cpp
		SFML_Framework/gui/widgets/EditBox.cpp
		SFML_Framework/gui/widgets/GUIWindow.cpp
		SFML_Framework/gui/widgets/Label.cpp
		SFML_Framework/gui/widgets/NumberField.cpp
		SFML_Framework/gui/widgets/PasswordField.cpp
		SFML_Framework/gui/widgets/ProgressBar.cpp
		SFML_Framework/gui/widgets/RadialCheckBox.cpp
		SFML_Framework/gui/widgets/ScrollBar.cpp
		SFML_Framework/gui/widgets/Slider.cpp
		SFML_Framework/gui/widgets/Spinner.cpp
		SFML_Framework/gui/widgets/Thumb.cpp )

install( TARGETS SFML_Framework
		CONFIGURATIONS Release
		EXPORT SFML_FrameworkConfig
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} )
install( EXPORT SFML_FrameworkConfig
		FILE SFML_FrameworkConfig.cmake
		DESTINATION ${INSTALL_CONFIGDIR} )

install( DIRECTORY SFML_Framework/
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME}
		FILES_MATCHING PATTERN "*.h*" )

add_subdirectory(sandbox)