#include "Game.h"

class EventSystem
{

private:
	EventSystem();
	static EventSystem* instance;
public:
	static EventSystem* getInstance();
	~EventSystem();
	void addExp(int stat, float exp);
};