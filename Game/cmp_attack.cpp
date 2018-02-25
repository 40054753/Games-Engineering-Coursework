#include "cmp_attack.h"



AttackComponent::AttackComponent(Entity *p) : Component(p) {}

void AttackComponent::setEntities(std::vector <std::shared_ptr<Entity>>& e) {
	_entities = e;
}
void AttackComponent::render() {}
void AttackComponent::update(double dt) 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
	{
		for (auto e : _entities) {
			if (length(_parent->getPosition() - e->getPosition()) < 100.0f) {				
			e->setForDelete();
				break;
			}
		}
	}
}
