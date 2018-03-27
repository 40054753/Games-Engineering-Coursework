#pragma once
#include "ecm.h"

class HealthComponent : public Component {

protected:
	int maxHealth;
	int health;
	int maxMana;
	int mana;
	float recoveryDelay = 3.0f;
	float recoveryTimer = 3.0f;
public:
	explicit HealthComponent(Entity *p);
	HealthComponent() = delete;
	int getHealth() { return health; }
	int getMana() { return mana; }
	void reduceHealth(int x);
	void reset();
	void reduceMana(int x);
	void render() override;
	void update(double dt) override;	

	
};

