#include "steering.h"
#include "cmp_path_follow.h"

using	namespace sf;

SteeringOutput Seek::getSteering() const noexcept
{
	SteeringOutput steering;
	steering.direction = _target->getPosition() - _character->getPosition();
	steering.direction = normalize(steering.direction);
	steering.rotation = 0.0f;
	return steering;
}