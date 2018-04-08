#pragma once
#include <ecm.h>
#include "steering.h"

class SteeringComponent : public Component
{
protected:
	float _speed;
	Seek _seek;
	Entity* _player;
	bool validMove(const sf::Vector2f&) const;

public:
	explicit SteeringComponent(Entity *p, Entity *player);
	void update(double) override;
	void move(const sf::Vector2f&);
	void move(float x, float y);
	void render() override {}
	SteeringComponent() = delete;
};