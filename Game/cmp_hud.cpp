#pragma once
#include "cmp_hud.h"
#include "SystemRenderer.h"
#include <string>
#include <iostream>

using namespace sf;

HudComponent::HudComponent(Entity *p) : Component(p)
{
	HP.setFillColor(sf::Color::Red);
	HP.setSize({ Renderer::gameWidth / 5.7f,Renderer::gameHeight / 25.0f });
	MP.setFillColor(sf::Color::Blue);
	MP.setSize({ Renderer::gameWidth / 5.7f,Renderer::gameHeight / 25.0f });
	text.setCharacterSize(30);
	text.setColor(sf::Color::White);
	setFont();
	
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
void HudComponent::reset()
{
	health = maxHealth;
	mana = maxMana;
}
void HudComponent::render() 
{
	Renderer::queue(&HP);
	Renderer::queue(&MP);
	Renderer::queue(&text);
}
void HudComponent::update(double dt)
{
}
int HudComponent::getHealth() {
	return health;
}

int HudComponent::getMana() {
	return mana;
}

sf::Text HudComponent::getHud() {
	return text;
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
	text.setString("HP: " + std::to_string((int)health) +"/" + std::to_string((int)maxHealth) + "\n" + "MP: " + std::to_string((int)mana) + "/" + std::to_string((int)maxMana));
}

void HudComponent::setFont()
{
	if (!font.loadFromFile("res/fonts/leadcoat.ttf")) {
	}
	else {
		text.setFont(font);
	}
}

void HudComponent::setPosition(Vector2f pos) {
	HP.setPosition(pos + Vector2f(50.0f, 12.0f));
	MP.setPosition(pos+ Vector2f(50.0f, 42.0f));
	text.setPosition(pos + Vector2f(10.0f,10.0f));
}
