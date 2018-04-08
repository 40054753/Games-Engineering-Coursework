#include "cmp_ai_steering.h"
#include "SystemRenderer.h"
#include "cmp_path_follow.h"
#include "astar.h"
#include <maths.h>
#include <levelsystem.h>

using namespace sf;
using namespace std;

SteeringComponent::SteeringComponent(Entity* p, Entity* player)
	: _player(player), _seek(Seek(p, player, 100.f)), Component(p) {}

void SteeringComponent::update(double dt)
{
	int randomTime = rand() % 100;
	const auto mva = (float)(dt * _speed);
	// If target (player) is within 300 pixels seek
	if (length(_parent->getPosition() - _player->getPosition()) < 300.0f)
	{
		auto ai = _parent->GetComponent<PathfindingComponent>();
		Vector2i movefrom(_parent->getPosition());
		Vector2i moveto(_player->getPosition());
		auto relative_pos = moveto;
		auto tile_coord = relative_pos / (int)ls::getTileSize();
		auto char_relative = _parent->getPosition() - ls::getOffset();
		auto char_tile = Vector2i(char_relative / ls::getTileSize());
		auto path = pathFind(char_tile, tile_coord);
		ai->setPath(path);

		auto output = _seek.getSteering();
		//move(output.direction * mva);
		double pi = 3.14159265359;
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