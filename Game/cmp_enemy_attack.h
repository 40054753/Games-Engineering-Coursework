#pragma once
#include "ecm.h"
#include "cmp_sprite.h"

class EnemyAttackComponent : public Component {

protected:
	float cooldown = 0.3f;
	std::shared_ptr<Entity> _player;
public:
	explicit EnemyAttackComponent(Entity *p);
	EnemyAttackComponent() = delete;
	void render() override;
	void update(double dt) override;
	void setPlayer(std::shared_ptr<Entity>& e);

};

