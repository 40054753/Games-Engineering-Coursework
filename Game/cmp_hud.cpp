#pragma once
#include "cmp_hud.h"
#include "SystemRenderer.h"
#include <string>
#include <iostream>
#include "Game.h"
#include "cmp_health.h"
using namespace sf;

HudComponent::HudComponent(Entity *p) : Component(p)
{

	HP.setFillColor(sf::Color::Red);
	HP.setSize({ Renderer::gameWidth / 5.7f,Renderer::gameHeight / 25.0f });
	MP.setFillColor(sf::Color::Blue);
	MP.setSize({ Renderer::gameWidth / 5.7f,Renderer::gameHeight / 25.0f });
	text.setCharacterSize(22);
	text.setColor(sf::Color::White);
	text.setFont(font);
	/////////////////////////////////    BOTTOM HUD BG ////////////////////////////////////////////
	buttonsBackground.setFillColor(sf::Color(255,255,255,150));
	buttonsBackground.setSize({ 0.5f*Renderer::gameWidth, 0.1f * Renderer::gameHeight});
	/////////////////////////////////   SKILLL BUTTONS ////////////////////////////////////////////
	skill1.setFillColor(sf::Color::Black);
	skill1.setSize({ 0.045f*Renderer::gameWidth, 0.07f * Renderer::gameHeight });
	skill2.setFillColor(sf::Color::Black);
	skill2.setSize({ 0.045f*Renderer::gameWidth, 0.07f * Renderer::gameHeight });
	skill3.setFillColor(sf::Color::Black);
	skill3.setSize({ 0.045f*Renderer::gameWidth, 0.07f * Renderer::gameHeight });
	skill4.setFillColor(sf::Color::Black);
	skill4.setSize({ 0.045f*Renderer::gameWidth, 0.07f * Renderer::gameHeight });
	skill5.setFillColor(sf::Color::Black);
	skill5.setSize({ 0.045f*Renderer::gameWidth, 0.07f * Renderer::gameHeight });

	label_skill1.setFont(font);
	label_skill1.setColor(sf::Color::Red);
	label_skill1.setCharacterSize(15.0f);
	label_skill1.setString("1");
	label_skill2.setFont(font);
	label_skill2.setColor(sf::Color::Red);
	label_skill2.setCharacterSize(15.0f);
	label_skill2.setString("2");
	label_skill3.setFont(font);
	label_skill3.setColor(sf::Color::Red);
	label_skill3.setCharacterSize(15.0f);
	label_skill3.setString("3");
	label_skill4.setFont(font);
	label_skill4.setColor(sf::Color::Red);
	label_skill4.setCharacterSize(15.0f);
	label_skill4.setString("4");
	label_skill5.setFont(font);
	label_skill5.setColor(sf::Color::Red);
	label_skill5.setCharacterSize(15.0f);
	label_skill5.setString("5");

	////////////////////////BUTTONS
	button_menu.setOutlineColor(sf::Color::Black);
	button_menu.setOutlineThickness(5.0f);
	button_menu.setFillColor(sf::Color(79,79,79,255));
	button_menu.setSize({ 0.045f*Renderer::gameWidth, 0.07f * Renderer::gameHeight });
	button_save.setOutlineColor(sf::Color::Black);
	button_save.setOutlineThickness(5.0f);
	button_save.setFillColor(sf::Color(79, 79, 79, 255));
	button_save.setSize({ 0.045f*Renderer::gameWidth, 0.07f * Renderer::gameHeight });
	button_inventory.setOutlineColor(sf::Color::Black);
	button_inventory.setOutlineThickness(5.0f);
	button_inventory.setFillColor(sf::Color(79, 79, 79, 255));
	button_inventory.setSize({ 0.045f*Renderer::gameWidth, 0.07f * Renderer::gameHeight });

	
}
void HudComponent::setPlayer(std::shared_ptr<Entity>& e) {
	_player = e;
}
void HudComponent::set(float h, float mh, float m, float mm)
{
	health = h;
	mana = m;
	maxHealth = mh;
	maxMana = mm;
	HP.setScale((float)(h/mh),1.0f);
	MP.setScale( (float)(m/mm) ,1.0f);
}
void HudComponent::resetButtons()
{
	highlighted = false;
	button_menu.setFillColor(sf::Color(79, 79, 79, 255));
	button_inventory.setFillColor(sf::Color(79, 79, 79, 255));
	button_save.setFillColor(sf::Color(79, 79, 79, 255));
}
void HudComponent::render() 
{
	Renderer::HUDqueue(&HP);
	Renderer::HUDqueue(&MP);
	Renderer::HUDqueue(&text);
	Renderer::HUDqueue(&buttonsBackground);	
	Renderer::HUDqueue(&skill1);
	Renderer::HUDqueue(&skill2);
	Renderer::HUDqueue(&skill3);
	Renderer::HUDqueue(&skill4);
	Renderer::HUDqueue(&skill5);

	Renderer::HUDqueue(&label_skill1);
	Renderer::HUDqueue(&label_skill2);
	Renderer::HUDqueue(&label_skill3);
	Renderer::HUDqueue(&label_skill4);
	Renderer::HUDqueue(&label_skill5);

	Renderer::HUDqueue(&button_inventory);
	Renderer::HUDqueue(&button_menu);
	Renderer::HUDqueue(&button_save);
}
void HudComponent::update(double dt)
{
	Vector2i mousePos = sf::Mouse::getPosition(Renderer::getWindow());

	if (mousePos.y >= 0.915f*WY && mousePos.y <= 0.985f*WY)
	{
		
		if (mousePos.x >= 0.57f*WX && mousePos.x <= 0.615f*WX)
		{
			button_menu.setFillColor(sf::Color::White);
			if(!highlighted)sound.play();
			highlighted = true;		
			if (sf::Mouse::isButtonPressed(Mouse::Left))
			{
				activeScene = menuScene; //switch to game
			}
		}
		else if (mousePos.x >= 0.63f*WX  && mousePos.x <= 0.675f*WX)
		{
			button_inventory.setFillColor(sf::Color::White);
			if (!highlighted)sound.play();
			highlighted = true;
			if (sf::Mouse::isButtonPressed(Mouse::Left))
			{
				/////////////////////////
			}
		}
		else if (mousePos.x >= 0.69f*WX && mousePos.x <= 0.735f*WX)
		{
			button_save.setFillColor(sf::Color::White);
			if (!highlighted)sound.play();
			highlighted = true;
			if (sf::Mouse::isButtonPressed(Mouse::Left))
			{
				///////////////
			}
		}
		else
		{
			resetButtons();
		}
		
	}
	else if (highlighted)
	{
		resetButtons();
	}
	auto health_mana = _player->GetComponent<HealthComponent>();
	set(health_mana->getHealth(), health_mana->getMaxHealth(), health_mana->getMana(), health_mana->getMaxMana());
	setText();
	setPosition();
}
void HudComponent::setMaxHealth(float healthChange) {
	maxHealth = healthChange;
}

void HudComponent::setHealth(float healthChange) {
	health = healthChange;
}

void HudComponent::setMaxMana(float manaChange) {
	maxMana = manaChange;
}

void HudComponent::setMana(float manaChange) {
	mana = manaChange;
}

void HudComponent::setText() {
	text.setString("HP " + std::to_string((int)health) +"/" + std::to_string((int)maxHealth) + "\n" + "MP " + std::to_string((int)mana) + "/" + std::to_string((int)maxMana));
}

void HudComponent::setPosition() 
{
	Vector2f windowZero = Vector2f(_player->getPosition().x - WX / 2, _player->getPosition().y - WY / 2);
	HP.setPosition(windowZero + Vector2f(0.052f*WX, 0.02f*WY));
	MP.setPosition(windowZero + Vector2f(0.052f*WX, 0.06f*WY));
	text.setPosition(windowZero + Vector2f(0.01f*WX, 0.025f*WY));
	buttonsBackground.setPosition(windowZero + Vector2f(0.25f*WX, 0.90f*WY));
	//////skillls
	skill1.setPosition(windowZero + Vector2f(0.26f*WX, 0.915f*WY));
	skill2.setPosition(windowZero + Vector2f(0.31f*WX, 0.915f*WY));
	skill3.setPosition(windowZero + Vector2f(0.36f*WX, 0.915f*WY));
	skill4.setPosition(windowZero + Vector2f(0.41f*WX, 0.915f*WY));
	skill5.setPosition(windowZero + Vector2f(0.46f*WX, 0.915f*WY));
	/////labels for skills
	label_skill1.setPosition(windowZero + Vector2f(0.265f*WX, 0.92f*WY));
	label_skill2.setPosition(windowZero + Vector2f(0.315f*WX, 0.92f*WY));
	label_skill3.setPosition(windowZero + Vector2f(0.365f*WX, 0.92f*WY));
	label_skill4.setPosition(windowZero + Vector2f(0.415f*WX, 0.92f*WY));
	label_skill5.setPosition(windowZero + Vector2f(0.465f*WX, 0.92f*WY));
	//////////////////buttons
	button_menu.setPosition(windowZero + Vector2f(0.57f*WX, 0.915f*WY));
	button_inventory.setPosition(windowZero + Vector2f(0.63f*WX, 0.915f*WY));
	button_save.setPosition(windowZero + Vector2f(0.69f*WX, 0.915f*WY));
}
