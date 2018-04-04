#pragma once
#include "ecm.h"
#include <string>

class HudComponent : public Component {

protected:
	sf::RectangleShape HP;
	sf::RectangleShape MP;
	float maxHealth;
	float health;
	float maxMana;
	float mana;
	sf::Text text;
public:
	void set(float health, float maxhealth, float mana, float maxmana);
	explicit HudComponent(Entity *p);
	HudComponent() = delete;
	int getHealth();
	int getMana();
	sf::Text getHud();
	void setMaxHealth(float maxHealth);
	void setHealth(float health);
	void setMaxMana(float maxMana);
	void setMana(float mana);
	void setText();
	void setPosition(sf::Vector2f pos);
	void reset();
	void render() override;
	void update(double dt) override;
};
