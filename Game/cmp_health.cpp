#include "cmp_health.h"



HealthComponent::HealthComponent(Entity *p) : Component(p) 
{
	health = 150;
	mana = 200;
	maxHealth = 150;
	maxMana = 200;
	stamina = 100;
	maxStamina = 100;
}
void HealthComponent::reset()
{
	health = maxHealth;
	mana = maxMana;
	stamina = maxStamina;
}
void HealthComponent::render() {}
void HealthComponent::update(double dt)
{
	////automatic recovery of health and mana over time 
	recoveryTimer -= dt;
	if (recoveryTimer <= 0)
	{
		if (health <= maxHealth-3)
			health += 3;
		if (mana <= maxMana-3)
			mana += 3;
		if (stamina <= maxStamina - 15)
			stamina += 15;
		recoveryTimer = recoveryDelay;
	}
}
void HealthComponent::reduceHealth(float x)
{
	health -= x;
}
void HealthComponent::reduceMana(float x)
{
	mana -= x;
}
void HealthComponent::reduceStamina(float x)
{
	stamina -= x;
}