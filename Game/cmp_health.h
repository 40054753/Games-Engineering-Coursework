#pragma once
#include "ecm.h"

class HealthComponent : public Component {

protected:
	float maxHealth;
	float health;
	float maxMana;
	float mana;
	float recoveryDelay = 3.0f;
	float recoveryTimer = 3.0f;
public:
	explicit HealthComponent(Entity *p);
	HealthComponent() = delete;
	int getHealth() { return health; }
	int getMaxHealth() { return maxHealth; }
	int getMaxMana() { return maxMana; }
	int getMana() { return mana; }
	void reduceHealth(float x);
	void reset();
	void reduceMana(float x);
	void render() override;
	void update(double dt) override;	

	
};

