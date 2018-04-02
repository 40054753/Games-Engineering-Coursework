#pragma once
#include "ecm.h"

class ProjectileComponent : public Component {

protected:
	std::vector <std::shared_ptr<Entity>> _entities;
	float textTime = 0.0f;
public:
	sf::Text damageText;
	std::vector<sf::Text> damageArray;
	explicit ProjectileComponent(Entity *p);
	ProjectileComponent() = delete;
	void render() override;
	void update(double dt) override;
	void setEntities(std::vector<std::shared_ptr<Entity>>& e);
};