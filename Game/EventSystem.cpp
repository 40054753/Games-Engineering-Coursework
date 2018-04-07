
#include "EventSystem.h"
#include "cmp_char_sheet.h"


EventSystem* EventSystem::instance;
EventSystem::EventSystem()
{
	
}
void EventSystem::setPlayer(std::shared_ptr<Entity>& e)
{
	_player = e;
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
	auto exp = _player->GetComponent<CharacterSheetComponent>();
	exp->addEXP(a, b);
}