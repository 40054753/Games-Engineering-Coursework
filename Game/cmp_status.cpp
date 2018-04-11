#include "cmp_status.h"
#include "cmp_sprite.h"
#include "Game.h"

StatusComponent::StatusComponent(Entity * p) : Component(p)
{
}

void StatusComponent::reset()
{
	burning = false;
	slowed = false;
	blinded = false;
}

void StatusComponent::render()
{
}

void StatusComponent::update(double dt)
{
	////timers for status
	if (blinded == true) {
		blindTimer -= dt;
		if (blindTimer <= 0)
		{
			blinded = false;
			blindTimer = 3.0f;
		}
	}
	if (burning == true) {
		burnTimer -= dt;
		if (burnTimer -= dt) {
			burning = false;
			burnTimer = 5.0f;
		}
	}
	if (slowed == true) {
		slowTimer -= dt;
		if (slowTimer < 0) {
			slowed = false;
			slowTimer = 2.0f;
		}
	}
}
