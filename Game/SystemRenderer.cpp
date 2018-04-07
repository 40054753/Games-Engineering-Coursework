#include "SystemRenderer.h"
#include <queue>
#include <iostream>

using namespace std;
using namespace sf;
static queue<const Drawable *>  spritesInt;
static queue<const Drawable *>  sprites0;
static queue<const Drawable *>  sprites1;
static queue<const Drawable *>  sprites2;
static queue<const Drawable *>  sprites3;
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
	while (!sprites3.empty())
		sprites3.pop();
	while (!sprites2.empty())
		sprites2.pop();
	while (!sprites1.empty())
		sprites2.pop();
	while (!sprites0.empty())
		sprites2.pop();
	while (!spritesInt.empty())
		spritesInt.pop();
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
	while (!sprites3.empty())
	{
		rw->draw(*sprites3.front());
		sprites3.pop();
	}
	while (!sprites2.empty())
	{
		rw->draw(*sprites2.front());
		sprites2.pop();
	}
	while (!sprites1.empty())
	{
		rw->draw(*sprites1.front());
		sprites1.pop();
	}
	while (!sprites0.empty())
	{
		rw->draw(*sprites0.front());
		sprites0.pop();
	}
	while (!spritesInt.empty())
	{
		rw->draw(*spritesInt.front());
		spritesInt.pop();
	}
	
}
void Renderer::queue(const sf::Drawable *s)
{
		sprites3.push(s);
}
void Renderer::queue(int p ,const sf::Drawable *s) 
{ 
	if (p == 3)
		sprites3.push(s);
	else if (p == 2)
		sprites2.push(s);
	else if (p == 1)
		sprites1.push(s);
	else if (p == 0)
		sprites0.push(s);
	else if (p == -1)
		spritesInt.push(s);
}	
