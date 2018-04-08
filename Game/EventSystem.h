#include "Game.h"

class EventSystem
{

private:
	bool refreshKeyLabels = false;
	bool gameLoaded = false;
	EventSystem();
	static EventSystem* instance;
	int resolution_index=0;
public:
	void refresh() { refreshKeyLabels = true; }
	bool is_for_refresh() {  return refreshKeyLabels; }
	void refreshed() { refreshKeyLabels = false; }
	int getRes() { return resolution_index; }
	static EventSystem* getInstance();
	bool isLoaded() { return gameLoaded; }
	void gameLoad() { gameLoaded = true; }
	void SaveGame();
	void LoadGame();
	~EventSystem();
	void addExp(int stat, float exp);
};