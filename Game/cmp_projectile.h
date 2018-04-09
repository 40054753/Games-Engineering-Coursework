#pragma once
#include "ecm.h"

class ProjectileComponent : public Component {

protected:
	std::vector <std::shared_ptr<Entity>> _entities;
	float textTime = 0.0f;
	float damage = 30;
	int type = 1;
	bool knockback = false;
	bool finishAnimation = false;
	float timer = 0.1f;
public:
	void setTimer(float t) { timer = t; }
	void finishAnimationFirst() { finishAnimation = true; }
	void addKnockback() { knockback = true; }
	sf::Text damageText;
	std::vector<sf::Text> damageArray;
	explicit ProjectileComponent(Entity *p);
	ProjectileComponent() = delete;
	void setDamage(int x) { damage = x; }
	void setType(int x) { type = x; } ////////////////FIRE-1 WATER-2 ........
	void render() override;
	void update(double dt) override;
	void setEntities(std::vector<std::shared_ptr<Entity>>& e);
};