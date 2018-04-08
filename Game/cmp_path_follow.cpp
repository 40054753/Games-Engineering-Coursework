#include "cmp_path_follow.h"
#include <levelsystem.h>

using namespace sf;

void PathfindingComponent::update(double dt) {
	_elapsed += dt;
	float speed = 80;
	const auto mva = (float)(dt * speed);
	if (_elapsed > 0.1) {
		_elapsed = 0.0;
		if (_index < _path.size()) {
			float new_x = ls::getOffset().x + _path[_index].x * ls::getTileSize();
			float new_y = ls::getOffset().y + _path[_index].y * ls::getTileSize();
			_parent->setPosition(Vector2f(new_x, new_y));
			++_index;
		}
	}
}

PathfindingComponent::PathfindingComponent(Entity* p) : Component(p) {}

void PathfindingComponent::setPath(std::vector<sf::Vector2i>& path) {
	_index = 0;
	_path = path;
	_pathset = true;
}

int PathfindingComponent::getNextIndexX()
{
	if (_index < _path.size()) {
		float new_x = ls::getOffset().x + _path[_index].x * ls::getTileSize();
		std::cout << "asdfasdf";
		return new_x;
	}
	else {
		std::cout << "asdfasdf";
		return 0;
	}
}

int PathfindingComponent::getNextIndexY() 
{
	if (_index < _path.size()) {
		float new_y = ls::getOffset().y + _path[_index].y * ls::getTileSize();
		std::cout << new_y;
		return new_y;
	}
	else {
		return 0;
	}
}
