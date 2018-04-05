#pragma once
#include "ecm.h"
#include <string>

class HudComponent : public Component {

protected:
	bool highlighted = false;
	std::shared_ptr<Entity> _player;
	sf::RectangleShape HP;
	sf::RectangleShape MP;
	////////////SKILL INTICATORS////////////////////////////////////
	sf::RectangleShape buttonsBackground;	
	sf::RectangleShape skill1;
	sf::RectangleShape skill2;
	sf::RectangleShape skill3;
	sf::RectangleShape skill4;
	sf::RectangleShape skill5;

	sf::Text label_skill1;
	sf::Text label_skill2;
	sf::Text label_skill3;
	sf::Text label_skill4;
	sf::Text label_skill5;

	/////////////////////////////////////////INGAME MENU BUTTONS
	sf::RectangleShape button_inventory;
	sf::RectangleShape button_menu;
	sf::RectangleShape button_save;

	float maxHealth;
	float health;
	float maxMana;
	float mana;
	sf::Text text;
public:
	void resetButtons();
	void set(float health, float maxhealth, float mana, float maxmana);
	explicit HudComponent(Entity *p);
	HudComponent() = delete;
	void setPlayer(std::shared_ptr<Entity>& e);
	void setMaxHealth(float maxHealth);
	void setHealth(float health);
	void setMaxMana(float maxMana);
	void setMana(float mana);
	void setText();
	void setPosition();
	void render() override;
	void update(double dt) override;
};
