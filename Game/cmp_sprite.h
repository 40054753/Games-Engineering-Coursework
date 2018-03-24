#pragma once
#include "ecm.h"

class ShapeComponent : public Component {
protected:
	std::shared_ptr<sf::Shape> _shape;

public:
	ShapeComponent() = delete;
	explicit ShapeComponent(Entity *p);

	void update(double dt) override;
	void render() override;

	sf::Shape &getShape() const;

	template<typename T, typename... Targs>
	void setShape(Targs... params) {
		_shape.reset(new T(params...));
	}
};

class SpriteComponent : public Component {
protected:
	std::shared_ptr<sf::Sprite> _sprite;

public:
	SpriteComponent() = delete;
	explicit SpriteComponent(Entity *p);
	std::vector<sf::IntRect> walkingAnimationDown;
	std::vector<sf::IntRect> walkingAnimationUp;
	std::vector<sf::IntRect> walkingAnimationRight;
	std::vector<sf::IntRect> walkingAnimationLeft;
	void update(double dt) override;
	void render() override;
	int frame=0;
	sf::Sprite &getSprite() const;
	float AnimationDelay = 0.15f;
	template<typename T, typename... Targs>
	void setSprite(Targs... params) {
		_sprite.reset(new T(params...));
	}
};