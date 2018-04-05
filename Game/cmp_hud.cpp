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

	///////////////////////////////INVENTORY/////////////////////////////
	inventory.setFillColor(sf::Color(255, 255, 255, 150));
	inventory.setSize({ 0.4f*WX, 0.825f*WY });

	////backpack
	backpack.setFillColor(sf::Color(120, 120, 120, 150));
	backpack.setSize({ 0.38f*WX, 0.26f*WY });
	backpack.setOutlineColor(sf::Color::Black);
	backpack.setOutlineThickness(3.0f);
	label_backpack.setFont(font);
	label_backpack.setColor(sf::Color::White);
	label_backpack.setOutlineColor(sf::Color::Black);
	label_backpack.setOutlineThickness(3.0f);
	label_backpack.setCharacterSize(25.0f);
	label_backpack.setString("Backpack");
	/////////BP slots///////////
	for(int i=0;i<BPslots;i++)
		{
			slots[i].setOutlineColor(sf::Color::Black);
			slots[i].setOutlineThickness(5.0f);
			slots[i].setFillColor(sf::Color(79, 79, 79, 255));
			slots[i].setSize({ 0.045f*WX, 0.07f * WY });
			
		}

	/////stats area
	statsArea.setFillColor(sf::Color(120, 120, 120, 150));
	statsArea.setSize({ 0.17f*WX, 0.47f*WY });
	statsArea.setOutlineColor(sf::Color::Black);
	statsArea.setOutlineThickness(3.0f);
	label_stats.setFont(font);
	label_stats.setColor(sf::Color::White);
	label_stats.setOutlineColor(sf::Color::Black);
	label_stats.setOutlineThickness(3.0f);
	label_stats.setCharacterSize(25.0f);
	label_stats.setString("Stats");

	///////////////equipped///////////
	equippedArea.setFillColor(sf::Color(120, 120, 120, 150));
	equippedArea.setSize({ 0.2f*WX, 0.42f*WY });
	equippedArea.setOutlineColor(sf::Color::Black);
	equippedArea.setOutlineThickness(3.0f);

	label_equipped.setFont(font);
	label_equipped.setColor(sf::Color::White);
	label_equipped.setOutlineColor(sf::Color::Black);
	label_equipped.setOutlineThickness(3.0f);
	label_equipped.setCharacterSize(25.0f);
	label_equipped.setString("Equipment");

	helmet.setOutlineColor(sf::Color::Black);
	helmet.setOutlineThickness(5.0f);
	helmet.setFillColor(sf::Color(79, 79, 79, 255));
	helmet.setSize({ 0.045f*WX, 0.07f * WY });

	armour.setOutlineColor(sf::Color::Black);
	armour.setOutlineThickness(5.0f);
	armour.setFillColor(sf::Color(79, 79, 79, 255));
	armour.setSize({ 0.045f*WX, 0.07f * WY });

	boots.setOutlineColor(sf::Color::Black);
	boots.setOutlineThickness(5.0f);
	boots.setFillColor(sf::Color(79, 79, 79, 255));
	boots.setSize({ 0.045f*WX, 0.07f * WY });

	weapon.setOutlineColor(sf::Color::Black);
	weapon.setOutlineThickness(5.0f);
	weapon.setFillColor(sf::Color(79, 79, 79, 255));
	weapon.setSize({ 0.045f*WX, 0.07f * WY });

	shield.setOutlineColor(sf::Color::Black);
	shield.setOutlineThickness(5.0f);
	shield.setFillColor(sf::Color(79, 79, 79, 255));
	shield.setSize({ 0.045f*WX, 0.07f * WY });
	
	///////////////////////////////////ICONS
	icon_weapon.setTexture(iconsTexture);
	icon_weapon.setTextureRect({0,0,50,50});

	icon_armour.setTexture(iconsTexture);
	icon_armour.setTextureRect({ 200,0,50,50 });

	icon_shield.setTexture(iconsTexture);
	icon_shield.setTextureRect({ 100,0,50,50 });

	icon_boots.setTexture(iconsTexture);
	icon_boots.setTextureRect({ 150,0,50,50 });

	icon_helmet.setTexture(iconsTexture);
	icon_helmet.setTextureRect({ 50,0,50,50 });

	icon_inventory.setTexture(iconsTexture);
	icon_inventory.setTextureRect({ 50,0,50,50 });


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
	Renderer::HUDqueue(&icon_inventory);
	if (showInventory || hideInventory)
	{
		Renderer::HUDqueue(&inventory);
		Renderer::HUDqueue(&backpack);
		Renderer::HUDqueue(&label_backpack);
		Renderer::HUDqueue(&statsArea);
		Renderer::HUDqueue(&equippedArea);
		Renderer::HUDqueue(&label_stats);
		Renderer::HUDqueue(&label_equipped);

		for (int i = 0; i<BPslots; i++)
		{
			Renderer::HUDqueue(&slots[i]);
		}
		Renderer::HUDqueue(&helmet);
		Renderer::HUDqueue(&armour);
		Renderer::HUDqueue(&boots);
		Renderer::HUDqueue(&weapon);
		Renderer::HUDqueue(&shield);

		Renderer::HUDqueue(&icon_weapon);
		Renderer::HUDqueue(&icon_armour);
		Renderer::HUDqueue(&icon_boots);
		Renderer::HUDqueue(&icon_helmet);
		Renderer::HUDqueue(&icon_shield);
	}
}
void HudComponent::update(double dt)
{
	if (showInventory && sliderX<= 0.39f*WX)
	{
		sliderX += 1.5f*WX * dt;
	}
	if (hideInventory && sliderX > 0.0f)
	{
		showInventory = false;
		sliderX -= 1.5f*WX * dt;
	}
	else if (hideInventory && sliderX <= 0.0f)
	{
		hideInventory = false;
	}
	if (buttonDelay<0 && Keyboard::isKeyPressed(Keyboard::I))
	{
		sound.play();
		buttonDelay = 0.2f;
		if (!showInventory)
			showInventory = true;
		else
			hideInventory = true;

	}
	if (Keyboard::isKeyPressed(Keyboard::Escape)) 
	{
		hideInventory = true;
	}
	
	Vector2i mousePos = sf::Mouse::getPosition(Renderer::getWindow());
	buttonDelay -= dt;
	if (mousePos.y >= 0.915f*WY && mousePos.y <= 0.985f*WY)
	{
		
		if (mousePos.x >= 0.57f*WX && mousePos.x <= 0.615f*WX)
		{
			button_menu.setFillColor(sf::Color::White);
			if(!highlighted)sound.play();
			highlighted = true;		
			if (sf::Mouse::isButtonPressed(Mouse::Left))
			{
				buttonDelay = 0.2f;
				activeScene = menuScene; //switch to game
			}
		}
		else if (mousePos.x >= 0.63f*WX  && mousePos.x <= 0.675f*WX)
		{
			button_inventory.setFillColor(sf::Color::White);
			if (!highlighted)sound.play();
			highlighted = true;
			if (buttonDelay<0 && sf::Mouse::isButtonPressed(Mouse::Left))
			{
				buttonDelay = 0.2f;
				if (!showInventory)
					showInventory = true;
				else
					hideInventory = true;
				
			}
		}
		else if (mousePos.x >= 0.69f*WX && mousePos.x <= 0.735f*WX)
		{
			button_save.setFillColor(sf::Color::White);
			if (!highlighted)sound.play();
			highlighted = true;
			if (buttonDelay<0 && sf::Mouse::isButtonPressed(Mouse::Left))
			{
				buttonDelay = 0.2f;
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
	icon_inventory.setPosition(button_inventory.getPosition());
	button_save.setPosition(windowZero + Vector2f(0.69f*WX, 0.915f*WY));
	////////////////////////////INVENTORY
	inventory.setPosition(windowZero + Vector2f(WX, 0.02f*WY) - Vector2f(sliderX,0));
	////backpack
	backpack.setPosition(inventory.getPosition() + Vector2f(0.007f*WX,0.55f*WY));
	label_backpack.setPosition(inventory.getPosition() + Vector2f(0.007f*WX, 0.50f*WY));
	int row =0;
	int column = 0;
	for (int i = 0; i<BPslots; i++)
	{
		if (column > (BPslots/3)-1)
		{
			row++;
			column =0;
		}
		slots[i].setPosition(backpack.getPosition() + Vector2f(0.0053f*WX, 0.008f*WY) + Vector2f(column * 0.054f*WX, row * 0.086f*WY));
		column++;
	}
	////stats
	statsArea.setPosition(inventory.getPosition() + Vector2f(0.215f*WX, 0.06f*WY));
	label_stats.setPosition(inventory.getPosition() + Vector2f(0.215f*WX, 0.01f*WY));

	///////////////equipped///////////
	equippedArea.setPosition(inventory.getPosition() + Vector2f(0.007f*WX, 0.06f*WY));
	label_equipped.setPosition(inventory.getPosition() + Vector2f(0.007f*WX, 0.01f*WY));

	helmet.setPosition(equippedArea.getPosition() + Vector2f(0.08f*WX, 0.01f*WY));
	armour.setPosition(equippedArea.getPosition() + Vector2f(0.08f*WX, 0.17f*WY));
	boots.setPosition(equippedArea.getPosition() + Vector2f(0.08f*WX, 0.3f*WY));
	weapon.setPosition(equippedArea.getPosition() + Vector2f(0.02f*WX, 0.17f*WY));
	shield.setPosition(equippedArea.getPosition() + Vector2f(0.14f*WX, 0.17f*WY));

	icon_weapon.setPosition(weapon.getPosition());
	icon_armour.setPosition(armour.getPosition());
	icon_shield.setPosition(shield.getPosition());
	icon_helmet.setPosition(helmet.getPosition());
	icon_boots.setPosition(boots.getPosition());
}
