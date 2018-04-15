#include "Game.h"
#include "levelsystem.h"

class EventSystem
{

private:

	//////////if newgame ///////////// for loading correct map
	bool newGame = false;

	bool mapChange = false;
	////////////////////////////CURRENT MAP SWITCHES//////////////////
	bool village0 = false;
	bool interior0 = false;
	sf::Vector2f new_destination = {100,100};


	bool LVUP = true;
	bool refreshKeyLabels = false;
	bool gameLoaded = false;
	EventSystem();
	static EventSystem* instance;
	int resolution_index=0;
public:
	bool is_newGame() { return newGame; }
	void setNewGame() { newGame = true; }
	int getCurrentMap();
	bool if_changeMap() { return mapChange; }
	void changeMap(sf::Vector2f d) { mapChange = true; new_destination = d; }
	sf::Vector2f getDest() { return new_destination; }
	void changeMapFinished() { mapChange = false; }
	//////////////////////map changers
	void map_village0() { village0 = true; interior0 = false; }
	void map_interior0() { village0 = false; interior0 = true; }

	//////////////////////////map checkers
	bool if_village0() { return village0; }
	bool if_interior0() { return interior0; }


	void switch_level_up() { LVUP = (LVUP) ? false : true; }
	bool is_leveled_up() { return LVUP; }

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