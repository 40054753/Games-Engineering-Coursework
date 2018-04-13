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
	dialogueBox.setSize(sf::Vector2f(0.98f*WX, 0.25f*WY));
	dialogueBox.setPosition(sf::Vector2f(0.025f* WX, 0.75f*WY));
	text.setColor(sf::Color::Black);
	text.setFont(font);
	text.setCharacterSize(27.0f * WX/1280);
}
void NPCComponent::setDialogue(std::string x)
{
	dialogue = x;
}
void NPCComponent::update(double dt) 
{
	interactionDelay -= dt;
	dialogueBox.setPosition(player->getPosition() + sf::Vector2f(-0.49f* WX, 0.14f*WY));
	text.setPosition(player->getPosition() + sf::Vector2f(-0.48f* WX, 0.15f*WY));
	if (interactionDelay <= 0 && (length(_parent->getPosition() - player->getPosition()) < 21.0f*WX/1280) && (sf::Keyboard::isKeyPressed(controls[12]) || sf::Joystick::isButtonPressed(0, sf::Joystick::Z)))
	{
		player->GetComponent<PlayerMovementComponent>()->immobilize();
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
	if (dialogueFinished && (length(_parent->getPosition() - player->getPosition()) < 21.0f*WX / 1280) && (sf::Keyboard::isKeyPressed(controls[12]) || sf::Joystick::isButtonPressed(0, sf::Joystick::Z)))
	{
		i = 0;
		trigger = false;
		dialogueFinished = false;
		interactionDelay = 0.4f;
		player->GetComponent<PlayerMovementComponent>()->mobilize();
	}
	
}
void NPCComponent::render() 
{
	if (trigger)
	{
		Renderer::queue(0,&dialogueBox);
		Renderer::queue(0,&text);
	}
}
void NPCComponent::interact()
{
	trigger = true;
}