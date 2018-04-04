#include "cmp_actor_movement.h"
#include "levelsystem.h"

using namespace sf;
static const Vector2i directions[] = { Vector2i{ 0, 1 }, Vector2i{ 1, 0 }, Vector2i{ 0, -1 }, Vector2i{ -1, 0 } };
//ACTOR MOVEMENT
void ActorMovementComponent::render() {}

void ActorMovementComponent::update(double dt) {}

ActorMovementComponent::ActorMovementComponent(Entity *p) : _speed(100.0f), Component(p) {}

bool ActorMovementComponent::validMove(const sf::Vector2f &pos) {
	return (LevelSystem::getTileAt(pos) != LevelSystem::WALL);
}

void ActorMovementComponent::move(const Vector2f &p) {
	auto pp = _parent->getPosition() + p;
	if (validMove(pp)) {
		_parent->setPosition(pp);
	}
}

void ActorMovementComponent::move(float x, float y) {
	move(Vector2f(x, y));
}

float ActorMovementComponent::getSpeed() const {
	return _speed;
}

void ActorMovementComponent::setSpeed(float speed) {
	_speed = speed;
}

void ActorMovementComponent::increaseSpeed(float speed) {
	_speed += speed;
}

ProjectileMovementComponent::ProjectileMovementComponent(Entity *p) : ActorMovementComponent(p) { _speed = 200.0f; }
void ProjectileMovementComponent::render() {}

void ProjectileMovementComponent::update(double dt)
{//amount to move
	auto face = _parent->getFace();
	if (face==1) {
		move(Vector2f(0, -_speed * dt));
	}
	else if (face == 3) {
		move(Vector2f(0, _speed * dt));
	}
	else if (face == 4) {
		move(Vector2f(-_speed * dt, 0));
	}
	else if (face == 2) {
		move(Vector2f(_speed * dt, 0));
	}
}
void ProjectileMovementComponent::move(const Vector2f &p)
{
	auto pp = _parent->getPosition() + p;
	if (validMove(pp))
	{
		_parent->setPosition(pp);
	}
	else
		_parent->setForDelete();

}


//PLAYER MOVEMENT COMPONENT
PlayerMovementComponent::PlayerMovementComponent(Entity *p) : ActorMovementComponent(p) { _parent->setPlayer(); }

void PlayerMovementComponent::update(double dt) {
	if (!immobilized)
	{
		int xdir = 0, ydir = 0;
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			_parent->setFace(1);
			move(Vector2f(0, -_speed * dt));
		}
		else if (Keyboard::isKeyPressed(Keyboard::S)) {
			_parent->setFace(3);
			move(Vector2f(0, _speed * dt));
		}
		else if (Keyboard::isKeyPressed(Keyboard::A)) {
			_parent->setFace(4);
			move(Vector2f(-_speed * dt, 0));
		}
		else if (Keyboard::isKeyPressed(Keyboard::D)) {
			_parent->setFace(2);
			move(Vector2f(_speed * dt, 0));
		}

		ActorMovementComponent::update(dt);
	}
}

void PlayerMovementComponent::render() {
	ActorMovementComponent::render();
}


EnemyAIComponent::EnemyAIComponent(Entity * p) : ActorMovementComponent(p) {
	_state = ROAMING;
	_speed = 100.0f;
	_direction = Vector2f(directions[rand() % 4]);
}

//ENEMY COMPONENT
void EnemyAIComponent::update(double dt) {
	//amount to move
	const auto mva = (float)(dt * _speed);
	//current position
	const Vector2f pos = _parent->getPosition();
	//next pos
	const Vector2f newPos = pos + _direction * mva;
	//inverse of current pos
	const Vector2i badDir = -1 * Vector2i(_direction);
	//random new direction
	Vector2i newDir = directions[(rand() % 4)];

	switch (_state)
	{
	case EnemyAIComponent::ROAMING:
		if (ls::getTileAt(newPos) == ls::WALL || ls::getTileAt(pos) == ls::WAYPOINT) { //if wall in front or at waypoint
			_state = ROTATING; //start rotating
		}
		else {
			move(_direction * mva); //keep moving
		}
		break;
	case EnemyAIComponent::ROTATING:
		//don't reverse and don't pick a direction which leads to a wall
		//std::cout << badDir << ";" << _direction << std::endl;
		while (newDir == badDir || ls::getTileAt(pos + Vector2f(newDir) * mva) == ls::WALL) {
			newDir = directions[rand() % 4]; 		//pick a new direction
													//std::cout << "WHILE LOOP: " << _state << newDir << badDir << std::endl;
		}
		_direction = Vector2f(newDir);
		_state = ROTATED;
		break;
	case EnemyAIComponent::ROTATED:
		//has it left the waypoint?
		if (ls::getTileAt(newPos) != ls::WAYPOINT) {
			_state = ROAMING; //yes, roam
		}
		move(_direction * mva); //No
		break;
	default:
		break;
	}
	//////////////SET DIRECTION PARENT IS FACING//////////////////////
	if (_direction.x == 0 && _direction.y < 0)
		_parent->setFace(1);
	else if (_direction.x > 0 && _direction.y == 0)
		_parent->setFace(2);
	else if (_direction.x == 0 && _direction.y > 0)
		_parent->setFace(3);
	else if (_direction.x < 0 && _direction.y == 0)
		_parent->setFace(4);

	ActorMovementComponent::update(dt);
}

void EnemyAIComponent::render() {
	ActorMovementComponent::render();
}