#pragma once
#include "cmp_hud.h"
#include "SystemRenderer.h"
#include <string>
#include <iostream>

using namespace sf;

HudComponent::HudComponent(Entity *p) : Component(p)
{
	health = 150;
	mana = 100;
	text.setCharacterSize(50);
	text.setColor(sf::Color::Green);
	maxHealth = 100;
	maxMana = 100;
	setFont();
	text.setString("Health : " + std::to_string(health) + "\n" + "Mana : " + std::to_string(mana));
}
void HudComponent::reset()
{
	health = maxHealth;
	mana = maxMana;
}
void HudComponent::render() {
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

void HudComponent::setMaxHealth(int healthChange) {
	maxHealth = healthChange;
}

void HudComponent::setHealth(int healthChange) {
	health = healthChange;
}

void HudComponent::setMaxMana(int manaChange) {
	maxMana = manaChange;
}

void HudComponent::setMana(int manaChange) {
	mana = manaChange;
}

void HudComponent::setText() {
	text.setString("Health : " + std::to_string(health) + "\n" + "Mana : " + std::to_string(mana));
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
	text.setPosition(pos);
}
