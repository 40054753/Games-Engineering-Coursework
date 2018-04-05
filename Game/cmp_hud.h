#pragma once
#include "ecm.h"
#include <string>

#define BPslots 21
class HudComponent : public Component {

protected:
	bool highlighted = false;
	bool showInventory = false;
	bool hideInventory = false;
	float buttonDelay = 0.0f;
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
	//////////////////////////////////////////inventory window
	sf::RectangleShape inventory;
	sf::RectangleShape backpack;
	sf::RectangleShape slots[BPslots];
	sf::RectangleShape statsArea;
	sf::Text label_backpack;
	sf::Text label_stats;
	sf::Text label_equipped;
	sf::RectangleShape equippedArea;
	sf::RectangleShape helmet;
	sf::RectangleShape armour;
	sf::RectangleShape boots;
	sf::RectangleShape weapon;
	sf::RectangleShape shield;

	////////////////////////////ICONS
	sf::Sprite icon_weapon;
	sf::Sprite icon_armour;
	sf::Sprite icon_boots;
	sf::Sprite icon_helmet;
	sf::Sprite icon_shield;
	float sliderX=0;
	float slideTime = 0.2f;


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
