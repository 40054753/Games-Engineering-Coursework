#include "Game.h"
#include "ecm.h"
#include "cmp_items.h"

class MonsterSpawner
{
private:
	MonsterSpawner();
	static MonsterSpawner* instance;
public:
	static MonsterSpawner* getInstance();
	~MonsterSpawner()=default;

	std::shared_ptr<Entity> spawn_zombie(sf::Vector2f loc);

	////////////////NPCS
	std::shared_ptr<Entity> spawn_NPC_WELCOME(sf::Vector2f loc);
	std::shared_ptr<Entity> spawn_NPC_MOM(sf::Vector2f loc);
};