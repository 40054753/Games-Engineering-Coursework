#pragma once
#include "ecm.h"
#include "cmp_sprite.h"

class EnemyAttackComponent : public Component {

protected:
	int level=0;
	float cooldown = 0.3f;
public:
	explicit EnemyAttackComponent(Entity *p);
	EnemyAttackComponent() = delete;
	void setLevel(int x) { level = x; }
	void render() override;
	void update(double dt) override;

};

