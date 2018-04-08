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

class CharacterSpriteComponent : public Component {
protected:
	std::shared_ptr<sf::Sprite> _sprite;

public:
	CharacterSpriteComponent() = delete;
	explicit CharacterSpriteComponent(Entity *p);
	std::vector<sf::IntRect> walkingAnimationDown;
	std::vector<sf::IntRect> walkingAnimationUp;
	std::vector<sf::IntRect> walkingAnimationRight;
	std::vector<sf::IntRect> walkingAnimationLeft;
	void update(double dt) override;
	void setScale();
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
class DamageTextComponent : public Component {
protected:
	sf::Text damageText;
	std::vector<sf::Text> damageArray;
	float textTime = 0.4f;
public:
	void setScale();
	DamageTextComponent() = delete;
	explicit DamageTextComponent(Entity *p);
	void setText(int x);
	void update(double dt) override;
	void render() override;

};
class EnemyHealthBarComponent : public Component {
protected:
	sf::RectangleShape hp;
public:
	void setScale();
	EnemyHealthBarComponent() = delete;
	explicit EnemyHealthBarComponent(Entity *p);
	void update(double dt) override;
	void render() override;

};
class StaticSpriteComponent : public Component {
protected:
	bool spin = false;
	std::shared_ptr<sf::Sprite> _sprite;

public:
	void setScale();
	void addSpin() { spin = true; }
	StaticSpriteComponent() = delete;
	explicit StaticSpriteComponent(Entity *p);
	void update(double dt) override;
	void render() override;
	sf::Sprite &getSprite() const;
	template<typename T, typename... Targs>
	void setSprite(Targs... params) {
		_sprite.reset(new T(params...));
	}
};