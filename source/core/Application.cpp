/*
 * =====================================================================================
 *
 *       Filename:  Application.cpp
 *
 *    Description:
 *
 *        Created:  29/07/2018 12:27:30
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Application.hpp"
#include "Config.hpp"
#include "ResourceHandler.hpp"

#include "GameState.hpp"

void Application::init() {
	CoreApplication::init();

	createWindow(Config::screenWidth, Config::screenHeight, Config::windowTitle);

	m_resourceHandler.add<sf::Texture>("texture-frets").loadFromFile("graphics/frets.png");

	ApplicationStateStack::getInstance().push<GameState>();
}

