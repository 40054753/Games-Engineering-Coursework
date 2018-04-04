#include <iostream>
#include "cmp_enemy_attack.h"
#include "cmp_health.h"
#include "cmp_actor_movement.h"
#include "cmp_projectile.h"
#include "cmp_sprite.h"
#include "SystemRenderer.h"
#include "Game.h"
#include <string>



EnemyAttackComponent::EnemyAttackComponent(Entity *p) : Component(p) {}

void EnemyAttackComponent::setPlayer(std::shared_ptr<Entity>& e) {
	_player = e;
}
void EnemyAttackComponent::render()
{

}
void EnemyAttackComponent::update(double dt)
{
	auto hp = _parent->GetComponent<HealthComponent>();
	if (hp->getHealth() < 0) _parent->setForDelete();
	if (!_parent->is_forDeletion())
	{
		///////////////////////////////////////////////////////WHEN PLAYER TOUCHES THE ENEMY//////////////////////////////////
		if (length(_parent->getPosition() - _player->getPosition()) < 20.0f)
		{
			auto hp = _player->GetComponent<HealthComponent>();
			auto d = _player->GetComponent<PlayerMovementComponent>();
			d->push((_player->getPosition() - _parent->getPosition()));
			auto pp = _player->GetComponent<CharacterSpriteComponent>();
			hp->reduceHealth(30);

		}
	}
	
}
