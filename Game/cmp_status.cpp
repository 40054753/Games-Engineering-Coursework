#include "cmp_status.h"

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
		std::cout << "doing this";
		blindTimer -= dt;
		if (blindTimer <= 0)
		{
			blinded = false;
			blindTimer = 3.0f;
		}
	}
}
