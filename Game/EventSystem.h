#include "Game.h"

class EventSystem
{

private:
	EventSystem();
	static EventSystem* instance;
	std::shared_ptr<Entity> _player;
public:
	void setPlayer(std::shared_ptr<Entity>& e);
	static EventSystem* getInstance();
	~EventSystem();
	void addExp(int stat, float exp);
};