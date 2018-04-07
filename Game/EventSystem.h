#include "Game.h"

class EventSystem
{

private:
	EventSystem();
	static EventSystem* instance;
public:
	static EventSystem* getInstance();
	void SaveGame();
	void LoadGame();
	~EventSystem();
	void addExp(int stat, float exp);
};