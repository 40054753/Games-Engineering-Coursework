#include "cmp_projectile.h"
#include "cmp_actor_movement.h"
#include "cmp_health.h"
#include "Game.h"
#include "SystemRenderer.h"
#include "cmp_sprite.h"
#include "cmp_char_sheet.h"
#include "EventSystem.h"

EventSystem* events = EventSystem::getInstance();

ProjectileComponent::ProjectileComponent(Entity *p) : Component(p) 
{

}

void ProjectileComponent::setEntities(std::vector <std::shared_ptr<Entity>>& e) {
	_entities = e;
}
void ProjectileComponent::render()
{

}
void ProjectileComponent::update(double dt)
{
	if(!_parent->is_forDeletion())
	for(auto g: _entities)
	if(!g->is_forDeletion())
	if (length(g->getPosition() - _parent->getPosition()) < 30.0f)
	{
		auto health_mana = g->GetComponent<HealthComponent>();
		health_mana->reduceHealth(30); //should be changed to the player's attack damage
		auto dmg = std::make_shared<Entity>();
		dmg->addComponent<DamageTextComponent>();
		dmg->setPosition(g->getPosition());
		gameScene->getEnts().push_back(dmg);
		events->addExp(1, 10);
		_parent->setForDelete();
	}
	
	
}
