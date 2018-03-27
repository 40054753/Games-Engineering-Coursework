#include "cmp_npc.h"


NPCComponent::NPCComponent(Entity *p) : Component(p) {}

void NPCComponent::update(double dt) 
{
	for(auto e : _entities)
	if ((length(_parent->getPosition() - e->getPosition()) < 21.0f) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		interact();
	}
}
void NPCComponent::setEntities(std::vector <std::shared_ptr<Entity>>& e) {
	_entities = e;
}
void NPCComponent::render() {}
void NPCComponent::interact()
{
	std::cout << "hello there!" << std::endl;
}