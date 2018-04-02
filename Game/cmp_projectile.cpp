#include "cmp_projectile.h"
#include "cmp_actor_movement.h"
#include "cmp_health.h"
#include "Game.h"
#include "SystemRenderer.h"

ProjectileComponent::ProjectileComponent(Entity *p) : Component(p) {}

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
	if (length(g->getPosition() - _parent->getPosition()) < 20.0f)
	{
		auto health_mana = g->GetComponent<HealthComponent>();
		health_mana->reduceHealth(30); //should be changed to the player's attack damage
		damageText.setString(std::to_string(30));
		
		damageText.setFont(font);
		damageText.setCharacterSize(20);
		damageText.setColor(sf::Color::Red);
		damageText.setPosition(g->getPosition());
		damageArray.insert(damageArray.begin(), damageText);
		if (health_mana->getHealth() <= 0) {
			g->setForDelete();
		}
		break;
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
		_parent->setForDelete();
	}
}
