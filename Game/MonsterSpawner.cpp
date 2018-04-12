
#include "MonsterSpawner.h"
#include "cmp_health.h"
#include "cmp_actor_movement.h"
#include "cmp_enemy_attack.h"
#include "cmp_ai_steering.h"
#include "cmp_npc.h"
#include "cmp_status.h"

MonsterSpawner* MonsterSpawner::instance;
MonsterSpawner::MonsterSpawner()
{
	
}
MonsterSpawner* MonsterSpawner::getInstance()
{
	if (instance == 0)
	{
		instance = new MonsterSpawner();
	}

	return instance;
}
std::shared_ptr<Entity> MonsterSpawner::spawn_zombie()
{
	auto ghost = std::make_shared<Entity>();
	ghost->addComponent<ActorMovementComponent>();
	auto s = ghost->addComponent<CharacterSpriteComponent>();
	s->getSprite().setTexture(zombieTexture);
	s->getSprite().setTextureRect({ 0,0,16,21 });
	s->getSprite().setScale({ 2.0f*WX / 1280, 2.0f*WY / 720 });
	s->getSprite().setOrigin(8.0f, 12.0f);
	ghost->addComponent<HealthComponent>();
	ghost->addComponent<EnemyHealthBarComponent>();
	ghost->addComponent<StatusComponent>();
	auto p = ghost->addComponent<EnemyAttackComponent>();
	p->setLevel(0);
	ghost->addComponent<SteeringComponent>(player.get());
	std::cout << player.get()->getPosition().x;
	gameScene->getEnts().push_back(ghost);
	return ghost;
}
std::shared_ptr<Entity> MonsterSpawner::spawn_NPC_WELCOME(sf::Vector2f loc)
{
	auto npc = std::make_shared<Entity>();
	auto n = npc->addComponent<CharacterSpriteComponent>();
	n->getSprite().setTexture(playerTexture);
	n->getSprite().setTextureRect({ 0,0,16,21 });
	n->getSprite().setScale({ 2.0f*WX / 1280, 2.0f*WY / 720 });
	n->getSprite().setOrigin(8.0f, 12.0f);
	npc->setPosition(loc);
	auto d = npc->addComponent<NPCComponent>();
	d->setDialogue("HELLO THERE, ADVENTURER! HELLO THERE, \nADVENTURER! HELLO THERE, ADVENTURER! ");
	gameScene->getEnts().push_back(npc);
	return npc;
}