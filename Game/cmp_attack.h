#pragma once
#include "ecm.h"
#include "cmp_sprite.h"

class AttackComponent : public Component {

protected:
	float cooldown = 0.3f;
	sf::Texture texture;
	std::vector <std::shared_ptr<Entity>> _entities;
	float textTime = 0.0f;
public:
	explicit AttackComponent(Entity *p);
	AttackComponent() = delete;
	sf::Text damageText;
	std::vector<sf::Text> damageArray;
	void render() override;
	void update(double dt) override;
	void setEntities(std::vector<std::shared_ptr<Entity>>& e);

	template<typename T, typename... Targs>
	void setShape(Targs... params) {
		_shape.reset(new T(params...));
	}
};

