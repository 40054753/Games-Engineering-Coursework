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
	void spawnPlayer();
	~EventSystem();
	void addExp(int stat, float exp);
};