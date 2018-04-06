#include "Game.h"
#include "ecm.h"
#include "cmp_items.h"

class ItemGenerator
{
private:
	ItemGenerator();
	static ItemGenerator* instance;
	std::shared_ptr<Entity> _player;
public:
	static ItemGenerator* getInstance();
	void setPlayer(std::shared_ptr<Entity>& e);
	~ItemGenerator();
	void create_iron_helmet(sf::Vector2f location);
	void create_leaf(sf::Vector2f location);
	void random_drop(int level,sf::Vector2f location);
};