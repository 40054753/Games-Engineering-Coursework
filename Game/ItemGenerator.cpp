
#include "ItemGenerator.h"
ItemGenerator* ItemGenerator::instance;
ItemGenerator::ItemGenerator()
{
	
}
ItemGenerator* ItemGenerator::getInstance()
{
	if (instance == 0)
	{
		instance = new ItemGenerator();
	}

	return instance;
}
void ItemGenerator::setPlayer(std::shared_ptr<Entity>& e) {
	_player = e;
}
ItemGenerator::~ItemGenerator()
{
}
void ItemGenerator::random_drop(int level, sf::Vector2f location)
{
	int drop = rand() % 100;
	switch (level)
	{
	case 0:
		if (drop >= 0 && drop < 100)
			create_iron_helmet(location);
		if (drop >= 0 && drop < 100)
			create_leaf(location);
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	default:
		break;
	}
}
void ItemGenerator::create_iron_helmet(sf::Vector2f location)
{
		auto item = std::make_shared<Entity>();
		item->setPosition(location);
		auto it = item->addComponent<ItemComponent>();
		it->point(item);
		it->setName("IRON HELMET");
		it->setType(HELMET);
		it->setDef(10);
		it->setPlayer(_player);
		it->getSprite().setTexture(itemsTexture);
		it->getSprite().setTextureRect({ 0,144,16,16 });
		it->getSprite().setScale({ 2, 2 });
		it->getSprite().setOrigin({ 8,8 });
		activeScene->getEnts().push_back(item);
}
void ItemGenerator::create_leaf(sf::Vector2f location)
{
	auto item = std::make_shared<Entity>();
	item->setPosition(location);
	auto it = item->addComponent<ItemComponent>();
	it->point(item);
	it->setName("Leaf");
	it->setType(ARMOUR);
	it->setDef(1);
	it->setPlayer(_player);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 16,192,16,16 });
	it->getSprite().setScale({ 2, 2 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
}