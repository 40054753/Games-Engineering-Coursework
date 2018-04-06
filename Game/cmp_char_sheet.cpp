#include "Game.h"
#include "cmp_char_sheet.h"
#include "cmp_items.h"

CharacterSheetComponent::CharacterSheetComponent(Entity *p) : Component(p) {}

void CharacterSheetComponent::equip(std::shared_ptr<Entity>& item)
{
	auto x = item->GetComponent<ItemComponent>()->getType();
	
	switch (x)
	{
	case WEAPON:
		weapon = item;
		break;
	case SHIELD:
		shield = item;
		break;
	case HELMET:
		helmet = item;
		break;
	case ARMOUR:
		armour = item;
		break;
	case BOOTS:
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
	
}
void CharacterSheetComponent::pickUp(std::shared_ptr<Entity>& item)
{
	if (_backpack.size() < 21)
	{
		_backpack.push_back(item);
	}
}