#include "SystemRenderer.h"
#include <queue>
#include <iostream>

using namespace std;
using namespace sf;

static queue<const Drawable *>  sprites;
static queue<const Drawable *>  HUDsprites;
static RenderWindow *rw;
static View playerCam(Vector2f(0.0f, 0.0f), Vector2f(1280.0f, 720.0f));

void Renderer::initialise(RenderWindow &r) { 
	rw = &r; 
	
}

sf::RenderWindow &Renderer::getWindow() { return *rw; }
void Renderer::updateView()
{
	
}
void Renderer::shutdown()
{
	while (!sprites.empty())
		sprites.pop();
	while (!HUDsprites.empty())
		HUDsprites.pop();
}
void Renderer::update(const double &) 
{
}
void Renderer::setCenter(Vector2f pos)
{
	playerCam.setCenter(pos);
}
void Renderer::resizeView()
{
		rw->setSize(Vector2u(1280.0f , 720.0f));
}
void Renderer::render()
{
	rw->setView(playerCam);
	if (rw == nullptr)
	{
		throw("No render window set! ");
	}
	while (!sprites.empty())
	{
		//every frame set the view to point at the player (playerCam centre gets updated in gamescene update)
		//std::cout << rw->getDefaultView().getCenter().x << "   " <<rw->getDefaultView().getCenter().y << std::endl;
		rw->draw(*sprites.front());
		sprites.pop();
	}
	while (!HUDsprites.empty())
	{
		//every frame set the view to point at the player (playerCam centre gets updated in gamescene update)
		//std::cout << rw->getDefaultView().getCenter().x << "   " <<rw->getDefaultView().getCenter().y << std::endl;
		rw->draw(*HUDsprites.front());
		HUDsprites.pop();
	}
	
}
void Renderer::queue(const sf::Drawable *s) { sprites.push(s); }
void Renderer::HUDqueue(const sf::Drawable *s) { HUDsprites.push(s); }