#include <iostream>
#include "cmp_attack.h"
#include "cmp_health.h"
#include "cmp_damage_text.h"
#include "SystemRenderer.h"
#include <string>



AttackComponent::AttackComponent(Entity *p) : Component(p) {}

void AttackComponent::setEntities(std::vector <std::shared_ptr<Entity>>& e) {
	_entities = e;
}
void AttackComponent::render() {
}
void AttackComponent::update(double dt) 
{
	static float attackTime = 0.0f;
	attackTime -= dt;
	static float textTime = 0.0f;
	textTime -= dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
	{
		for (auto e : _entities) {
			if (attackTime <= 0 && length(_parent->getPosition() - e->getPosition()) < 100.0f) {
				attackTime = 0.2f;
				//this should take the hp of the entity, reduce it by the AD of whatever hits it
				auto health_mana = e->GetComponent<HealthComponent>();
				health_mana->reduceHealth(30); //should be changed to the player's attack damage
				damageText.setString(std::to_string(30));
				if (!font.loadFromFile("res/fonts/leadcoat.ttf")) {
					std::cout << "Cannot load font!" << std::endl;
				}
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
