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
	int frame=0; //Current frame of player/npc animation (goes from 0 to 3)
	int facing; //direction player/npc is facing 1 - north, then clockwise (1-4)
	sf::Sprite &getSprite() const;
	const float AnimationDelay = 0.15f; //delay between frames of animation
	float AnimationCounter = 0.15f; //used as a count-down between frames, then set to AnimationDelay when frame changes
	template<typename T, typename... Targs>
	void setSprite(Targs... params) {
		_sprite.reset(new T(params...));
	}
};