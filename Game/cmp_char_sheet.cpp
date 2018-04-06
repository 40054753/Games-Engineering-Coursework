#include "Game.h"
#include "cmp_char_sheet.h"

CharacterSheetComponent::CharacterSheetComponent(Entity *p) : Component(p) {}


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