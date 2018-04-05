#include "cmp_ai_steering.h"
#include "SystemRenderer.h"

using namespace sf;

SteeringComponent::SteeringComponent(Entity * p, Entity* player)
	: _player(player), _seek(Seek(p, player, 100.f)),
	_flee(Flee(p, player, 100.0f)), Component(p) {
	_speed = 80.0f;
}

void SteeringComponent::update(double dt)
{
	const auto mva = (float)(dt * _speed);
	// If target (player) is more than 100 pixels away seek
	if (length(_parent->getPosition() - _player->getPosition()) < 300.0f)
	{
		auto output = _seek.getSteering();
		move(output.direction * mva);
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