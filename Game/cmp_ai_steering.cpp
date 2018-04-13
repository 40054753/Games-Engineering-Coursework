#include "cmp_ai_steering.h"
#include "cmp_status.h"
#include "SystemRenderer.h"
#include <maths.h>

using namespace sf;

SteeringComponent::SteeringComponent(Entity * p, Entity* player)
	: _player(player), _seek(Seek(p, player, 100.f)),
	_flee(Flee(p, player, 100.0f)), Component(p) {
	_speed = 80.0f;
}

void SteeringComponent::update(double dt)
{
	auto slowed = _parent->GetComponent<StatusComponent>();
	if (slowed->getSlowed()) {
		std::cout << "asdf";
		_speed = 40.0f;
	}
	else {
		_speed = 80.0f;
	}
	const auto mva = (float)(dt * _speed);
	// If target (player) is within 300 pixels seek
	if (length(_parent->getPosition() - _player->getPosition()) < 300.0f && length(_parent->getPosition() - _player->getPosition()) > 20.0f)
	{
		double pi = 3.14159265359;
		auto output = _seek.getSteering();
		move(output.direction * mva);

		Vector2f j(_parent->getPosition());
		Vector2f k(_player->getPosition());

		float angle = atan2f(k.y-j.y, k.x-j.x) * 180 / pi;


		if (angle >= 45 && angle < 135) {
			_parent->setFace(3);
		}
		if (angle >= 135 && angle <= 180 || angle >= -180 && angle < -135) {
			_parent->setFace(4);
		}
		if (angle >= -135 && angle < -45) {
			_parent->setFace(1);
		}
		if (angle >= -45 && angle < 45) {
			_parent->setFace(2);
		}
	}
}

bool SteeringComponent::validMove(const sf::Vector2f& pos) const
{
	if (pos.x < 0.0f || pos.y > Renderer::getWindow().getSize().x ||
		pos.y < 0.0f || pos.y > Renderer::getWindow().getSize().y)
	{
		return false;
	}
	return true;
}

void SteeringComponent::move(const Vector2f& p)
{
	auto new_pos = _parent->getPosition() + p;
	if (validMove(new_pos))
	{
		_parent->setPosition(new_pos);
	}
}

void SteeringComponent::move(float x, float y)
{
	move(Vector2f(x, y));
}