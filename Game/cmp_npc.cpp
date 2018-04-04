#include "cmp_npc.h"
#include "SystemRenderer.h"
#include "Game.h"
#include "cmp_actor_movement.h"

sf::Clock timer;
int i = 0;
int y = 0;
NPCComponent::NPCComponent(Entity *p) : Component(p) 
{
	dialogueBox.setFillColor(sf::Color(255,255,255,200));
	dialogueBox.setSize(sf::Vector2f(0.98f*Renderer::gameWidth, 0.25f*Renderer::gameHeight));
	dialogueBox.setPosition(sf::Vector2f(0.025f* Renderer::gameWidth, 0.75f*Renderer::gameHeight));
	text.setColor(sf::Color::Black);
	text.setFont(font);
	text.setCharacterSize(27.0f);
}
void NPCComponent::setDialogue(std::string x)
{
	dialogue = x;
}
void NPCComponent::update(double dt) 
{
	interactionDelay -= dt;
	dialogueBox.setPosition(_player->getPosition() + sf::Vector2f(-0.49f* Renderer::gameWidth, 0.20f*Renderer::gameHeight));
	text.setPosition(_player->getPosition() + sf::Vector2f(-0.48f* Renderer::gameWidth, 0.21f*Renderer::gameHeight));
	if (interactionDelay <= 0 && (length(_parent->getPosition() - _player->getPosition()) < 21.0f) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		_player->GetComponent<PlayerMovementComponent>()->immobilize();
		interact();
	}
		

	if (trigger && timer.getElapsedTime().asMilliseconds() > 40.0f && i < dialogue.length())
	{
		timer.restart();
		i++;
		text.setString(sf::String(dialogue.substr(0, i)));
	}
	
	if (i >= dialogue.size())
	{
		dialogueFinished = true;
	}
	if (dialogueFinished && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		i = 0;
		trigger = false;
		dialogueFinished = false;
		interactionDelay = 0.4f;
		_player->GetComponent<PlayerMovementComponent>()->mobilize();
	}
	
}
void NPCComponent::setEntities(std::shared_ptr<Entity>& e) {
	_player = e;
}
void NPCComponent::render() 
{
	if (trigger)
	{
		Renderer::queue(&dialogueBox);
		Renderer::queue(&text);
	}
}
void NPCComponent::interact()
{
	trigger = true;
}