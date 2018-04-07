
#include "ItemGenerator.h"
#include "cmp_char_sheet.h"

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
ItemGenerator::~ItemGenerator()
{
}
void ItemGenerator::load(int id, bool equipped)
{
	switch (id)
	{
	case 0:
		recreate_iron_helmet(equipped);
		break;
	case 1:
		recreate_leaf(equipped);
		break;
	default:
		break;
	}
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
		it->setID(0);
		it->point(item);
		it->setName("IRON HELMET");
		it->setType(HELMET);
		it->setDef(10);
		it->getSprite().setTexture(itemsTexture);
		it->getSprite().setTextureRect({ 0,144,16,16 });
		it->getSprite().setScale({ 2, 2 });
		it->getSprite().setOrigin({ 8,8 });
		activeScene->getEnts().push_back(item);
}
void ItemGenerator::recreate_iron_helmet(bool equipped)
{
	auto item = std::make_shared<Entity>();
	auto it = item->addComponent<ItemComponent>();
	item->setPosition({ 100,100 });
	it->setID(0);
	it->point(item);
	it->setName("IRON HELMET");
	it->setType(HELMET);
	it->setDef(10);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 0,144,16,16 });
	it->getSprite().setScale({ 2, 2 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
	auto x = player->GetComponent<CharacterSheetComponent>();
	x->pickUp(item);
	if (equipped) x->equip(item);
}
void ItemGenerator::create_leaf(sf::Vector2f location)
{
	auto item = std::make_shared<Entity>();
	item->setPosition(location);
	auto it = item->addComponent<ItemComponent>();
	it->setID(1);
	it->point(item);
	it->setName("Leaf");
	it->setType(ARMOUR);
	it->setDef(1);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 16,192,16,16 });
	it->getSprite().setScale({ 2, 2 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
}
void ItemGenerator::recreate_leaf(bool equipped)
{
	auto item = std::make_shared<Entity>();
	auto it = item->addComponent<ItemComponent>();
	it->setID(1);
	it->point(item);
	it->setName("Leaf");
	it->setType(ARMOUR);
	it->setDef(1);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 16,192,16,16 });
	it->getSprite().setScale({ 2, 2 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
	auto x = player->GetComponent<CharacterSheetComponent>();
	x->pickUp(item);
	if (equipped) x->equip(item);
}