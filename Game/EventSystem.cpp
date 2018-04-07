
#include "EventSystem.h"
#include "cmp_char_sheet.h"
#include "Game.h"

EventSystem* EventSystem::instance;
EventSystem::EventSystem()
{
	
}
EventSystem* EventSystem::getInstance()
{
	if (instance == 0)
	{
		instance = new EventSystem();
	}

	return instance;
}
EventSystem::~EventSystem()
{
}
void EventSystem::addExp(int a, float b)
{
	auto exp = player->GetComponent<CharacterSheetComponent>();
	exp->addEXP(a, b);
}