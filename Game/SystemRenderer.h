#pragma once
#include <SFML/Graphics.hpp>

namespace  Renderer
{

	constexpr uint16_t gameWidth = 1280;
	constexpr uint16_t gameHeight = 720;

	void initialise(sf::RenderWindow &);
	sf::RenderWindow &getWindow();
	void updateView();
	void shutdown();
	void update(const double &);
	void queue(const sf::Drawable *s);
	void queue(int priority, const sf::Drawable *s);
	void queue(const sf::Drawable *s);
	void render();
	void setCenter(sf::Vector2f pos);
	void resizeView();
};
