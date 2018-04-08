#include <iostream>
#include "EventSystem.h"
#include "cmp_attack.h"
#include "cmp_health.h"
#include "cmp_actor_movement.h"
#include "cmp_projectile.h"
#include "cmp_sprite.h"
#include "SystemRenderer.h"
#include "cmp_char_sheet.h"
#include "Game.h"
#include <string>


AttackComponent::AttackComponent(Entity *p) : Component(p) 
{
	
}

void AttackComponent::setEntities(std::vector <std::shared_ptr<Entity>>& e) {
	_entities = e;
}
void AttackComponent::render() 
{
}
void AttackComponent::update(double dt) 
{
	EventSystem* events = EventSystem::getInstance();
	auto char_cheet = _parent->GetComponent<CharacterSheetComponent>();
	auto health_mana = _parent->GetComponent<HealthComponent>();
	static float attackTime = 0.0f;
	attackTime -= dt;
	cooldown -= dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		if (cooldown < 0.0f && health_mana->getMana()>20 )
		{
			health_mana->reduceMana(20);
			cooldown = 0.3f;
			auto bullet = std::make_shared<Entity>();
			bullet->setPosition(_parent->getPosition());
			auto pr = bullet->addComponent<ProjectileMovementComponent>();
			bullet->setFace(_parent->getFace());
		    auto c2 = bullet->addComponent<ProjectileComponent>();
			c2->setEntities(_entities);
			auto dmg = player->GetComponent<CharacterSheetComponent>();
			c2->setDamage((dmg->getLevelFire()*5.0f) + 20.0f);
			c2->setType(1);
			auto s = bullet->addComponent<StaticSpriteComponent>();
			s->getSprite().setTexture(spellsTexture);
			s->addSpin();
			s->getSprite().setTextureRect({ 0,0,30,30 });
			s->getSprite().setScale({ 1.0f, 1.0f });
			s->getSprite().setOrigin({ 8.0f, 12.0f });

			activeScene->getEnts().push_back(bullet);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
	{
		for (auto e : _entities) 
		{
			if (!e->is_forDeletion())
			if (attackTime <= 0 && length(_parent->getPosition() - e->getPosition()) < 100.0f*WX / 1280) {
				attackTime = 0.2f;
				//this should take the hp of the entity, reduce it by the AD of whatever hits it
				auto health_mana = e->GetComponent<HealthComponent>();
				auto att = player->GetComponent<CharacterSheetComponent>();
				health_mana->reduceHealth(att->getStatAttack()); //should be changed to the player's attack damage
				events->addExp(0, 10.0f);
				auto dmg = std::make_shared<Entity>();
				auto txt = dmg->addComponent<DamageTextComponent>();
				dmg->setPosition(e->getPosition());
				txt->setText(att->getStatAttack());
				activeScene->getEnts().push_back(dmg);
			}
		}
	}
	
}
