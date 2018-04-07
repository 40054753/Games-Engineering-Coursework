#include "Game.h"
#include "cmp_char_sheet.h"
#include "cmp_items.h"

CharacterSheetComponent::CharacterSheetComponent(Entity *p) : Component(p)
{
	//////////////////////exp to progress befween levels
	experience_thresholds[0] = 100;
	experience_thresholds[1] = 100;
	experience_thresholds[2] = 100;
	experience_thresholds[3] = 100;
	experience_thresholds[4] = 100;
	experience_thresholds[5] = 100;
	experience_thresholds[6] = 100;
	experience_thresholds[7] = 100;
	experience_thresholds[8] = 100;
	experience_thresholds[9] = 100;

}
void CharacterSheetComponent::addEXP(int stat, float amount)
{
	switch (stat)
	{
	case 0:
		experience_melee += amount;
	break;
	case 1:
		experience_fire += amount;
		break;
	case 2:
		experience_water += amount;
		break;
	case 3:
		experience_wind += amount;
		break;
	case 4:
		experience_earth += amount;
		break;
	default:
		break;
	}
}
void CharacterSheetComponent::equip(std::shared_ptr<Entity>& item)
{
	auto x = item->GetComponent<ItemComponent>();
	x->equip();
	switch (x->getType())
	{
	case WEAPON:
		if(weapon!=nullptr)
			weapon->GetComponent<ItemComponent>()->unequip();
		weapon = item;
		break;
	case SHIELD:
		if (shield != nullptr)
			shield->GetComponent<ItemComponent>()->unequip();
		shield = item;
		break;
	case HELMET:
		if (helmet != nullptr)
			helmet->GetComponent<ItemComponent>()->unequip();
		helmet = item;
		break;
	case ARMOUR:
		if (armour != nullptr)
			armour->GetComponent<ItemComponent>()->unequip();
		armour = item;
		break;
	case BOOTS:
		if (boots != nullptr)
			boots->GetComponent<ItemComponent>()->unequip();
		boots = item;
		break;
	default:
		break;
	}
}
void CharacterSheetComponent::render()
{
}

void CharacterSheetComponent::update(double dt)
{	
	if (weapon != nullptr)
		if (!weapon->is_forDeletion())
			stat_melee_attack = level_melee * 2.0f + weapon->GetComponent<ItemComponent>()->getAtt();
		else
			stat_melee_attack = level_melee * 2.0f;
	else
		stat_melee_attack = level_melee * 2.0f;
	///////////////////////////////////////making sure items are equipped first, otherwise 0//////////////////
	float helmet_def = 0;
	float armour_def = 0;
	float shield_def = 0;
	float boots_def = 0;
	if (helmet != nullptr)
		if(!helmet->is_forDeletion())
			helmet_def = helmet->GetComponent<ItemComponent>()->getDef();
	if (armour != nullptr)
		if (!armour->is_forDeletion())
			armour_def = armour->GetComponent<ItemComponent>()->getDef();
	if (shield != nullptr)
		if (!shield->is_forDeletion())
			shield_def = shield->GetComponent<ItemComponent>()->getDef();
	if (boots != nullptr)
		if (!boots->is_forDeletion())
			boots_def = boots->GetComponent<ItemComponent>()->getDef();

	stat_defence = level_melee * 0.5f + helmet_def + armour_def + shield_def + boots_def;
	if(boots != nullptr)
		if (!boots->is_forDeletion())
			stat_speed = boots->GetComponent<ItemComponent>()->getSpd();

	if (experience_melee >= experience_thresholds[(int)level_melee] && level_melee<MAX_LEVEL)
	{
		experience_melee =  experience_melee - experience_thresholds[(int)level_melee];
		level_melee++;
	}
	if (experience_fire >= experience_thresholds[(int)level_fire] && level_fire<MAX_LEVEL)
	{
		experience_fire = experience_fire - experience_thresholds[(int)level_fire];
		level_fire++;
	}
	if (experience_water >= experience_thresholds[(int)level_water] && level_water<MAX_LEVEL)
	{
		experience_water = experience_water - experience_thresholds[(int)level_water];
		level_water++;
	}
	if (experience_wind >= experience_thresholds[(int)level_wind] && level_wind<MAX_LEVEL)
	{
		experience_wind = experience_wind - experience_thresholds[(int)level_wind];
		level_wind++;
	}
	if (experience_earth >= experience_thresholds[(int)level_earth] && level_earth<MAX_LEVEL)
	{
		experience_earth = experience_earth - experience_thresholds[(int)level_earth];
		level_earth++;
	}
}
std::vector<std::string> CharacterSheetComponent::getBPINFO()
{
	std::vector<std::string> temp;
	for (auto item : _backpack)
	{
		auto text = item->GetComponent<ItemComponent>();
		temp.push_back(" " + text->getName() + "\nAttack: " + std::to_string((int)text->getAtt()) + "\nDefence: " + std::to_string((int)text->getDef()) + "\nSpeed: " + std::to_string((int)text->getSpd()));
	}
	return temp;
}
void CharacterSheetComponent::pickUp(std::shared_ptr<Entity>& item)
{
	if (_backpack.size() < 21)
	{
		_backpack.push_back(item);
	}
}