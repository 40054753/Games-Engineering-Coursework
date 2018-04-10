#pragma once
#include "cmp_hud.h"
#include "SystemRenderer.h"
#include <string>
#include <iostream>
#include "Game.h"
#include "cmp_char_sheet.h"
#include "cmp_items.h"
#include "cmp_health.h"
#include "EventSystem.h"

using namespace sf;
Vector2f windowZero;
std::shared_ptr<Entity> selectedItem;
int selectedIndex;
EventSystem* evs = EventSystem::getInstance();

sf::Sprite equipped_weapon;
sf::Sprite equipped_armour;
sf::Sprite equipped_boots;
sf::Sprite equipped_helmet;
sf::Sprite equipped_shield;

HudComponent::HudComponent(Entity *p) : Component(p)
{
	
	equipped_weapon.setScale(WX / 1280, WY / 720);
	equipped_armour.setScale(WX / 1280, WY / 720);
	equipped_boots.setScale(WX / 1280, WY / 720);
	equipped_helmet.setScale(WX / 1280, WY / 720);
	equipped_shield.setScale(WX / 1280, WY / 720);

	HP.setFillColor(sf::Color::Red);
	HP.setSize({ WX / 5.7f,WY / 25.0f });
	MP.setFillColor(sf::Color::Blue);
	MP.setSize({ WX / 5.7f,WY / 25.0f });
	STAM.setFillColor(sf::Color(244, 139, 34, 255));
	STAM.setSize({ WX / 5.7f,WY / 25.0f });

	text.setCharacterSize(22);
	text.setScale(WX / 1280, WY / 720);
	text.setColor(sf::Color::White);
	text.setFont(font);
	/////////////////////////////////    BOTTOM HUD BG ////////////////////////////////////////////
	buttonsBackground.setFillColor(sf::Color(255,255,255,150));
	buttonsBackground.setSize({ 0.5f*WX, 0.1f * WY});
	/////////////////////////////////   SKILLL BUTTONS ////////////////////////////////////////////
	skill1.setFillColor(sf::Color::Black);
	skill1.setSize({ 0.045f*WX, 0.07f * WY });
	skill2.setFillColor(sf::Color::Black);
	skill2.setSize({ 0.045f*WX, 0.07f * WY });
	skill3.setFillColor(sf::Color::Black);
	skill3.setSize({ 0.045f*WX, 0.07f * WY });
	skill4.setFillColor(sf::Color::Black);
	skill4.setSize({ 0.045f*WX, 0.07f * WY });
	skill5.setFillColor(sf::Color::Black);
	skill5.setSize({ 0.045f*WX, 0.07f * WY });

	label_skill1.setFont(font);
	label_skill1.setColor(sf::Color::Red);
	label_skill1.setCharacterSize(15.0f);
	label_skill1.setScale(WX / 1280, WY / 720);
	label_skill1.setString(codes[controls[5]]);
	label_skill2.setFont(font);
	label_skill2.setColor(sf::Color::Red);
	label_skill2.setCharacterSize(15.0f);
	label_skill2.setScale(WX / 1280, WY / 720);
	label_skill2.setString(codes[controls[6]]);
	label_skill3.setFont(font);
	label_skill3.setColor(sf::Color::Red);
	label_skill3.setCharacterSize(15.0f);
	label_skill3.setScale(WX / 1280, WY / 720);
	label_skill3.setString(codes[controls[6]]);
	label_skill4.setFont(font);
	label_skill4.setColor(sf::Color::Red);
	label_skill4.setCharacterSize(15.0f);
	label_skill4.setScale(WX / 1280, WY / 720);
	label_skill4.setString(codes[controls[7]]);
	label_skill5.setFont(font);
	label_skill5.setColor(sf::Color::Red);
	label_skill5.setCharacterSize(15.0f);
	label_skill5.setScale(WX / 1280, WY / 720);
	label_skill5.setString(codes[controls[8]]);

	////////////////////////BUTTONS
	button_menu.setOutlineColor(sf::Color::Black);
	button_menu.setOutlineThickness(5.0f);
	button_menu.setFillColor(sf::Color(79,79,79,255));
	button_menu.setSize({ 0.045f*WX, 0.07f * WY });
	button_save.setOutlineColor(sf::Color::Black);
	button_save.setOutlineThickness(5.0f);
	button_save.setFillColor(sf::Color(79, 79, 79, 255));
	button_save.setSize({ 0.045f*WX, 0.07f * WY });
	button_inventory.setOutlineColor(sf::Color::Black);
	button_inventory.setOutlineThickness(5.0f);
	button_inventory.setFillColor(sf::Color(79, 79, 79, 255));
	button_inventory.setSize({ 0.045f*WX, 0.07f * WY });

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
	label_backpack.setScale(WX / 1280, WY / 720);
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
	statsArea.setSize({ 0.205f*WX, 0.475f*WY });
	statsArea.setOutlineColor(sf::Color::Black);
	statsArea.setOutlineThickness(3.0f);
	label_stats.setFont(font);
	label_stats.setColor(sf::Color::White);
	label_stats.setOutlineColor(sf::Color::Black);
	label_stats.setOutlineThickness(3.0f);
	label_stats.setCharacterSize(25.0f);
	label_stats.setScale(WX / 1280, WY / 720);
	label_stats.setString("Stats");

	///////////////equipped///////////
	equippedArea.setFillColor(sf::Color(120, 120, 120, 150));
	equippedArea.setSize({ 0.165f*WX, 0.42f*WY });
	equippedArea.setOutlineColor(sf::Color::Black);
	equippedArea.setOutlineThickness(3.0f);

	label_equipped.setFont(font);
	label_equipped.setColor(sf::Color::White);
	label_equipped.setOutlineColor(sf::Color::Black);
	label_equipped.setOutlineThickness(3.0f);
	label_equipped.setCharacterSize(25.0f);
	label_equipped.setScale(WX / 1280, WY / 720);
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
	icon_weapon.setScale(WX / 1280, WY / 720);

	icon_armour.setTexture(iconsTexture);
	icon_armour.setTextureRect({ 200,0,50,50 });
	icon_armour.setScale(WX / 1280, WY / 720);

	icon_shield.setTexture(iconsTexture);
	icon_shield.setTextureRect({ 100,0,50,50 });
	icon_shield.setScale(WX / 1280, WY / 720);

	icon_boots.setTexture(iconsTexture);
	icon_boots.setTextureRect({ 150,0,50,50 });
	icon_boots.setScale(WX / 1280, WY / 720);

	icon_helmet.setTexture(iconsTexture);
	icon_helmet.setTextureRect({ 50,0,50,50 });
	icon_helmet.setScale(WX / 1280, WY / 720);

	icon_inventory.setTexture(iconsTexture);
	icon_inventory.setTextureRect({ 50,0,50,50 });
	icon_inventory.setScale(WX / 1280, WY / 720);

	icon_save.setTexture(iconsTexture);
	icon_save.setTextureRect({ 250,0,50,50 });
	icon_save.setScale(WX / 1280, WY / 720);

	icon_menu.setTexture(iconsTexture);
	icon_menu.setTextureRect({ 300,0,50,50 });
	icon_menu.setScale(WX / 1280, WY / 720);



	///////////////////////ITEM INTERACTION
	itemInfo.setFont(font);
	itemInfo.setColor(sf::Color::White);
	itemInfo.setOutlineColor(sf::Color::Black);
	itemInfo.setOutlineThickness(2.0f);
	itemInfo.setCharacterSize(16.0f);
	itemInfo.setScale(WX / 1280, WY / 720);
	infoArea.setFillColor(sf::Color(255, 255, 255, 150));
	infoArea.setSize({ 0.17f*WX, 0.15f*WY });

	itemOptionsEquip.setFont(font);
	itemOptionsEquip.setColor(sf::Color::White);
	itemOptionsEquip.setOutlineColor(sf::Color::Black);
	itemOptionsEquip.setOutlineThickness(3.0f);
	itemOptionsEquip.setCharacterSize(25.0f);
	itemOptionsEquip.setScale(WX / 1280, WY / 720);
	itemOptionsEquip.setString("Equip");
	itemOptionsDrop.setFont(font);
	itemOptionsDrop.setColor(sf::Color::White);
	itemOptionsDrop.setOutlineColor(sf::Color::Black);
	itemOptionsDrop.setOutlineThickness(3.0f);
	itemOptionsDrop.setCharacterSize(25.0f);
	itemOptionsDrop.setScale(WX / 1280, WY / 720);
	itemOptionsDrop.setString("Drop");
	itemOptionsArea.setFillColor(sf::Color(170, 170, 170, 255));
	itemOptionsArea.setSize({ 0.1f*WX, 0.11f*WY });

	//////////////////STATS AREA
	experience_levels.setFont(font);
	experience_levels.setColor(sf::Color::White);
	experience_levels.setCharacterSize(13.0f);
	experience_levels.setScale(WX / 1280, WY / 720);
	//////progress bars
	progressBar_Melee.setFillColor(sf::Color::Cyan);
	progressBar_Melee.setSize({ WX / 5.2f,WY / 30.0f });
	progressBar_Melee_BG.setFillColor(sf::Color::Black);
	progressBar_Melee_BG.setOutlineColor(sf::Color::Black);
	progressBar_Melee_BG.setOutlineThickness(3.0f);
	progressBar_Melee_BG.setSize({ WX / 5.2f,WY / 30.0f });

	progressBar_Fire.setFillColor(sf::Color::Cyan);
	progressBar_Fire.setSize({ WX / 5.2f,WY / 30.0f });
	progressBar_Fire_BG.setFillColor(sf::Color::Black);
	progressBar_Fire_BG.setOutlineColor(sf::Color::Black);
	progressBar_Fire_BG.setOutlineThickness(3.0f);
	progressBar_Fire_BG.setSize({ WX / 5.2f,WY / 30.0f });

	progressBar_Water.setFillColor(sf::Color::Cyan);
	progressBar_Water.setSize({ WX / 5.2f,WY / 30.0f });
	progressBar_Water_BG.setFillColor(sf::Color::Black);
	progressBar_Water_BG.setOutlineColor(sf::Color::Black);
	progressBar_Water_BG.setOutlineThickness(3.0f);
	progressBar_Water_BG.setSize({ WX / 5.2f,WY / 30.0f });

	progressBar_Wind.setFillColor(sf::Color::Cyan);
	progressBar_Wind.setSize({ WX / 5.2f,WY / 30.0f });
	progressBar_Wind_BG.setFillColor(sf::Color::Black);
	progressBar_Wind_BG.setOutlineColor(sf::Color::Black);
	progressBar_Wind_BG.setOutlineThickness(3.0f);
	progressBar_Wind_BG.setSize({ WX / 5.2f,WY / 30.0f });

	progressBar_Earth.setFillColor(sf::Color::Cyan);
	progressBar_Earth.setSize({ WX / 5.2f,WY / 30.0f });
	progressBar_Earth_BG.setFillColor(sf::Color::Black);
	progressBar_Earth_BG.setOutlineColor(sf::Color::Black);
	progressBar_Earth_BG.setOutlineThickness(3.0f);
	progressBar_Earth_BG.setSize({ WX / 5.2f,WY / 30.0f });
	//////////////////////////////////////////////////////SKILL TREEE/////////////////////////
	skill_tree.setFillColor(sf::Color(255, 255, 255, 150));
	skill_tree.setSize({ 0.62f*WX, 0.825f*WY });

	label_skill_tree.setFont(font);
	label_skill_tree.setColor(sf::Color::White);
	label_skill_tree.setOutlineColor(sf::Color::Black);
	label_skill_tree.setOutlineThickness(3.0f);
	label_skill_tree.setCharacterSize(25.0f);
	label_skill_tree.setScale(WX / 1280, WY / 720);
	label_skill_tree.setString("Skill tree");

	fire_tree.setFillColor(sf::Color(120, 120, 120, 150));
	fire_tree.setSize({ 0.27f*WX, 0.35f*WY });
	fire_tree.setOutlineColor(sf::Color::Black);
	fire_tree.setOutlineThickness(3.0f);

	water_tree.setFillColor(sf::Color(120, 120, 120, 150));
	water_tree.setSize({ 0.27f*WX, 0.35f*WY });
	water_tree.setOutlineColor(sf::Color::Black);
	water_tree.setOutlineThickness(3.0f);

	wind_tree.setFillColor(sf::Color(120, 120, 120, 150));
	wind_tree.setSize({ 0.27f*WX, 0.35f*WY });
	wind_tree.setOutlineColor(sf::Color::Black);
	wind_tree.setOutlineThickness(3.0f);

	earth_tree.setFillColor(sf::Color(120, 120, 120, 150));
	earth_tree.setSize({ 0.27f*WX, 0.35f*WY });
	earth_tree.setOutlineColor(sf::Color::Black);
	earth_tree.setOutlineThickness(3.0f);

	label_fire.setFont(font);
	label_fire.setColor(sf::Color::White);
	label_fire.setOutlineColor(sf::Color::Black);
	label_fire.setOutlineThickness(3.0f);
	label_fire.setCharacterSize(20.0f);
	label_fire.setScale(WX / 1280, WY / 720);
	label_fire.setString("Fire");

	label_water.setFont(font);
	label_water.setColor(sf::Color::White);
	label_water.setOutlineColor(sf::Color::Black);
	label_water.setOutlineThickness(3.0f);
	label_water.setCharacterSize(20.0f);
	label_water.setScale(WX / 1280, WY / 720);
	label_water.setString("Water");

	label_wind.setFont(font);
	label_wind.setColor(sf::Color::White);
	label_wind.setOutlineColor(sf::Color::Black);
	label_wind.setOutlineThickness(3.0f);
	label_wind.setCharacterSize(20.0f);
	label_wind.setScale(WX / 1280, WY / 720);
	label_wind.setString("Wind");

	label_earth.setFont(font);
	label_earth.setColor(sf::Color::White);
	label_earth.setOutlineColor(sf::Color::Black);
	label_earth.setOutlineThickness(3.0f);
	label_earth.setCharacterSize(20.0f);
	label_earth.setScale(WX / 1280, WY / 720);
	label_earth.setString("Earth");

	spell_fire_1.setTexture(spell_icons);
	spell_fire_1.setTextureRect({0,0,55,55});
	spell_fire_1.setScale(WX / 1280, WY / 720);

	spell_fire_2.setTexture(spell_icons);
	spell_fire_2.setTextureRect({ 0,56,55,55 });
	spell_fire_2.setScale(WX / 1280, WY / 720);
	spell_fire_2.setColor(sf::Color(50, 50, 50, 255));
	spell_fire_3.setTexture(spell_icons);
	spell_fire_3.setTextureRect({ 0,112,55,55 });
	spell_fire_3.setScale(WX / 1280, WY / 720);
	spell_fire_3.setColor(sf::Color(50, 50, 50, 255));
	spell_fire_4.setTexture(spell_icons);
	spell_fire_4.setTextureRect({ 0,168,55,55 });
	spell_fire_4.setScale(WX / 1280, WY / 720);
	spell_fire_4.setColor(sf::Color(50, 50, 50, 255));
	spell_fire_5.setTexture(spell_icons);
	spell_fire_5.setTextureRect({ 0,224,55,55 });
	spell_fire_5.setScale(WX / 1280, WY / 720);
	spell_fire_5.setColor(sf::Color(50, 50, 50, 255));
	spell_water_1.setTexture(spell_icons);
	spell_water_1.setTextureRect({ 56,0,55,55 });
	spell_water_1.setScale(WX / 1280, WY / 720);
	
	spell_water_2.setTexture(spell_icons);
	spell_water_2.setTextureRect({ 56,56,55,55 });
	spell_water_2.setScale(WX / 1280, WY / 720);
	spell_water_2.setColor(sf::Color(50, 50, 50, 255));
	spell_water_3.setTexture(spell_icons);
	spell_water_3.setTextureRect({ 56,112,55,55 });
	spell_water_3.setScale(WX / 1280, WY / 720);
	spell_water_3.setColor(sf::Color(50, 50, 50, 255));
	spell_water_4.setTexture(spell_icons);
	spell_water_4.setTextureRect({ 56,168,55,55 });
	spell_water_4.setScale(WX / 1280, WY / 720);
	spell_water_4.setColor(sf::Color(50, 50, 50, 255));
	spell_water_5.setTexture(spell_icons);
	spell_water_5.setTextureRect({ 56,224,55,55 });
	spell_water_5.setScale(WX / 1280, WY / 720);
	spell_water_5.setColor(sf::Color(50, 50, 50, 255));
	spell_wind_1.setTexture(spell_icons);
	spell_wind_1.setTextureRect({ 168,0,55,55 });
	spell_wind_1.setScale(WX / 1280, WY / 720);

	spell_wind_2.setTexture(spell_icons);
	spell_wind_2.setTextureRect({ 168,56,55,55 });
	spell_wind_2.setScale(WX / 1280, WY / 720);
	spell_wind_2.setColor(sf::Color(50, 50, 50, 255));
	spell_wind_3.setTexture(spell_icons);
	spell_wind_3.setTextureRect({ 168,112,55,55 });
	spell_wind_3.setScale(WX / 1280, WY / 720);
	spell_wind_3.setColor(sf::Color(50, 50, 50, 255));
	spell_wind_4.setTexture(spell_icons);
	spell_wind_4.setTextureRect({ 168,168,55,55 });
	spell_wind_4.setScale(WX / 1280, WY / 720);
	spell_wind_4.setColor(sf::Color(50, 50, 50, 255));
	spell_wind_5.setTexture(spell_icons);
	spell_wind_5.setTextureRect({ 168,224,55,55 });
	spell_wind_5.setScale(WX / 1280, WY / 720);
	spell_wind_5.setColor(sf::Color(50, 50, 50, 255));
	spell_earth_1.setTexture(spell_icons);
	spell_earth_1.setTextureRect({ 112,0,55,55 });
	spell_earth_1.setScale(WX / 1280, WY / 720);

	spell_earth_2.setTexture(spell_icons);
	spell_earth_2.setTextureRect({ 112,56,55,55 });
	spell_earth_2.setScale(WX / 1280, WY / 720);
	spell_earth_2.setColor(sf::Color(50, 50, 50, 255));
	spell_earth_3.setTexture(spell_icons);
	spell_earth_3.setTextureRect({ 112,112,55,55 });
	spell_earth_3.setScale(WX / 1280, WY / 720);
	spell_earth_3.setColor(sf::Color(50, 50, 50, 255));
	spell_earth_4.setTexture(spell_icons);
	spell_earth_4.setTextureRect({ 112,168,55,55 });
	spell_earth_4.setScale(WX / 1280, WY / 720);
	spell_earth_4.setColor(sf::Color(50, 50, 50, 255));
	spell_earth_5.setTexture(spell_icons);
	spell_earth_5.setTextureRect({ 112,224,55,55 });
	spell_earth_5.setScale(WX / 1280, WY / 720);
	spell_earth_5.setColor(sf::Color(50, 50, 50, 255));

}

void HudComponent::getStats()
{
	auto x = player->GetComponent<CharacterSheetComponent>();

	experience_levels.setString("Meele LV: " + std::to_string((int)x->getLevelMelee())
							+ "\n\n\nFire LV: " + std::to_string((int)x->getLevelFire())
							+ "\n\n\nWater LV: " + std::to_string((int)x->getLevelWater())
							+ "\n\n\nWind LV: " + std::to_string((int)x->getLevelWind())
							+ "\n\n\nEarth LV: " + std::to_string((int)x->getLevelEarth())
							+ "\n\n\nAttack: " + std::to_string((int)x->getStatAttack())
							+ "\nDefence: " + std::to_string((int)x->getStatDefence())
							+ "\nSpeed: " + std::to_string((int)x->getStatSpeed()));
	progressBar_Melee.setScale((x->getExpMeele()/x->getRequiredExp(x->getLevelMelee())), 1.0f);
	progressBar_Fire.setScale((x->getExpFire() / x->getRequiredExp(x->getLevelFire())), 1.0f);
	progressBar_Water.setScale((x->getExpWater() / x->getRequiredExp(x->getLevelWater())), 1.0f);
	progressBar_Wind.setScale((x->getExpWind() / x->getRequiredExp(x->getLevelWind())), 1.0f);
	progressBar_Earth.setScale((x->getExpEarth() / x->getRequiredExp(x->getLevelEarth())), 1.0f);

}

void HudComponent::set(float h, float mh, float m, float mm, float s, float ms)
{
	health = h;
	mana = m;
	maxHealth = mh;
	maxMana = mm;
	stamina = s;
	maxStamina = ms;
	HP.setScale((float)(h/mh),1.0f);
	MP.setScale( (float)(m/mm) ,1.0f);
	STAM.setScale((float)(s / ms), 1.0f);
}
void HudComponent::resetButtons()
{
	highlighted = false;
	button_menu.setFillColor(sf::Color(79, 79, 79, 255));
	button_inventory.setFillColor(sf::Color(79, 79, 79, 255));
	button_save.setFillColor(sf::Color(79, 79, 79, 255));
}
void HudComponent::resetSlot(int i)
{
		slots[i].setFillColor(sf::Color(79, 79, 79, 255));
}
void HudComponent::render() 
{
	if (!show_skill_tree)
	{
		Renderer::queue(0, &HP);
		Renderer::queue(0, &MP);
		Renderer::queue(0, &STAM);
		Renderer::queue(0, &text);
	}
	Renderer::queue(0,&buttonsBackground);	
	Renderer::queue(0,&skill1);
	Renderer::queue(0,&skill2);
	Renderer::queue(0,&skill3);
	Renderer::queue(0,&skill4);
	Renderer::queue(0,&skill5);

	Renderer::queue(0,&label_skill1);
	Renderer::queue(0,&label_skill2);
	Renderer::queue(0,&label_skill3);
	Renderer::queue(0,&label_skill4);
	Renderer::queue(0,&label_skill5);

	Renderer::queue(0,&button_inventory);
	Renderer::queue(0,&button_menu);
	Renderer::queue(0,&button_save);
	Renderer::queue(0,&icon_inventory);
	Renderer::queue(0, &icon_save);
	Renderer::queue(0, &icon_menu);
	if (show_skill_tree || hide_skill_tree)
	{
		Renderer::queue(0, &skill_tree);
		Renderer::queue(0, &label_skill_tree);
		Renderer::queue(0, &fire_tree);
		Renderer::queue(0, &water_tree);
		Renderer::queue(0, &wind_tree);
		Renderer::queue(0, &earth_tree);

		Renderer::queue(0, &label_fire);
		Renderer::queue(0, &label_water);
		Renderer::queue(0, &label_wind);
		Renderer::queue(0, &label_earth);

		Renderer::queue(0, &spell_fire_1);
		Renderer::queue(0, &spell_fire_2);
		Renderer::queue(0, &spell_fire_3);
		Renderer::queue(0, &spell_fire_4);
		Renderer::queue(0, &spell_fire_5);

		Renderer::queue(0, &spell_water_1);
		Renderer::queue(0, &spell_water_2);
		Renderer::queue(0, &spell_water_3);
		Renderer::queue(0, &spell_water_4);
		Renderer::queue(0, &spell_water_5);

		Renderer::queue(0, &spell_wind_1);
		Renderer::queue(0, &spell_wind_2);
		Renderer::queue(0, &spell_wind_3);
		Renderer::queue(0, &spell_wind_4);
		Renderer::queue(0, &spell_wind_5);

		Renderer::queue(0, &spell_earth_1);
		Renderer::queue(0, &spell_earth_2);
		Renderer::queue(0, &spell_earth_3);
		Renderer::queue(0, &spell_earth_4);
		Renderer::queue(0, &spell_earth_5);
	}
	if (showInventory || hideInventory)
	{
		Renderer::queue(0,&inventory);
		Renderer::queue(0,&backpack);
		Renderer::queue(0,&label_backpack);
		Renderer::queue(0,&statsArea);
		Renderer::queue(0, &progressBar_Melee_BG);
		Renderer::queue(0, &progressBar_Melee);
		Renderer::queue(0, &progressBar_Fire_BG);
		Renderer::queue(0, &progressBar_Fire);
		Renderer::queue(0, &progressBar_Water_BG);
		Renderer::queue(0, &progressBar_Water);
		Renderer::queue(0, &progressBar_Wind_BG);
		Renderer::queue(0, &progressBar_Wind);
		Renderer::queue(0, &progressBar_Earth_BG);
		Renderer::queue(0, &progressBar_Earth);
		Renderer::queue(0, &experience_levels);
		Renderer::queue(0,&equippedArea);
		Renderer::queue(0,&label_stats);
		Renderer::queue(0,&label_equipped);

		for (int i = 0; i<BPslots; i++)
		{
			Renderer::queue(0,&slots[i]);
		}
		Renderer::queue(0,&helmet);
		Renderer::queue(0,&armour);
		Renderer::queue(0,&boots);
		Renderer::queue(0,&weapon);
		Renderer::queue(0,&shield);

		auto x = player->GetComponent<CharacterSheetComponent>();
		if (x->getHelmet()!=nullptr)
		{
			if(!x->getHelmet()->is_forDeletion())
				Renderer::queue(0, &equipped_helmet);
			else
				Renderer::queue(0, &icon_helmet);
		}
		else
		{
			Renderer::queue(0, &icon_helmet);
		}
		if (x->getArmour() != nullptr)
		{
			if (!x->getArmour()->is_forDeletion())
				Renderer::queue(0, &equipped_armour);
			else
				Renderer::queue(0, &icon_armour);
		}
		else
		{
			Renderer::queue(0, &icon_armour);
		}
		if (x->getBoots() != nullptr)
		{
			if (!x->getBoots()->is_forDeletion())
				Renderer::queue(0, &equipped_boots);
			else 
				Renderer::queue(0, &icon_boots);
		}
		else
		{
			Renderer::queue(0, &icon_boots);
		}
		if (x->getWeapon() != nullptr)
		{
			if (!x->getWeapon()->is_forDeletion())
				Renderer::queue(0, &equipped_weapon);
			else
				Renderer::queue(0, &icon_weapon);
		}
		else
		{
			Renderer::queue(0, &icon_weapon);
		}
		if (x->getShield() != nullptr)
		{
			if (!x->getShield()->is_forDeletion())
				Renderer::queue(0, &equipped_shield);
			else
				Renderer::queue(0, &icon_shield);
		}
		else
		{
			Renderer::queue(0, &icon_shield);
		}
			
	

		if (displayInfo)
		{
			Renderer::queue(-1, &infoArea);
			Renderer::queue(-1, &itemInfo);
		}
		if (displayItemOptions)
		{
			Renderer::queue(-1, &itemOptionsArea);
			Renderer::queue(-1, &itemOptionsEquip);		
			Renderer::queue(-1, &itemOptionsDrop);
		}
		
		
	}

}

void HudComponent::reload()
{
	auto x = player->GetComponent<CharacterSheetComponent>();

	if (x->getHelmet() != nullptr)
	{
		auto sprite = x->getHelmet()->GetComponent<ItemComponent>();
		equipped_helmet = sprite->getSprite();
	}
	if (x->getArmour() != nullptr)
	{
		auto sprite = x->getArmour()->GetComponent<ItemComponent>();
		equipped_armour = sprite->getSprite();
	}
	if (x->getBoots() != nullptr)
	{
		auto sprite = x->getBoots()->GetComponent<ItemComponent>();
		equipped_boots = sprite->getSprite();
	}
	if (x->getWeapon() != nullptr)
	{
		auto sprite = x->getWeapon()->GetComponent<ItemComponent>();
		equipped_weapon = sprite->getSprite();
	}
	if (x->getShield() != nullptr)
	{
		auto sprite = x->getShield()->GetComponent<ItemComponent>();
		equipped_shield = sprite->getSprite();
	}
	
	
				
	
}
void HudComponent::update(double dt)
{
	auto x = player->GetComponent<CharacterSheetComponent>();
	if (evs->is_leveled_up())
	{
		int fire_lv = x->getLevelFire();
		int water_lv = x->getLevelFire();
		int wind_lv = x->getLevelFire();
		int earth_lv = x->getLevelFire();
		if(fire_lv>=3)
			spell_fire_2.setColor(sf::Color(255, 255, 255, 255));
		if (fire_lv >= 5)
			spell_fire_3.setColor(sf::Color(255, 255, 255, 255));
		if (fire_lv >= 7)
			spell_fire_4.setColor(sf::Color(255, 255, 255, 255));
		if (fire_lv >= 9)
			spell_fire_5.setColor(sf::Color(255, 255, 255, 255));

		if (water_lv >= 3)
			spell_water_2.setColor(sf::Color(255, 255, 255, 255));
		if (water_lv >= 5)
			spell_water_3.setColor(sf::Color(255, 255, 255, 255));
		if (water_lv >= 7)
			spell_water_4.setColor(sf::Color(255, 255, 255, 255));
		if (water_lv >= 9)
			spell_water_5.setColor(sf::Color(255, 255, 255, 255));

		if (wind_lv >= 3)
			spell_wind_2.setColor(sf::Color(255, 255, 255, 255));
		if (wind_lv >= 5)
			spell_wind_3.setColor(sf::Color(255, 255, 255, 255));
		if (wind_lv >= 7)
			spell_wind_4.setColor(sf::Color(255, 255, 255, 255));
		if (wind_lv >= 9)
			spell_wind_5.setColor(sf::Color(255, 255, 255, 255));

		if (earth_lv >= 3)
			spell_earth_2.setColor(sf::Color(255, 255, 255, 255));
		if (earth_lv >= 5)
			spell_earth_3.setColor(sf::Color(255, 255, 255, 255));
		if (earth_lv >= 7)
			spell_earth_4.setColor(sf::Color(255, 255, 255, 255));
		if (earth_lv >= 9)
			spell_earth_5.setColor(sf::Color(255, 255, 255, 255));

		evs->switch_level_up();
	}
	if (evs->is_for_refresh())
	{
		label_skill1.setString(codes[controls[5]]);
		label_skill2.setString(codes[controls[6]]);
		label_skill3.setString(codes[controls[7]]);
		label_skill4.setString(codes[controls[8]]);
		label_skill5.setString(codes[controls[9]]);
		evs->refreshed();
	}
	
	auto backpack = x->getBP();
	auto info = x->getBPINFO();
	getStats();
	if (displayItemOptions)
	{
		if (mousePos.x >= itemOptionsEquip.getPosition().x - windowZero.x  && mousePos.x <= itemOptionsEquip.getPosition().x + 0.08f*WX- windowZero.x)
		{
			if (mousePos.y >= itemOptionsEquip.getPosition().y - windowZero.y  && mousePos.y <= itemOptionsEquip.getPosition().y + 0.045f*WY - windowZero.y)
			{
				if (buttonDelay < 0 && sf::Mouse::isButtonPressed(Mouse::Left))
				{
					buttonDelay = 0.1f;
					auto x = player->GetComponent<CharacterSheetComponent>();
					x->equip(selectedItem);
					auto it = selectedItem->GetComponent<ItemComponent>();
					ITEM_TYPE type = it->getType();
					switch (type)
					{
					case HELMET:
						equipped_helmet = it->getSprite();
						break;
					case ARMOUR:
						equipped_armour = it->getSprite();
						break;
					case BOOTS:
						equipped_boots = it->getSprite();
						break;
					case WEAPON:
						equipped_weapon = it->getSprite();
						break;
					case SHIELD:
						equipped_shield = it->getSprite();
						break;
					default:
						break;
					}
					displayItemOptions = false;
					
				}
				itemOptionsEquip.setOutlineColor(Color::Green);
				itemOptionsDrop.setOutlineColor(Color::Black);
			}
			else if (mousePos.y >= itemOptionsDrop.getPosition().y - windowZero.y  && mousePos.y <= itemOptionsDrop.getPosition().y + 0.045f*WY - windowZero.y)
			{
				itemOptionsDrop.setOutlineColor(Color::Green);
				itemOptionsEquip.setOutlineColor(Color::Black);
				if (buttonDelay < 0 && sf::Mouse::isButtonPressed(Mouse::Left))
				{					
					buttonDelay = 0.1f;
					selectedItem->setForDelete();
					player->GetComponent<CharacterSheetComponent>()->dropOne();
					displayItemOptions = false;
				}
			}
			else
			{
				itemOptionsDrop.setOutlineColor(Color::Black);
				itemOptionsEquip.setOutlineColor(Color::Black);
			}
		}
		else
		{
			itemOptionsEquip.setOutlineColor(Color::Black);
			if (buttonDelay<0 && (sf::Mouse::isButtonPressed(Mouse::Left) || sf::Keyboard::isKeyPressed(controls[0]) || sf::Keyboard::isKeyPressed(controls[1]) || sf::Keyboard::isKeyPressed(controls[2]) || sf::Keyboard::isKeyPressed(controls[3])))
			{
				buttonDelay = 0.1f;
				displayItemOptions = false;
			}
		}
	}
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



	if ( show_skill_tree && tree_sliderX <= 0.75f*WX)
	{
		tree_sliderX += 2.5f*WX * dt;
	}
	if (hide_skill_tree && tree_sliderX > 0.0f)
	{
		show_skill_tree = false;
		tree_sliderX -= 2.5f*WX * dt;
	}
	else if (hide_skill_tree && tree_sliderX <= 0.0f)
	{
		hide_skill_tree = false;
	}

	if (buttonDelay<0 && Keyboard::isKeyPressed(controls[10]))
	{
		sound.play();
		buttonDelay = 0.2f;
		if (!showInventory)
			showInventory = true;
		else
			hideInventory = true;

	}
	if (buttonDelay<0 && Keyboard::isKeyPressed(Keyboard::K))
	{
		sound.play();
		buttonDelay = 0.2f;
		if (!show_skill_tree)
			show_skill_tree = true;
		else
			hide_skill_tree = true;

	}
	if (Keyboard::isKeyPressed(controls[11]))
	{
		hideInventory = true;
		displayInfo = false;
		displayItemOptions = false;
	}
	mousePos = sf::Mouse::getPosition(Renderer::getWindow());
	buttonDelay -= dt;
	int i = 0;
	for (auto item : backpack)
	{
		if (!item->is_forDeletion())
		{
			if (mousePos.y >= slots[i].getPosition().y - windowZero.y  && mousePos.y <= slots[i].getPosition().y + 0.07f*WY - windowZero.y)
			{
				if (mousePos.x >= slots[i].getPosition().x - windowZero.x  && mousePos.x <= slots[i].getPosition().x + 0.045f*WX - windowZero.x)
				{
					slots[i].setFillColor(Color::White);
					if (buttonDelay < 0 && sf::Mouse::isButtonPressed(Mouse::Right))
					{
							selectedItem = item;
							selectedIndex = i;
							buttonDelay = 0.1f;					
							itemInfo.setPosition(mousePos.x + windowZero.x + 0.015f*WX, mousePos.y + windowZero.y + 0.01f*WY);
							infoArea.setPosition(mousePos.x + windowZero.x, mousePos.y + windowZero.y);
							itemInfo.setString(info[selectedIndex]);
							displayInfo = true;
							displayItemOptions = false;
						}

					if (buttonDelay < 0 && sf::Mouse::isButtonPressed(Mouse::Left))
					{
						buttonDelay = 0.1f;
						
						itemOptionsEquip.setPosition(mousePos.x + windowZero.x + 0.012f*WX, mousePos.y + windowZero.y + 0.01f*WY);
						itemOptionsDrop.setPosition(mousePos.x + windowZero.x + 0.012f*WX, mousePos.y + windowZero.y + 0.06f*WY);
						itemOptionsArea.setPosition(mousePos.x + windowZero.x, mousePos.y + windowZero.y);
						selectedItem = item;
						selectedIndex = i;
						displayInfo = false;
						displayItemOptions = true;
					}

				}
				else
				{
					
					resetSlot(i);
					if (buttonDelay < 0 && sf::Mouse::isButtonPressed(Mouse::Left))
					{
						displayInfo = false;
					}
				}
			}
			else
			{
				
				resetSlot(i);
				if (buttonDelay < 0 && sf::Mouse::isButtonPressed(Mouse::Left))
				{
					displayInfo = false;
				}
			}
			i++;
		}
	}
	if (mousePos.y >= 0.915f*WY && mousePos.y <= 0.985f*WY)
	{
		
		if (mousePos.x >= 0.69f*WX && mousePos.x <= 0.735f*WX)
		{
			button_menu.setFillColor(sf::Color::White);
			if(!highlighted)sound.play();
			highlighted = true;		
			if (sf::Mouse::isButtonPressed(Mouse::Left))
			{
				buttonDelay = 0.2f;
				activeScene = menuScene; //switch to game
				std::cout << "Active Scene: " + std::to_string(activeScene->getID()) << std::endl;
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
		else if (mousePos.x >= 0.57f*WX && mousePos.x <= 0.615f*WX)
		{
			button_save.setFillColor(sf::Color::White);
			if (!highlighted)sound.play();
			highlighted = true;
			if (buttonDelay<0 && sf::Mouse::isButtonPressed(Mouse::Left))
			{
				buttonDelay = 0.2f;
				evs->SaveGame();
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
	auto health_mana = player->GetComponent<HealthComponent>();
	set(health_mana->getHealth(), health_mana->getMaxHealth(), health_mana->getMana(), health_mana->getMaxMana(), health_mana->getStamina(), health_mana->getMaxStamina());
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
	text.setString("HP " + std::to_string((int)health) +"/" + std::to_string((int)maxHealth) + "\n" + "MP " + std::to_string((int)mana) + "/" + std::to_string((int)maxMana) + "\n" + "ST " + std::to_string((int)stamina) + "/" + std::to_string((int)maxStamina));
}

void HudComponent::setPosition() 
{
	windowZero = Vector2f(player->getPosition().x - WX / 2, player->getPosition().y - WY / 2);
	HP.setPosition(windowZero + Vector2f(0.052f*WX, 0.02f*WY));
	MP.setPosition(windowZero + Vector2f(0.052f*WX, 0.06f*WY));
	STAM.setPosition(windowZero + Vector2f(0.052f*WX, 0.105f*WY));
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
	button_save.setPosition(windowZero + Vector2f(0.57f*WX, 0.915f*WY));
	icon_menu.setPosition(button_menu.getPosition());
	button_inventory.setPosition(windowZero + Vector2f(0.63f*WX, 0.915f*WY));
	icon_inventory.setPosition(button_inventory.getPosition());
	button_menu.setPosition(windowZero + Vector2f(0.69f*WX, 0.915f*WY));
	icon_save.setPosition(button_save.getPosition());
	////////////////////////////INVENTORY
	inventory.setPosition(windowZero + Vector2f(WX, 0.02f*WY) - Vector2f(sliderX, 0));

	////backpack
	backpack.setPosition(inventory.getPosition() + Vector2f(0.007f*WX, 0.55f*WY));
	
	int row = 0;
	int column = 0;
	for (int i = 0; i < BPslots; i++)
	{
		if (column >(BPslots / 3) - 1)
		{
			row++;
			column = 0;
		}
		slots[i].setPosition(backpack.getPosition() + Vector2f(0.0053f*WX, 0.008f*WY) + Vector2f(column * 0.054f*WX, row * 0.086f*WY));
		column++;
	}
	auto x = player->GetComponent<CharacterSheetComponent>();
	auto _backpack = x->getBP();
	int i = 0;
	for (auto item : _backpack)
	{
		if (!item->is_forDeletion())
			item->setPosition(slots[i++].getPosition() + Vector2f(0.023f*WX, 0.03f*WY));
	}
	if (showInventory || hideInventory)
	{
		label_backpack.setPosition(inventory.getPosition() + Vector2f(0.007f*WX, 0.50f*WY));
		
		////stats
		statsArea.setPosition(inventory.getPosition() + Vector2f(0.18f*WX, 0.06f*WY));
		label_stats.setPosition(inventory.getPosition() + Vector2f(0.18f*WX, 0.01f*WY));
		experience_levels.setPosition(statsArea.getPosition() + Vector2f(0.005f*WX, 0.005f*WY));
		///////////level bars///////////
		progressBar_Melee.setPosition(statsArea.getPosition() + Vector2f(0.005f*WX, 0.035f*WY));
		progressBar_Melee_BG.setPosition(statsArea.getPosition() + Vector2f(0.005f*WX, 0.035f*WY));
		progressBar_Fire.setPosition(statsArea.getPosition() + Vector2f(0.005f*WX, 0.115f*WY));
		progressBar_Fire_BG.setPosition(statsArea.getPosition() + Vector2f(0.005f*WX, 0.115f*WY));
		progressBar_Water.setPosition(statsArea.getPosition() + Vector2f(0.005f*WX, 0.195f*WY));
		progressBar_Water_BG.setPosition(statsArea.getPosition() + Vector2f(0.005f*WX, 0.195f*WY));
		progressBar_Wind.setPosition(statsArea.getPosition() + Vector2f(0.005f*WX, 0.275f*WY));
		progressBar_Wind_BG.setPosition(statsArea.getPosition() + Vector2f(0.005f*WX, 0.275f*WY));
		progressBar_Earth.setPosition(statsArea.getPosition() + Vector2f(0.005f*WX, 0.355f*WY));
		progressBar_Earth_BG.setPosition(statsArea.getPosition() + Vector2f(0.005f*WX, 0.355f*WY));


		///////////////equipped///////////
		equippedArea.setPosition(inventory.getPosition() + Vector2f(0.007f*WX, 0.06f*WY));
		label_equipped.setPosition(inventory.getPosition() + Vector2f(0.007f*WX, 0.01f*WY));

		helmet.setPosition(equippedArea.getPosition() + Vector2f(0.06f*WX, 0.01f*WY));
		equipped_helmet.setPosition(helmet.getPosition() + Vector2f(0.023f*WX, 0.03f*WY));
		armour.setPosition(equippedArea.getPosition() + Vector2f(0.06f*WX, 0.17f*WY));
		equipped_armour.setPosition(armour.getPosition() + Vector2f(0.023f*WX, 0.03f*WY));
		boots.setPosition(equippedArea.getPosition() + Vector2f(0.06f*WX, 0.3f*WY));
		equipped_boots.setPosition(boots.getPosition() + Vector2f(0.023f*WX, 0.03f*WY));
		weapon.setPosition(equippedArea.getPosition() + Vector2f(0.005f*WX, 0.17f*WY));
		equipped_weapon.setPosition(weapon.getPosition() + Vector2f(0.023f*WX, 0.03f*WY));
		shield.setPosition(equippedArea.getPosition() + Vector2f(0.115f*WX, 0.17f*WY));
		equipped_shield.setPosition(shield.getPosition() + Vector2f(0.023f*WX, 0.03f*WY));

		icon_weapon.setPosition(weapon.getPosition());
		icon_armour.setPosition(armour.getPosition());
		icon_shield.setPosition(shield.getPosition());
		icon_helmet.setPosition(helmet.getPosition());
		icon_boots.setPosition(boots.getPosition());

		
	}
	if (show_skill_tree || hide_skill_tree)
	{
		////skill tree
		skill_tree.setPosition(windowZero + Vector2f(-0.8f*WX, 0.02f*WY) + Vector2f(tree_sliderX, 0));
		label_skill_tree.setPosition(skill_tree.getPosition() + Vector2f(0.05f*WX, 0.01f*WY));
		fire_tree.setPosition(skill_tree.getPosition() + Vector2f(0.05f*WX, 0.08f*WY));
		water_tree.setPosition(skill_tree.getPosition() + Vector2f(0.33f*WX, 0.08f*WY));
		wind_tree.setPosition(skill_tree.getPosition() + Vector2f(0.05f*WX, 0.45f*WY));
		earth_tree.setPosition(skill_tree.getPosition() + Vector2f(0.33f*WX, 0.45f*WY));

		label_fire.setPosition(fire_tree.getPosition() + Vector2f(0.02f*WX, 0.01f*WY));
		label_water.setPosition(water_tree.getPosition() + Vector2f(0.02f*WX, 0.01f*WY));
		label_wind.setPosition(wind_tree.getPosition() + Vector2f(0.02f*WX, 0.01f*WY));
		label_earth.setPosition(earth_tree.getPosition() + Vector2f(0.02f*WX, 0.01f*WY));

		spell_fire_1.setPosition(fire_tree.getPosition() + Vector2f(0.02f*WX, 0.05f*WY));
		spell_fire_2.setPosition(fire_tree.getPosition() + Vector2f(0.02f*WX, 0.25f*WY));
		spell_fire_3.setPosition(fire_tree.getPosition() + Vector2f(0.10f*WX, 0.05f*WY));
		spell_fire_4.setPosition(fire_tree.getPosition() + Vector2f(0.10f*WX, 0.25f*WY));
		spell_fire_5.setPosition(fire_tree.getPosition() + Vector2f(0.20f*WX, 0.15f*WY));
		spell_water_1.setPosition(water_tree.getPosition() + Vector2f(0.02f*WX, 0.05f*WY));
		spell_water_2.setPosition(water_tree.getPosition() + Vector2f(0.02f*WX, 0.25f*WY));
		spell_water_3.setPosition(water_tree.getPosition() + Vector2f(0.10f*WX, 0.05f*WY));
		spell_water_4.setPosition(water_tree.getPosition() + Vector2f(0.10f*WX, 0.25f*WY));
		spell_water_5.setPosition(water_tree.getPosition() + Vector2f(0.20f*WX, 0.15f*WY));
		spell_wind_1.setPosition(wind_tree.getPosition() + Vector2f(0.02f*WX, 0.05f*WY));
		spell_wind_2.setPosition(wind_tree.getPosition() + Vector2f(0.02f*WX, 0.25f*WY));
		spell_wind_3.setPosition(wind_tree.getPosition() + Vector2f(0.10f*WX, 0.05f*WY));
		spell_wind_4.setPosition(wind_tree.getPosition() + Vector2f(0.10f*WX, 0.25f*WY));
		spell_wind_5.setPosition(wind_tree.getPosition() + Vector2f(0.20f*WX, 0.15f*WY));
		spell_earth_1.setPosition(earth_tree.getPosition() + Vector2f(0.02f*WX, 0.05f*WY));
		spell_earth_2.setPosition(earth_tree.getPosition() + Vector2f(0.02f*WX, 0.25f*WY));
		spell_earth_3.setPosition(earth_tree.getPosition() + Vector2f(0.10f*WX, 0.05f*WY));
		spell_earth_4.setPosition(earth_tree.getPosition() + Vector2f(0.10f*WX, 0.25f*WY));
		spell_earth_5.setPosition(earth_tree.getPosition() + Vector2f(0.20f*WX, 0.15f*WY));
	}

}
