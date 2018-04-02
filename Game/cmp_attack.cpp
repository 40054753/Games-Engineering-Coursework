#include <iostream>
#include "cmp_attack.h"
#include "cmp_health.h"
#include "cmp_actor_movement.h"
#include "cmp_projectile.h"
#include "cmp_sprite.h"
#include "SystemRenderer.h"
#include "Game.h"
#include <string>



AttackComponent::AttackComponent(Entity *p) : Component(p) {}

void AttackComponent::setEntities(std::vector <std::shared_ptr<Entity>>& e) {
	_entities = e;
}
void AttackComponent::render() 
{

}
void AttackComponent::update(double dt) 
{
	auto health_mana = _parent->GetComponent<HealthComponent>();
	static float attackTime = 0.0f;
	attackTime -= dt;
	cooldown -= dt;

	textTime -= dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		if (cooldown < 0.0f && health_mana->getMana()>20 )
		{
			health_mana->reduceMana(20);
			cooldown = 0.3f;
			auto bullet = std::make_shared<Entity>();
			auto pr = bullet->addComponent<ProjectileMovementComponent>();
			bullet->setFace(_parent->getFace());
		    auto c2 = bullet->addComponent<ProjectileComponent>();
			c2->setEntities(_entities);
			auto s = bullet->addComponent<StaticSpriteComponent>();
			s->getSprite().setTexture(playerTexture);
			s->getSprite().setTextureRect({ 0,0,15,15 });
			s->getSprite().setScale({ 1.0f, 1.0f });
			s->getSprite().setOrigin({ 8.0f, 12.0f });
			s->getSprite().setPosition({ 100.0f, 100.0f });
			bullet->setPosition(_parent->getPosition());
			gameScene->getEnts().push_back(bullet);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
	{
		for (auto e : _entities) {
			if (attackTime <= 0 && length(_parent->getPosition() - e->getPosition()) < 100.0f) {
				attackTime = 0.2f;
				//this should take the hp of the entity, reduce it by the AD of whatever hits it
				auto health_mana = e->GetComponent<HealthComponent>();
				health_mana->reduceHealth(30); //should be changed to the player's attack damage
				damageText.setString(std::to_string(30));
				damageText.setFont(font);
				damageText.setCharacterSize(20);
				damageText.setColor(sf::Color::Red);
				damageText.setPosition(e->getPosition());
				damageArray.insert(damageArray.begin(), damageText);
				if (health_mana->getHealth() <= 0) {
					e->setForDelete();
				}
				break;
			}
		}
	}
	if (textTime <= 0) {
		if (!damageArray.empty()) {
			damageArray.pop_back();
		}
		textTime = 0.4f;
	}
	for (int i = 0; i < damageArray.size(); i++) {
		std::string string2 = std::to_string(damageArray.size());
		std::cout << string2;
		Renderer::queue(&damageArray[i]);
	}
}
