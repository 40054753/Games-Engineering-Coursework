#pragma once
#include "ecm.h"
#include <string>

class HudComponent : public Component {

protected:
	int maxHealth;
	int health;
	int maxMana;
	int mana;
	sf::Text text;
	sf::Font font;
public:
	explicit HudComponent(Entity *p);
	HudComponent() = delete;
	int getHealth();
	int getMana();
	sf::Text getHud();
	void setMaxHealth(int maxHealth);
	void setHealth(int health);
	void setMaxMana(int maxMana);
	void setMana(int mana);
	void setText();
	void setFont();
	void setPosition(sf::Vector2f pos);
	void reset();
	void render() override;
	void update(double dt) override;
};
