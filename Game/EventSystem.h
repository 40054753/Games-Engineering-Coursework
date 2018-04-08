#include "Game.h"

class EventSystem
{

private:
	bool gameLoaded = false;
	EventSystem();
	static EventSystem* instance;
public:
	static EventSystem* getInstance();
	bool isLoaded() { return gameLoaded; }
	void gameLoad() { gameLoaded = true; }
	void SaveGame();
	void LoadGame();
	~EventSystem();
	void addExp(int stat, float exp);
};